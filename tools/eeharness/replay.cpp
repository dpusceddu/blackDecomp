#include "replay.hpp"
#include "event_journal.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace ee {
namespace {
struct Writer {
    std::ostream& stream;
    template<class T> void operator()(T raw) {
        const auto value=static_cast<uint64_t>(raw);
        for (unsigned i=0;i<8;++i) stream.put(char(value>>(i*8)));
        if (!stream) throw Fault("cannot write replay state");
    }
};
struct Reader {
    std::istream& stream;
    template<class T> void operator()(T& value) {
        uint64_t bits=0;
        for (unsigned i=0;i<8;++i) {
            const int b=stream.get();
            if (b<0) throw Fault("truncated replay state");
            bits |= uint64_t(b)<<(i*8);
        }
        value=static_cast<T>(bits);
    }
};
template<class Codec, class S> void state_fields(Codec& c, S& s) {
    const auto quad=[&](auto& q) { for (auto& w:q.w) c(w); };
    for (auto& q:s.gpr) quad(q);
    quad(s.hi); quad(s.lo);
    for (auto& bank:{&s.cop0,&s.fpr,&s.fcr,&s.vi}) for (auto& w:*bank) c(w);
    for (auto& q:s.vf) quad(q);
    quad(s.vacc); c(s.facc);c(s.pc);c(s.next_pc);c(s.sa);c(s.facc_overflow);c(s.vu_micro_running);
    auto& v=s.vu;
    c(v.cycle);c(v.issued);c(v.pc);c(v.next_pc);c(v.clip_history);c(v.end_delay);c(v.debug_delay);
    c(v.m_seen);c(v.stopped);c(v.debug_bits);
    for (auto& q:v.vector_ready) for(auto& w:q)c(w);
    for (auto& w:v.integer_ready)c(w);
    for (auto& w:v.branch_ready)c(w);
    for (auto& w:v.branch_previous)c(w);
    for (auto& w:v.accumulator_overflow)c(w);
    uint64_t count=v.pending.size();c(count);
    if(count>1024)throw Fault("invalid replay VU pipeline size");
    if constexpr (!std::is_const_v<S>) v.pending.resize(count);
    for(auto& w:v.pending){c(w.kind);c(w.ready);c(w.reg);c(w.mask);quad(w.value);c(w.flags);c(w.sticky);c(w.macro);}
    for(auto& t:s.tlb){c(t.page_mask);c(t.entry_hi);for(auto& w:t.entry_lo)c(w);c(t.initialized);}
    c(s.mmu_enabled);c(s.delay_slot);c(s.pending_call);c(s.call_target);c(s.call_site);c(s.instructions);c(s.ee_cycle);
    c(s.next_vblank);count=s.replay_interrupts.size();c(count);
    if(count>1024)throw Fault("invalid replay interrupt queue");
    if constexpr (!std::is_const_v<S>) s.replay_interrupts.resize(count);
    for(auto& irq:s.replay_interrupts){c(irq.ready);c(irq.handler);c(irq.argument);}
}
uint32_t u32(std::istream& in) {
    uint32_t v=0;
    for(unsigned i=0;i<4;++i){const int b=in.get();if(b<0)throw Fault("truncated snapshot bridge");v|=uint32_t(b)<<(i*8);}
    return v;
}
uint64_t u64(std::istream& in) {const uint64_t lo=u32(in);return lo|(uint64_t(u32(in))<<32);}
std::vector<uint8_t> block(std::istream& in,size_t size) {
    std::vector<uint8_t> bytes(size);in.read(reinterpret_cast<char*>(bytes.data()),std::streamsize(size));
    if(!in)throw Fault("truncated snapshot memory");return bytes;
}
}
void save_state(std::ostream& out,const State& state){Writer w{out};state_fields(w,state);}
State restore_state(std::istream& in){State s;Reader r{in};state_fields(r,s);return s;}
void save_entry(std::ostream& out,Machine& m,uint32_t address,uint64_t ordinal) {
    Writer w{out};w(address);w(ordinal);save_state(out,m.state);
    w(m.trace.writes.size());
    for(const auto [a,b]:m.trace.writes){w(a);w(b);}
    w(m.memory.hardware_updates.size());
    for(const auto& [key,v]:m.memory.hardware_updates){w(key.first);w(key.second);w(v);}
    m.trace.writes.clear();m.memory.hardware_updates.clear();
}
bool restore_entry(std::istream& in,Machine& m,uint32_t& address,uint64_t& ordinal) {
    if(in.peek()==std::char_traits<char>::eof())return false;
    Reader r{in};r(address);r(ordinal);m.state=restore_state(in);
    uint64_t size=0;r(size);if(size>Memory::ram_size+Memory::scratch_size+2*Memory::vu_size)throw Fault("invalid memory delta size");
    for(uint64_t i=0;i<size;++i){uint32_t a=0;uint8_t b=0;r(a);r(b);m.memory.write_physical(a,1,b);}
    r(size);if(size>1000000)throw Fault("invalid hardware delta size");
    for(uint64_t i=0;i<size;++i){uint32_t a=0,width=0;uint64_t value=0;r(a);r(width);r(value);m.memory.hardware_responses[{a,width}]=value;}
    m.trace={};return true;
}
Machine import_snapshot(std::istream& in) {
    if(block(in,8)!=std::vector<uint8_t>({'E','E','S','N','A','P','0','1'}))throw Fault("invalid snapshot bridge");
    Machine m;auto& s=m.state;
    const auto quad=[&](Quad& q){for(auto& w:q.w)w=u32(in);};
    for(auto& q:s.gpr)quad(q);quad(s.hi);quad(s.lo);
    for(auto* b:{&s.cop0,&s.fpr,&s.fcr})for(auto& w:*b)w=u32(in);
    for(auto& q:s.vf)quad(q);
    for(auto& w:s.vi)w=u32(in);
    quad(s.vacc);s.facc=u32(in);s.start(u32(in));s.sa=u32(in);s.ee_cycle=u64(in);
    s.vu.cycle=s.ee_cycle;s.vu.clip_history=s.vi[18];s.mmu_enabled=true;
    // PCSX2 saves a non-ticking Random slot (zero in the supplied state).
    // Seed this hardware-only clock register within Wired..47, and expose the
    // substitution as a stub event rather than changing gameplay RAM.
    if((s.cop0[1]&63)<(s.cop0[6]&63) || (s.cop0[1]&63)>47){
        s.cop0[1]=47;Event e{EventKind::cop0_read,s.pc,1};e.default_response=true;e.bytes={47,0,0,0};m.trace.events.push_back(e);
    }
    for(auto& t:s.tlb){t.page_mask=u32(in);t.entry_hi=u32(in);for(auto& w:t.entry_lo)w=u32(in);t.initialized=true;}
    for(const auto [address,size]:{std::pair{0u,Memory::ram_size},std::pair{0x70000000u,Memory::scratch_size},
                                  std::pair{0x11004000u,Memory::vu_size},std::pair{0x11000000u,Memory::vu_size}})
        m.memory.load(address,block(in,size));
    const auto hw=block(in,65536);
    for(unsigned width:{1u,2u,4u,8u})for(uint32_t off=0;off+width<=hw.size();off+=width){
        uint64_t value=0;for(unsigned i=0;i<width;++i)value|=uint64_t(hw[off+i])<<(i*8);
        m.memory.hardware_responses[{0x10000000+off,width}]=value;
    }
    if(in.peek()!=std::char_traits<char>::eof())throw Fault("trailing snapshot bridge data");
    return m;
}

