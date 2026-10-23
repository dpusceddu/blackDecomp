#include "ee.hpp"
#include "fpu.hpp"

#include <iostream>
#include <limits>

namespace {
unsigned checks = 0;
void check(bool pass, const char* what) {
    ++checks;
    if (!pass) throw ee::Fault(what);
}
uint32_t r(unsigned rs,unsigned rt,unsigned rd,unsigned sa,unsigned fn) {
    return rs<<21 | rt<<16 | rd<<11 | sa<<6 | fn;
}
uint32_t i(unsigned op,unsigned rs,unsigned rt,int imm) {
    return op<<26 | rs<<21 | rt<<16 | uint16_t(imm);
}
void code(ee::Machine& m, std::initializer_list<uint32_t> words) {
    uint32_t p = 0x1000;
    for (auto w : words) { m.memory.write(p,4,w); p += 4; }
    m.state.start(0x1000);
}
void memory() {
    ee::Memory m;
    m.write(0x1000,8,0x8877665544332211);
    for (auto alias : {0x1000u,0x80001000u,0xa0001000u,0x20001000u,0x30001000u})
        check(m.read(alias,8) == 0x8877665544332211,"RAM aliases");
    check(m.read(0x1003,1) == 0x44,"little endian byte");
    auto snapshot = m;
    m.write(0x1000,4,0);
    check(snapshot.read(0x1000,4) == 0x44332211,"COW replay snapshot");
    m.write(0x1ffd,8,0xfedcba9876543210);
    auto boundary = m;
    m.write(0x1fff,4,0x12345678);
    check(boundary.read(0x1ffd,8) == 0xfedcba9876543210 && m.read(0x1fff,4) == 0x12345678,"cross-page reads/writes preserve both snapshot pages");
    m.write(0x70003ffc,4,0x12345678);
    check(m.read(0x70003ffc,4) == 0x12345678,"scratchpad boundary");
    m.write(0x11000000,8,0x1234); m.write(0x11004000,8,0x5678);
    check(m.read(0x11000000,8) == 0x1234 && m.read(0x11004000,8) == 0x5678,"separate VU memories");
    ee::Trace t;
    check(m.read(0x10003000,4,&t) == 0 && t.events.back().default_response,"explicit default hardware response");
    m.hardware_responses[{0x10003000,4}] = 0x80;
    check(m.read(0x10003000,4,&t) == 0x80 && !t.events.back().default_response,"supplied hardware response");
    bool fault = false;
    try { m.write(ee::Memory::ram_size-2,4,1); } catch (const ee::Fault&) { fault = true; }
    check(fault,"no RAM wrap at boundary");
}
void integer() {
    ee::Machine m;
    code(m,{i(9,0,2,5)});
    m.state.gpr[0].low(99); m.step();
    check(m.state.gpr[2].low() == 5,"input snapshots cannot change the physical zero register");
    code(m,{i(9,0,2,7)}); m.step();
    code(m,{i(9,0,2,11)}); m.step();
    check(m.state.gpr[2].low() == 11,"decode cache follows changed instruction words at the same address");
    m.state.gpr[2].high(0x123456789abcdef0);
    code(m,{i(0x0f,0,2,0x8000),i(9,2,2,-1),r(0,2,3,0,2),i(9,0,0,42)});
    m.run(4);
    check(m.state.gpr[2].low() == 0x7fffffff,"32-bit wrapping add sign extension");
    check(m.state.gpr[2].high() == 0x123456789abcdef0,"scalar preserves upper 64 bits");
    check(m.state.gpr[3].low() == 0x7fffffff,"srl sign extension");
    check(m.state.gpr[0] == ee::Quad{},"zero register immutable");
    code(m,{r(0,2,3,0,0x3e)}); m.step();
    check(m.state.gpr[3].low() == 0,"dsrl32 shift count");
    m.state.gpr[4].low(0xffffffff80000000); m.state.gpr[5].low(0xffffffffffffffff);
    code(m,{r(4,5,2,0,0x1a)}); m.step();
    check(m.state.lo.low() == 0xffffffff80000000 && m.state.hi.low() == 0,"division signed overflow");
    m.state.gpr[5].low(0);
    code(m,{r(4,5,0,0,0x1a)}); m.step();
    check(m.state.lo.low() == 1 && m.state.hi.low() == 0xffffffff80000000,"division by zero negative");
    code(m,{r(4,5,0,0,0x1b)}); m.step();
    check(m.state.lo.low() == ~uint64_t(0),"unsigned division by zero");
    m.state.gpr[4].low(0x7fffffff);
    code(m,{i(8,4,2,1)});
    check(m.run(1).stop == ee::Stop::fault,"trapping signed addition");
    code(m,{i(0x19,4,2,-1)}); m.step();
    check(m.state.gpr[2].low() == 0x7ffffffe,"64-bit signed immediate");
    for (uint32_t status : {0u,0x10u,0x08u,0x20010u,0x12u,0x14u}) {
        m.state.cop0[12] = status;
        code(m,{0x42000038}); m.step();
        const bool permitted = status == 0 || status == 0x20010 || status == 0x12 || status == 0x14;
        check(bool(m.state.cop0[12] & 0x10000) == permitted,"EI honors privilege and EDI/EXL/ERL");
        m.state.cop0[12] = status | 0x10000;
        code(m,{0x42000039}); m.step();
        check(bool(m.state.cop0[12] & 0x10000) != permitted,"DI honors privilege and EDI/EXL/ERL");
    }
    for (unsigned shift = 0; shift < 64; ++shift) {
        m.state.gpr[4].low(shift); m.state.gpr[5].low(0x8000000000000000);
        code(m,{r(4,5,2,0,0x17)}); m.step();
        const auto expected = shift ? (~uint64_t(0) << (64-shift)) | (uint64_t(1) << (63-shift)) : uint64_t(1) << 63;
        check(m.state.gpr[2].low() == expected,"all arithmetic right shifts");
    }
}
void delays() {
    ee::Machine m;
    code(m,{i(9,0,4,1),i(4,4,4,2),i(9,0,2,7),i(9,0,2,99),r(31,0,0,0,8),i(9,2,2,1)});
    auto result = m.call(0x1000,20);
    check(result.stop == ee::Stop::returned && m.state.gpr[2].low() == 8,"taken branch and return delay slots");
    code(m,{i(0x14,0,4,1),i(9,0,2,99),i(9,0,2,3)});
    m.step();
    check(m.state.pc == 0x1008 && !m.state.delay_slot,"likely false annuls delay slot");
    m.step(); check(m.state.gpr[2].low() == 3,"annulled instruction has no side effect");
    code(m,{i(5,0,0,1),i(9,0,2,4),i(9,0,2,5)});
    m.step(); check(m.state.delay_slot,"ordinary untaken branch still has a delay slot");
    m.step(); check(m.state.gpr[2].low() == 4,"untaken delay executed");
    code(m,{0x0c000404,i(9,0,4,42),i(9,0,2,7),0, r(31,0,0,0,8),0});
    unsigned entries = 0;
    m.capture_entries.insert(0x1010);
    m.on_entry = [&](uint32_t addr,const ee::State& s,const ee::Memory& mem) {
        ++entries; check(addr == 0x1010 && s.gpr[4].low() == 42,"capture includes call delay arguments");
        check(mem.bytes(0x1010,4).size() == 4,"capture carries replay memory");
    };
    m.run(3);
    check(entries == 1 && m.trace.events.back().arguments[0].low() == 42,"ordered call after delay");
    code(m,{i(4,0,0,1),i(4,0,0,1)});
    check(m.run(2).stop == ee::Stop::fault,"undefined nested delay branch stops");
}
void coprocessor_control() {
    for (unsigned variant = 0; variant < 4; ++variant) for (bool condition : {false,true}) {
        ee::Machine m;
        m.memory.hardware_responses[{0x1000e010,4}] = condition ? 0x205 : 0x005;
        m.memory.hardware_responses[{0x1000e020,4}] = 0x205;
        code(m,{i(0x10,8,variant,2),i(9,0,2,7),i(9,0,2,11),i(9,0,2,13)});
        m.step();
        const bool taken = condition == bool(variant&1), annulled = !taken && bool(variant&2);
        check(m.state.pc == (annulled ? 0x1008u : 0x1004u),"BC0 likely annulment follows sampled DMA condition");
        check(m.trace.events.size() == 2 && !m.trace.events[0].default_response,"BC0 records configured DMA condition inputs");
        m.step();
        check(m.state.pc == (taken ? 0x100cu : annulled ? 0x100cu : 0x1008u),"BC0 target and ordinary delay-slot sequencing");
        check(m.state.gpr[2].low() == (annulled ? 11u : 7u),"BC0 delay side effects occur only when not annulled");

        ee::Machine vu;
        vu.state.vi[29] = condition ? 0x100 : 0;
        code(vu,{i(0x12,8,variant,2),i(9,0,2,7),i(9,0,2,11),i(9,0,2,13)});
        vu.step(); vu.step();
        check(vu.state.pc == (taken ? 0x100cu : annulled ? 0x100cu : 0x1008u),"BC2 uses VU1 busy status with branch/likely delay behavior");
    }
    ee::Machine none;
    code(none,{i(0x10,8,1,2)}); none.step();
    check(none.state.next_pc == 0x100c && none.trace.events[0].default_response,"no selected DMA channels satisfies the default completion condition");
    for (uint32_t status : {0u,2u,4u,6u}) {
        ee::Machine m;
        m.state.cop0[12] = status|0x10000;
        m.state.cop0[14] = 0x2000; m.state.cop0[30] = 0x3000;
        code(m,{0x42000018,i(9,0,2,99)}); m.step();
        const bool error = status&4;
        check(m.state.pc == (error ? 0x3000u : 0x2000u) && m.state.next_pc == m.state.pc+4 && !m.state.delay_slot,
              "ERET chooses ErrorEPC before EPC and has no delay slot");
        check(m.state.cop0[12] == ((status|0x10000)&~(error ? 4u : 2u)),"ERET clears only the selected exception level");
        check(m.state.gpr[2].low() == 0,"ERET does not execute its following instruction");
    }
    ee::Machine invalid;
    code(invalid,{i(4,0,0,1),0x42000018});
    check(invalid.run(2).stop == ee::Stop::fault,"ERET in a branch delay slot faults instead of inventing behavior");
    for (uint32_t input : {0u,1u,15u,16u,65535u}) {
        ee::Machine m; m.state.gpr[4].low(input);
        code(m,{r(4,0,0,0,0x29),r(0,0,2,0,0x28)}); m.run(2);
        check(m.state.gpr[2].low() == (input&15),"MTSA/MFSA published readback masks high bits");
    }
}
void unaligned() {
    // Check every little-endian LWL/LWR/SWL/SWR/LDL/LDR/SDL/SDR position.
    for (unsigned width : {4u,8u}) for (unsigned pos = 0; pos < width; ++pos)
        for (bool left : {false,true}) for (bool load : {false,true}) {
            ee::Machine m;
            m.state.gpr[4].low(0x2000+pos); m.state.gpr[2].low(0xa7a6a5a4a3a2a1a0);
            for (unsigned b = 0; b < width; ++b) m.memory.write(0x2000+b,1,0x10+b);
            const unsigned opcode = load ? (width == 4 ? (left ? 0x22:0x26) : (left ? 0x1a:0x1b)) :
                                           (width == 4 ? (left ? 0x2a:0x2e) : (left ? 0x2c:0x2d));
            code(m,{i(opcode,4,2,0)}); m.step();
            for (unsigned b = 0; b < width; ++b) {
                const bool active = left ? b <= pos : b >= pos;
                const unsigned regbyte = left ? width-1-pos+b : b-pos;
                if (load && active)
                    check(((m.state.gpr[2].low() >> (regbyte*8)) & 255) == 0x10+b,"unaligned load byte mapping");
                if (!load) check(m.memory.read(0x2000+b,1) == (active ? 0xa0+regbyte : 0x10+b),"unaligned store byte mapping");
            }
            if (load && width == 4 && !left && pos)
                check(m.state.gpr[2].w[1] == 0xa7a6a5a4,"partial LWR preserves bits 63:32");
        }
}
void packed() {
    ee::Machine m;
    m.state.gpr[4].w = {1,2,3,4}; m.state.gpr[5].w = {5,6,7,8};
    code(m,{0x70000000 | r(4,5,4,0x12,8)}); m.step();
    check(m.state.gpr[4].w == std::array<uint32_t,4>{5,1,6,2},"PExtLW and destination alias");
    m.state.gpr[4].w = {0x7fffffff,0x80000000,1,0xffffffff};
    m.state.gpr[5].w = {1,0xffffffff,2,0xffffffff};
    code(m,{0x70000000 | r(4,5,2,0x10,8)}); m.step();
    check(m.state.gpr[2].w == std::array<uint32_t,4>{0x7fffffff,0x80000000,3,0xfffffffe},"signed packed saturation");
    m.state.gpr[4].w = {0xffffffff,1,0x80000000,0};
    m.state.gpr[5].w = {2,0,2,0};
    code(m,{0x70000000 | r(4,5,2,0x0c,9)}); m.step();
    check(m.state.gpr[2].low() == 0xfffffffffffffffe && m.state.gpr[2].high() == 0xffffffff00000000,"two signed packed products");
    m.state.gpr[4].low(0xffffffff); m.state.gpr[5].low(2);
    code(m,{0x70000000 | r(4,5,2,0,0x18)}); m.step();
    check(m.state.gpr[2].low() == 0xfffffffffffffffe && m.state.hi.high() == ~uint64_t(0),"MULT1 signed product and second accumulator bank");
    m.state.gpr[4].w = {0xfffe0001,0xfffc0003,0xfffa0005,0xfff80007};
    m.state.gpr[5].w = {0x00020002,0x00020002,0x00020002,0x00020002};
    code(m,{0x70000000 | r(4,5,4,0x1c,9)}); m.step();
    check(m.state.gpr[4].w == std::array<uint32_t,4>{2,6,10,14},"PMULTH returns even products with source alias");
    check(m.state.lo.w == std::array<uint32_t,4>{2,0xfffffffc,10,0xfffffff4},"PMULTH LO lane layout");
    check(m.state.hi.w == std::array<uint32_t,4>{6,0xfffffff8,14,0xfffffff0},"PMULTH HI lane layout");
    m.state.gpr[4].w = {0xfffe0001,0xfffc0003,0xfffa0005,0xfff80007};
    code(m,{0x70000000 | r(4,5,2,0x10,9)}); m.step();
    check(m.state.gpr[2].w == std::array<uint32_t,4>{4,12,20,28},"PMADDH wraps per-word accumulator additions");
    code(m,{0x70000000 | r(4,5,2,0x14,9)}); m.step();
    check(m.state.gpr[2].w == std::array<uint32_t,4>{2,6,10,14},"PMSUBH reverses accumulator additions");
    code(m,{0x70000000 | r(4,5,2,0x11,9)}); m.step();
    check(m.state.gpr[2].w == std::array<uint32_t,4>{0xfffffffe,0xfffffffe,0xfffffffe,0xfffffffe},"PHMADH horizontal products");
    code(m,{0x70000000 | r(4,5,2,0x15,9)}); m.step();
    check(m.state.gpr[2].w == std::array<uint32_t,4>{0xfffffffa,0xfffffff2,0xffffffea,0xffffffe2},"PHMSBH horizontal subtraction");
    check(m.state.lo.w[1] == 3 && m.state.hi.w[3] == 15,"PHMSBH secondary accumulator words");
    m.state.lo.w = {0xffffffff,0,0,0}; m.state.hi.w = {0x7fffffff,0,0x80000000,0};
    code(m,{0x70000000 | r(0,0,2,2,0x30)}); m.step();
    check(m.state.gpr[2].low() == 0x7fffffff && m.state.gpr[2].high() == 0xffffffff80000000,"PMFHL.SLW saturation from 64-bit accumulators");
    m.state.lo.w = {0x00010000,0xffff0000,0x80000000,0x7fffffff}; m.state.hi = m.state.lo;
    code(m,{0x70000000 | r(0,0,2,4,0x30)}); m.step();
    check(m.state.gpr[2].w == std::array<uint32_t,4>{0x80007fff,0x80007fff,0x7fff8000,0x7fff8000},"PMFHL.SH signed narrowing saturation");
    m.state.gpr[4].w = {0x03020100,0x07060504,0x0b0a0908,0x0f0e0d0c};
    m.state.gpr[5].w = {0x13121110,0x17161514,0x1b1a1918,0x1f1e1d1c};
    for (unsigned sa = 0; sa < 16; ++sa) {
        m.state.sa = sa;
        code(m,{0x70000000 | r(4,5,2,0x1b,0x28)}); m.step();
        for (unsigned b = 0; b < 16; ++b) {
            const unsigned source = b+sa;
            check(m.state.gpr[2].lane(b,8) == (source < 16 ? source+16 : source-16),"QFSRV all byte shifts");
        }
    }
}
void traces() {
    ee::Machine a;
    code(a,{i(9,4,2,1),r(31,0,0,0,8),0});
    auto b = a;
    check(a.call(0x1000,10).stop == ee::Stop::returned && b.call(0x1000,10).stop == ee::Stop::returned,"identical controls return");
    const std::array<unsigned,1> returns = {2};
    check(ee::difference(a,b,returns,{}).empty(),"identical controls agree");
    b.memory.write(0x1000,4,i(9,4,2,2));
    b.call(0x1000,10);
    check(!ee::difference(a,b,returns,{}).empty(),"deliberate mutation detected");
    b = a; b.trace.events.push_back({ee::EventKind::syscall,0x1000,1});
    check(ee::difference(a,b,returns,{}) == "ordered external events","external event mismatch detected");
    b = a; b.trace.writes[0x3000] = 1;
    check(ee::difference(a,b,returns,{}) == "memory writes","memory mismatch detected");
    b = a; b.state.gpr[2].high(1);
    check(!ee::difference(a,b,returns,{}).empty(),"128-bit return upper lane mutation detected");
    a.trace = {}; b.trace = {};
    a.memory.write(0x4000,4,0x44332211,&a.trace);
    b.memory.write(0x4000,2,0x2211,&b.trace); b.memory.write(0x4002,2,0x4433,&b.trace);
    b.state = a.state;
    check(ee::difference(a,b,returns,{}).empty(),"ordinary RAM store grouping is not observable");
    ee::Machine mmio;
    mmio.state.gpr[4].low(0x10003001);
    mmio.memory.hardware_responses[{0x10003000,4}] = 0x44332211;
    code(mmio,{i(0x26,4,2,0)}); mmio.step();
    check(mmio.trace.events.size() == 1 && mmio.state.gpr[2].w[0] == 0x00443322,"partial load preserves one aligned MMIO access");
    code(a,{0x46000008});
    check(a.run(1).stop == ee::Stop::fault,"reserved FPU opcode stops");
    b = a;
    check(ee::difference(a,b,returns,{}) == "incomplete execution","identical faults cannot pass trace comparison");
    code(a,{0x42000001});
    check(a.run(1).stop == ee::Stop::fault,"TLBR without a supplied entry cannot fabricate state");
    code(a,{0xffffffff}); // valid SD with an invalid address is not an invented response
    a.state.gpr[31].low(0x50000000);
    check(a.run(1).stop == ee::Stop::fault,"unmapped execution cannot pass");
}
void replay_and_elf() {
    ee::Machine m;
    code(m,{0x0c000404,i(9,0,4,42),0,0,i(9,4,2,1),r(31,0,0,0,8),i(9,0,3,7)});
    ee::State saved;
    ee::Memory memory;
    unsigned captures = 0;
    m.capture_entries.insert(0x1010);
    m.on_entry = [&](uint32_t,const ee::State& state,const ee::Memory& input) {
        saved = state; memory = input; ++captures;
    };
    m.run(3);
    check(captures == 1 && saved.pc == 0x1010,"recorded entry PC");
    m.memory.write(0x5000,4,9);
    ee::Machine replay;
    replay.state = saved; replay.memory = memory;
    check(replay.run(10,0x1008).stop == ee::Stop::returned,"recorded entry replays to its original return");
    check(replay.state.gpr[2].low() == 43 && replay.state.gpr[3].low() == 7,"recorded entry has both banks and delay-slot output");
    check(replay.memory.read(0x5000,4) == 0,"replay memory remains independent");
    check(replay.run(0,0x1008).stop == ee::Stop::returned,"return at zero instruction budget");
    code(replay,{i(9,0,2,42)});
    check(replay.run(0).stop == ee::Stop::budget,"budget exhaustion is not a return");
    bool rejected = false;
    try { ee::load_elf(memory,std::vector<uint8_t>(51)); } catch (const ee::Fault&) { rejected = true; }
    check(rejected,"short ELF rejected");
}
void vu_transfers_and_integer() {
    ee::Machine m;
    m.state.gpr[2].w = {0x23456789,0xabcdef01,0xbeefdead,0xc0dec0de};
    const auto pattern = m.state.gpr[2];
    code(m,{0x48a21800,0x48231800}); // QMTC2 r2,vf3; QMFC2 r3,vf3
    m.run(2);
    check(m.state.vf[3] == pattern && m.state.gpr[3] == pattern,"VU full 128-bit transfers");
    code(m,{0x48a20000}); m.step();
    check(m.state.vf[0].w == std::array<uint32_t,4>{0,0,0,0x3f800000},"QMTC2 cannot change VF0");
    m.state.gpr[2].w = {0xffffffff,0x11223344,0x55667788,0x99aabbcc};
    code(m,{0x48c20800,0x48430800}); m.run(2);
    check(m.state.vi[1] == 0xffff && m.state.gpr[3].low() == 0xffff,"VI writes narrow to 16 bits and CFC2 zero extends");
    m.state.gpr[3].high(0x1234567887654321);
    code(m,{0x48c2a800,0x4843a800}); m.run(2);
    check(m.state.vi[21] == 0xffffffff && m.state.gpr[3].low() == ~uint64_t(0),"CFC2 sign extends 32-bit I register");
    check(m.state.gpr[3].high() == 0x1234567887654321,"CFC2 preserves upper 64 GPR bits");
    code(m,{0x48c2a000,0x4843a000}); m.run(2);
    check(m.state.vi[20] == 0x3fffffff && m.state.gpr[3].low() == 0x7fffff,"R register keeps fixed exponent and masks CFC2 read");
    m.state.vi[16] = 0x23; m.state.vi[17] = 0x2468;
    code(m,{0x48c28000,0x48c28800,0x48c29000}); m.run(3);
    check(m.state.vi[16] == 0xfe3,"CTC2 status writes sticky bits, preserving current flags");
    check(m.state.vi[17] == 0x2468 && m.state.vi[18] == 0xffffff,"CTC2 MAC is read-only and CLIP is 24 bits");
    m.state.gpr[4].low(0x4000);
    m.memory.write_quad(0x4010,pattern);
    code(m,{i(0x36,4,2,16),i(0x3e,4,2,32)}); m.run(2);
    check(m.state.vf[2] == pattern && m.memory.read_quad(0x4020) == pattern,"LQC2 and SQC2 address offsets and 128-bit payloads");
    code(m,{i(0x36,4,0,16)}); m.step();
    check(m.state.vf[0].w[3] == 0x3f800000 && m.state.vf[0].w[0] == 0,"LQC2 discards writes to VF0");
    code(m,{i(0x36,4,2,1)});
    check(m.run(1).stop == ee::Stop::fault,"LQC2 rejects unaligned address rather than silently aligning");
    for (unsigned mask = 0; mask < 16; ++mask) {
        m.state.vf[2].w = {1,2,3,4}; m.state.vf[3].w = {5,6,7,8};
        code(m,{0x4a00033c | mask<<21 | 3<<16 | 2<<11,0x48241800}); m.run(2);
        for (unsigned lane = 0; lane < 4; ++lane)
            check(m.state.vf[3].w[lane] == (mask & (8u>>lane) ? lane+1 : lane+5),"VMOVE preserves unselected lanes");
    }
    m.state.vf[2].w = {1,2,3,4};
    code(m,{0x4be00000 | 2<<16 | 2<<11 | 0x33d,0x48241000}); m.run(2);
    check(m.state.vf[2].w == std::array<uint32_t,4>{2,3,4,1},"VMR32 rotates snapshot before aliased destination writes");
    for (unsigned immediate = 0; immediate < 32; ++immediate) {
        m.state.vi[2] = 0xfff0;
        code(m,{0x4a011032 | immediate<<6}); m.step();
        const int signed_immediate = immediate & 16 ? int(immediate)-32 : int(immediate);
        check(m.state.vi[1] == uint16_t(0xfff0+signed_immediate),"VIADDI signed five-bit immediate and 16-bit wrap");
    }
}
void floats() {
    // Selected numerical outcomes also occur in ps2autotests' hardware result
    // logs (revision and references in README). Tests here are authored anew.
    check(ee::fpu::equal(0,0x80000000),"FPU signed zeros compare equal");
    check(ee::fpu::equal(0x00000001,0x80001337),"FPU denormals compare as zero");
    check(ee::fpu::less(0x7f800000,0x7f800001),"exponent 255 is finite, ordered by significand");
    check(ee::fpu::less(0xffffffff,0xff800000),"negative finite extended exponents");
    check(!ee::fpu::less(0x80000000,0),"negative zero is not numerically less");
    check(ee::fpu::maximum(0,0x80000000) == 0,"MAX signed zero");
    check(ee::fpu::minimum(0,0x80000000) == 0x80000000,"MIN signed zero");
    check(ee::fpu::minimum(1,0x3f800000) == 1,"MIN preserves selected denormal bits");
    check(ee::fpu::from_integer(0x7fffffff) == 0x4effffff,"CVT.S.W truncates positive integer");
    check(ee::fpu::from_integer(0x80000000) == 0xcf000000,"CVT.S.W minimum signed integer");
    check(ee::fpu::from_integer(0xffffffff) == 0xbf800000,"CVT.S.W signed input");
    check(ee::fpu::to_integer(0x3fc147ae) == 1,"CVT.W.S truncates positive fraction");
    check(ee::fpu::to_integer(0xbfc147ae) == 0xffffffff,"CVT.W.S truncates negative fraction");
    check(ee::fpu::to_integer(0x7fffffff) == 0x7fffffff,"CVT.W.S positive saturation");
    check(ee::fpu::to_integer(0xffffffff) == 0x80000000,"CVT.W.S negative saturation");
    check(ee::fpu::to_integer(0x4effffff) == 0x7fffff80,"CVT.W.S highest nonsaturating exponent");
    check(ee::fpu::to_integer(0xceffffff) == 0x80000080,"CVT.W.S negative boundary");
    check(ee::fpu::to_integer(0x80001337) == 0,"CVT.W.S flushes denormals");
    ee::Machine m;
    m.state.fpr[4] = 0xffffffff;
    m.state.fcr[31] = 0x0103c079;
    code(m,{0x46002085}); m.step(); // ABS.S f2,f4
    check(m.state.fpr[2] == 0x7fffffff,"ABS bit operation accepts all encodings");
    check(m.state.fcr[31] == 0x01030079,"ABS clears cause O/U but preserves sticky bits");
    m.state.fpr[4] = 1; m.state.fpr[5] = 0;
    code(m,{0x46052032}); m.step(); // C.EQ.S f4,f5
    check(m.state.fcr[31] & 0x800000,"COP1 compare condition");
    code(m,{0x45010001,0,0}); m.step();
    check(m.state.next_pc == 0x1008 && m.state.delay_slot,"COP1 branch condition and delay");
    for (unsigned index = 0; index < 32; ++index) {
        code(m,{0x44420000 | index<<11}); m.step();
        check(m.state.gpr[2].low() == m.state.fcr[index < 16 ? 0 : 31],"CFC1 hardware register aliases");
    }
    m.state.gpr[2].low(0xffffffff);
    code(m,{0x44c2f800}); m.step();
    check(m.state.fcr[31] == 0x0183c079,"CTC1 writable bits and fixed round-to-zero mode");
    check(ee::fpu::add(0x3f800000,0xb3000000).bits == 0x3f800000,"ADD discards operand beyond one alignment bit");
    check(ee::fpu::add(0x3f800000,0xb3800000).bits == 0x3f7fffff,"ADD retains one alignment bit");
    check(ee::fpu::add(0x80000000,0x80000000).bits == 0x80000000,"negative zero plus negative zero");
    check(ee::fpu::subtract(0x80000000,0).bits == 0x80000000,"negative zero minus positive zero");
    check(ee::fpu::add(0x7fffffff,0xffffffff).bits == 0,"extended exponent cancellation");
    auto value = ee::fpu::add(0x7fffffff,0x7fffffff);
    check(value.bits == 0x7fffffff && value.overflow,"ADD saturates beyond finite exponent 255");
    value = ee::fpu::subtract(0x00800001,0x00800000);
    check(value.bits == 0 && value.underflow,"SUB underflow flush");
    value = ee::fpu::subtract(0x00800000,0x00800001);
    check(value.bits == 0x80000000 && value.underflow,"SUB negative underflow sign");
    check(ee::fpu::multiply(0x3f800000,0x3fffffff).bits == 0x3ffffffe,"MUL truncated tree discarded carry");
    check(ee::fpu::multiply(0x3fffffff,0x3f800000).bits == 0x3fffffff,"MUL operand order can change final bit");
    value = ee::fpu::multiply(0x00800000,0x3f000000);
    check(value.bits == 0 && value.underflow,"MUL underflow reports exponent loss");
    value = ee::fpu::multiply(1,0x3f800000);
    check(value.bits == 0 && !value.underflow,"flushing input denormal does not raise underflow");
    value = ee::fpu::divide(0,0);
    check(value.bits == 0x7fffffff && value.invalid && !value.divide_zero,"DIV zero by zero invalid");
    value = ee::fpu::divide(0xbf800000,0);
    check(value.bits == 0xffffffff && value.divide_zero && !value.invalid,"DIV signed zero denominator");
    check(ee::fpu::square_root(0x40000000).bits == 0x3fb504f3,"SQRT hardware numerical log edge");
    check(ee::fpu::square_root(0xffffffff).bits == 0x5fb504f3,"SQRT extended finite range and absolute input");
    check(ee::fpu::square_root(0x80000000).bits == 0,"SQRT negative zero hardware log");
    check(ee::fpu::reciprocal_root(0x3f800000,0x41c80000).bits == 0x3e4ccccd,"RSQRT uses divider recurrence");
    for (const auto [word,a,b,expected] : std::array<std::array<uint32_t,4>,7>{{
        {0x46050084,0,0xbf800000,0x01020041},
        {0x46052083,0,0,0x01020041},
        {0x46052083,0x3f800000,0,0x01010021},
        {0x46052080,0x7f800001,0x7f800001,0x01008011},
        {0x46052082,0x7f7fffff,0x7f7fffff,0x01008011},
        {0x46052083,0x00800000,0x40400000,0x01000001},
        {0x46052083,0x3f800000,0x4040ffff,0x01000001}
    }}) {
        m.state.fpr[4] = a; m.state.fpr[5] = b; m.state.fcr[31] = 0x01000001;
        code(m,{word}); m.step();
        check(m.state.fcr[31] == expected,"published FCR31 situation");
    }
    m.state.fpr[4] = 0x7fffffff; m.state.fpr[5] = 0x7fffffff;
    code(m,{0x4605201a}); m.step(); // MULA.S
    check(m.state.facc == 0x7fffffff && m.state.facc_overflow,"MULA retains accumulator overflow state");
    m.state.fpr[4] = 0; m.state.fpr[5] = 0;
    code(m,{0x4605209c}); m.step(); // MADD.S
    check(m.state.fpr[2] == 0x7fffffff && (m.state.fcr[31]&0x8000),"MADD consumes hidden accumulator overflow state");
    code(m,{0x46052018}); m.step(); // ADDA.S clears hidden overflow
    check(m.state.facc == 0 && !m.state.facc_overflow,"ADDA replaces hidden accumulator state");
}
void float_product_exceptions() {
    // EE instruction manual MADD.S/MADDA.S/MSUB.S/MSUBA.S: product-stage
    // underflow sets SU before the ACC-overflow path selects the result.
    struct Case { uint32_t acc,a,b,result,flags; bool acc_overflow; };
    const std::array cases = {
        Case{0x40000000,0x00800000,0x3f000000,0x40000000,8,false},
        Case{0xc0000000,0x80800000,0x3f000000,0xc0000000,8,false},
        Case{0x7fffffff,0x00800000,0x3f000000,0x7fffffff,0x8018,true},
        Case{0xffffffff,0x80800000,0x3f000000,0xffffffff,0x8018,true},
        Case{0x7fffffff,0x00000001,0x3f000000,0x7fffffff,0x8010,true},
        Case{0xffffffff,0x80000001,0x3f000000,0xffffffff,0x8010,true},
        Case{0x7fffffff,0x3f800000,0x3f800000,0x7fffffff,0x8010,true},
        Case{0xffffffff,0x3f800000,0x3f800000,0xffffffff,0x8010,true},
    };
    for (const auto& test : cases) for (unsigned function : {0x1c,0x1d,0x1e,0x1f}) {
        ee::Machine m;
        m.state.fpr[4] = test.a; m.state.fpr[5] = test.b;
        m.state.facc = test.acc; m.state.facc_overflow = test.acc_overflow;
        m.state.fcr[31] = 0x0103c061; // clear old O/U causes; retain I/D causes and sticky flags
        code(m,{0x46052080 | function}); m.step();
        const bool to_acc = function&2;
        check((to_acc ? m.state.facc : m.state.fpr[2]) == test.result,"COP1 multiply-accumulate selects the documented final result");
        check(m.state.fcr[31] == (0x01030061|test.flags),"COP1 multiply underflow contributes SU even when an overflowed ACC dominates");
        check(m.state.facc_overflow == test.acc_overflow,"COP1 multiply-accumulate retains the selected accumulator overflow state");
    }
}
}

int main() {
    try {
        memory(); integer(); delays(); coprocessor_control(); unaligned(); packed(); traces(); floats(); float_product_exceptions(); replay_and_elf(); vu_transfers_and_integer();
        std::cout << "OK " << checks << " semantic assertions (partial EE harness)\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << "after " << checks << " checks: " << e.what() << '\n'; return 1; }
}
