#include "differential.hpp"
#include "replay.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>

namespace ee {
namespace {
std::string hex(uint32_t value){std::ostringstream s;s<<"0x"<<std::hex<<value;return s.str();}
bool stack_byte(const Machine& m,uint32_t address,uint32_t top) {
    return m.minimum_stack<=top && top-m.minimum_stack<=65536 && address>=m.minimum_stack && address<top;
}
uint32_t word(const std::vector<uint8_t>& bytes,size_t at) {
    if(at+4>bytes.size())throw Fault("truncated candidate ELF");
    return uint32_t(bytes[at])|(uint32_t(bytes[at+1])<<8)|(uint32_t(bytes[at+2])<<16)|(uint32_t(bytes[at+3])<<24);
}
uint32_t half(const std::vector<uint8_t>& bytes,size_t at){return word(bytes,at)&65535;}
std::map<uint32_t,std::vector<uint8_t>> candidate_image(const std::string& path) {
    std::ifstream input(path,std::ios::binary);
    const std::vector<uint8_t> bytes{std::istreambuf_iterator<char>(input),std::istreambuf_iterator<char>()};
    if(bytes.size()<52 || word(bytes,0)!=0x464c457f || bytes[4]!=1 || bytes[5]!=1 || half(bytes,18)!=8 || half(bytes,16)!=2)
        throw Fault("candidate is not a linked little-endian MIPS ELF32");
    std::map<uint32_t,std::vector<uint8_t>> image;
    const uint32_t offset=word(bytes,32),size=half(bytes,46),count=half(bytes,48);
    if(size!=40 || uint64_t(offset)+uint64_t(size)*count>bytes.size())throw Fault("invalid candidate section table");
    for(unsigned i=0;i<count;++i){const size_t at=offset+i*size;
        const uint32_t flags=word(bytes,at+8),address=word(bytes,at+12),file=word(bytes,at+16),length=word(bytes,at+20);
        if(!(flags&2) || !length)continue;
        if((flags&1) || word(bytes,at+4)!=1 || address<0x08000000 || uint64_t(address)+length>0x09000000 || uint64_t(file)+length>bytes.size())
            throw Fault("candidate must contain only immutable pilot sections in 0x08000000..0x09000000");
        for(const auto& [base,data]:image)if(address<uint64_t(base)+data.size() && base<uint64_t(address)+length)throw Fault("overlapping candidate sections");
        image[address]={bytes.begin()+file,bytes.begin()+file+length};
    }
    if(image.empty())throw Fault("empty candidate image");return image;
}
struct Pilot {
    FunctionContract contract;
    std::map<uint32_t,std::vector<uint8_t>> image;
    uint64_t recorded=0,fuzzed=0,passed=0,failed=0,instructions=0;
    std::string first_error;
    uint64_t first_index=0;
    std::set<uint32_t> pcs;
    std::set<std::pair<uint32_t,uint32_t>> edges;
};
void exercise(const Machine& input,Pilot& pilot,uint64_t index,uint64_t budget,bool fuzzed) {
    auto original=input,candidate=input;
    original.trace={};candidate.trace={};original.on_entry={};candidate.on_entry={};
    const uint32_t stack=input.state.gpr[29].w[0],return_pc=input.state.gpr[31].w[0];
    original.minimum_stack=stack;candidate.minimum_stack=stack;
    candidate.memory.candidate_regions=pilot.image;
    candidate.state.start(pilot.contract.candidate);
    // The captured state is at entry, after the caller's delay slot and call
    // event. No synthetic call or replacement of the caller's return address.
    original.state.pending_call=false;
    run_replay(original,budget,return_pc);run_replay(candidate,budget,return_pc);
    const auto error=observable_difference(original,candidate,pilot.contract,stack);
    if(fuzzed)++pilot.fuzzed;else ++pilot.recorded;
    if(error.empty())++pilot.passed;else {++pilot.failed;if(pilot.first_error.empty()){pilot.first_error=error;pilot.first_index=index;}}
    pilot.instructions+=original.outcome.executed;
    for(auto pc:original.trace.instructions)if(pc>=pilot.contract.original && pc<pilot.contract.end)pilot.pcs.insert(pc);
    for(auto edge:original.trace.edges)if(edge.first>=pilot.contract.original && edge.first<pilot.contract.end)pilot.edges.insert(edge);
}
}

std::string observable_difference(const Machine& a,const Machine& b,const FunctionContract& contract,uint32_t stack) {
    if(a.outcome.stop!=Stop::returned || b.outcome.stop!=Stop::returned)
        return "incomplete execution: original "+std::to_string(int(a.outcome.stop))+" "+a.outcome.error+", candidate "+std::to_string(int(b.outcome.stop))+" "+b.outcome.error;
    if(contract.returns=="i32") {if(a.state.gpr[2].w[0]!=b.state.gpr[2].w[0])return "integer return";}
    else if(contract.returns=="i64") {if(a.state.gpr[2].low()!=b.state.gpr[2].low())return "64-bit return";}
    else if(contract.returns=="i128") {if(a.state.gpr[2]!=b.state.gpr[2])return "128-bit return";}
    else if(contract.returns=="f32") {if(a.state.fpr[0]!=b.state.fpr[0])return "float return";}
    else if(contract.returns!="void")return "unsupported return ABI";
    if(contract.returns!="void" && contract.returns!="f32" &&
       (stack_byte(a,a.state.gpr[2].w[0],stack) || stack_byte(b,b.state.gpr[2].w[0],stack)))return "escaping local stack return needs an explicit contract";
    for(unsigned r:{16u,17u,18u,19u,20u,21u,22u,23u,28u,29u,30u})
        if(a.state.gpr[r]!=b.state.gpr[r])return "preserved GPR "+std::to_string(r);
    for(unsigned r=20;r<32;++r)if(a.state.fpr[r]!=b.state.fpr[r])return "preserved FPR "+std::to_string(r);
    // Until individual VU calling contracts are recovered, keep all VU/FPU
    // auxiliary outputs observable. This can reject correct candidates.
    if(a.state.vf!=b.state.vf || a.state.vi!=b.state.vi || a.state.vacc!=b.state.vacc || a.state.vu_micro_running!=b.state.vu_micro_running)
        return "VU outputs";
    if(a.state.fcr!=b.state.fcr || a.state.facc!=b.state.facc || a.state.facc_overflow!=b.state.facc_overflow)return "FPU auxiliary outputs";
    if(!a.state.vu.pending.empty() || !b.state.vu.pending.empty())return "pending VU outputs need an explicit contract";
    for(unsigned r=0;r<32;++r)if(r!=1 && r!=9 && a.state.cop0[r]!=b.state.cop0[r])return "COP0 output "+std::to_string(r);
    auto left=a.trace.writes,right=b.trace.writes;
    // Only bytes below the captured SP that execution actually allocated are
    // local scratch. Caller storage, scratchpad and VU memory stay observable.
    std::erase_if(left,[&](auto item){return stack_byte(a,item.first,stack);});
    std::erase_if(right,[&](auto item){return stack_byte(b,item.first,stack);});
    for(const auto* m:{&a,&b})for(const auto& [address,value]:m->trace.writes){
        (void)value;
        if(!(address&3) && !stack_byte(*m,address,stack) &&
           address<Memory::ram_size-4 && stack_byte(*m,uint32_t(const_cast<Memory&>(m->memory).read_physical(address,4)),stack))
            return "escaping local stack pointer needs an explicit contract";
    }
    if(left!=right){
        for(const auto& [address,value]:left)if(!right.contains(address) || right.at(address)!=value)return "memory write at "+hex(address);
        for(const auto& [address,value]:right)if(!left.contains(address) || left.at(address)!=value)return "extra memory write at "+hex(address);
    }
    auto le=a.trace.events,re=b.trace.events;
    const auto root=[](const Event& e){return e.kind==EventKind::call && e.pc==0xfffffffc;};
    std::erase_if(le,root);std::erase_if(re,root);
    for(auto& e:le)e.pc=0;for(auto& e:re)e.pc=0;
    // Compare all argument banks conservatively. No inferred arity, pointer
    // rebasing, ignored calls, or fabricated callee results.
    if(le!=re){
        size_t i=0;while(i<std::min(le.size(),re.size()) && le[i]==re[i])++i;
        return "ordered event "+std::to_string(i)+(i<le.size()?" original target "+hex(le[i].address):"")+(i<re.size()?" candidate target "+hex(re[i].address):"");
    }
    if(a.memory.hardware_responses!=b.memory.hardware_responses)return "hardware response state";
    return {};
}

void differential_main(int argc,char** argv) {
    if(argc!=7)throw Fault("usage: eeharness differential SNAPSHOT CORPUS MANIFEST PATCHLIST BUDGET");
    std::ifstream snapshot(argv[2],std::ios::binary);auto input=import_snapshot(snapshot);input.memory.scratch_dma=true;
    std::ifstream manifest(argv[4]);std::map<uint32_t,Pilot> pilots;uint32_t address=0,end=0,entry=0;std::string returns,path;
    while(manifest>>std::hex>>address>>end>>entry>>returns>>std::quoted(path)){
        if(address>=end || pilots.contains(address))throw Fault("invalid or duplicate differential target");
        Pilot pilot;pilot.contract={address,end,entry,returns};pilot.image=candidate_image(path);
        if(!pilot.image.contains(entry) && ![&](){for(const auto& [base,bytes]:pilot.image)if(entry>=base && entry<uint64_t(base)+bytes.size())return true;return false;}())throw Fault("candidate entry outside image");
        pilots.emplace(address,std::move(pilot));
    }
    if(!manifest.eof() || pilots.empty())throw Fault("invalid differential manifest");
    struct Patch{uint32_t address,width;uint64_t before,after;};std::multimap<uint64_t,Patch> patches;
    std::ifstream patchfile(argv[5]);uint64_t index=0,before=0,after=0;uint32_t width=0;
    while(patchfile>>std::dec>>index>>std::hex>>address>>before>>after>>std::dec>>width){
        if(width!=1 && width!=2 && width!=4)throw Fault("invalid differential patch width");patches.emplace(index,Patch{address,width,before,after});
    }
    if(!patchfile.eof())throw Fault("invalid differential patches");
    std::ifstream corpus(argv[3],std::ios::binary);char magic[8];corpus.read(magic,8);
    if(std::string(magic,8)!="EECAP001")throw Fault("invalid differential corpus");
    uint64_t ordinal=0;index=0;const auto budget=std::stoull(argv[6]);
    while(restore_entry(corpus,input,address,ordinal)){
        const auto found=pilots.find(address);
        if(found!=pilots.end()){
            if(input.state.pc!=address || input.state.delay_slot)throw Fault("capture is not at a function entry");
            exercise(input,found->second,index,budget,false);
            const auto [begin,last]=patches.equal_range(index);
            for(auto patch=begin;patch!=last;++patch){auto mutated=input;const auto& p=patch->second;
                const auto physical=mutated.translate(p.address,Machine::Access::write);
                if(physical>=Memory::ram_size || mutated.memory.read_physical(physical,p.width)!=p.before)throw Fault("differential fuzz preimage mismatch");
                mutated.memory.write_physical(physical,p.width,p.after);exercise(mutated,found->second,index,budget,true);
            }
        }
        ++index;
    }
    std::cout<<"[";bool first=true;
    for(const auto& [key,p]:pilots){if(!first)std::cout<<',';first=false;
        std::cout<<"{\"address\":"<<key<<",\"recorded\":"<<p.recorded<<",\"fuzzed\":"<<p.fuzzed<<",\"passed\":"<<p.passed<<",\"failed\":"<<p.failed
                 <<",\"original_instructions\":"<<p.instructions<<",\"first_failure_index\":"<<p.first_index<<",\"first_error\":"<<std::quoted(p.first_error)<<",\"pcs\":[";
        bool comma=false;for(auto pc:p.pcs){if(comma)std::cout<<',';comma=true;std::cout<<pc;}
        std::cout<<"],\"edges\":[";comma=false;for(auto [from,to]:p.edges){if(comma)std::cout<<',';comma=true;std::cout<<'['<<from<<','<<to<<']';}std::cout<<"]}";
    }
    std::cout<<"]\n";
}
}