// Black's registered EE handlers are recovered from 0x2b4780. This profile
// delivers output-DMA completion and NTSC vblank stubs to the original handlers;
// gameplay RAM changes only through guest instructions. It is not a GS/VU1 or
// kernel scheduler implementation, and has no hardware-accuracy claim.
namespace {
constexpr uint64_t vblank_period=294912000/60;
thread_local EventJournal* capture_events=nullptr;
void replay_step(Machine& m) {
    const size_t first=m.trace.events.size();m.step();
    for(size_t i=first;i<m.trace.events.size();++i){const auto& e=m.trace.events[i];
        if(e.kind!=EventKind::hardware_write || e.bytes.size()!=4 ||
           (e.address!=0x10009000 && e.address!=0x1000a000))continue;
        const uint32_t value=uint32_t(e.bytes[0])|(uint32_t(e.bytes[1])<<8);
        if((value&0x100) && m.state.next_vblank)m.state.replay_interrupts.push_back({m.state.ee_cycle+256,0x2b2638,e.address==0x10009000?1u:2u});
    }
}
Result replay_run(Machine& m,uint64_t budget,uint32_t return_pc=0xffffffff,bool interrupts=true) {
    const uint64_t initial=m.state.instructions;
    Result result;
    try{
        while(m.state.instructions-initial<budget){
            if(m.state.pc==return_pc && !m.state.delay_slot){result.stop=Stop::returned;break;}
            if(interrupts && m.state.next_vblank && m.state.ee_cycle>=m.state.next_vblank){
                m.state.replay_interrupts.push_back({m.state.ee_cycle,0x2b2ba8,2});
                m.state.next_vblank=m.state.ee_cycle+vblank_period;
            }
            const uint32_t status=m.state.cop0[12];
            if(interrupts && !m.state.delay_slot && (status&0x10001)==0x10001 && !(status&6)){
                auto& pending=m.state.replay_interrupts;
                const auto found=std::find_if(pending.begin(),pending.end(),[&](const auto& irq){return irq.ready<=m.state.ee_cycle;});
                if(found!=pending.end()){
                    const auto irq=*found;pending.erase(found);const auto interrupted=m.state;
                    Event event{EventKind::interrupt,m.state.pc,irq.handler};event.default_response=true;
                    event.bytes={uint8_t(irq.argument)};m.trace.events.push_back(event);
                    m.state.start(irq.handler);m.state.gpr[4].low(irq.argument);m.state.gpr[31].low(uint64_t(int64_t(-4)));
                    m.state.cop0[12]|=2; // kernel exception context; callbacks cannot nest here
                    const auto handled=replay_run(m,std::min(uint64_t(100000),budget-(m.state.instructions-initial)),0xfffffffc,false);
                    if(handled.stop!=Stop::returned)throw Fault("external callback did not return: "+handled.error);
                    const auto after=m.state;m.state=interrupted;
                    m.state.ee_cycle=after.ee_cycle;m.state.instructions=after.instructions;
                    m.state.cop0[9]=after.cop0[9];m.state.cop0[1]=after.cop0[1];
                    m.state.vu=after.vu;m.state.vu_micro_running=after.vu_micro_running;
                    m.state.vf=after.vf;m.state.vi=after.vi;m.state.vacc=after.vacc;
                    m.state.replay_interrupts=after.replay_interrupts;
                    continue;
                }
            }
            replay_step(m);
            if(capture_events)capture_events->drain(m.trace);
        }
    }catch(const Fault& error){result.stop=Stop::fault;result.error=error.what();}
    result.executed=m.state.instructions-initial;m.outcome=result;return result;
}
}

