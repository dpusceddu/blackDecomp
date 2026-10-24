#include "vu.hpp"
#include "fpu.hpp"

#include <algorithm>
#include <bit>
#include <limits>
#include <string_view>

namespace ee {
namespace {
bool lane_enabled(unsigned mask, unsigned lane) { return mask & (8u >> lane); }
unsigned lanes(uint32_t word) { return word >> 21 & 15; }
unsigned lane_mask(unsigned lane) { return 8u >> lane; }
int signed_bits(uint32_t value, unsigned bits) {
    const uint32_t mask = (1u << bits)-1;
    value &= mask;
    return int(value & (mask>>1))-int(value & (1u << (bits-1)));
}
bool arithmetic(std::string_view name) {
    return name.starts_with("vadd") || name.starts_with("vsub") || name.starts_with("vmul") ||
           name.starts_with("vmadd") || name.starts_with("vmsub") || name.starts_with("vop");
}
uint32_t scaled_integer(uint32_t bits, unsigned fraction) {
    const unsigned exponent = bits >> 23 & 255;
    if (!exponent) return 0;
    if (exponent+fraction > 157) return bits & 0x80000000 ? 0x80000000 : 0x7fffffff;
    return fpu::to_integer(bits+(fraction << 23));
}
uint32_t scaled_float(uint32_t bits, unsigned fraction) {
    auto value = fpu::from_integer(bits);
    if (value & 0x7fffffff) value -= fraction << 23;
    return value;
}
struct Source { enum Kind { vector, broadcast, immediate, quotient, none } kind = vector; unsigned component = 0; };
Source source(const Decoded& d) {
    const unsigned fn = d.word&63, extended = (d.word&3) | (d.word >> 4 & 0x7c);
    if (fn < 0x1c) return {Source::broadcast,fn&3};
    if (fn >= 0x3c) {
        if (extended < 0x10 || (extended >= 0x18 && extended <= 0x1b)) return {Source::broadcast,extended&3};
        if ((extended >= 0x10 && extended <= 0x17) || extended == 0x1d) return {Source::none};
        if (extended == 0x1c || extended == 0x20 || extended == 0x21 || extended == 0x24 || extended == 0x25) return {Source::quotient};
        if (extended == 0x1e || extended == 0x22 || extended == 0x23 || extended == 0x26 || extended == 0x27) return {Source::immediate};
    } else {
        if (fn == 0x1c || fn == 0x20 || fn == 0x21 || fn == 0x24 || fn == 0x25) return {Source::quotient};
        if (fn == 0x1d || fn == 0x1e || fn == 0x1f || fn == 0x22 || fn == 0x23 || fn == 0x26 || fn == 0x27) return {Source::immediate};
    }
    return {};
}
} // namespace

void VuEngine::advance(uint64_t cycle) {
    s_.vu.cycle = std::max(s_.vu.cycle,cycle);
    auto& pending = s_.vu.pending;
    std::stable_sort(pending.begin(),pending.end(),[](const auto& a,const auto& b) { return a.ready < b.ready; });
    size_t consumed = 0;
    for (const auto& write : pending) {
        if (write.ready > s_.vu.cycle) break;
        ++consumed;
        if (write.kind == VuWriteKind::vector) {
            if (write.reg) for (unsigned lane = 0; lane < 4; ++lane)
                if (lane_enabled(write.mask,lane)) s_.vf[write.reg].w[lane] = write.value.w[lane];
        } else if (write.kind == VuWriteKind::integer) {
            if (write.reg) s_.vi[write.reg] = write.value.w[0]&0xffff;
        } else if (write.kind == VuWriteKind::mac) {
            s_.vi[17] = write.value.w[0];
            s_.vi[16] = (s_.vi[16]&~15u) | write.flags | (write.flags << 6) | write.sticky;
        } else if (write.kind == VuWriteKind::clip) s_.vi[18] = write.value.w[0]&0xffffff;
        else if (write.kind == VuWriteKind::status) s_.vi[16] = (s_.vi[16]&0x3f) | (write.value.w[0]&0xfc0);
        else if (write.kind == VuWriteKind::quotient) {
            s_.vi[22] = write.value.w[0];
            s_.vi[16] = (s_.vi[16]&~0x30u) | write.flags | (write.flags << 6);
        }
    }
    pending.erase(pending.begin(),pending.begin()+consumed);
    s_.vi[0] = 0;
    s_.vf[0].w = {0,0,0,0x3f800000};
}
void VuEngine::drain() {
    uint64_t last = s_.vu.cycle;
    for (const auto& write : s_.vu.pending) last = std::max(last,write.ready);
    advance(last);
}
void VuEngine::synchronize_vector(unsigned reg,bool macro_only) {
    uint64_t ready = s_.vu.cycle;
    for (const auto& write : s_.vu.pending)
        if (reg && write.reg == reg && (!macro_only || write.macro) &&
            (write.kind == VuWriteKind::vector || (macro_only && write.kind == VuWriteKind::integer)))
            ready = std::max(ready,write.ready);
    catch_up(ready);
}
void VuEngine::synchronize_control(unsigned reg,bool macro_only) {
    uint64_t ready = s_.vu.cycle;
    for (const auto& write : s_.vu.pending)
        if ((!macro_only || write.macro) &&
            ((reg && reg < 16 && write.reg == reg && (write.kind == VuWriteKind::integer ||
                 (macro_only && write.kind == VuWriteKind::vector))) ||
            (reg == 16 && (write.kind == VuWriteKind::mac || write.kind == VuWriteKind::status || write.kind == VuWriteKind::quotient)) ||
            (reg == 17 && write.kind == VuWriteKind::mac) || (reg == 18 && write.kind == VuWriteKind::clip) ||
            (reg == 22 && write.kind == VuWriteKind::quotient))) ready = std::max(ready,write.ready);
    catch_up(ready);
}
uint64_t VuEngine::ready(const Access& upper,const Access& lower) const {
    uint64_t ready = s_.vu.cycle;
    for (unsigned reg = 1; reg < 32; ++reg) for (unsigned lane = 0; lane < 4; ++lane)
        if (lane_enabled(upper.vf[reg] | lower.vf[reg],lane)) ready = std::max(ready,s_.vu.vector_ready[reg][lane]);
    for (unsigned reg = 1; reg < 16; ++reg)
        if ((upper.vi | lower.vi) & (1u << reg)) ready = std::max(ready,s_.vu.integer_ready[reg]);
    if (upper.quotient || lower.quotient) for (const auto& write : s_.vu.pending)
        if (write.kind == VuWriteKind::quotient) ready = std::max(ready,write.ready);
    return ready;
}
void VuEngine::vector_write(const Effect& effect) {
    if (!effect.reg || !effect.mask) return;
    VuWrite write{VuWriteKind::vector,s_.vu.cycle+4,effect.reg,effect.mask,effect.value};
    for (unsigned lane = 0; lane < 4; ++lane) if (lane_enabled(effect.mask,lane))
        s_.vu.vector_ready[effect.reg][lane] = write.ready;
    s_.vu.pending.push_back(write);
}
void VuEngine::integer_write(unsigned reg,uint32_t value,bool flag_bypass,bool load) {
    reg &= 15;
    if (!reg) return;
    if (load) {
        VuWrite write{VuWriteKind::integer,s_.vu.cycle+4,reg};
        write.value.w[0] = value;
        s_.vu.integer_ready[reg] = write.ready;
        s_.vu.pending.push_back(write);
    } else {
        s_.vu.branch_previous[reg] = uint16_t(s_.vi[reg]);
        s_.vu.branch_ready[reg] = s_.vu.cycle+(flag_bypass ? 1 : 2);
        s_.vi[reg] = value&0xffff;
    }
}
uint16_t VuEngine::branch_value(unsigned reg) const {
    reg &= 15;
    return s_.vu.cycle < s_.vu.branch_ready[reg] ? s_.vu.branch_previous[reg] : uint16_t(s_.vi[reg]);
}
void VuEngine::schedule_flags(uint32_t mac,uint32_t sticky) {
    uint32_t current = 0;
    for (unsigned flag = 0; flag < 4; ++flag) if (mac & (15u << (flag*4))) current |= 1u << flag;
    VuWrite write{VuWriteKind::mac,s_.vu.cycle+4};
    write.value.w[0] = mac; write.flags = current; write.sticky = sticky;
    s_.vu.pending.push_back(write);
}

VuEngine::Access VuEngine::upper_access(const Decoded& d) const {
    Access access;
    const auto& n = d.name;
    const unsigned mask = lanes(d.word);
    if (n == "vnop") return access;
    if (n == "vclipw") { access.vf[d.rd] = 14; access.vf[d.rt] |= 1; return access; }
    access.vf[d.rd] = mask;
    if (n.starts_with("vitof") || n.starts_with("vftoi") || n == "vabs") return access;
    if (n == "vopmula" || n == "vopmsub") { access.vf[d.rd] = 14; access.vf[d.rt] |= 14; return access; }
    const auto operand = source(d);
    if (operand.kind == Source::immediate || operand.kind == Source::quotient || operand.kind == Source::none) return access;
    access.vf[d.rt] |= operand.kind == Source::broadcast ? lane_mask(operand.component) : mask;
    return access;
}
VuEngine::Effect VuEngine::upper(const Decoded& d) {
    const auto& n = d.name;
    const unsigned mask = lanes(d.word);
    if (n == "vnop") return {};
    if (n == "vclipw") {
        uint32_t bits = 0;
        const auto bound = fpu::flush_zero(s_.vf[d.rt].w[3])&0x7fffffff;
        for (unsigned lane = 0; lane < 3; ++lane) {
            const uint32_t value = fpu::flush_zero(s_.vf[d.rd].w[lane]);
            if ((value&0x7fffffff) > bound) bits |= 1u << (lane*2+unsigned(bool(value&0x80000000)));
        }
        s_.vu.clip_history = ((s_.vu.clip_history << 6)|bits)&0xffffff;
        VuWrite write{VuWriteKind::clip,s_.vu.cycle+4};
        write.value.w[0] = s_.vu.clip_history;
        s_.vu.pending.push_back(write);
        return {};
    }
    const bool conversion = n.starts_with("vitof") || n.starts_with("vftoi");
    const bool accumulator = n.starts_with("vadda") || n.starts_with("vsuba") || n.starts_with("vmula") ||
                             n.starts_with("vmadda") || n.starts_with("vmsuba") || n == "vopmula";
    Effect effect{conversion || n == "vabs" ? d.rt : d.sa,mask};
    if (n == "vopmula" || n == "vopmsub") effect.mask &= 14;
    uint32_t mac = 0, sticky = 0;
    for (unsigned lane = 0; lane < 4; ++lane) if (lane_enabled(effect.mask,lane)) {
        uint32_t a = s_.vf[d.rd].w[lane], b = s_.vf[d.rt].w[lane];
        fpu::Arithmetic value;
        if (conversion) {
            const auto fraction = unsigned(std::stoul(n.substr(5)));
            value.bits = n.starts_with("vitof") ? scaled_float(a,fraction) : scaled_integer(a,fraction);
        } else if (n == "vabs") value.bits = a&0x7fffffff;
        else {
            const auto operand = source(d);
            if (operand.kind == Source::immediate) b = s_.vi[21];
            else if (operand.kind == Source::quotient) b = s_.vi[22];
            else if (operand.kind == Source::broadcast) b = s_.vf[d.rt].w[operand.component];
            if (n == "vopmula" || n == "vopmsub") {
                // Both operations use the same cyclic lane product. The
                // instruction operands, not these lanes, are swapped for a cross.
                const unsigned x = (lane+1)%3;
                const unsigned y = (lane+2)%3;
                a = s_.vf[d.rd].w[x]; b = s_.vf[d.rt].w[y];
            }
            if (n.starts_with("vadd")) value = fpu::add(a,b);
            else if (n.starts_with("vsub")) value = fpu::subtract(a,b);
            else if (n.starts_with("vmul") || n == "vopmula") value = fpu::multiply(a,b);
            else if (n.starts_with("vmadd") || n.starts_with("vmsub") || n == "vopmsub") {
                const auto product = fpu::multiply(a,b);
                // VU manual 3.3.2/3.3.6: both calculation stages contribute
                // sticky flags; only the final stage contributes MAC/current.
                if (!(product.bits&0x7fffffff)) sticky |= 1u<<6;
                if (product.bits&0x80000000) sticky |= 1u<<7;
                if (product.underflow) sticky |= 1u<<8;
                if (product.overflow) sticky |= 1u<<9;
                value = fpu::accumulate_product(s_.vacc.w[lane],product,s_.vu.accumulator_overflow[lane],n.starts_with("vmsub") || n == "vopmsub");
            }
            else if (n.starts_with("vmax")) value.bits = fpu::maximum(a,b);
            else if (n.starts_with("vmini")) value.bits = fpu::minimum(a,b);
            else throw Fault("unsupported VU upper operation: "+n);
        }
        effect.value.w[lane] = value.bits;
        if (arithmetic(n)) {
            if (!(value.bits&0x7fffffff)) mac |= lane_mask(lane);
            if (value.bits&0x80000000) mac |= lane_mask(lane)<<4;
            if (value.underflow) mac |= lane_mask(lane)<<8;
            if (value.overflow) mac |= lane_mask(lane)<<12;
            if (value.product_underflow) sticky |= 1u << 8;
        }
        if (accumulator) { s_.vacc.w[lane] = value.bits; s_.vu.accumulator_overflow[lane] = value.overflow; }
    }
    if (arithmetic(n)) schedule_flags(mac,sticky);
    return accumulator ? Effect{} : effect;
}

Decoded VuEngine::decode_lower(uint32_t word) {
    Decoded d = decode(0x4a000000 | (word&0x1ffffff));
    d.word = word;
    d.name = "reserved";
    switch (word >> 25) {
    case 0: d.name = "lq"; break;
    case 1: d.name = "sq"; break;
    case 4: d.name = "ilw"; break;
    case 5: d.name = "isw"; break;
    case 8: d.name = "iaddiu"; break;
    case 9: d.name = "isubiu"; break;
    case 0x10: d.name = "fceq"; break;
    case 0x11: d.name = "fcset"; break;
    case 0x12: d.name = "fcand"; break;
    case 0x13: d.name = "fcor"; break;
    case 0x14: d.name = "fseq"; break;
    case 0x15: d.name = "fsset"; break;
    case 0x16: d.name = "fsand"; break;
    case 0x17: d.name = "fsor"; break;
    case 0x18: d.name = "fmeq"; break;
    case 0x1a: d.name = "fmand"; break;
    case 0x1b: d.name = "fmor"; break;
    case 0x1c: d.name = "fcget"; break;
    case 0x20: d.name = "b"; break;
    case 0x21: d.name = "bal"; break;
    case 0x24: d.name = "jr"; break;
    case 0x25: d.name = "jalr"; break;
    case 0x28: d.name = "ibeq"; break;
    case 0x29: d.name = "ibne"; break;
    case 0x2c: d.name = "ibltz"; break;
    case 0x2d: d.name = "ibgtz"; break;
    case 0x2e: d.name = "iblez"; break;
    case 0x2f: d.name = "ibgez"; break;
    case 0x40:
        d = decode(0x4a000000 | (word&0x1ffffff));
        d.word = word;
        if (d.sa == 26 && (word&63) == 0x3c) d.name = "xtop";
        if (d.sa == 26 && (word&63) == 0x3d) d.name = "xitop";
        break;
    }
    return d;
}
bool VuEngine::lower_supported(const Decoded& d) {
    static const std::set<std::string> operations = {
        "lq","sq","ilw","isw","iaddiu","isubiu","fceq","fcset","fcand","fcor","fseq","fsset","fsand","fsor",
        "fmeq","fmand","fmor","fcget","b","bal","jr","jalr","ibeq","ibne","ibltz","ibgtz","iblez","ibgez",
        "viadd","visub","viaddi","viand","vior","vmove","vmr32","vlqi","vsqi","vlqd","vsqd","vdiv","vsqrt",
        "vrsqrt","vwaitq","vmtir","vmfir","vilwr","viswr","vrnext","vrget","vrinit","vrxor","xitop"
    };
    return operations.contains(d.name);
}

VuEngine::Access VuEngine::lower_access(const Decoded& d) const {
    Access access;
    const auto& n = d.name;
    const unsigned mask = lanes(d.word);
    if (n == "vmove" || n == "vmr32") {
        if (n == "vmove") access.vf[d.rd] = mask;
        else for (unsigned lane = 0; lane < 4; ++lane) if (lane_enabled(mask,lane)) access.vf[d.rd] |= lane_mask((lane+1)%4);
    } else if (n == "lq" || n == "vlqi" || n == "vlqd" || n == "ilw" || n == "vilwr") access.vi = 1u << (d.rd&15);
    else if (n == "sq" || n == "vsqi" || n == "vsqd") {
        access.vi = 1u << (d.rt&15); access.vf[d.rd] = mask;
    } else if (n == "isw" || n == "viswr" || n == "viadd" || n == "visub" || n == "viand" || n == "vior" ||
               n == "ibeq" || n == "ibne" || n.starts_with("fm")) access.vi = (1u << (d.rd&15)) | (1u << (d.rt&15));
    else if (n == "viaddi" || n == "iaddiu" || n == "isubiu" || n == "jr" || n == "jalr" || n.starts_with("ib") || n == "vmfir")
        access.vi = 1u << (d.rd&15);
    else if (n == "vmtir" || n == "vrinit" || n == "vrxor") access.vf[d.rd] = lane_mask(d.word >> 21 & 3);
    else if (n == "vdiv" || n == "vrsqrt" || n == "vsqrt") {
        if (n != "vsqrt") access.vf[d.rd] = lane_mask(d.word >> 21 & 3);
        access.vf[d.rt] |= lane_mask(d.word >> 23 & 3);
        access.quotient = true;
    } else if (n == "vwaitq") access.quotient = true;
    return access;
}

uint32_t VuEngine::read_word(uint32_t qword,unsigned lane) {
    if (!(qword&0x400)) return uint32_t(memory_.read(0x11004000 | (qword&255)*16 | lane*4,4,&trace_,access_pc_));
    const uint32_t address = (qword&0x43f)*16+lane*4;
    const auto response = memory_.hardware_responses.find({address,4});
    const uint32_t result = response == memory_.hardware_responses.end() ? 0 : uint32_t(response->second);
    Event event{EventKind::vu1_read,access_pc_,address};
    event.default_response = response == memory_.hardware_responses.end();
    for (unsigned i = 0; i < 4; ++i) event.bytes.push_back(uint8_t(result >> (8*i)));
    trace_.events.push_back(event);
    return result;
}
void VuEngine::write_word(uint32_t qword,unsigned lane,uint32_t value) {
    if (!(qword&0x400)) { memory_.write(0x11004000 | (qword&255)*16 | lane*4,4,value,&trace_,access_pc_); return; }
    Event event{EventKind::vu1_write,access_pc_,(qword&0x43f)*16+lane*4};
    for (unsigned i = 0; i < 4; ++i) event.bytes.push_back(uint8_t(value >> (8*i)));
    trace_.events.push_back(event);
}

VuEngine::Effect VuEngine::lower(const Decoded& d,uint32_t pc,const std::array<Quad,32>& vf,
                                 const std::array<uint32_t,32>& vi,bool macro) {
    access_pc_ = pc;
    const auto& n = d.name;
    const unsigned mask = lanes(d.word), is = d.rd&15, it = d.rt&15, id = d.sa&15;
    const uint32_t a = vi[is], b = vi[it];
    if (n == "viadd" || n == "visub" || n == "viand" || n == "vior")
        integer_write(id,n == "viadd" ? a+b : n == "visub" ? a-b : n == "viand" ? a&b : a|b);
    else if (n == "viaddi") integer_write(it,a+uint32_t(signed_bits(d.sa,5)));
    else if (n == "iaddiu" || n == "isubiu") {
        const uint32_t immediate = (d.word&0x7ff) | (d.word >> 10 & 0x7800);
        integer_write(it,n == "iaddiu" ? a+immediate : a-immediate);
    } else if (n == "vmove" || n == "vmr32" || n == "vmfir") {
        Effect effect{d.rt,mask};
        for (unsigned lane = 0; lane < 4; ++lane) if (lane_enabled(mask,lane))
            effect.value.w[lane] = n == "vmfir" ? uint32_t(signed_bits(a,16)) : vf[d.rd].w[n == "vmr32" ? (lane+1)%4 : lane];
        return effect;
    } else if (n == "vmtir") integer_write(it,vf[d.rd].w[d.word >> 21 & 3]);
    else if (n == "lq" || n == "vlqi" || n == "vlqd" || n == "sq" || n == "vsqi" || n == "vsqd") {
        const bool load = n == "lq" || n == "vlqi" || n == "vlqd";
        uint32_t address = load ? a : b;
        if (n == "vlqd" || n == "vsqd") --address;
        if (n == "lq" || n == "sq") address += uint32_t(signed_bits(d.word,11));
        Effect effect{d.rt,mask};
        for (unsigned lane = 0; lane < 4; ++lane) if (lane_enabled(mask,lane)) {
            if (load) effect.value.w[lane] = read_word(address,lane);
            else write_word(address,lane,vf[d.rd].w[lane]);
        }
        // Micro mode bypasses the address update after one cycle. Macro mode
        // writes it with the instruction's four-cycle register result.
        if (n == "vlqi" || n == "vsqi") integer_write(load ? is : it,address+1,false,macro);
        if (n == "vlqd" || n == "vsqd") integer_write(load ? is : it,address,false,macro);
        return load ? effect : Effect{};
    } else if (n == "ilw" || n == "isw" || n == "vilwr" || n == "viswr") {
        const bool load = n == "ilw" || n == "vilwr";
        if (load && std::popcount(mask) != 1) throw Fault("VU integer load requires one selected lane");
        const uint32_t address = a+((n == "ilw" || n == "isw") ? uint32_t(signed_bits(d.word,11)) : 0);
        uint32_t value = 0;
        for (unsigned lane = 0; lane < 4; ++lane) if (lane_enabled(mask,lane)) {
            if (load) value = read_word(address,lane); else write_word(address,lane,b&0xffff);
        }
        if (load && mask) integer_write(it,value,false,true);
    } else if (n == "vdiv" || n == "vsqrt" || n == "vrsqrt") {
        const uint32_t fs = vf[d.rd].w[d.word >> 21 & 3], ft = vf[d.rt].w[d.word >> 23 & 3];
        const auto value = n == "vdiv" ? fpu::divide(fs,ft) : n == "vsqrt" ? fpu::square_root(ft) : fpu::reciprocal_root(fs,ft);
        VuWrite write{VuWriteKind::quotient,s_.vu.cycle+(n == "vrsqrt" ? 13 : 7)};
        write.value.w[0] = value.bits; write.flags = (value.invalid ? 16 : 0) | (value.divide_zero ? 32 : 0);
        s_.vu.pending.push_back(write);
    } else if (n == "vwaitq") return {};
    else if (n == "vrinit" || n == "vrxor" || n == "vrget" || n == "vrnext") {
        if (n == "vrinit") s_.vi[20] = 0x3f800000 | (vf[d.rd].w[d.word >> 21 & 3]&0x7fffff);
        else if (n == "vrxor") s_.vi[20] = 0x3f800000 | ((s_.vi[20]^vf[d.rd].w[d.word >> 21 & 3])&0x7fffff);
        else {
            if (n == "vrnext") {
                const uint32_t r = s_.vi[20];
                s_.vi[20] = 0x3f800000 | (((r << 1) | ((r >> 22 ^ r >> 4)&1))&0x7fffff);
            }
            Effect effect{d.rt,mask}; effect.value.w.fill(s_.vi[20]); return effect;
        }
    } else if (n == "fcset") {
        s_.vu.clip_history = d.word&0xffffff;
        VuWrite write{VuWriteKind::clip,s_.vu.cycle+4}; write.value.w[0] = s_.vu.clip_history; s_.vu.pending.push_back(write);
    } else if (n == "fcget") integer_write(it,vi[18]&0xfff,true);
    else if (n == "fceq" || n == "fcand" || n == "fcor") {
        const uint32_t immediate = d.word&0xffffff;
        integer_write(1,n == "fceq" ? vi[18] == immediate : n == "fcand" ? bool(vi[18]&immediate) : (vi[18]|immediate) == 0xffffff,true);
    } else if (n == "fsset") {
        VuWrite write{VuWriteKind::status,s_.vu.cycle+4};
        write.value.w[0] = (d.word&0x7ff) | (d.word >> 10 & 0x800); s_.vu.pending.push_back(write);
    } else if (n == "fseq" || n == "fsand" || n == "fsor") {
        const uint32_t immediate = (d.word&0x7ff) | (d.word >> 10 & 0x800);
        integer_write(it,n == "fseq" ? vi[16] == immediate : n == "fsand" ? vi[16]&immediate : vi[16]|immediate,true);
    } else if (n == "fmeq" || n == "fmand" || n == "fmor") {
        integer_write(it,n == "fmeq" ? vi[17] == a : n == "fmand" ? vi[17]&a : vi[17]|a,true);
    } else if (n == "b" || n == "bal" || n == "jr" || n == "jalr" || n.starts_with("ib")) {
        const auto x = branch_value(is), y = branch_value(it);
        bool take = true;
        if (n == "ibeq") take = x == y;
        if (n == "ibne") take = x != y;
        if (n == "ibltz") take = signed_bits(x,16) < 0;
        if (n == "ibgtz") take = signed_bits(x,16) > 0;
        if (n == "iblez") take = signed_bits(x,16) <= 0;
        if (n == "ibgez") take = signed_bits(x,16) >= 0;
        // JR/JALR take the current bypassed integer input, including when
        // source and link destination alias; conditional branches use backup.
        const uint32_t target = n == "jr" || n == "jalr" ? a*8 : pc+8+uint32_t(signed_bits(d.word,11)*8);
        if (n == "bal" || n == "jalr") integer_write(it,(pc+16)/8);
        if (take) s_.vu.next_pc = target&0xff8;
    } else if (n == "xtop" || n == "xitop") {
        if (n == "xtop") throw Fault("XTOP is a VU1 instruction");
        integer_write(it,uint32_t(memory_.read(0x100038d0,4,&trace_,pc))&0x3ff);
    } else throw Fault("unsupported VU lower operation: "+n);
    return {};
}

void VuEngine::start(uint32_t byte_address) {
    if (byte_address&7) throw Fault("unaligned VU0 entry");
    drain();
    s_.vu.pc = byte_address&0xff8; s_.vu.next_pc = (s_.vu.pc+8)&0xff8;
    s_.vu.end_delay = false; s_.vu.debug_delay = false; s_.vu.m_seen = false; s_.vu.stopped = false;
    s_.vu.clip_history = s_.vi[18];
    s_.vu_micro_running = true;
    s_.vi[29] = (s_.vi[29]&~14u)|1;
}
void VuEngine::reset() {
    const uint64_t cycle = s_.vu.cycle, issued = s_.vu.issued;
    s_.vu = {};
    s_.vu.cycle = cycle; s_.vu.issued = issued;
    s_.vu_micro_running = false;
    s_.vi[16] = s_.vi[17] = s_.vi[18] = 0;
    s_.vi[28] &= ~12u; s_.vi[29] &= ~0xffu;
    // VF/VI general registers and I/Q/R have no specified reset data value.
    // Preserve their supplied contents; discard all pending computation.
}
void VuEngine::force_break() {
    drain();
    s_.vu_micro_running = false;
    s_.vu.stopped = true;
    s_.vu.end_delay = s_.vu.debug_delay = false;
    s_.vi[29] = (s_.vi[29]&~15u)|8;
    s_.vi[26] = s_.vu.pc/8;
}
bool VuEngine::step_until(uint64_t deadline) {
    if (!s_.vu_micro_running) throw Fault("VU0 is not running");
    if (s_.vu.cycle >= deadline) return false;
    const uint32_t pc = s_.vu.pc;
    const uint32_t lo = uint32_t(memory_.read(0x11000000+pc,4));
    const uint32_t hi = uint32_t(memory_.read(0x11000000+pc+4,4));
    const auto& up = decode_cached(0x4a000000 | (hi&0x1ffffff));
    const auto down = decode_lower(lo);
    const bool immediate = hi&0x80000000;
    if (!immediate && !lower_supported(down)) throw Fault("unsupported VU lower instruction: "+down.name);
    if (s_.vu.end_delay && !immediate && (down.name == "ilw" || down.name == "vilwr"))
        throw Fault("VU integer load in E-bit delay slot is undefined");
    const uint64_t issue = ready(upper_access(up),immediate ? Access{} : lower_access(down));
    if (issue >= deadline) { advance(deadline); return false; }
    advance(issue);
    const auto vf = s_.vf; const auto vi = s_.vi;
    const bool ending = s_.vu.end_delay;
    const bool debugging = s_.vu.debug_delay;
    const uint32_t prior_debug_bits = s_.vu.debug_bits;
    s_.vu.pc = s_.vu.next_pc; s_.vu.next_pc = (s_.vu.pc+8)&0xff8;
    const auto upper_effect = upper(up);
    const auto lower_effect = immediate ? Effect{} : lower(down,pc,vf,vi);
    if (immediate) s_.vi[21] = lo;
    vector_write(upper_effect);
    if (!upper_effect.reg || upper_effect.reg != lower_effect.reg) vector_write(lower_effect);
    s_.vu.end_delay = hi&0x40000000;
    s_.vu.m_seen = s_.vu.m_seen || (hi&0x20000000);
    const uint32_t debug_bits = ((hi&0x10000000) && (s_.vi[28]&4) ? 0x10000000 : 0) |
                                ((hi&0x08000000) && (s_.vi[28]&8) ? 0x08000000 : 0);
    const bool branch = down.name == "b" || down.name == "bal" || down.name == "jr" || down.name == "jalr" || down.name.starts_with("ib");
    s_.vu.debug_delay = debug_bits && branch && !immediate;
    s_.vu.debug_bits = debug_bits;
    trace_.micro_instructions.insert(pc);
    ++s_.vu.issued;
    advance(s_.vu.cycle+1);
    if (ending || debugging || (debug_bits && !s_.vu.debug_delay)) {
        s_.vu_micro_running = false; s_.vi[29] &= ~1u;
        s_.vi[26] = s_.vu.pc/8;
        if (debugging || debug_bits) {
            const auto bits = debugging ? prior_debug_bits : debug_bits;
            s_.vu.stopped = true;
            s_.vi[29] |= bits&0x10000000 ? 2 : 4;
            trace_.events.push_back(Event{EventKind::vu_debug,pc,bits});
        }
    }
    return true;
}
void VuEngine::step() {
    step_until(std::numeric_limits<uint64_t>::max());
    if (!s_.vu_micro_running) drain();
}
void VuEngine::catch_up(uint64_t deadline) {
    while (s_.vu_micro_running && s_.vu.cycle < deadline)
        if (!step_until(deadline)) break;
    advance(deadline);
}
void VuEngine::interlock(bool allow_m) {
    if (s_.vu_micro_running) {
        const auto result = run(1000000,allow_m);
        if (result.stop == Stop::fault) throw Fault("VU0 interlock fault: "+result.error);
        if (s_.vu_micro_running && !(allow_m && s_.vu.m_seen)) throw Fault("VU0 interlock instruction budget exhausted");
    }
    if (!s_.vu_micro_running) {
        uint64_t completed = s_.vu.cycle;
        for (const auto& write : s_.vu.pending) if (!write.macro) completed = std::max(completed,write.ready);
        advance(completed);
    }
}
Result VuEngine::run(uint64_t budget,bool stop_on_m) {
    Result result;
    if (stop_on_m && s_.vu_micro_running && s_.vu.m_seen) return result;
    try {
        for (; result.executed < budget && s_.vu_micro_running; ++result.executed) {
            step();
            if (stop_on_m && s_.vu.m_seen) { ++result.executed; return result; }
        }
        if (!s_.vu_micro_running) result.stop = Stop::returned;
    } catch (const Fault& fault) { result.stop = Stop::fault; result.error = fault.what(); }
    return result;
}

uint32_t VuEngine::macro_registers(const Decoded& d,bool upper_operation) const {
    const auto access = upper_operation ? upper_access(d) : lower_access(d);
    uint32_t registers = access.vi;
    for (unsigned reg = 1; reg < 32; ++reg) if (access.vf[reg]) registers |= 1u<<reg;
    const auto& n = d.name;
    if (upper_operation) {
        const bool accumulator = n.starts_with("vadda") || n.starts_with("vsuba") || n.starts_with("vmula") ||
                                 n.starts_with("vmadda") || n.starts_with("vmsuba") || n == "vopmula";
        if (!accumulator && n != "vnop" && n != "vclipw")
            registers |= 1u << (n.starts_with("vitof") || n.starts_with("vftoi") || n == "vabs" ? d.rt : d.sa);
    } else {
        if (n == "viadd" || n == "visub" || n == "viand" || n == "vior") registers |= 1u<<(d.sa&15);
        else if (n == "viaddi" || n == "vmtir" || n == "vilwr") registers |= 1u<<(d.rt&15);
        else if (n == "vmove" || n == "vmr32" || n == "vmfir" || n == "vrget" || n == "vrnext") registers |= 1u<<d.rt;
        else if (n == "vlqi" || n == "vlqd") registers |= (1u<<d.rt) | (1u<<(d.rd&15));
        else if (n == "vsqi" || n == "vsqd") registers |= 1u<<(d.rt&15);
    }
    return registers&~1u;
}
void VuEngine::macro(const Decoded& d) {
    interlock();
    if (s_.vu.stopped) throw Fault("VU0 macro arithmetic in debug stop state is indeterminate");
    const bool upper_operation = arithmetic(d.name) || d.name.starts_with("vmax") || d.name.starts_with("vmini") ||
        d.name.starts_with("vitof") || d.name.starts_with("vftoi") || d.name == "vabs" || d.name == "vclipw" || d.name == "vnop";
    uint64_t issue = upper_operation ? ready(upper_access(d),{}) : ready({},lower_access(d));
    // VU manual 5.4.2: macro hazards use whole register numbers, including
    // destination WAW hazards and the VF/VI number alias. Micro mode retains
    // its per-lane RAW checks and does not use these additional interlocks.
    const auto registers = macro_registers(d,upper_operation);
    for (const auto& write : s_.vu.pending)
        if (write.macro && write.reg && (registers&(1u<<write.reg)) &&
            (write.kind == VuWriteKind::vector || write.kind == VuWriteKind::integer))
            issue = std::max(issue,write.ready);
    advance(issue);
    const size_t prior = s_.vu.pending.size();
    if (upper_operation) vector_write(upper(d));
    else vector_write(lower(d,s_.vu.pc,s_.vf,s_.vi,true));
    for (size_t i = prior; i < s_.vu.pending.size(); ++i) s_.vu.pending[i].macro = true;
    advance(s_.vu.cycle+1);
}

} // namespace ee
