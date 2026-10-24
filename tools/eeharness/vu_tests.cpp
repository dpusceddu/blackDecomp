#include "vu.hpp"
#include <array>
#include <bit>
#include <cmath>
#include <iostream>

namespace {
unsigned checks = 0;
constexpr uint32_t nop = 0x2ff, lower_nop = 0x8000033c;
void check(bool result,const char* label) { ++checks; if (!result) throw ee::Fault(label); }
uint32_t upper(unsigned function,unsigned dest,unsigned fs,unsigned ft,unsigned mask=15) {
    return mask<<21 | ft<<16 | fs<<11 | dest<<6 | function;
}
uint32_t ext(unsigned function,unsigned fs=0,unsigned ft=0,unsigned mask=0) {
    return 0x80000000 | mask<<21 | ft<<16 | fs<<11 | function;
}
void pair(ee::Machine& m,unsigned pc,uint32_t hi=nop,uint32_t lo=lower_nop) {
    m.memory.write(0x11000000+pc,4,lo); m.memory.write(0x11000004+pc,4,hi);
}
void end(ee::Machine& m,unsigned pc) { pair(m,pc,nop|0x40000000); pair(m,pc+8); }
void flags_and_hazards() {
    ee::Machine m;
    m.state.vf[1].w = {0x3f800000,0x3f800000,0x3f800000,0x3f800000};
    pair(m,0,upper(0x28,2,1,1,8)); // ADD.x
    pair(m,8,upper(0x28,3,2,1,4)); // reads Y, which has no producer
    pair(m,16,upper(0x28,4,2,1,8)); // reads X, waits for the first result
    end(m,24);
    ee::VuEngine e(m.state,m.memory,m.trace);
    e.start(0); e.step();
    check(m.state.vu.cycle == 1 && m.state.vf[2].w[0] == 0,"FMAC vector write is pending");
    check(m.state.vi[17] == 0,"MAC flags do not become visible at issue");
    e.step(); check(m.state.vu.cycle == 2,"unrelated vector lane does not stall");
    e.step(); check(m.state.vu.cycle == 5,"dependent vector lane stalls to producer completion");
    check(m.state.vf[2].w[0] == 0x40000000,"stalled source sees producer value");
    check(e.run(10).stop == ee::Stop::returned,"E bit ends after its delay pair");
    check(m.state.vf[4].w[0] == 0x40400000,"dependent ADD uses the completed source");
    check(m.trace.micro_instructions.size() == 5,"micro coverage contains issued pairs");

    ee::Machine clip;
    clip.state.vf[1].w.fill(0x40000000);
    for (unsigned pc = 0; pc < 32; pc += 8) pair(clip,pc,pc ? nop : upper(0x1ff,0,1,0),0x38010000 | pc/8<<16);
    pair(clip,32,nop,0x38050000); end(clip,40);
    ee::VuEngine c(clip.state,clip.memory,clip.trace); c.start(0);
    check(c.run(100).stop == ee::Stop::returned,"clip pipeline fixture completes");
    check(clip.state.vi[1] == 0 && clip.state.vi[2] == 0 && clip.state.vi[3] == 0 && clip.state.vi[4] == 0,
          "flag readers see four-cycle delay without implicit interlock");
    check(clip.state.vi[5] == 0x15,"clip result visible at the fourth following issue");
    ee::Machine sticky;
    pair(sticky,0,nop,0x2a2007c0); // FSSET 0xfc0: immediate bit 11 is stored at bit 21
    for (unsigned pc = 8; pc < 40; pc += 8) pair(sticky,pc);
    end(sticky,40);
    ee::VuEngine fs(sticky.state,sticky.memory,sticky.trace); fs.start(0); fs.run(100);
    check(sticky.state.vi[16] == 0xfc0,"FSSET split immediate includes DS sticky flag");
}
void simultaneous() {
    ee::Machine m;
    m.state.vf[1].w = {0x3f800000,0x40000000,0x40400000,0x40800000};
    m.state.vf[2].w = {0x40a00000,0x40c00000,0x40e00000,0x41000000};
    // Upper writes VF2.X; lower reads the incoming VF2.X and writes VF3.X.
    pair(m,0,upper(0x28,2,1,1,8),ext(0x33c,2,3,8));
    // A same-register lower write is discarded even on disjoint lanes.
    pair(m,8,upper(0x28,4,1,1,8),ext(0x33c,1,4,1));
    end(m,16);
    ee::VuEngine e(m.state,m.memory,m.trace); e.start(0); e.run(100);
    check(m.state.vf[3].w[0] == 0x40a00000,"lower reads input state before simultaneous upper write");
    check(m.state.vf[4].w[0] == 0x40000000 && m.state.vf[4].w[3] == 0,"upper beats lower at whole-register granularity");
    ee::Machine immediate;
    immediate.state.vi[21] = 0x3f800000;
    pair(immediate,0,upper(0x1e,1,0,0,1)|0x80000000,0x40000000);
    pair(immediate,8,upper(0x1e,2,0,0,1)); end(immediate,16);
    ee::VuEngine i(immediate.state,immediate.memory,immediate.trace); i.start(0); i.run(100);
    check(immediate.state.vf[1].w[3] == 0x3f800000 && immediate.state.vf[2].w[3] == 0x40000000,"LOI affects the next pair's I operand");
}
void memory_and_branch() {
    ee::Machine m;
    m.state.vi[1] = 255;
    m.memory.write(0x11004ff0,4,0x12345678);
    pair(m,0,nop,ext(0x37c,1,2,8)); // LQI.x VF2,(VI1++)
    pair(m,8,nop,ext(0x3fc,2,3)); // MTIR VI3,VF2.x, stalls on VF
    end(m,16);
    ee::VuEngine e(m.state,m.memory,m.trace); e.start(0); e.run(100);
    check(m.state.vi[1] == 256 && m.state.vf[2].w[0] == 0x12345678,"VU LQI address and postincrement");
    check(m.state.vi[3] == 0x5678,"MTIR truncates a completed vector lane");

    for (bool bypass : {false,true}) {
        ee::Machine branch;
        branch.state.vi[1] = 1;
        // ALU changes VI1 to zero; an immediately following branch reads the
        // backup. A flag check has its documented direct branch bypass.
        pair(branch,0,nop,bypass ? 0x2c010000 : ext(0x32,0,1));
        pair(branch,8,nop,0x50000802); // IBEQ VI1,VI0,+2
        pair(branch,16);
        pair(branch,24,nop,ext(0x32 | 1<<6,0,2));
        end(branch,32);
        ee::VuEngine b(branch.state,branch.memory,branch.trace); b.start(0); b.run(100);
        check(branch.state.vi[2] == unsigned(!bypass),"conditional branch ALU backup versus flag-check bypass");
    }
}
void conversion_and_random() {
    ee::Machine m;
    m.state.vf[1].w = {0x7fffffff,0x80000000,0xffffffff,65536};
    pair(m,0,upper(0x13c,0,1,2)); // ITOF0 VF2,VF1
    pair(m,8,upper(0x17d,0,2,3)); // FTOI4 VF3,VF2
    end(m,16);
    ee::VuEngine e(m.state,m.memory,m.trace); e.start(0); e.run(100);
    check(m.state.vf[2].w[0] == 0x4effffff && m.state.vf[2].w[1] == 0xcf000000,"VU fixed-to-float signed/truncated boundary");
    check(m.state.vf[3].w[0] == 0x7fffffff && m.state.vf[3].w[1] == 0x80000000,"VU scaled float-to-fixed saturation");
    check(m.state.vf[3].w[2] == 0xfffffff0 && m.state.vf[3].w[3] == 1048576,"VU fixed-point fraction scaling");
    ee::Machine rng;
    rng.state.vf[1].w[0] = 0x01234567;
    pair(rng,0,nop,ext(0x43e,1));
    for (unsigned i = 0; i < 4; ++i) pair(rng,(i+1)*8,nop,ext(0x43c,0,i+2,15));
    end(rng,40);
    ee::VuEngine r(rng.state,rng.memory,rng.trace); r.start(0); r.run(100);
    const std::array<uint32_t,4> expected = {0x3fc68ace,0x3f8d159d,0x3f9a2b3b,0x3fb45677};
    for (unsigned i = 0; i < 4; ++i) check(rng.state.vf[i+2].w[0] == expected[i],"published RNEXT sequence");
    ee::Machine minmax;
    minmax.state.vf[1].w = {0xbf800000,0,0x40000000,0x7fffffff};
    minmax.state.vf[2].w = {0x3f800000,0x80000000,0x3f800000,0xff800000};
    pair(minmax,0,upper(0x2b,3,1,2)); pair(minmax,8,upper(0x2f,4,1,2)); end(minmax,16);
    ee::VuEngine mm(minmax.state,minmax.memory,minmax.trace); mm.start(0); mm.run(100);
    check(minmax.state.vf[3].w == std::array<uint32_t,4>{0x3f800000,0,0x40000000,0x7fffffff},"VMAX uses component-wise second register");
    check(minmax.state.vf[4].w == std::array<uint32_t,4>{0xbf800000,0x80000000,0x3f800000,0xff800000},"VMINI uses second register rather than I");
    ee::Machine cross;
    cross.state.vf[1].w = {0x3f800000,0x40000000,0x40400000,0x40800000};
    cross.state.vf[2].w = {0x40800000,0x40a00000,0x40c00000,0x40e00000};
    pair(cross,0,upper(0x2fe,0,1,2)); pair(cross,8,upper(0x2e,3,2,1)); end(cross,16);
    ee::VuEngine cp(cross.state,cross.memory,cross.trace); cp.start(0); cp.run(100);
    check(cross.state.vf[3].w == std::array<uint32_t,4>{0xc0400000,0x40c00000,0xc0400000,0},"outer-product pair preserves native operand order and W");
}
void outer_product_and_normalization() {
    // VU User's Manual 6.0, pp. 116-117 and 305-306: both operations
    // multiply (fs.y*ft.z, fs.z*ft.x, fs.x*ft.y). The second operation's
    // register operands are reversed to obtain a vector cross product.
    for (bool macro : {false,true}) {
        const auto execute = [macro](ee::Machine& m,const std::vector<uint32_t>& words) {
            if (macro) {
                unsigned pc = 0x1000;
                for (auto word : words) { m.memory.write(pc,4,0x4a000000|word); pc += 4; }
                m.memory.write(pc,4,0x03e00008); m.memory.write(pc+4,4,0);
                check(m.call(0x1000,100).stop == ee::Stop::returned,"macro outer-product fixture returns");
                ee::VuEngine engine(m.state,m.memory,m.trace); engine.drain();
            } else {
                unsigned pc = 0;
                for (auto word : words) { pair(m,pc,word); pc += 8; }
                end(m,pc);
                ee::VuEngine engine(m.state,m.memory,m.trace); engine.start(0);
                check(engine.run(100).stop == ee::Stop::returned,"micro outer-product fixture returns");
            }
        };
        const auto inputs = [](ee::Machine& m) {
            m.state.vf[1].w = {0x3f800000,0x40000000,0x40400000,0x40800000}; // (1,2,3,4)
            m.state.vf[2].w = {0x40800000,0x40a00000,0x40c00000,0x40e00000}; // (4,5,6,7)
            m.state.vf[3].w[3] = 0x12345678;
        };
        ee::Machine subtract;
        inputs(subtract);
        subtract.state.vacc.w = {0x41a00000,0x41f00000,0x42200000,0x76543210}; // (20,30,40)
        execute(subtract,{upper(0x2e,3,1,2,14)});
        check(subtract.state.vf[3].w == std::array<uint32_t,4>{0x41000000,0x41900000,0x420c0000,0x12345678},
              "OPMSUB independently subtracts (12,12,5) from (20,30,40)");
        check(subtract.state.vacc.w == std::array<uint32_t,4>{0x41a00000,0x41f00000,0x42200000,0x76543210},
              "OPMSUB preserves the supplied accumulator");
        ee::Machine cancel;
        inputs(cancel);
        execute(cancel,{upper(0x2fe,0,1,2,14),upper(0x2e,3,1,2,14)});
        check(cancel.state.vf[3].w == std::array<uint32_t,4>{0,0,0,0x12345678},
              "the same operand order cancels the outer-product accumulator");
        check(cancel.state.vi[17] == 14,"outer-product cancellation sets all XYZ zero flags");
        for (unsigned destination : {1u,2u,3u}) {
            ee::Machine cross;
            inputs(cross);
            const auto untouched = cross.state.vf[destination].w[3];
            execute(cross,{upper(0x2fe,0,1,2,14),upper(0x2e,destination,2,1,14)});
            check(cross.state.vf[destination].w == std::array<uint32_t,4>{0xc0400000,0x40c00000,0xc0400000,untouched},
                  "(1,2,3) crossed with (4,5,6) is (-3,6,-3), including aliased destinations");
            check(cross.state.vi[17] == 0xa0,"cross product reports negative X/Z with no zero lanes");
        }
    }
    ee::Machine normal;
    normal.state.vf[1].w = {0,0xc0800000,0x40400000,0}; // (0,-4,3)
    normal.state.vf[2].w = {0x3f800000,0,0,0}; // (1,0,0)
    normal.state.vf[3].w[3] = 0x12345678;
    pair(normal,0,upper(0x2fe,0,1,2,14));
    pair(normal,8,upper(0x2e,3,2,1,14)); // cross = (0,3,4)
    pair(normal,16,upper(0x2a,4,3,3,14));
    pair(normal,24,upper(0x01,5,4,4,8));
    pair(normal,32,upper(0x02,5,5,4,8)); // length squared = 25
    pair(normal,40,nop,ext(0x3be,0,5,3)); // RSQRT Q,VF0.w,VF5.x
    pair(normal,48,nop,ext(0x3bf)); // WAITQ
    pair(normal,56,upper(0x1c,3,3,0,14)); // MULq.xyz
    end(normal,64);
    ee::VuEngine engine(normal.state,normal.memory,normal.trace); engine.start(0);
    check(engine.run(100).stop == ee::Stop::returned,"cross-product normalization fixture returns");
    check(normal.state.vf[5].w[0] == 0x41c80000,"nondegenerate cross product has squared length 25");
    const auto x = std::bit_cast<float>(normal.state.vf[3].w[0]);
    const auto y = std::bit_cast<float>(normal.state.vf[3].w[1]);
    const auto z = std::bit_cast<float>(normal.state.vf[3].w[2]);
    check(x == 0 && std::abs(y-0.6f) < 0.000001f && std::abs(z-0.8f) < 0.000001f,
          "cross-product normalization produces the independent 3-4-5 unit vector");
    check(std::abs(x*x+y*y+z*z-1.0f) < 0.000002f,"normalized cross product has unit length");
    check(normal.state.vf[3].w[3] == 0x12345678,"normalization preserves the unselected W lane");
}
void replay_and_termination() {
    ee::Machine m;
    m.state.vf[1].w[3] = 0x40800000;
    pair(m,0,nop,ext(0x3bc,0,1,15)); pair(m,8,upper(0x1c,2,0,0));
    pair(m,16,upper(0x1c,3,0,0),ext(0x3bf)); end(m,24);
    ee::VuEngine e(m.state,m.memory,m.trace); e.start(0); e.step();
    auto replay = m;
    ee::VuEngine r(replay.state,replay.memory,replay.trace);
    const auto a = e.run(100), b = r.run(100);
    check(a.stop == ee::Stop::returned && b.stop == ee::Stop::returned && m.state == replay.state,"snapshot retains pending Q and pipeline state");
    check(m.state.vf[2].w[3] == 0 && m.state.vf[3].w[3] == 0x3e800000,"Q stays old until WAITQ");
    ee::Machine bounded;
    pair(bounded,0,nop,0x400007ff); pair(bounded,8);
    ee::VuEngine loop(bounded.state,bounded.memory,bounded.trace); loop.start(0);
    check(loop.run(20).stop == ee::Stop::budget,"micro infinite loop is bounded");
    for (bool enabled : {false,true}) {
        ee::Machine debug;
        debug.state.vi[28] = enabled ? 4 : 0;
        pair(debug,0,nop|0x10000000);
        pair(debug,8,nop,ext(0x32 | 1<<6,0,1)); end(debug,16);
        ee::VuEngine d(debug.state,debug.memory,debug.trace); d.start(0); d.run(100);
        check(debug.state.vi[1] == unsigned(!enabled),"D bit requires its FBRST enable and has no ordinary delay slot");
        check(debug.state.vu.stopped == enabled,"debug stop distinguished from E termination");
    }
    ee::Machine debug_branch;
    debug_branch.state.vi[28] = 8;
    pair(debug_branch,0,nop|0x08000000,0x40000003);
    pair(debug_branch,8,nop,ext(0x32 | 1<<6,0,1));
    ee::VuEngine db(debug_branch.state,debug_branch.memory,debug_branch.trace); db.start(0); db.run(100);
    check(debug_branch.state.vi[1] == 1 && debug_branch.state.vi[26] == 4,"T-bit branch executes its delay pair and stores branch target in TPC");
    ee::Machine mbit;
    pair(mbit,0,nop|0x20000000); pair(mbit,8); end(mbit,16);
    ee::VuEngine mb(mbit.state,mbit.memory,mbit.trace); mb.start(0);
    mb.run(1,true);
    check(mbit.state.vu_micro_running && mbit.state.vu.m_seen,"M bit releases an interlock without ending the microprogram");
    mb.run(1);
    check(mbit.state.vu.m_seen,"M transfer window remains latched during micro execution");
}
void deadlines() {
    ee::Machine m;
    m.memory.write(0x11004000,4,0x12345678);
    pair(m,0,nop,ext(0x37c,1,2,8)); // load VF2.x
    pair(m,8,nop,ext(0x3fc,2,3)); // waits for the loaded lane
    pair(m,16,nop,0x03001001); // SQ.x VF2,1(VI0)
    end(m,24);
    ee::VuEngine e(m.state,m.memory,m.trace); e.start(0);
    auto replay = m;
    e.catch_up(2);
    check(m.state.vu.issued == 1 && m.state.vu.cycle == 2,"catch-up does not issue beyond a dependency deadline");
    check(m.state.vi[3] == 0 && m.trace.writes.empty(),"future register and memory effects remain unpublished");
    e.catch_up(4);
    check(m.state.vu.issued == 1 && m.state.vf[2].w[0] == 0x12345678,"producer writeback occurs at deadline without next issue");
    e.catch_up(5);
    check(m.state.vi[3] == 0x5678 && m.trace.writes.empty(),"consumer issues when its dependency is ready");
    e.catch_up(6);
    check(m.memory.read(0x11004010,4) == 0x12345678 && !m.trace.writes.empty(),"store appears only when its pair issues");
    ee::VuEngine r(replay.state,replay.memory,replay.trace); r.run(3);
    check(m.state == replay.state && m.trace == replay.trace,"incremental catch-up replays the same issued prefix");
    ee::Machine ending;
    ending.state.vf[1].w.fill(0x3f800000);
    pair(ending,0,upper(0x28,2,1,1)|0x40000000); pair(ending,8);
    ee::VuEngine fin(ending.state,ending.memory,ending.trace); fin.start(0); fin.catch_up(2);
    check(!ending.state.vu_micro_running && ending.state.vf[2].w[0] == 0,"ending does not publish future FMAC writeback during catch-up");
    fin.interlock();
    check(ending.state.vf[2].w[0] == 0x40000000 && ending.state.vu.cycle == 4,"completion interlock drains the final micro result");
}
void ee_integration() {
    const auto code = [](ee::Machine& m,std::initializer_list<uint32_t> words) {
        unsigned pc = 0x1000;
        for (auto word : words) { m.memory.write(pc,4,word); pc += 4; }
        m.state.start(0x1000);
    };
    ee::Machine read;
    read.state.vf[1].w.fill(0x3f800000);
    pair(read,0,upper(0x28,2,1,1)); end(read,8);
    code(read,{0x4a000038,0x48231000,0x48241001});
    read.step();
    check(read.state.vu_micro_running && read.state.vu.issued == 0,"VCALLMS launches an asynchronous microprogram");
    read.step();
    check(read.state.gpr[3].w[0] == 0 && read.state.vu_micro_running,"QMFC2.ni reads current state without draining micro writes");
    read.step();
    check(read.state.gpr[4].w[0] == 0x40000000 && !read.state.vu_micro_running,"QMFC2.i sees the final micro result");

    ee::Machine control;
    pair(control,0,nop,ext(0x32 | 5<<6,0,1)); end(control,8);
    code(control,{0x4a000038,0x48430800,0x48440801});
    control.step(); control.step();
    check(control.state.gpr[3].low() == 5 && control.state.vu_micro_running,"CFC2.ni observes an issued integer result while micro remains active");
    control.step();
    check(control.state.gpr[4].low() == 5 && !control.state.vu_micro_running,"CFC2.i waits for completion");

    for (bool interlocked : {false,true}) for (bool vector : {false,true}) {
        ee::Machine write;
        write.state.gpr[2].w.fill(0x1234);
        pair(write,0); pair(write,8,nop|0x20000000);
        pair(write,16,nop|0x20000000); pair(write,24,nop|0x60000000); pair(write,32,nop|0x20000000);
        code(write,{0x4a000038,(vector ? 0x48a20800u : 0x48c20800u) | unsigned(interlocked)});
        write.step(); write.step();
        check(write.state.vu_micro_running && write.state.vu.issued == (interlocked ? 2u : 1u),"write transfer applies the selected M interlock");
        check(vector ? write.state.vf[1].w[0] == 0x1234 : write.state.vi[1] == 0x1234,"EE write reaches its selected VU bank");
        if (interlocked) {
            check(write.state.vu.m_seen,"M window remains latched for following interlocked transfers");
            code(write,{(vector ? 0x48a21001u : 0x48c21001u)}); write.step();
            check(write.state.vu.issued == 3 && write.state.vu_micro_running,"a following write proceeds within the open M window");
        }
    }
    ee::Machine macro;
    macro.state.vf[1].w.fill(0x3f800000);
    pair(macro,0,upper(0x28,2,1,1)); end(macro,8);
    code(macro,{0x4a000038,0x4a000000 | upper(0x28,3,2,1),0x48241800});
    macro.step(); macro.step();
    check(!macro.state.vu_micro_running,"macro arithmetic interlocks with an active microprogram");
    macro.step();
    check(macro.state.gpr[4].w[0] == 0x40400000,"macro arithmetic consumes micro results and QMFC2.ni waits for macro writeback");

    ee::Machine indirect;
    indirect.state.vi[27] = 4;
    pair(indirect,32,nop|0x40000000,ext(0x32 | 7<<6,0,1)); pair(indirect,40);
    code(indirect,{0x4a000039,0x48430801}); indirect.step(); indirect.step();
    check(indirect.state.gpr[3].low() == 7 && indirect.state.vi[26] == 6,"VCALLMSR uses CMSAR0 units and preserves final TPC");

    ee::Machine transfers;
    transfers.state.gpr[2].low(0x2000);
    transfers.state.vf[1].w.fill(0x3f800000);
    ee::Quad payload; payload.w = {1,2,3,4}; transfers.memory.write_quad(0x2010,payload);
    pair(transfers,0,upper(0x28,2,1,1));
    pair(transfers,8); pair(transfers,16); end(transfers,24);
    code(transfers,{0x4a000038,0xf8420000,0xd8430010}); // SQC2 VF2; LQC2 VF3
    transfers.step(); transfers.step();
    check(transfers.memory.read_quad(0x2000) == ee::Quad{} && transfers.state.vu_micro_running,"SQC2 does not wait for a micro producer");
    transfers.step();
    check(transfers.state.vf[3] == payload && transfers.state.vu_micro_running,"LQC2 transfers while micro is active");
    auto cloned = transfers;
    code(transfers,{0x48241001}); code(cloned,{0x48241001}); transfers.step(); cloned.step();
    check(transfers.state == cloned.state && transfers.trace == cloned.trace,"EE replay retains concurrent micro clocks and pending writes");
}
void edge_flags_and_control() {
    // Sony's documented operand-order asymmetry, with the 129.5 hardware
    // observation published at fobes.dev/ps2/detecting-emu-vu-floats.
    ee::Machine asymmetric;
    asymmetric.state.vf[1].w.fill(0x3f800000); asymmetric.state.vf[2].w.fill(0x43018000);
    pair(asymmetric,0,upper(0x2a,3,1,2)); pair(asymmetric,8,upper(0x2a,4,2,1)); end(asymmetric,16);
    ee::VuEngine as(asymmetric.state,asymmetric.memory,asymmetric.trace); as.start(0); as.run(100);
    check(asymmetric.state.vf[3].w[0] == 0x43017fff,"VU 1 * 129.5 loses the published last bit");
    check(asymmetric.state.vf[4].w[0] == 0x43018000,"VU 129.5 * 1 preserves its multiplicand exactly");
    ee::Machine arithmetic;
    arithmetic.state.vf[1].w = {0x00800000,0x7fffffff,0xbf800000,0x80000000};
    arithmetic.state.vf[2].w = {0x3f000000,0x40000000,0x3f800000,0x3f800000};
    pair(arithmetic,0,upper(0x2a,3,1,2)); end(arithmetic,8);
    ee::VuEngine a(arithmetic.state,arithmetic.memory,arithmetic.trace); a.start(0); a.run(100);
    check(arithmetic.state.vf[3].w == std::array<uint32_t,4>{0,0x7fffffff,0xbf800000,0x80000000},
          "VU FMAC underflow, finite exponent 255, overflow clamp and signed zero");
    check(arithmetic.state.vi[17] == 0x4839 && arithmetic.state.vi[16] == 0x3cf,
          "VU lane MAC flags reduce into current and sticky status flags");

    for (unsigned operation : {0x3bcu,0x3bdu,0x3beu}) {
        ee::Machine invalid;
        invalid.state.vf[1].w[0] = 0;
        invalid.state.vf[2].w[0] = operation == 0x3bd ? 0xbf800000 : 0;
        pair(invalid,0,nop,ext(operation,1,2)); end(invalid,8);
        ee::VuEngine i(invalid.state,invalid.memory,invalid.trace); i.start(0); i.run(100);
        check((invalid.state.vi[16]&0xc30) == 0x410,"VU invalid division or negative root sets I/IS without D/DS");
        check(invalid.state.vi[22] == (operation == 0x3bd ? 0x3f800000u : 0x7fffffffu),"VU invalid Q result uses magnitude root or maximum");
    }
    ee::Machine divide;
    divide.state.vf[1].w[0] = 0xbf800000;
    pair(divide,0,nop,ext(0x3bc,1,2)); end(divide,8);
    ee::VuEngine d(divide.state,divide.memory,divide.trace); d.start(0); d.run(100);
    check(divide.state.vi[22] == 0xffffffff && (divide.state.vi[16]&0xc30) == 0x820,"VU division by zero preserves result sign and sets D/DS");

    ee::Machine control;
    control.state.vf[1].w.fill(0x3f800000);
    pair(control,0,upper(0x28,2,1,1)); pair(control,8); end(control,16);
    ee::VuEngine c(control.state,control.memory,control.trace); c.start(0); c.step();
    control.state.vi[16] = 0xfff; control.state.vi[17] = 0xffff; control.state.vi[18] = 0xffffff;
    control.state.gpr[2].low(0x30e); // reset VU0/VU1, enable bits initially set
    control.memory.write(0x1000,4,0x48c2e000); control.state.start(0x1000); control.step();
    check(!control.state.vu_micro_running && control.state.vu.pending.empty() && !control.state.vu.stopped,"FBRST reset discards pending computation and returns VU0 to ready");
    check(control.state.vi[16] == 0 && control.state.vi[17] == 0 && control.state.vi[18] == 0 && control.state.vi[28] == 0,
          "FBRST resets flags and debug enables while command bits read zero");
    check(control.state.vf[1].w[0] == 0x3f800000 && control.state.vf[2].w[0] == 0,"reset preserves supplied unspecified data registers without completing canceled writes");
    check(control.trace.events.back().kind == ee::EventKind::vu_control && control.trace.events.back().default_response,
          "VU1 reset is recorded as an external device command");
    c.start(0); c.step();
    control.state.gpr[2].low(1);
    control.state.start(0x1000); control.step();
    check(control.state.vu.stopped && !control.state.vu_micro_running && (control.state.vi[29]&15) == 8,
          "force break enters stop with VFS0 status");
    c.start(16);
    check(control.state.vu_micro_running && (control.state.vi[29]&15) == 1,"VCALL restart clears stop reasons and sets busy");
    c.interlock();
    control.state.gpr[2].low(0x12345);
    control.memory.write(0x1000,4,0x48c2f800); control.state.start(0x1000); control.step();
    check(control.state.vi[31] == 0x2345 && control.trace.events.back().address == 31 && control.trace.events.back().default_response,
          "CMSAR1 retains its address and records the VU1 execution stub");
}
void product_sum_flags() {
    // Literal cases from the flag rules in VU manual 3.3.6. Multiplication
    // contributes ZS/SS/US/OS even when ACC dominates the final result.
    struct Case { uint32_t acc,a,b,result,mac,status; bool acc_overflow=false,subtract=false; };
    const std::array cases = {
        Case{0x3f800000,0,0x3f800000,0x3f800000,0,0x40},
        Case{0x40000000,0xbf800000,0x3f800000,0x3f800000,0,0x80},
        Case{0x3f800000,0x00800000,0x3f000000,0x3f800000,0,0x140},
        Case{0xbf800000,0x80800000,0x3f000000,0xbf800000,0x80,0x1c2},
        Case{0x7fffffff,0,0x3f800000,0x7fffffff,0x8000,0x248,true},
        Case{0x7fffffff,0xbf800000,0x3f800000,0x7fffffff,0x8000,0x288,true},
        Case{0xffffffff,0x3f800000,0x3f800000,0xffffffff,0x8080,0x28a,true},
        Case{0xffffffff,0,0x3f800000,0xffffffff,0x8080,0x2ca,true},
        Case{0x7fffffff,0x00800000,0x3f000000,0x7fffffff,0x8000,0x348,true},
        Case{0xffffffff,0x80800000,0x3f000000,0xffffffff,0x8080,0x3ca,true},
        Case{0x3f800000,0x7fffffff,0x40000000,0x7fffffff,0x8000,0x208},
        Case{0x3f800000,0xffffffff,0x40000000,0xffffffff,0x8080,0x28a},
        Case{0x3f800000,0x7fffffff,0x40000000,0xffffffff,0x8080,0x28a,false,true},
        Case{0x3f800000,0xffffffff,0x40000000,0x7fffffff,0x8000,0x288,false,true},
        Case{0x7fffffff,0x7fffffff,0x3f800000,0x7fffffff,0x8000,0x208},
        Case{0x00800001,0x80800000,0x3f800000,0,0x808,0x1c5},
        Case{0x80800001,0x00800000,0x3f800000,0x80000000,0x888,0x1c7},
        Case{0x80000000,0,0xbf800000,0x80000000,0x88,0xc3},
    };
    for (const auto& test : cases) for (bool macro : {false,true}) for (bool to_acc : {false,true}) {
        ee::Machine m;
        m.state.vf[1].w[0] = test.a; m.state.vf[2].w[0] = test.b;
        m.state.vacc.w[0] = test.acc; m.state.vu.accumulator_overflow[0] = test.acc_overflow;
        m.state.vi[16] = 0xc30; // FDIV current/sticky fields survive FMAC work.
        const uint32_t function = to_acc ? (test.subtract ? 0x2fd : 0x2bd) : (test.subtract ? 0x2d : 0x29);
        const auto word = upper(function,to_acc ? 0 : 3,1,2,8);
        if (macro) {
            m.memory.write(0x1000,4,0x4a000000|word);
            m.state.start(0x1000); m.step();
            ee::VuEngine engine(m.state,m.memory,m.trace); engine.drain();
        } else {
            pair(m,0,word); end(m,8);
            ee::VuEngine engine(m.state,m.memory,m.trace); engine.start(0); engine.run(100);
        }
        check((to_acc ? m.state.vacc.w[0] : m.state.vf[3].w[0]) == test.result,"MADD/MSUB numeric result across result and accumulator forms");
        check(m.state.vi[17] == test.mac,"MADD/MSUB MAC flags describe the final result only");
        check(m.state.vi[16] == (test.status|0xc30),"MADD/MSUB sticky flags include product and final stages without changing FDIV fields");
    }
}
void concurrent_flag_writeback() {
    ee::Machine m;
    m.state.vf[1].w[0] = 0x3f800000;
    m.state.vf[3].w[0] = 0xbf800000;
    m.state.vf[4].w[0] = 0x3f800000;
    m.state.vacc.w[0] = 0x40000000;
    // FDIV commits after seven clocks; FSSET and FMAC commit after four.
    // Each producer changes only its own current flags and accumulates into
    // the sticky flags present at writeback, including another unit's writes.
    pair(m,0,nop,ext(0x3bc,1,2)); // DIV +1/0: D/DS at clock 7
    pair(m,8,nop,0x2a000000); // FSSET 0: clear sticky flags at clock 5
    pair(m,16,upper(0x29,5,3,4,8)); // MADD +2 + (-1*1): SS at clock 6
    for (unsigned cycle = 3; cycle <= 7; ++cycle)
        pair(m,cycle*8,nop,0x2c2007ff | (cycle+1)<<16); // FSAND all flags
    pair(m,64,nop,ext(0x3bd,0,1)); // SQRT +1: clears current D at clock 15
    for (unsigned cycle = 9; cycle <= 15; ++cycle)
        pair(m,cycle*8,cycle == 9 ? upper(0x28,6,0,0,8) : nop,0x2c2007ff | cycle<<16);
    end(m,128);
    ee::VuEngine engine(m.state,m.memory,m.trace); engine.start(0);
    check(engine.run(100).stop == ee::Stop::returned,"concurrent flag-writeback fixture returns");
    for (unsigned reg = 4; reg <= 6; ++reg)
        check(m.state.vi[reg] == 0,"flag readers observe producer latency without an implicit stall");
    check(m.state.vi[7] == 0x80,"product SS reaches status before the pending FDIV result");
    for (unsigned reg = 8; reg <= 12; ++reg)
        check(m.state.vi[reg] == 0x8a0,"FDIV preserves FMAC sticky flags when its D/DS result arrives");
    check(m.state.vi[13] == 0x8e1 && m.state.vi[14] == 0x8e1,"later FMAC preserves D/DS and accumulates Z/ZS");
    check(m.state.vi[15] == 0x8c1,"successful SQRT clears current D while preserving earlier sticky flags");
    check(m.state.vi[22] == 0x3f800000 && m.state.vi[17] == 8,"FDIV and FMAC commit separate result registers");
}
void macro_hazards() {
    const auto code = [](ee::Machine& m,std::initializer_list<uint32_t> words) {
        unsigned pc = 0x1000;
        for (auto word : words) { m.memory.write(pc,4,word); pc += 4; }
        m.state.start(0x1000);
    };
    const auto add = [](unsigned dest,unsigned fs,unsigned ft,unsigned mask) {
        return 0x4a000000 | upper(0x28,dest,fs,ft,mask);
    };
    for (bool destination : {false,true}) {
        ee::Machine m;
        m.state.vf[1].w.fill(0x3f800000);
        m.state.vf[2].w[1] = 0x40a00000;
        code(m,{add(2,1,1,8),destination ? add(2,1,1,4) : add(3,2,1,4)});
        m.step();
        auto replay = m;
        m.step(); replay.step();
        check(m.state.vu.cycle == 5,"macro RAW/WAW checks use whole register numbers across disjoint lanes");
        ee::VuEngine engine(m.state,m.memory,m.trace); engine.drain();
        check(m.state.vf[2].w[0] == 0x40000000 &&
              (destination ? m.state.vf[2].w[1] == 0x40000000 : m.state.vf[3].w[1] == 0x40c00000),
              "macro disjoint-lane RAW/WAW interlocks preserve numerical results");
        ee::VuEngine other(replay.state,replay.memory,replay.trace); other.drain();
        check(m.state == replay.state && m.trace == replay.trace,"macro hazard replay retains pending register writes");
    }
    for (unsigned transfer : {0x48a51000u,0xd8820000u,0x48c51000u}) {
        ee::Machine m;
        m.state.vf[1].w.fill(0x3f800000);
        m.state.gpr[4].low(0x2000);
        m.state.gpr[5].w = {0x12345678,0x9abcdef0,0x13579bdf,0x2468ace0};
        m.memory.write_quad(0x2000,m.state.gpr[5]);
        code(m,{add(2,1,1,8),transfer}); m.step(); m.step();
        const bool interlocked = m.state.ee_cycle == 5;
        ee::VuEngine engine(m.state,m.memory,m.trace); engine.drain();
        check(transfer == 0x48c51000 ? m.state.vi[2] == 0x5678 : m.state.vf[2] == m.state.gpr[5],
              "an older macro result cannot overwrite the later EE transfer");
        check(interlocked,"EE transfer waits for a macro destination WAW hazard, including VF/VI number aliases");
    }
    for (unsigned consumer : {0x48451000u,0x4a031072u}) {
        ee::Machine m;
        m.state.vf[1].w.fill(0x3f800000); m.state.vi[2] = 10;
        code(m,{add(2,1,1,8),consumer}); m.step(); m.step();
        check(m.state.ee_cycle == 5,"integer macro/EE readers share the pending VF register number hazard");
        check(consumer == 0x48451000 ? m.state.gpr[5].low() == 10 : m.state.vi[3] == 11,
              "register-number interlocks preserve the selected VI operand");
    }
    for (unsigned consumer : {0x48451000u,0x48c51000u,0x48251000u,0x48a51000u}) {
        ee::Machine m;
        m.state.gpr[5].w.fill(0x1234);
        m.memory.write(0x11004000,4,0x3f800000);
        code(m,{0x4a000000 | upper(0x37c,0,2,3,8),consumer}); // VLQI.x VF3,(VI2++)
        m.step();
        check(m.state.vi[2] == 0,"macro address update stays pending with its load result");
        m.step();
        check(m.state.ee_cycle == 5,"EE vector/integer reads and writes wait for a macro address update with the same register number");
        ee::VuEngine engine(m.state,m.memory,m.trace); engine.drain();
        if (consumer == 0x48451000) check(m.state.gpr[5].low() == 1,"CFC2 sees the completed macro postincrement");
        if (consumer == 0x48c51000) check(m.state.vi[2] == 0x1234,"CTC2 supersedes the completed macro postincrement");
        if (consumer == 0x48a51000) check(m.state.vf[2] == m.state.gpr[5],"QMTC2 writes after an aliased VI producer completes");
    }
    for (bool clip : {false,true}) {
        ee::Machine m;
        m.state.vf[1].w.fill(0x40000000);
        m.state.gpr[5].low(clip ? 0x123456 : 0);
        code(m,{clip ? 0x4a000000 | upper(0x1ff,0,1,0) : add(2,0,0,8),clip ? 0x48c59000u : 0x48c58000u});
        m.step(); m.step();
        check(m.state.ee_cycle == 5,"EE flag write waits for the preceding macro flag result");
        ee::VuEngine engine(m.state,m.memory,m.trace); engine.drain();
        check(clip ? m.state.vi[18] == 0x123456 && m.state.vu.clip_history == 0x123456 : m.state.vi[16] == 1,
              "older macro flags cannot undo the later EE flag write");
    }
    ee::Machine independent;
    independent.state.vf[1].w.fill(0x3f800000);
    independent.state.gpr[5].w.fill(0x1234);
    code(independent,{add(2,1,1,8),0x48a52000}); independent.step(); independent.step();
    check(independent.state.ee_cycle == 2 && independent.state.vf[2].w[0] == 0,
          "EE transfer to a different register leaves unrelated macro work pending");

    ee::Machine micro;
    micro.state.vf[1].w.fill(0x3f800000); micro.state.gpr[5].w.fill(0x1234);
    pair(micro,0,upper(0x28,2,1,1,8)); end(micro,8);
    code(micro,{0x4a000038,0x48a51000}); micro.step(); micro.step();
    check(micro.state.ee_cycle == 2 && micro.state.vu_micro_running && micro.state.vf[2] == micro.state.gpr[5],
          "noninterlocked EE writes do not acquire macro-only waits from micro producers");
}
}

int main() {
    try {
        flags_and_hazards(); simultaneous(); memory_and_branch(); conversion_and_random(); outer_product_and_normalization(); replay_and_termination(); deadlines(); ee_integration(); edge_flags_and_control(); product_sum_flags(); concurrent_flag_writeback(); macro_hazards();
        std::cout << "OK " << checks << " VU semantic assertions\n";
        return 0;
    } catch (const std::exception& error) { std::cerr << "after " << checks << " VU checks: " << error.what() << '\n'; return 1; }
}