Result run_replay(Machine& m,uint64_t budget,uint32_t return_pc) {
    return replay_run(m,budget,return_pc);
}

void replay_main(int argc,char** argv) {
    const std::string command=argv[1];
    if(command=="replay-fuzz"){
        if(argc!=6)throw Fault("usage: eeharness replay-fuzz SNAPSHOT CORPUS PATCHLIST BUDGET");
        std::ifstream input(argv[2],std::ios::binary);auto m=import_snapshot(input);m.memory.scratch_dma=true;
        std::ifstream corpus(argv[3],std::ios::binary),patches(argv[4]);
        if(block(corpus,8)!=std::vector<uint8_t>({'E','E','C','A','P','0','0','1'}))throw Fault("invalid capture format");
        uint64_t index=0,wanted=0,ordinal=0,before=0,after=0;uint32_t function=0,address=0,width=0;
        bool loaded=false,first=true;std::cout<<'[';
        while(patches>>wanted>>std::hex>>address>>before>>after>>std::dec>>width){
            if(loaded && wanted<index)throw Fault("fuzz patches must be in corpus order");
            while(!loaded || index<wanted){if(!restore_entry(corpus,m,function,ordinal))throw Fault("fuzz entry outside corpus");
                if(loaded)++index;loaded=true;}
            if(!function || (width!=1 && width!=2 && width!=4))throw Fault("invalid fuzz input");
            auto variant=m;const uint32_t physical=variant.translate(address,Machine::Access::write);
            if(physical>=Memory::ram_size || variant.memory.read_physical(physical,width)!=before)throw Fault("fuzz preimage differs from recorded state");
            variant.memory.write_physical(physical,width,after);
            const auto result=replay_run(variant,std::stoull(argv[5]),variant.state.gpr[31].w[0]);
            if(!first)std::cout<<',';first=false;
            std::cout<<"{\"index\":"<<index<<",\"function\":"<<function<<",\"executed\":"<<result.executed
                     <<",\"stop\":"<<int(result.stop)<<",\"error\":"<<std::quoted(result.error)<<'}';
        }
        if(!patches.eof())throw Fault("invalid fuzz patch list");std::cout<<"]\n";return;
    }
    if(command=="replay-entry"){
        if(argc!=6)throw Fault("usage: eeharness replay-entry SNAPSHOT CORPUS INDEX BUDGET");
        std::ifstream input(argv[2],std::ios::binary);auto m=import_snapshot(input);m.memory.scratch_dma=true;
        std::ifstream corpus(argv[3],std::ios::binary);uint32_t address=0;uint64_t ordinal=0;
        if(block(corpus,8)!=std::vector<uint8_t>({'E','E','C','A','P','0','0','1'}))throw Fault("invalid capture format");
        const uint64_t index=std::stoull(argv[4]);
        for(uint64_t i=0;i<=index;++i)if(!restore_entry(corpus,m,address,ordinal))throw Fault("entry index outside corpus");
        auto other=m;const auto result=replay_run(m,std::stoull(argv[5]),m.state.gpr[31].w[0]);
        const auto repeated=replay_run(other,std::stoull(argv[5]),other.state.gpr[31].w[0]);
        if(!(m.state==other.state) || !(m.trace==other.trace) || result.stop!=repeated.stop || result.error!=repeated.error)
            throw Fault("entry replay is not repeatable");
        std::cout<<"{\"address\":"<<address<<",\"ordinal\":"<<ordinal<<",\"executed\":"<<result.executed
                 <<",\"stop\":"<<int(result.stop)<<",\"error\":"<<std::quoted(result.error)<<",\"repeatable\":true}\n";return;
    }
    if(argc!=5 && argc!=7 && argc!=9 && argc!=10)throw Fault("usage: eeharness replay SNAPSHOT FUNCTIONS BUDGET [ENTRY A0 [ITERATIONS CORPUS [STACK]]]");
    std::ifstream input(argv[2],std::ios::binary);auto m=import_snapshot(input);
    m.memory.scratch_dma=true;
    // Isolated per-frame update roots retain output-only hardware as passive
    // stubs. Full dispatcher/resume runs also exercise renderer callbacks.
    if(argc<7 || std::stoul(argv[5],nullptr,0)==0x102bd0)
        m.state.next_vblank=m.state.ee_cycle+vblank_period;
    std::ifstream functions(argv[3]);uint32_t address;
    std::map<uint32_t,uint64_t> counts;
    while(functions>>std::hex>>address){m.capture_entries.insert(address);counts[address]=0;}
    std::ofstream corpus;
    if(argc>=9){corpus.open(argv[8],std::ios::binary);if(!corpus)throw Fault("cannot create capture corpus");corpus.write("EECAP001",8);}
    std::unique_ptr<EventJournal> journal;
    if(corpus.is_open()){journal=std::make_unique<EventJournal>(std::string(argv[8])+".events.gz");capture_events=journal.get();}
    uint64_t stored=0;
    m.on_entry=[&](uint32_t a,const State&,const Memory&){
        const auto count=++counts[a];
        if(corpus.is_open() && count<=20){save_entry(corpus,m,a,count);++stored;}
    };
    Result result;
    uint64_t completed=0,executed=0;
    if(argc>=7){
        const auto iterations=argc>=9?std::stoull(argv[7]):1;
        for(uint64_t i=0;i<iterations;++i){
            m.state.gpr[4].low(std::stoul(argv[6],nullptr,0));m.state.start(std::stoul(argv[5],nullptr,0));
            if(argc==10)m.state.gpr[29].low(std::stoul(argv[9],nullptr,0));
            m.state.gpr[31].low(uint64_t(int64_t(-4)));
            m.state.pending_call=true;m.state.call_target=m.state.pc;m.state.call_site=0xfffffffc;
            result=replay_run(m,std::stoull(argv[4]),0xfffffffc);executed+=result.executed;
            if(result.stop!=Stop::returned)break;
            ++completed;
        }
    }else{result=replay_run(m,std::stoull(argv[4]));executed=result.executed;}
    if(corpus.is_open()){
        save_entry(corpus,m,0,0); // terminal checkpoint, never a function input
        corpus.flush();if(!corpus)throw Fault("cannot finish capture corpus");
    }
    uint64_t event_records=0;
    if(journal){journal->drain(m.trace,true);event_records=journal->records();capture_events=nullptr;}
    std::cout<<"{\"executed\":"<<executed<<",\"iterations_completed\":"<<completed<<",\"stored\":"<<stored<<",\"pc\":"<<m.state.pc<<",\"stop\":"<<int(result.stop)
             <<",\"error\":"<<std::quoted(result.error)<<",\"event_records\":"<<event_records<<",\"bad_address\":"<<m.state.cop0[8]<<",\"unique_pcs\":"<<m.trace.instructions.size()<<",\"entries\":{";
    bool first=true;for(const auto& [a,n]:counts)if(n){if(!first)std::cout<<',';first=false;std::cout<<std::quoted(std::to_string(a))<<':'<<n;}
    std::cout<<"},\"recent_calls\":[";first=true;
    const size_t begin=m.trace.events.size()>40?m.trace.events.size()-40:0;
    for(size_t i=begin;i<m.trace.events.size();++i){const auto& e=m.trace.events[i];if(!first)std::cout<<',';first=false;
        std::cout<<'['<<int(e.kind)<<','<<e.pc<<','<<e.address;
        for(auto b:e.bytes)std::cout<<','<<unsigned(b);
        std::cout<<']';}
    std::cout<<"]}\n";
}
}
