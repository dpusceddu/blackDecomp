#include "ee.hpp"

#include <algorithm>
#include <bit>

namespace ee {
namespace {
bool global(const TlbEntry& entry) { return entry.entry_lo[0]&entry.entry_lo[1]&1; }
bool scratch(const TlbEntry& entry) { return entry.entry_lo[0]&0x80000000; }
uint32_t pair_mask(const TlbEntry& entry) { return scratch(entry) ? 0x3fff : entry.page_mask|0x1fff; }
bool matches(const TlbEntry& entry,uint32_t address,unsigned asid) {
    return entry.initialized && !((entry.entry_hi^address)&~pair_mask(entry)) &&
           (global(entry) || (entry.entry_hi&255) == asid);
}
void validate_mask(uint32_t mask) {
    switch (mask) {
    case 0: case 0x6000: case 0x1e000: case 0x7e000:
    case 0x1fe000: case 0x7fe000: case 0x1ffe000: return;
    default: throw Fault("undefined TLB page mask");
    }
}
} // namespace

uint32_t Machine::translate(uint32_t address,Access access) {
    if(memory.candidate_address(address)) {
        if(access==Access::write)throw Fault("write to immutable differential candidate");
        return address;
    }
    if (!state.mmu_enabled) return Memory::physical(address);
    const uint32_t status = state.cop0[12];
    const unsigned privilege = status&6 ? 0 : (status >> 3)&3;
    const auto fail = [&](const char* error,bool tlb) -> uint32_t {
        state.cop0[8] = address;
        if (tlb) {
            state.cop0[10] = (address&0xffffe000) | (state.cop0[10]&255);
            state.cop0[4] = (state.cop0[4]&0xff800000) | ((address>>9)&0x7ffff0);
        }
        throw Fault(error);
    };
    if (privilege == 3) throw Fault("reserved COP0 privilege mode");
    if (address >= 0x80000000 && (privilege == 2 || (privilege == 1 && (address < 0xc0000000 || address >= 0xe0000000))))
        return fail("address outside the current privilege space",false);
    if (address >= 0x80000000 && address < 0xc0000000) return address&0x1fffffff;
    if (address < 0x80000000 && (status&4)) return address; // ERL bypasses kuseg translation
    const TlbEntry* found = nullptr;
    for (const auto& entry : state.tlb) if (matches(entry,address,state.cop0[10]&255)) {
        if (found) throw Fault("undefined multiple TLB match");
        found = &entry;
    }
    if (!found) return fail("TLB refill required",true);
    const uint32_t page_size = (pair_mask(*found)+1)/2;
    const unsigned half = scratch(*found) ? 0 : bool(address&page_size);
    const uint32_t lo = found->entry_lo[half];
    if (!(lo&2)) return fail("TLB invalid page",true);
    if (access == Access::write && !(lo&4)) return fail("TLB modification of a read-only page",true);
    if (scratch(*found)) return 0x70000000 | (address&0x3fff);
    const unsigned cache = lo>>3&7;
    if (cache != 2 && cache != 3 && cache != 7) throw Fault("reserved TLB cache attribute");
    const uint32_t frame = (lo&0x03ffffc0)<<6;
    return (frame&~(page_size-1)) | (address&(page_size-1));
}

void Machine::cop0(const Decoded& d) {
    const auto& n = d.name;
    const auto put = [&](unsigned reg,uint32_t value) {
        if (reg) state.gpr[reg].low(uint64_t(int64_t(std::bit_cast<int32_t>(value))));
    };
    if (n == "mfc0" || n == "mtc0") {
        if (d.word&0x7ff) throw Fault("unvalidated COP0 register selector");
        if (n == "mfc0") {
            if (d.rd == 9) {
                Event event{EventKind::cop0_read,current_pc_,9};
                event.default_response = true; // deterministic clock profile
                for (unsigned i = 0; i < 4; ++i) event.bytes.push_back(uint8_t(state.cop0[9] >> (i*8)));
                trace.events.push_back(event);
            }
            put(d.rt,state.cop0[d.rd]); return;
        }
        const uint32_t value = state.gpr[d.rt].w[0];
        switch (d.rd) {
        case 0: state.cop0[0] = (state.cop0[0]&0x80000000) | (value&63); break;
        case 1: case 8: case 15: break; // read-only Random, BadVAddr and PRId
        case 2: state.cop0[2] = value&0x83ffffff; break;
        case 3: state.cop0[3] = value&0x03ffffff; break;
        case 4: state.cop0[4] = (state.cop0[4]&0x7ffff0) | (value&0xff800000); break;
        case 5: state.cop0[5] = value&0x01ffe000; break;
        case 6:
            if ((value&63) > 47) throw Fault("undefined Wired index above 47");
            state.cop0[6] = value&63; state.cop0[1] = 47; break;
        case 10: state.cop0[10] = value&0xffffe0ff; break;
        case 11: state.cop0[11] = value; state.cop0[13] &= ~0x8000u; break;
        case 12: state.cop0[12] = (state.cop0[12]&0x40000) | (value&0xf0c39c1f); break;
        case 13: break; // EE Cause fields are read-only; no software interrupt bits
        default: state.cop0[d.rd] = value; break;
        }
    } else if (n == "tlbwi" || n == "tlbwr") {
        const unsigned index = state.cop0[n == "tlbwi" ? 0 : 1]&63;
        if (index >= state.tlb.size()) throw Fault("undefined TLB index above 47");
        TlbEntry entry{state.cop0[5]&0x01ffe000,state.cop0[10]&0xffffe0ff,
                       {state.cop0[2]&0x83ffffff,state.cop0[3]&0x03ffffff},true};
        if (scratch(entry)) {
            if (entry.page_mask || (entry.entry_hi&0x2000) || ((entry.entry_lo[0]^entry.entry_lo[1])&6))
                throw Fault("undefined scratchpad TLB layout");
            for (auto& lo : entry.entry_lo) lo = (lo&~0x38u)|0x10;
        }
        validate_mask(entry.page_mask);
        const bool g = global(entry);
        for (auto& lo : entry.entry_lo) lo = (lo&~1u)|unsigned(g);
        state.tlb[index] = entry;
    } else if (n == "tlbr") {
        const unsigned index = state.cop0[0]&63;
        if (index >= state.tlb.size() || !state.tlb[index].initialized) throw Fault("TLBR requires a supplied TLB entry");
        const auto& entry = state.tlb[index];
        state.cop0[5] = entry.page_mask;
        state.cop0[10] = entry.entry_hi&~entry.page_mask;
        state.cop0[2] = entry.entry_lo[0]; state.cop0[3] = entry.entry_lo[1];
    } else if (n == "tlbp") {
        unsigned matches_found = 0;
        uint32_t index = 0x80000000;
        for (unsigned i = 0; i < state.tlb.size(); ++i) if (matches(state.tlb[i],state.cop0[10]&0xffffe000,state.cop0[10]&255)) {
            ++matches_found; index = i;
        }
        if (matches_found > 1) throw Fault("undefined multiple TLB probe match");
        state.cop0[0] = index;
    } else if (n.starts_with("bc0")) {
        const uint32_t status = uint32_t(memory.read(0x1000e010,4,&trace,current_pc_));
        const uint32_t control = uint32_t(memory.read(0x1000e020,4,&trace,current_pc_));
        const bool completed = (status&control&0x3ff) == (control&0x3ff);
        branch(completed == bool(d.rt&1),bool(d.rt&2),current_pc_+4+uint32_t(int32_t(d.immediate)*4));
    } else if (n == "eret") {
        if (was_delay_) throw Fault("ERET in a delay slot is undefined");
        const bool error = state.cop0[12]&4;
        state.pc = state.cop0[error ? 30 : 14]; state.next_pc = state.pc+4;
        state.cop0[12] &= ~(error ? 4u : 2u); state.pending_call = false;
    } else if (n == "ei" || n == "di") {
        const uint32_t status = state.cop0[12];
        if ((status&((1u<<17)|6)) || !(status&0x18)) {
            if (n == "ei") state.cop0[12] |= 0x10000; else state.cop0[12] &= ~0x10000u;
        }
    } else throw Fault("missing COP0 handler: "+n);
}

void Machine::advance_cop0(uint64_t cycles,bool count_written,bool wired_written) {
    if (!count_written) {
        const uint32_t old = state.cop0[9];
        uint64_t distance = uint32_t(state.cop0[11]-old);
        if (!distance) distance = uint64_t(1)<<32;
        if (cycles >= distance) state.cop0[13] |= 0x8000;
        state.cop0[9] = old+uint32_t(cycles);
    }
    if (!wired_written) {
        const unsigned wired = state.cop0[6]&63;
        if (wired > 47) throw Fault("undefined Wired index above 47");
        const unsigned range = 48-wired;
        const unsigned prior = state.cop0[1]&63;
        if (prior < wired || prior > 47) throw Fault("Random index outside Wired range");
        state.cop0[1] = wired+(prior-wired+range-unsigned(cycles%range))%range;
    }
}

} // namespace ee
