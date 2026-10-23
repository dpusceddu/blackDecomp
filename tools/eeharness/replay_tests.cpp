#include "replay.hpp"
#include "event_journal.hpp"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace {
void require(bool condition,const char* error){if(!condition)throw ee::Fault(error);}
void state_codec(){
    ee::State state;
    state.gpr[31].w={0x12345678,0x9abcdef0,0x13579bdf,0x2468ace0};
    state.next_pc=0x1020;state.delay_slot=true;state.pending_call=true;state.mmu_enabled=true;
    state.facc_overflow=true;state.vu_micro_running=true;state.vu.accumulator_overflow[2]=true;
    state.vu.pending.push_back({ee::VuWriteKind::vector,123,17,13,{{1,2,3,4}},0x88,0x123,true});
    state.vu.pending.push_back({ee::VuWriteKind::quotient,127,22,0,{{0x3f800000,0,0,0}},0x40,0x80,false});
    state.replay_interrupts.push_back({99999,0x100000,2});state.next_vblank=123456;
    state.tlb[47]={0x7fe000,0x800000,{0x10001f,0x20001f},true};
    std::stringstream stream(std::ios::in|std::ios::out|std::ios::binary);ee::save_state(stream,state);
    const auto restored=ee::restore_state(stream);
    require(state==restored,"register/pending-pipeline replay codec lost state");
    std::stringstream truncated(stream.str().substr(0,stream.str().size()-1));bool failed=false;
    try{(void)ee::restore_state(truncated);}catch(const ee::Fault&){failed=true;}
    require(failed,"truncated replay must fail");
}
void capture_codec(){
    ee::Machine original,restored;
    original.memory.scratch_dma=true;restored.memory.scratch_dma=true;
    std::stringstream stream(std::ios::in|std::ios::out|std::ios::binary);
    original.memory.write(0x1fff,4,0x89abcdef,&original.trace);
    original.memory.write(0x70000000,4,0x11223344,&original.trace);
    original.memory.write(0x11000000,4,0xaabbccdd,&original.trace);
    original.state.start(0x101000);ee::save_entry(stream,original,0x101000,1);
    original.memory.write(0x1000d410,4,0x1ff0,&original.trace);
    original.memory.write(0x1000d480,4,0x100,&original.trace);
    original.memory.write(0x1000d420,4,2,&original.trace);
    original.memory.write(0x1000d400,4,0x100,&original.trace);
    original.state.pc=0x102000;ee::save_entry(stream,original,0x102000,2);
    uint32_t address=0;uint64_t ordinal=0;
    require(ee::restore_entry(stream,restored,address,ordinal) && address==0x101000 && ordinal==1,"first entry metadata");
    require(restored.memory.read(0x1fff,4)==0x89abcdef && restored.memory.read(0x70000000,4)==0x11223344,"entry memory delta across pages");
    require(restored.memory.read(0x11000000,4)==0xaabbccdd,"entry VU microcode delta");
    require(ee::restore_entry(stream,restored,address,ordinal) && ordinal==2 && restored.state==original.state,"second entry state");
    require(restored.memory.bytes(0x70000100,32)==original.memory.bytes(0x1ff0,32),"DMA writes retained by capture");
    require(restored.memory.hardware_responses==original.memory.hardware_responses,"hardware response deltas retained");
    require(!ee::restore_entry(stream,restored,address,ordinal),"clean corpus EOF");
}
void local_dma(){
    ee::Memory m;ee::Trace trace;m.scratch_dma=true;
    for(unsigned i=0;i<8;++i)m.write(0x2000+i*16,4,0x100+i);
    m.write(0x1000e030,4,0x00020001,&trace); // transfer two, skip one
    m.write(0x1000d410,4,0x2000,&trace);m.write(0x1000d480,4,0x3ff0,&trace);m.write(0x1000d420,4,4,&trace);
    m.write(0x1000d400,4,0x108,&trace);
    require(m.read(0x70003ff0,4)==0x100 && m.read(0x70000000,4)==0x101 &&
            m.read(0x70000010,4)==0x103 && m.read(0x70000020,4)==0x104,"interleave copy and scratchpad wrap");
    require(m.read(0x1000d400,4)==8 && m.read(0x1000d420,4)==0,"DMA completion clears start and remaining count");
    m.write(0x1000d010,4,0x3000,&trace);m.write(0x1000d080,4,0x3ff0,&trace);m.write(0x1000d020,4,2,&trace);m.write(0x1000d000,4,0x100,&trace);
    require(m.read(0x3000,4)==0x100 && m.read(0x3010,4)==0x101,"scratchpad-to-RAM copies real payload");
    require(!trace.events.empty() && trace.writes.contains(0x3000),"DMA external commands and memory writes recorded");
    bool failed=false;try{m.write(0x1000d400,4,0x104);}catch(const ee::Fault&){failed=true;}
    require(failed,"unsupported DMA chain must fail closed");
}
void ordered_events(){
    const auto path=std::filesystem::temp_directory_path()/
        ("ee-events-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".gz");
    ee::Trace trace;ee::EventJournal journal(path.string());
    for(uint32_t n=0;n<5000;++n){
        ee::Event event{ee::EventKind::call,n,0x100000+n};event.bytes={uint8_t(n),uint8_t(n>>8)};
        event.arguments[7].w[3]=n^0x12345678;event.float_arguments[7]=n;event.default_response=n&1;
        trace.events.push_back(event);journal.drain(trace);
    }
    journal.drain(trace,true);
    require(journal.records()==5000 && trace.events.size()==64,"event streaming retains every record and bounded diagnostics");
    gzFile input=gzopen(path.string().c_str(),"rb");require(input!=nullptr,"event journal read");
    std::vector<uint8_t> data;std::array<uint8_t,8192> block{};int count;
    while((count=gzread(input,block.data(),unsigned(block.size())))>0)data.insert(data.end(),block.begin(),block.begin()+count);
    require(count==0 && gzclose(input)==Z_OK,"event gzip integrity");std::filesystem::remove(path);
    require(data.size()==8+5000*182 && std::string(data.begin(),data.begin()+8)=="EEEVT001","event file schema and record count");
    const auto u32=[&](size_t at){return uint32_t(data.at(at))|(uint32_t(data.at(at+1))<<8)|(uint32_t(data.at(at+2))<<16)|(uint32_t(data.at(at+3))<<24);};
    for(uint32_t n=0;n<5000;++n){const size_t at=8+n*182;
        require(u32(at)==uint32_t(ee::EventKind::call) && u32(at+4)==n && u32(at+8)==0x100000+n && u32(at+12)==2 && u32(at+16)==(n&1),"ordered event metadata");
        require(data[at+20]==uint8_t(n) && data[at+21]==uint8_t(n>>8) && u32(at+146)==(n^0x12345678) && u32(at+178)==n,"ordered event payload and full argument banks");
    }
}
void function_entries(){
    ee::Machine m;m.capture_entries={0x1000,0x1100};unsigned root=0,tail=0;
    m.on_entry=[&](uint32_t address,const ee::State&,const ee::Memory&){if(address==0x1000)++root;else ++tail;};
    // Increment a0 three times, looping back to the entry word, then return.
    for(auto [address,word]:{std::pair{0x1000u,0x24840001u},std::pair{0x1004u,0x28880003u},
                            std::pair{0x1008u,0x1500fffdu},std::pair{0x100cu,0u},
                            std::pair{0x1010u,0x03e00008u},std::pair{0x1014u,0u}})m.memory.write(address,4,word);
    require(m.call(0x1000,100).stop==ee::Stop::returned && root==1 && m.state.gpr[4].w[0]==3,"entry loop visits must not inflate captured call counts");
    m.memory.write(0x1000,4,0x08000440);m.memory.write(0x1004,4,0);
    m.memory.write(0x1100,4,0x03e00008);m.memory.write(0x1104,4,0);
    require(m.call(0x1000,100).stop==ee::Stop::returned && root==2 && tail==1,"cross-function tail entry remains captured");
}
}
int main(){try{state_codec();capture_codec();local_dma();ordered_events();function_entries();std::cout<<"OK replay state, memory journal, DMA, ordered event and function entry checks\n";return 0;}
catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
