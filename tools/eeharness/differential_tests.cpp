#include "differential.hpp"
#include <iostream>

namespace {
void require(bool value,const char* message){if(!value)throw ee::Fault(message);}
void code(ee::Machine& m,uint32_t base,std::initializer_list<uint32_t> words,bool candidate=false){
    std::vector<uint8_t> bytes;
    for(auto word:words)for(unsigned i=0;i<4;++i)bytes.push_back(uint8_t(word>>(i*8)));
    if(candidate)m.memory.candidate_regions[base]=bytes;else m.memory.load(base,bytes);
}
void comparison(){
    ee::Machine a,b;a.state.gpr[29].low(0x1ff0000);b.state=a.state;
    // The candidate uses t0 and an extra instruction; int return is identical.
    code(a,0x1000,{0x03e00008,0x24820001});
    code(b,0x08000000,{0x24880001,0x03e00008,0x01001021},true);
    a.state.gpr[4].low(41);b.state.gpr[4].low(41);
    a.call(0x1000,100);b.call(0x08000000,100);
    ee::FunctionContract c{0x1000,0x1008,0x08000000,"i32"};
    require(ee::observable_difference(a,b,c,0x1ff0000).empty(),"relocated nonmatching register allocation rejected");
    b.state.gpr[2].w[0]++;
    require(ee::observable_difference(a,b,c,0x1ff0000)=="integer return","mutated return not detected");b.state.gpr[2]=a.state.gpr[2];
    b.trace.writes[0x2000]=1;
    require(!ee::observable_difference(a,b,c,0x1ff0000).empty(),"mutated RAM write not detected");b.trace.writes.clear();
    b.trace.events.push_back({ee::EventKind::call,0,0x2000});
    require(!ee::observable_difference(a,b,c,0x1ff0000).empty(),"changed ordered call not detected");b.trace.events.clear();
    b.outcome.stop=ee::Stop::budget;
    require(!ee::observable_difference(a,b,c,0x1ff0000).empty(),"budget stop counted as agreement");
    bool failed=false;try{b.memory.write(0x08000000,4,0);}catch(const ee::Fault&){failed=true;}
    require(failed,"candidate text was writable");
    require(a.trace.instructions.contains(0x1000) && a.trace.edges.contains({0x1000,0x1004}),"original coverage missing");
}
void stack_scope(){
    ee::Machine a,b;a.outcome.stop=b.outcome.stop=ee::Stop::returned;
    a.minimum_stack=0x1f00;b.minimum_stack=0x1e00;
    a.trace.writes[0x1ff0]=1;b.trace.writes[0x1ef0]=2;
    const ee::FunctionContract c{0x1000,0x1100,0x08000000,"void"};
    require(ee::observable_difference(a,b,c,0x2000).empty(),"allocated local spill bytes compared");
    b.trace.writes[0x2000]=3;
    require(!ee::observable_difference(a,b,c,0x2000).empty(),"caller stack storage wrongly excluded");
    b.trace.writes.erase(0x2000);b.trace.writes[0x70000000]=1;
    require(!ee::observable_difference(a,b,c,0x2000).empty(),"scratchpad wrongly excluded");
    b.trace.writes.clear();b.state.vf[1].w[0]=1;
    require(!ee::observable_difference(a,b,c,0x2000).empty(),"VU output mutation not detected");
}
}
int main(){try{comparison();stack_scope();std::cout<<"OK differential mutation, ABI, stack scope and coverage checks\n";return 0;}
catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
