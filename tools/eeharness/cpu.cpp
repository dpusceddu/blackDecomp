#include "ee.hpp"
#include "fpu.hpp"
#include "vu.hpp"

#include <algorithm>
#include <bit>
#include <iomanip>
#include <limits>
#include <sstream>

namespace ee {
namespace {
uint64_t sign32(uint32_t x) { return uint64_t(int64_t(std::bit_cast<int32_t>(x))); }
int64_t signed64(uint64_t x) { return std::bit_cast<int64_t>(x); }
int32_t signed32(uint32_t x) { return std::bit_cast<int32_t>(x); }
uint64_t arithmetic_right(uint64_t x, unsigned shift, unsigned width) {
    const uint64_t mask = width == 64 ? ~uint64_t(0) : 0xffffffff;
    x &= mask;
    if (!shift) return x;
    return (x >> shift) | ((x & (uint64_t(1) << (width-1))) ? mask ^ (mask >> shift) : 0);
}
uint64_t checked_add(uint64_t a, uint64_t b, unsigned width, bool subtract) {
    const uint64_t sign = uint64_t(1) << (width-1);
    const uint64_t result = subtract ? a-b : a+b;
    if (((subtract ? a^b : ~(a^b)) & (a^result) & sign) != 0)
        throw Fault("integer arithmetic overflow");
    return width == 32 ? sign32(uint32_t(result)) : result;
}
void product(State& s, unsigned bank, unsigned dest, uint32_t a, uint32_t b, bool unsign, bool add) {
    uint64_t v = unsign ? uint64_t(a)*b : uint64_t(int64_t(signed32(a))*signed32(b));
    const unsigned i = bank*2;
    if (add) v += uint64_t(s.lo.w[i]) | (uint64_t(s.hi.w[i]) << 32);
    const uint64_t low = sign32(uint32_t(v)), high = sign32(uint32_t(v >> 32));
    if (bank) { s.lo.high(low); s.hi.high(high); }
    else { s.lo.low(low); s.hi.low(high); }
    if (dest) s.gpr[dest].low(low);
}
void quotient(State& s, unsigned bank, uint32_t a, uint32_t b, bool unsign) {
    uint32_t q, r;
    if (unsign) {
        q = b ? a/b : 0xffffffff;
        r = b ? a%b : a;
    } else if (!b) {
        q = signed32(a) < 0 ? 1 : 0xffffffff;
        r = a;
    } else if (a == 0x80000000 && b == 0xffffffff) {
        q = a; r = 0;
    } else {
        q = uint32_t(signed32(a)/signed32(b)); r = uint32_t(signed32(a)%signed32(b));
    }
    if (bank) { s.lo.high(sign32(q)); s.hi.high(sign32(r)); }
    else { s.lo.low(sign32(q)); s.hi.low(sign32(r)); }
}
} // namespace

void Machine::branch(bool condition, bool likely, uint32_t target) {
    if (was_delay_) throw Fault("control transfer in a delay slot");
    if (condition) state.next_pc = target;
    state.delay_slot = true;
    if (likely && !condition) {
        state.pc += 4;
        state.next_pc += 4;
        state.delay_slot = false;
    }
}

void Machine::call_event(uint32_t target) {
    Event event{EventKind::call, state.call_site, target};
    std::copy_n(state.gpr.begin()+4, 8, event.arguments.begin());
    std::copy_n(state.fpr.begin()+12, 8, event.float_arguments.begin());
    trace.events.push_back(event);
}

void Machine::step() {
    outcome = {}; // stepping invalidates a previously completed execution
    const uint64_t cycle_before = state.ee_cycle;
    VuEngine(state,memory,trace).catch_up(state.ee_cycle);
    state.gpr[0] = {}; // the physical zero register cannot be changed by an input snapshot
    if (state.pc & 3) throw Fault("unaligned instruction fetch");
    // Instruction fetch must never receive a fabricated hardware response.
    const uint32_t address = translate(state.pc,Access::execute);
    if (address >= Memory::ram_size && !(address >= 0x70000000 && address < 0x70004000) &&
        !memory.candidate_address(address,4))
        throw Fault("instruction fetch outside executable memory");
    const uint32_t word = uint32_t(memory.read_physical(address, 4));
    const auto& d = decode_cached(word);
    if (!d.supported) {
        std::ostringstream message;
        message << "unsupported " << d.name << " at 0x" << std::hex << state.pc << " (0x" << word << ')';
        throw Fault(message.str());
    }
    const bool linked_entry = state.pending_call && !state.delay_slot;
    if (linked_entry) {
        if (state.pc != state.call_target) throw Fault("call target state mismatch");
        call_event(state.call_target);
        state.pending_call = false;
    }
    if (on_entry && capture_entries.contains(state.pc)) {
        // A loop may branch back to its function's first word. Count calls and
        // entries from another function, rather than every such loop visit.
        const auto prior = capture_entries.upper_bound(current_pc_);
        const bool crossed = prior == capture_entries.begin() || *std::prev(prior) != state.pc;
        if (linked_entry || crossed) on_entry(state.pc, state, memory);
    }
    const unsigned op = word>>26;
    const unsigned cop = op == 0x10 ? 0 : (op == 0x11 || op == 0x31 || op == 0x39) ? 1 :
                         (op == 0x12 || op == 0x36 || op == 0x3e) ? 2 : 3;
    const bool kernel = (state.cop0[12]&6) || !(state.cop0[12]&0x18);
    if (cop < 3 && d.name != "ei" && d.name != "di" && !(cop == 0 && kernel) && !(state.cop0[12]&(1u<<(28+cop)))) {
        state.cop0[13] = (state.cop0[13]&~0x3000007cu) | (cop<<28) | (11u<<2);
        throw Fault("coprocessor unusable");
    }
    current_pc_ = state.pc;
    was_delay_ = state.delay_slot;
    state.pc = state.next_pc;
    state.next_pc += 4;
    state.delay_slot = false;
    if (word >> 26 == 0x1c) mmi(d);
    else if (word >> 26 == 0x10) cop0(d);
    else if (word >> 26 == 0x11) cop1(d);
    else if (word >> 26 == 0x12) cop2(d);
    else integer(d);
    state.gpr[0] = {};
    minimum_stack=std::min(minimum_stack,state.gpr[29].w[0]);
    state.vf[0] = {};
    state.vf[0].w[3] = 0x3f800000;
    state.vi[0] = 0;
    trace.instructions.insert(current_pc_);
    trace.edges.emplace(current_pc_, state.pc);
    ++state.instructions;
    state.ee_cycle = std::max(state.ee_cycle+1,state.vu.cycle);
    advance_cop0(state.ee_cycle-cycle_before,d.name == "mtc0" && d.rd == 9,d.name == "mtc0" && d.rd == 6);
}

Result Machine::run(uint64_t budget, uint32_t return_pc) {
    Result result;
    try {
        for (; result.executed < budget; ++result.executed) {
            if (state.pc == return_pc && !state.delay_slot) {
                result.stop = Stop::returned; outcome = result; return result;
            }
            step();
        }
        if (state.pc == return_pc && !state.delay_slot) result.stop = Stop::returned;
    } catch (const Fault& e) { result.stop = Stop::fault; result.error = e.what(); }
    outcome = result;
    return result;
}
Result Machine::call(uint32_t address, uint64_t budget) {
    constexpr uint32_t sentinel = 0xfffffffc;
    state.start(address);
    state.gpr[31].low(sign32(sentinel));
    state.pending_call = true; state.call_target = address; state.call_site = sentinel;
    trace = {};
    return run(budget, sentinel);
}

void Machine::integer(const Decoded& d) {
    const auto& n = d.name;
    const uint64_t a = state.gpr[d.rs].low(), b = state.gpr[d.rt].low();
    const uint64_t imm = uint64_t(int64_t(d.immediate));
    const unsigned op = d.word >> 26;
    const auto put = [&](unsigned r, uint64_t v) { if (r) state.gpr[r].low(v); };
    const auto linked = [&](uint32_t target, unsigned dest) {
        put(dest, sign32(current_pc_+8));
        branch(true, false, target);
        if (dest) { state.pending_call = true; state.call_target = target; state.call_site = current_pc_; }
    };
    const uint32_t target = current_pc_ + 4 + uint32_t(int32_t(d.immediate)*4);
    if (n == "j" || n == "jal") {
        const uint32_t to = ((current_pc_+4) & 0xf0000000) | ((d.word & 0x3ffffff) << 2);
        if (n == "jal") linked(to,31); else branch(true,false,to);
    } else if (n == "jr" || n == "jalr") {
        if (n == "jalr") linked(uint32_t(a),d.rd); else branch(true,false,uint32_t(a));
    } else if (n == "beq" || n == "beql" || n == "bne" || n == "bnel") {
        branch((a == b) == (n == "beq" || n == "beql"), n.ends_with('l'),target);
    } else if (n == "blez" || n == "blezl" || n == "bgtz" || n == "bgtzl") {
        branch((signed64(a) <= 0) == (n == "blez" || n == "blezl"),n.ends_with('l'),target);
    } else if (n.starts_with("bltz") || n.starts_with("bgez")) {
        const bool condition = (signed64(a) < 0) == n.starts_with("bltz");
        const bool link = d.rt & 16, likely = d.rt & 2;
        if (link) put(31,sign32(current_pc_+8)); // link is written even if branch is not taken
        branch(condition,likely,target);
        if (link && condition) { state.pending_call = true; state.call_target = target; state.call_site = current_pc_; }
    } else if (n == "addiu") put(d.rt,sign32(uint32_t(a+imm)));
    else if (n == "addi") put(d.rt,checked_add(a,imm,32,false));
    else if (n == "daddiu") put(d.rt,a+imm);
    else if (n == "daddi") put(d.rt,checked_add(a,imm,64,false));
    else if (n == "addu") put(d.rd,sign32(uint32_t(a+b)));
    else if (n == "subu") put(d.rd,sign32(uint32_t(a-b)));
    else if (n == "add" || n == "sub") put(d.rd,checked_add(a,b,32,n == "sub"));
    else if (n == "daddu") put(d.rd,a+b);
    else if (n == "dsubu") put(d.rd,a-b);
    else if (n == "dadd" || n == "dsub") put(d.rd,checked_add(a,b,64,n == "dsub"));
    else if (n == "and") put(d.rd,a&b);
    else if (n == "or") put(d.rd,a|b);
    else if (n == "xor") put(d.rd,a^b);
    else if (n == "nor") put(d.rd,~(a|b));
    else if (n == "andi") put(d.rt,a & uint16_t(d.immediate));
    else if (n == "ori") put(d.rt,a | uint16_t(d.immediate));
    else if (n == "xori") put(d.rt,a ^ uint16_t(d.immediate));
    else if (n == "lui") put(d.rt,sign32(uint32_t(uint16_t(d.immediate)) << 16));
    else if (n == "slt") put(d.rd,signed64(a)<signed64(b));
    else if (n == "sltu") put(d.rd,a<b);
    else if (n == "slti") put(d.rt,signed64(a)<int64_t(d.immediate));
    else if (n == "sltiu") put(d.rt,a<imm);
    else if (n == "movz" || n == "movn") { if ((b == 0) == (n == "movz")) put(d.rd,a); }
    else if (n == "sll" || n == "sllv") put(d.rd,sign32(uint32_t(b) << (n == "sll" ? d.sa : a&31)));
    else if (n == "srl" || n == "srlv") put(d.rd,sign32(uint32_t(b) >> (n == "srl" ? d.sa : a&31)));
    else if (n == "sra" || n == "srav") put(d.rd,sign32(uint32_t(arithmetic_right(b,n == "sra" ? d.sa : a&31,32))));
    else if (n.starts_with("dsll") || n.starts_with("dsrl") || n.starts_with("dsra")) {
        const unsigned shift = n.ends_with('v') ? a&63 : d.sa + (n.ends_with("32") ? 32 : 0);
        put(d.rd,n.starts_with("dsll") ? b << shift : n.starts_with("dsrl") ? b >> shift : arithmetic_right(b,shift,64));
    } else if (n == "mfhi") put(d.rd,state.hi.low());
    else if (n == "mflo") put(d.rd,state.lo.low());
    else if (n == "mthi") state.hi.low(a);
    else if (n == "mtlo") state.lo.low(a);
    else if (n == "mult" || n == "multu") product(state,0,d.rd,uint32_t(a),uint32_t(b),n == "multu",false);
    else if (n == "div" || n == "divu") quotient(state,0,uint32_t(a),uint32_t(b),n == "divu");
    else if (n == "mfsa") put(d.rd,state.sa&15);
    else if (n == "mtsa") state.sa = uint32_t(a)&15;
    else if (n == "mtsab") state.sa = (uint32_t(a)^uint16_t(d.immediate))&15;
    else if (n == "mtsah") state.sa = ((uint32_t(a)^uint16_t(d.immediate))&7)*2;
    else if (n.starts_with('t') && (op == 0 || op == 1)) {
        const uint64_t rhs = op == 1 ? imm : b;
        bool fire = false;
        if (n.starts_with("tgeu") || n == "tgeiu") fire = a >= rhs;
        else if (n.starts_with("tge")) fire = signed64(a) >= signed64(rhs);
        else if (n.starts_with("tltu") || n == "tltiu") fire = a < rhs;
        else if (n.starts_with("tlt")) fire = signed64(a) < signed64(rhs);
        else if (n.starts_with("teq")) fire = a == rhs;
        else if (n.starts_with("tne")) fire = a != rhs;
        if (fire) throw Fault("integer trap");
    } else if (n == "break") throw Fault("break instruction");
    else if (n == "syscall") {
        Event event{EventKind::syscall,current_pc_,uint32_t(state.gpr[3].low())};
        std::copy_n(state.gpr.begin()+4,8,event.arguments.begin());
        event.default_response = true;
        trace.events.push_back(event);
        put(2,0); // explicit stub, recorded; not a scheduler or kernel model
    } else if (n == "sync" || n == "cache" || n == "pref") {
        trace.events.push_back(Event{n == "sync" ? EventKind::sync : EventKind::cache,current_pc_,uint32_t(a+imm)});
    } else if (op >= 0x1a) {
        const uint32_t addr = uint32_t(a+imm);
        const auto read = [&](unsigned width) { return memory.read_physical(translate(addr,Access::read),width,&trace,current_pc_); };
        const auto write = [&](unsigned width, uint64_t v) { memory.write_physical(translate(addr,Access::write),width,v,&trace,current_pc_); };
        const auto aligned = [&](unsigned width) { if (addr & (width-1)) throw Fault("unaligned scalar access"); };
        if (n == "lb") put(d.rt,uint64_t(int64_t(int8_t(read(1)))));
        else if (n == "lbu") put(d.rt,read(1));
        else if (n == "lh") { aligned(2); put(d.rt,uint64_t(int64_t(int16_t(read(2))))); }
        else if (n == "lhu") { aligned(2); put(d.rt,read(2)); }
        else if (n == "lw" || n == "lwu") { aligned(4); const auto v = uint32_t(read(4)); put(d.rt,n == "lw" ? sign32(v) : v); }
        else if (n == "ld") { aligned(8); put(d.rt,read(8)); }
        else if (n == "sb") write(1,b);
        else if (n == "sh") { aligned(2); write(2,b); }
        else if (n == "sw") { aligned(4); write(4,b); }
        else if (n == "sd") { aligned(8); write(8,b); }
        else if (n == "lq") {
            auto q = memory.read_quad_physical(translate(addr&~15u,Access::read),&trace,current_pc_);
            if (d.rt) state.gpr[d.rt] = q;
        } else if (n == "sq") memory.write_quad_physical(translate(addr&~15u,Access::write),state.gpr[d.rt],&trace,current_pc_);
        else if (n == "lwc1") { aligned(4); state.fpr[d.rt] = uint32_t(read(4)); }
        else if (n == "swc1") { aligned(4); write(4,state.fpr[d.rt]); }
        else if (n == "lqc2") {
            aligned(16);
            VuEngine(state,memory,trace).synchronize_vector(d.rt,true);
            state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
            const auto value = memory.read_quad_physical(translate(addr,Access::read),&trace,current_pc_);
            if (d.rt) state.vf[d.rt] = value;
        } else if (n == "sqc2") {
            VuEngine(state,memory,trace).synchronize_vector(d.rt,true);
            state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
            aligned(16); memory.write_quad_physical(translate(addr,Access::write),state.vf[d.rt],&trace,current_pc_);
        }
        else if (n == "lwl" || n == "lwr" || n == "ldl" || n == "ldr" ||
                 n == "swl" || n == "swr" || n == "sdl" || n == "sdr") {
            const unsigned width = n[1] == 'd' ? 8 : 4;
            const unsigned pos = addr & (width-1);
            const bool left = n.back() == 'l', load = n.front() == 'l';
            const unsigned count = left ? pos+1 : width-pos;
            const uint32_t base = left ? addr-pos : addr;
            const unsigned start = left ? width-count : 0;
            uint64_t v = b;
            // A partial load performs one aligned memory read. In particular,
            // an MMIO load must not become a sequence of invented byte reads.
            const uint64_t loaded = load ? memory.read_physical(translate(addr&~(width-1),Access::read),width,&trace,current_pc_) : 0;
            for (unsigned i = 0; i < count; ++i) {
                const unsigned shift = (start+i)*8;
                if (load) v = (v & ~(uint64_t(255) << shift)) |
                    (((loaded >> ((base+i-(addr & ~(width-1)))*8)) & 255) << shift);
                else memory.write_physical(translate(base+i,Access::write),1,b >> shift,&trace,current_pc_);
            }
            // LWR at a nonzero byte offset preserves GPR bits 63:32.
            if (load) put(d.rt,width == 4 && !(n == "lwr" && pos) ? sign32(uint32_t(v)) : v);
        } else throw Fault("missing integer handler: " + n);
    } else throw Fault("missing integer handler: " + n);
}

void Machine::cop1(const Decoded& d) {
    const auto& n = d.name;
    const auto put = [&](uint64_t value) { if (d.rt) state.gpr[d.rt].low(value); };
    if (n == "mfc1") put(sign32(state.fpr[d.rd]));
    else if (n == "mtc1") state.fpr[d.rd] = state.gpr[d.rt].w[0];
    // Hardware CFC1 reads alias by bit 4 of fs (ps2autotests fcr result log).
    else if (n == "cfc1") put(sign32(state.fcr[d.rd & 16 ? 31 : 0]));
    else if (n == "ctc1") {
        if (d.rd == 31) state.fcr[31] = (state.gpr[d.rt].w[0] & 0x0083c078) | 0x01000001;
    } else if (n.starts_with("bc1")) {
        const bool condition = bool(state.fcr[31] & 0x00800000) == bool(d.rt&1);
        branch(condition,d.rt&2,current_pc_+4+uint32_t(int32_t(d.immediate)*4));
    } else if (n == "mov.s") state.fpr[d.sa] = state.fpr[d.rd];
    else if (n == "abs.s" || n == "neg.s" || n == "max.s" || n == "min.s") {
        const uint32_t a = state.fpr[d.rd], b = state.fpr[d.rt];
        state.fpr[d.sa] = n == "abs.s" ? a & 0x7fffffff : n == "neg.s" ? a ^ 0x80000000 :
                          n == "max.s" ? fpu::maximum(a,b) : fpu::minimum(a,b);
        state.fcr[31] &= ~0xc000u;
    } else if (n == "cvt.s.w") state.fpr[d.sa] = fpu::from_integer(state.fpr[d.rd]);
    else if (n == "cvt.w.s") state.fpr[d.sa] = fpu::to_integer(state.fpr[d.rd]);
    else if (n == "c.f.s" || n == "c.eq.s" || n == "c.lt.s" || n == "c.le.s") {
        const uint32_t a = state.fpr[d.rd], b = state.fpr[d.rt];
        const bool condition = n == "c.eq.s" ? fpu::equal(a,b) : n == "c.lt.s" ? fpu::less(a,b) :
                               n == "c.le.s" ? fpu::less(a,b) || fpu::equal(a,b) : false;
        state.fcr[31] = (state.fcr[31] & ~0x800000u) | (condition ? 0x800000 : 0);
    } else {
        const uint32_t a = state.fpr[d.rd], b = state.fpr[d.rt];
        fpu::Arithmetic value;
        const bool accumulator = n == "adda.s" || n == "suba.s" || n == "mula.s" || n == "madda.s" || n == "msuba.s";
        if (n == "add.s" || n == "adda.s") value = fpu::add(a,b);
        else if (n == "sub.s" || n == "suba.s") value = fpu::subtract(a,b);
        else if (n == "mul.s" || n == "mula.s") value = fpu::multiply(a,b);
        else if (n == "div.s") value = fpu::divide(a,b);
        else if (n == "sqrt.s") value = fpu::square_root(b); // SQRT's source is ft, not fs
        else if (n == "rsqrt.s") value = fpu::reciprocal_root(a,b);
        else if (n == "madd.s" || n == "madda.s" || n == "msub.s" || n == "msuba.s")
            value = fpu::accumulate(state.facc,a,b,state.facc_overflow,n.starts_with("msub"));
        else throw Fault("missing COP1 handler: " + n);
        if (n == "div.s" || n == "sqrt.s" || n == "rsqrt.s") {
            state.fcr[31] &= ~0x30000u;
            if (value.divide_zero) state.fcr[31] |= 0x10020;
            if (value.invalid) state.fcr[31] |= 0x20040;
        } else {
            state.fcr[31] &= ~0xc000u;
            if (value.overflow) state.fcr[31] |= 0x8010;
            if (value.underflow) state.fcr[31] |= 0x4008;
            if (value.product_underflow) state.fcr[31] |= 8;
        }
        if (accumulator) { state.facc = value.bits; state.facc_overflow = value.overflow; }
        else state.fpr[d.sa] = value.bits;
    }
}

void Machine::cop2(const Decoded& d) {
    VuEngine vu(state,memory,trace);
    const auto& n = d.name;
    const bool read = n == "qmfc2" || n == "cfc2";
    const bool write = n == "qmtc2" || n == "ctc2";
    if ((read || write) && (d.word&1)) {
        vu.interlock(write);
        state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
    }
    if (n.starts_with("bc2")) {
        const bool vu1_busy = state.vi[29]&0x100;
        branch(vu1_busy == bool(d.rt&1),bool(d.rt&2),current_pc_+4+uint32_t(int32_t(d.immediate)*4));
    } else if (n == "qmfc2") {
        vu.synchronize_vector(d.rd,true);
        state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
        if (d.rt) state.gpr[d.rt] = state.vf[d.rd];
    } else if (n == "qmtc2") {
        vu.synchronize_vector(d.rd,true);
        state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
        if (d.rd) state.vf[d.rd] = state.gpr[d.rt];
    } else if (n == "cfc2") {
        vu.synchronize_control(d.rd,true);
        state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
        uint32_t value = state.vi[d.rd];
        if (d.rd < 16) value &= 0xffff;
        else if (d.rd == 20) value &= 0x7fffff;
        else if (d.rd == 19) value = state.fcr[0]; // hardware identification read
        else if (d.rd == 23 || d.rd == 24 || d.rd == 25 || d.rd == 30)
            throw Fault("reserved VU control register read is not validated");
        if (d.rt) state.gpr[d.rt].low(sign32(value));
    } else if (n == "ctc2") {
        const uint32_t value = state.gpr[d.rt].w[0];
        if (!d.rd) return;
        if (d.rd < 16) {
            vu.synchronize_control(d.rd,true);
            state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
            state.vi[d.rd] = value & 0xffff;
        }
        else if (d.rd == 16) {
            vu.synchronize_control(d.rd,true);
            state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
            state.vi[16] = (state.vi[16]&0x3f) | (value&0xfc0);
        }
        else if (d.rd == 17 || d.rd == 19 || d.rd == 26 || d.rd == 29) return;
        else if (d.rd == 18) {
            vu.synchronize_control(d.rd,true);
            state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
            state.vi[18] = state.vu.clip_history = value & 0xffffff;
        }
        else if (d.rd == 20) state.vi[20] = 0x3f800000 | (value & 0x7fffff);
        else if (d.rd == 21 || d.rd == 22) state.vi[d.rd] = value;
        else if (d.rd == 27) state.vi[27] = value & 0xffff;
        else if (d.rd == 28 || d.rd == 31) {
            Event event{EventKind::vu_control,current_pc_,d.rd};
            for (unsigned byte = 0; byte < 4; ++byte) event.bytes.push_back(uint8_t(value >> (byte*8)));
            event.default_response = d.rd == 31 || (value&0x300);
            trace.events.push_back(event);
            if (d.rd == 31) {
                if (!(state.vi[29]&0x100)) state.vi[31] = value&0xffff;
                // VU1 execution is an explicitly recorded external device stub.
            } else {
                state.vi[28] = value&0xc0c;
                if (value&2) vu.reset(); else if (value&1) vu.force_break();
                if (value&0x200) { state.vi[28] &= ~0xc00u; state.vi[29] &= ~0xff00u; }
                else if (value&0x100) state.vi[29] = (state.vi[29]&~0xf00u)|0x800;
                state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
            }
        }
        else throw Fault("VU control command is not implemented");
    } else if (n == "vcallms" || n == "vcallmsr") {
        vu.interlock();
        vu.start(n == "vcallms" ? (d.word >> 6 & 0x7fff)*8 : state.vi[27]*8);
        state.ee_cycle = std::max(state.ee_cycle,state.vu.cycle);
    } else vu.macro(d);
}

void Machine::mmi(const Decoded& d) {
    const auto& n = d.name;
    // Snapshot operands before writing: rd may alias either input register.
    const Quad a = state.gpr[d.rs], b = state.gpr[d.rt];
    Quad r{};
    if (n == "madd" || n == "maddu" || n == "madd1" || n == "maddu1" ||
        n == "mult1" || n == "multu1") {
        const bool unsign = n == "maddu" || n == "maddu1" || n == "multu1";
        product(state,n.ends_with('1'),d.rd,a.w[0],b.w[0],unsign,n.starts_with("madd"));
        return;
    }
    if (n == "div1" || n == "divu1") { quotient(state,1,a.w[0],b.w[0],n == "divu1"); return; }
    if (n == "mfhi1" || n == "mflo1") {
        if (d.rd) state.gpr[d.rd].low(n == "mfhi1" ? state.hi.high() : state.lo.high());
        return;
    }
    if (n == "mthi1" || n == "mtlo1") {
        if (n == "mthi1") state.hi.high(a.low()); else state.lo.high(a.low());
        return;
    }
    if (n == "plzcw") {
        r = state.gpr[d.rd]; // only two low words change
        for (unsigned i = 0; i < 2; ++i) r.w[i] = std::countl_zero((a.w[i]&0x80000000) ? ~a.w[i] : a.w[i])-1;
    } else if (n == "pand" || n == "por" || n == "pxor" || n == "pnor") {
        for (unsigned i = 0; i < 4; ++i)
            r.w[i] = n == "pand" ? a.w[i]&b.w[i] : n == "por" ? a.w[i]|b.w[i] : n == "pxor" ? a.w[i]^b.w[i] : ~(a.w[i]|b.w[i]);
    } else if (n == "pcpyld") { r.low(b.low()); r.high(a.low()); }
    else if (n == "pcpyud") { r.low(a.high()); r.high(b.high()); }
    else if (n == "pmfhi") r = state.hi;
    else if (n == "pmflo") r = state.lo;
    else if (n == "pmthi") { state.hi = a; return; }
    else if (n == "pmtlo") { state.lo = a; return; }
    else if (n == "pmthl.lw") {
        state.lo.w[0] = a.w[0]; state.hi.w[0] = a.w[1];
        state.lo.w[2] = a.w[2]; state.hi.w[2] = a.w[3]; return;
    } else if (n == "pmfhl.lw" || n == "pmfhl.uw") {
        const unsigned lane = n == "pmfhl.uw" ? 1 : 0;
        r.w = {state.lo.w[lane],state.hi.w[lane],state.lo.w[lane+2],state.hi.w[lane+2]};
    } else if (n == "pmfhl.slw") {
        for (unsigned bank = 0; bank < 2; ++bank) {
            const unsigned lane = bank*2;
            const auto value = signed64(uint64_t(state.lo.w[lane]) | uint64_t(state.hi.w[lane]) << 32);
            const auto clamped = std::clamp(value,int64_t(-0x80000000ll),int64_t(0x7fffffff));
            if (!bank) r.low(uint64_t(clamped)); else r.high(uint64_t(clamped));
        }
    } else if (n == "pmfhl.lh" || n == "pmfhl.sh") {
        for (unsigned i = 0; i < 8; ++i) {
            const auto& source = i % 4 < 2 ? state.lo : state.hi;
            const unsigned lane = i/4*2 + i%2;
            const uint32_t value = source.w[lane];
            const int32_t narrowed = n == "pmfhl.sh" ? std::clamp(signed32(value),-32768,32767) : int32_t(value & 0xffff);
            r.lane(i,16,uint32_t(narrowed));
        }
    } else if (n == "pmulth" || n == "pmaddh" || n == "pmsubh" || n == "phmadh" || n == "phmsbh") {
        const auto multiply = [&](unsigned i) {
            const int32_t x = int32_t(a.lane(i,16) & 0x7fff)-int32_t(a.lane(i,16) & 0x8000);
            const int32_t y = int32_t(b.lane(i,16) & 0x7fff)-int32_t(b.lane(i,16) & 0x8000);
            return uint32_t(x*y);
        };
        if (n == "phmadh" || n == "phmsbh") {
            for (unsigned pair = 0; pair < 4; ++pair) {
                auto& accumulator = pair&1 ? state.hi : state.lo;
                const unsigned lane = pair/2*2;
                const uint32_t even = multiply(pair*2), odd = multiply(pair*2+1);
                accumulator.w[lane] = n == "phmadh" ? odd+even : odd-even;
                // PHMSBH also complements the odd product in the accumulator's
                // secondary word; this needs independent hardware edge tests.
                accumulator.w[lane+1] = n == "phmadh" ? odd : ~odd;
            }
        } else for (unsigned i = 0; i < 8; ++i) {
            auto& accumulator = i%4 < 2 ? state.lo : state.hi;
            auto& dest = accumulator.w[i/4*2+i%2];
            const auto value = multiply(i);
            dest = n == "pmulth" ? value : n == "pmaddh" ? dest+value : dest-value;
        }
        r.w = {state.lo.w[0],state.hi.w[0],state.lo.w[2],state.hi.w[2]};
    } else if (n == "pmultw" || n == "pmultuw" || n == "pmaddw" || n == "pmadduw" || n == "pmsubw") {
        const bool unsign = n == "pmultuw" || n == "pmadduw";
        for (unsigned bank = 0; bank < 2; ++bank) {
            const unsigned i = bank*2;
            uint64_t v = unsign ? uint64_t(a.w[i])*b.w[i] : uint64_t(int64_t(signed32(a.w[i]))*signed32(b.w[i]));
            const uint64_t previous = uint64_t(state.lo.w[i]) | uint64_t(state.hi.w[i]) << 32;
            if (n == "pmaddw" || n == "pmadduw") v += previous;
            if (n == "pmsubw") v = previous-v;
            if (!bank) { state.lo.low(sign32(uint32_t(v))); state.hi.low(sign32(uint32_t(v >> 32))); r.low(v); }
            else { state.lo.high(sign32(uint32_t(v))); state.hi.high(sign32(uint32_t(v >> 32))); r.high(v); }
        }
    } else if (n == "pdivw" || n == "pdivuw" || n == "pdivbw") {
        for (unsigned bank = 0; bank < 2; ++bank) {
            if (n == "pdivbw") {
                for (unsigned lane = 0; lane < 4; ++lane) {
                    State tmp;
                    quotient(tmp,0,a.w[lane],uint32_t(int32_t(int16_t(b.w[0]))),false);
                    state.lo.w[lane] = tmp.lo.w[0]; state.hi.w[lane] = tmp.hi.w[0];
                }
                return;
            }
            quotient(state,bank,a.w[bank*2],b.w[bank*2],n == "pdivuw");
        }
        return;
    } else if (n == "qfsrv") {
        // SA is in bytes. Funnel the 256-bit concatenation rs:rt right.
        const unsigned shift = (state.sa&15)*8;
        const std::array<uint64_t,4> q = {b.low(),b.high(),a.low(),a.high()};
        const unsigned index = shift/64, bits = shift%64;
        const auto part = [&](unsigned i) { return (q[index+i] >> bits) | (bits ? q[index+i+1] << (64-bits) : 0); };
        r.low(part(0)); r.high(part(1));
    } else if (n == "psllvw" || n == "psrlvw" || n == "psravw") {
        for (unsigned bank = 0; bank < 2; ++bank) {
            const unsigned i = bank*2, shift = a.w[i]&31;
            const uint32_t v = n == "psllvw" ? b.w[i] << shift : n == "psrlvw" ? b.w[i] >> shift : uint32_t(arithmetic_right(b.w[i],shift,32));
            if (!bank) r.low(sign32(v)); else r.high(sign32(v));
        }
    } else if (n == "pexeh" || n == "prevh" || n == "pexew" || n == "prot3w" || n == "pexch" || n == "pexcw") {
        const unsigned bits = n.ends_with('h') ? 16 : 32;
        std::array<unsigned,8> order{};
        if (n == "pexeh") order = {2,1,0,3,6,5,4,7};
        if (n == "prevh") order = {3,2,1,0,7,6,5,4};
        if (n == "pexch") order = {0,2,1,3,4,6,5,7};
        if (n == "pexew") order = {2,1,0,3};
        if (n == "prot3w") order = {1,2,0,3};
        if (n == "pexcw") order = {0,2,1,3};
        for (unsigned i = 0; i < 128/bits; ++i) r.lane(i,bits,b.lane(order[i],bits));
    } else if (n == "pinth" || n == "pinteh") {
        for (unsigned i = 0; i < 4; ++i) {
            r.lane(i*2,16,b.lane(n == "pinth" ? i : i*2,16));
            r.lane(i*2+1,16,a.lane(n == "pinth" ? i+4 : i*2,16));
        }
    } else if (n == "pcpyh") {
        for (unsigned i = 0; i < 8; ++i) r.lane(i,16,b.lane(i < 4 ? 0 : 4,16));
    } else if (n == "pext5" || n == "ppac5") {
        for (unsigned i = 0; i < 4; ++i) {
            const uint32_t v = b.w[i];
            if (n == "pext5") r.w[i] = ((v&31)<<3) | ((v&0x3e0)<<6) | ((v&0x7c00)<<9) | ((v&0x8000)<<16);
            else r.w[i] = ((v>>3)&31) | ((v>>6)&0x3e0) | ((v>>9)&0x7c00) | ((v>>16)&0x8000);
        }
    } else {
        const unsigned bits = n.ends_with('b') ? 8 : n.ends_with('h') ? 16 : 32;
        const unsigned count = 128/bits;
        const uint64_t mask = (uint64_t(1) << bits)-1;
        const auto signed_lane = [&](uint32_t x) { return int64_t(x & ((1u << (bits-1))-1)) - int64_t(x & (1u << (bits-1))); };
        if (n.starts_with("pextl") || n.starts_with("pextu")) {
            const unsigned start = n.starts_with("pextu") ? count/2 : 0;
            for (unsigned i = 0; i < count/2; ++i) {
                r.lane(i*2,bits,b.lane(start+i,bits)); r.lane(i*2+1,bits,a.lane(start+i,bits));
            }
        } else if (n.starts_with("ppac")) {
            for (unsigned i = 0; i < count/2; ++i) {
                r.lane(i,bits,b.lane(i*2,bits)); r.lane(i+count/2,bits,a.lane(i*2,bits));
            }
        } else for (unsigned i = 0; i < count; ++i) {
            const uint64_t x = a.lane(i,bits), y = b.lane(i,bits);
            const int64_t sx = signed_lane(uint32_t(x)), sy = signed_lane(uint32_t(y));
            uint64_t v;
            if (n.starts_with("psll")) v = y << (d.sa & (bits-1));
            else if (n.starts_with("psrl")) v = y >> (d.sa & (bits-1));
            else if (n.starts_with("psra")) v = uint64_t(sy >> (d.sa & (bits-1)));
            else if (n.starts_with("pcgt")) v = sx > sy ? mask : 0;
            else if (n.starts_with("pceq")) v = x == y ? mask : 0;
            else if (n.starts_with("pmax")) v = uint64_t(std::max(sx,sy));
            else if (n.starts_with("pmin")) v = uint64_t(std::min(sx,sy));
            else if (n.starts_with("pabs")) v = uint64_t(std::min(sy < 0 ? -sy : sy,int64_t(mask>>1)));
            else if (n == "padsbh") v = i < 4 ? x-y : x+y;
            else if (n.starts_with("padds") || n.starts_with("psubs"))
                v = uint64_t(std::clamp(n.starts_with("padd") ? sx+sy : sx-sy,-int64_t((mask>>1)+1),int64_t(mask>>1)));
            else if (n.starts_with("paddu")) v = std::min(x+y,mask);
            else if (n.starts_with("psubu")) v = x >= y ? x-y : 0;
            else if (n.starts_with("padd")) v = x+y;
            else if (n.starts_with("psub")) v = x-y;
            else throw Fault("missing MMI handler: " + n);
            r.lane(i,bits,uint32_t(v));
        }
    }
    if (d.rd) state.gpr[d.rd] = r;
}

std::string difference(const Machine& a, const Machine& b, std::span<const unsigned> returns,
                       std::span<const unsigned> float_returns) {
    if (a.outcome.stop != Stop::returned || b.outcome.stop != Stop::returned) return "incomplete execution";
    for (unsigned r : returns) if (a.state.gpr.at(r) != b.state.gpr.at(r)) return "integer return register " + std::to_string(r);
    for (unsigned r : float_returns) if (a.state.fpr.at(r) != b.state.fpr.at(r)) return "float return register " + std::to_string(r);
    if (a.trace.writes != b.trace.writes) return "memory writes";
    auto left = a.trace.events, right = b.trace.events;
    for (auto& event : left) event.pc = 0;
    for (auto& event : right) event.pc = 0;
    if (left != right) return "ordered external events";
    return {};
}
} // namespace ee
