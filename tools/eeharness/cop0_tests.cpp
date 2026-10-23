#include "ee.hpp"

#include <array>
#include <iostream>

namespace {
unsigned checks = 0;
void check(bool value,const char* label) { ++checks; if (!value) throw ee::Fault(label); }
template<class Function> bool faults(Function action) {
    try { action(); } catch (const ee::Fault&) { return true; }
    return false;
}
void instruction(ee::Machine& m,uint32_t word) {
    m.memory.write(0x1000,4,word); m.state.start(0x80001000); m.step();
}
void mapping(ee::Machine& m,unsigned index,uint32_t address,uint32_t mask,uint32_t even,uint32_t odd) {
    m.state.cop0[0] = index; m.state.cop0[5] = mask; m.state.cop0[10] = address;
    m.state.cop0[2] = even; m.state.cop0[3] = odd;
    instruction(m,0x42000002);
}
uint32_t frame(uint32_t address,unsigned flags=0x1e) { return address>>6 | flags; }
void pages() {
    for (uint32_t mask : {0u,0x6000u,0x1e000u,0x7e000u,0x1fe000u,0x7fe000u,0x1ffe000u}) {
        ee::Machine m; m.state.mmu_enabled = true;
        constexpr uint32_t base = 0x40000000, even = 0x00400000, odd = 0x01000000;
        const uint32_t page = (mask+0x2000)/2;
        mapping(m,7,base|0x37,mask,frame(even),frame(odd));
        for (uint32_t offset : {0u,3u,page-1}) {
            check(m.translate(base+offset,ee::Machine::Access::read) == ((even&~(page-1))|offset),"TLB even page translation at every supported size");
            check(m.translate(base+page+offset,ee::Machine::Access::write) == ((odd&~(page-1))|offset),"TLB odd page and physical alignment at every supported size");
        }
        m.state.cop0[5] = 0; m.state.cop0[10] = 0; m.state.cop0[2] = m.state.cop0[3] = 0;
        instruction(m,0x42000001);
        check(m.state.cop0[5] == mask && m.state.cop0[10] == (base|0x37),"TLBR round-trips the indexed page size and EntryHi");
        check(m.state.cop0[2] == frame(even) && m.state.cop0[3] == frame(odd),"TLBR restores both physical frame entries");
    }
    ee::Machine invalid;
    check(faults([&] { mapping(invalid,0,0,0x2000,frame(0),frame(0x1000)); }),"undefined intermediate page mask faults");
    check(faults([&] { mapping(invalid,48,0,0,frame(0),frame(0x1000)); }),"TLBWI out-of-range index faults");
}
void asids_and_permissions() {
    ee::Machine m; m.state.mmu_enabled = true;
    constexpr uint32_t address = 0x00400000;
    mapping(m,2,address|3,0,frame(0x8000),frame(0x9000));
    m.state.cop0[10] = 4;
    check(faults([&] { m.translate(address+0x123,ee::Machine::Access::read); }),"ASID mismatch requires refill");
    check(m.state.cop0[8] == address+0x123 && m.state.cop0[10] == (address|4),"refill records virtual address and preserves ASID");
    check((m.state.cop0[4]&0x7ffff0) == ((address>>9)&0x7ffff0),"refill updates Context BadVPN2");
    instruction(m,0x42000008);
    check(m.state.cop0[0]&0x80000000,"TLBP reports a miss in Index.P");
    m.state.cop0[10] = address|3; instruction(m,0x42000008);
    check(m.state.cop0[0] == 2,"TLBP finds the ASID-qualified indexed entry");
    mapping(m,2,address|3,0,frame(0x8000,0x1f),frame(0x9000,0x1f));
    m.state.cop0[10] = 255;
    check(m.translate(address,ee::Machine::Access::read) == 0x8000,"both Global bits bypass ASID matching");
    mapping(m,2,address|3,0,frame(0x8000,0x1f),frame(0x9000,0x1e));
    m.state.cop0[0] = 2; instruction(m,0x42000001);
    check(!(m.state.cop0[2]&1) && !(m.state.cop0[3]&1),"TLBR exposes the conjunction of both Global bits");
    m.state.cop0[10] = 4;
    check(faults([&] { m.translate(address,ee::Machine::Access::read); }),"one Global bit does not bypass the ASID");
    mapping(m,2,address,0,frame(0x8000,0x1a),frame(0x9000,0x18));
    check(m.translate(address,ee::Machine::Access::read) == 0x8000,"valid clean TLB page permits reads");
    check(faults([&] { m.translate(address,ee::Machine::Access::write); }),"clean TLB page rejects stores");
    check(faults([&] { m.translate(address+0x1000,ee::Machine::Access::execute); }),"invalid odd page rejects instruction fetch");
    mapping(m,3,address,0,frame(0xa000),frame(0xb000));
    check(faults([&] { m.translate(address,ee::Machine::Access::read); }),"multiple matching TLB entries fault as undefined");
    m.state.cop0[10] = address;
    check(faults([&] { instruction(m,0x42000008); }),"multiple TLB probe matches also fault");
}
void scratch_and_privilege() {
    ee::Machine m; m.state.mmu_enabled = true;
    mapping(m,0,0x70000000,0,0x80000006,6);
    for (uint32_t offset : {0u,0xfffu,0x1000u,0x2000u,0x3fffu})
        check(m.translate(0x70000000+offset,ee::Machine::Access::write) == 0x70000000+offset,"scratchpad TLB entry covers one contiguous 16 KB region");
    check(faults([&] { m.translate(0x70004000,ee::Machine::Access::read); }),"scratchpad mapping does not cover its adjacent virtual region");
    m.state.cop0[0] = 0; instruction(m,0x42000001);
    check((m.state.cop0[2]&0x38) == 0x10 && (m.state.cop0[3]&0x38) == 0x10,"scratchpad cache fields read as uncached");
    check(faults([&] { mapping(m,1,0x10000,0x6000,0x80000006,6); }),"scratchpad requires a zero page mask");
    check(faults([&] { mapping(m,1,0x12000,0,0x80000006,6); }),"scratchpad virtual base requires 16 KB alignment");
    check(faults([&] { mapping(m,1,0x10000,0,0x80000006,2); }),"scratchpad halves must agree on valid and dirty bits");
    m.state.cop0[12] = 0;
    check(m.translate(0x80001234,ee::Machine::Access::read) == 0x1234 && m.translate(0xa0001234,ee::Machine::Access::write) == 0x1234,"kernel kseg0/kseg1 bypass the TLB");
    m.state.cop0[12] = 0x10;
    check(faults([&] { m.translate(0x80001234,ee::Machine::Access::read); }),"user cannot access kernel direct segments");
    m.state.cop0[12] = 8;
    check(faults([&] { m.translate(0xa0001234,ee::Machine::Access::read); }),"supervisor cannot access kernel direct segments");
    m.state.cop0[12] = 0;
    mapping(m,1,0xc0000000,0,frame(0x8000),frame(0x9000));
    m.state.cop0[12] = 8;
    check(m.translate(0xc0000000,ee::Machine::Access::read) == 0x8000,"supervisor mapped segment uses the TLB");
    m.state.cop0[12] = 0x14;
    check(m.translate(0x00400000,ee::Machine::Access::read) == 0x00400000,"ERL forces kernel privilege and direct kuseg");
    m.state.cop0[12] = 0x12;
    check(m.translate(0x80001234,ee::Machine::Access::read) == 0x1234,"EXL also forces kernel privilege");
}
void execution_and_snapshot() {
    ee::Machine m;
    mapping(m,0,0x00400000,0,frame(0x8000),frame(0xa000));
    const std::array<uint32_t,4> program = {0xac820000,0x8c830000,0x03e00008,0};
    for (unsigned i = 0; i < program.size(); ++i) m.memory.write(0x8000+i*4,4,program[i]);
    m.state.mmu_enabled = true;
    m.state.gpr[4].low(0x00401000); m.state.gpr[2].low(0xf00dbeef);
    auto replay = m;
    check(m.call(0x00400000,20).stop == ee::Stop::returned,"mapped instruction fetch and return complete");
    check(m.state.gpr[3].low() == 0xfffffffff00dbeef && m.memory.read(0xa000,4) == 0xf00dbeef,"mapped scalar load/store use physical data pages");
    check(m.trace.writes.contains(0xa000) && !m.trace.writes.contains(0x00401000),"trace writes use canonical physical addresses");
    replay.call(0x00400000,20);
    check(replay.state == m.state && replay.trace == m.trace,"MMU input snapshot reproduces execution and traces");
    mapping(replay,0,0x00400000,0,frame(0xb000),frame(0xc000));
    check(m.translate(0x00400000,ee::Machine::Access::read) == 0x8000,"later TLB writes do not mutate an earlier snapshot");
    ee::Memory memory;
    memory.write(0,4,0x1234);
    check(faults([&] { memory.read_physical(0x20000000,4); }),"physical addresses cannot accidentally re-enter the legacy virtual-alias path");
}
void clocks_and_registers() {
    ee::Machine m;
    m.state.cop0[9] = 0xfffffffe; m.state.cop0[11] = 0;
    instruction(m,0);
    check(m.state.cop0[9] == 0xffffffff && !(m.state.cop0[13]&0x8000),"Count advances once per issue clock before wrap");
    instruction(m,0);
    check(m.state.cop0[9] == 0 && (m.state.cop0[13]&0x8000),"Count wrap at Compare asserts pending timer interrupt");
    m.state.gpr[2].low(100); instruction(m,0x40825800);
    check(m.state.cop0[11] == 100 && !(m.state.cop0[13]&0x8000),"writing Compare clears the pending timer interrupt");
    instruction(m,0x40024800);
    check(m.state.gpr[2].low() == 1 && m.trace.events.back().kind == ee::EventKind::cop0_read && m.trace.events.back().default_response,"Count reads are recorded timing-profile observations");
    m.state.gpr[2].low(47); instruction(m,0x40823000);
    check(m.state.cop0[6] == 47 && m.state.cop0[1] == 47,"writing Wired resets Random to the upper bound");
    for (unsigned i = 0; i < 5; ++i) instruction(m,0);
    check(m.state.cop0[1] == 47,"one-entry Random range remains at the wired boundary");
    m.state.gpr[2].low(45); instruction(m,0x40823000);
    instruction(m,0); check(m.state.cop0[1] == 46,"Random decrements through the unwired range");
    instruction(m,0); check(m.state.cop0[1] == 45,"Random reaches Wired inclusively");
    instruction(m,0); check(m.state.cop0[1] == 47,"Random wraps to entry 47");
    m.state.cop0[10] = 0x00400000; m.state.cop0[2] = frame(0x8000); m.state.cop0[3] = frame(0x9000);
    instruction(m,0x42000006);
    check(m.state.tlb[47].initialized,"TLBWR writes the Random-selected entry");
    m.state.gpr[2].low(63);
    check(faults([&] { instruction(m,0x40823000); }),"Wired values above 47 fault as undefined");
}
void coprocessor_permissions() {
    for (const auto [word,cop] : std::array<std::pair<uint32_t,unsigned>,6>{{
        {0x46000000,1},{0xc4800000,1},{0xe4800000,1},{0x4a0002ff,2},{0xd8800000,2},{0xf8800000,2}}}) {
        ee::Machine m; m.state.cop0[12] &= ~(1u<<(28+cop));
        m.state.gpr[4].low(0x2000);
        check(faults([&] { instruction(m,word); }),"disabled coprocessor rejects arithmetic and memory transfers");
        check((m.state.cop0[13]&0x3000007c) == (cop<<28 | 11<<2),"coprocessor-unusable Cause identifies the unit");
    }
    ee::Machine user;
    user.state.cop0[12] = 0x10;
    check(faults([&] { instruction(user,0x40024800); }),"user COP0 access requires CU0");
    user.state.cop0[12] = 0x10000010;
    check(!faults([&] { instruction(user,0x40024800); }),"CU0 permits the user-mode COP0 read");
    user.state.cop0[12] = 0;
    check(!faults([&] { instruction(user,0x40024800); }),"kernel COP0 read works independently of CU0");
    user.state.cop0[13] = 0xf000fc7c; user.state.gpr[2].low(0);
    instruction(user,0x40826800);
    check(user.state.cop0[13] == 0xf000fc7c,"MTC0 Cause cannot fabricate or clear hardware interrupt fields");
    user.state.gpr[2].low(0xffffffff); user.state.cop0[12] = 0x40000;
    instruction(user,0x40826000);
    check(user.state.cop0[12] == 0xf0c79c1f,"Status write preserves read-only CH and removes reserved bits");
}
} // namespace

int main() {
    try {
        pages(); asids_and_permissions(); scratch_and_privilege(); execution_and_snapshot(); clocks_and_registers(); coprocessor_permissions();
        std::cout << "OK " << checks << " COP0/MMU semantic assertions\n";
        return 0;
    } catch (const std::exception& error) { std::cerr << "after " << checks << " COP0 checks: " << error.what() << '\n'; return 1; }
}
