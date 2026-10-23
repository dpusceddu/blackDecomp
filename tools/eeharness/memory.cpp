#include "ee.hpp"

#include <algorithm>
#include <bit>
#include <cstring>
#include <limits>

namespace ee {

uint32_t Quad::lane(unsigned index, unsigned bits) const {
    return (w.at(index * bits / 32) >> (index * bits % 32)) &
           (bits == 32 ? 0xffffffffu : (1u << bits) - 1);
}
void Quad::lane(unsigned index, unsigned bits, uint32_t value) {
    auto& word = w.at(index * bits / 32);
    const unsigned shift = index * bits % 32;
    const uint32_t mask = bits == 32 ? 0xffffffffu : (1u << bits) - 1;
    word = (word & ~(mask << shift)) | ((value & mask) << shift);
}

State::State() {
    vf[0].w[3] = 0x3f800000; // VF00 = (0, 0, 0, 1)
    fcr[0] = 0x2e00;
    fcr[31] = 0x1000001;
    cop0[1] = 47; // Random: highest TLB entry at reset
    cop0[12] = 0x70000000; // runnable synthetic profile: COP0/COP1/COP2 enabled
}
void State::start(uint32_t address) {
    pc = address;
    next_pc = address + 4;
    delay_slot = false;
    pending_call = false;
}

Memory::Memory() : pages_((ram_size + scratch_size + 2 * vu_size) / 4096) {
    // All untouched pages share an immutable zero page until first write.
    auto zero = std::make_shared<Page>();
    std::fill(pages_.begin(), pages_.end(), zero);
}
bool Memory::candidate_address(uint32_t address,unsigned width) const {
    const auto next=candidate_regions.upper_bound(address);
    if(next==candidate_regions.begin())return false;
    const auto& [base,bytes]=*std::prev(next);
    return uint64_t(address)+width<=uint64_t(base)+bytes.size();
}
uint32_t Memory::physical(uint32_t a) {
    if (a >= 0x80000000 && a < 0xc0000000) return a & 0x1fffffff;
    if (a >= 0x20000000 && a < 0x40000000) return a & 0x0fffffff;
    return a;
}
uint32_t Memory::offset(uint32_t a, unsigned width) {
    const uint64_t end = uint64_t(a) + width;
    if (a < ram_size && end <= ram_size) return a;
    if (a >= 0x70000000 && end <= 0x70000000ull + scratch_size)
        return ram_size + a - 0x70000000;
    if (a >= 0x11000000 && end <= 0x11001000)
        return ram_size + scratch_size + a - 0x11000000;
    if (a >= 0x11004000 && end <= 0x11005000)
        return ram_size + scratch_size + vu_size + a - 0x11004000;
    throw Fault("unmapped memory access");
}
uint8_t Memory::byte(uint32_t a) const { return (*pages_.at(a / 4096))[a % 4096]; }
void Memory::byte(uint32_t a, uint8_t v) {
    auto& page = pages_.at(a / 4096);
    if (page.use_count() != 1) page = std::make_shared<Page>(*page);
    (*page)[a % 4096] = v;
}
static bool hardware(uint32_t a, unsigned width) {
    const uint64_t end = uint64_t(a) + width;
    return (a >= 0x10000000 && end <= 0x10010000) ||
           (a >= 0x11008000 && end <= 0x11010000) || // VU1 code/data are external
           (a >= 0x12000000 && end <= 0x12002000) ||
           (a >= 0x1c000000 && end <= 0x1c200000) || // IOP RAM
           (a >= 0x1f800000 && end <= 0x1f810000);
}
uint64_t Memory::read(uint32_t address, unsigned width, Trace* trace, uint32_t pc) {
    return read_physical(physical(address),width,trace,pc);
}
uint64_t Memory::read_physical(uint32_t a, unsigned width, Trace* trace, uint32_t pc) {
    if (width != 1 && width != 2 && width != 4 && width != 8) throw Fault("invalid read width");
    if (candidate_address(a,width)) {
        const auto region=std::prev(candidate_regions.upper_bound(a));
        uint64_t value=0;
        for(unsigned i=0;i<width;++i)value|=uint64_t(region->second[a-region->first+i])<<(8*i);
        return value;
    }
    if (hardware(a, width)) {
        const auto response = hardware_responses.find({a, width});
        uint64_t value = response == hardware_responses.end() ? 0 : response->second;
        Event event{EventKind::hardware_read, pc, a};
        event.default_response = response == hardware_responses.end();
        for (unsigned i = 0; i < width; ++i) event.bytes.push_back(uint8_t(value >> (8*i)));
        if (trace) trace->events.push_back(event);
        return width == 8 ? value : value & ((uint64_t(1) << (width*8)) - 1);
    }
    const auto off = offset(a, width);
    uint64_t value = 0;
    if constexpr (std::endian::native == std::endian::little) {
        if ((off%4096)+width <= 4096) {
            std::memcpy(&value,pages_.at(off/4096)->data()+off%4096,width);
            return value;
        }
    }
    for (unsigned i = 0; i < width; ++i) value |= uint64_t(byte(off + i)) << (8*i);
    return value;
}
void Memory::write(uint32_t address, unsigned width, uint64_t value, Trace* trace, uint32_t pc) {
    write_physical(physical(address),width,value,trace,pc);
}
void Memory::write_physical(uint32_t a, unsigned width, uint64_t value, Trace* trace, uint32_t pc) {
    if (width != 1 && width != 2 && width != 4 && width != 8) throw Fault("invalid write width");
    if(candidate_address(a,width))throw Fault("write to immutable differential candidate");
    if (hardware(a, width)) {
        Event event{EventKind::hardware_write, pc, a};
        for (unsigned i = 0; i < width; ++i) event.bytes.push_back(uint8_t(value >> (8*i)));
        if (trace) trace->events.push_back(event);
        if (scratch_dma) scratch_dma_write(a,width,value,trace,pc);
        return;
    }
    const auto off = offset(a, width);
    if constexpr (std::endian::native == std::endian::little) {
        if ((off%4096)+width <= 4096) {
            auto& page = pages_.at(off/4096);
            if (page.use_count() != 1) page = std::make_shared<Page>(*page);
            std::memcpy(page->data()+off%4096,&value,width);
            if (trace) for (unsigned i = 0; i < width; ++i) trace->writes[a+i] = uint8_t(value >> (8*i));
            return;
        }
    }
    for (unsigned i = 0; i < width; ++i) {
        const auto b = uint8_t(value >> (8*i));
        byte(off + i, b);
        if (trace) trace->writes[a + i] = b;
    }
}
void Memory::scratch_dma_write(uint32_t a,unsigned width,uint64_t value,Trace* trace,uint32_t pc) {
    const bool from=a>=0x1000d000 && a<0x1000d100;
    const bool to=a>=0x1000d400 && a<0x1000d500;
    const bool global=a==0x1000e000 || a==0x1000e030 || a==0x1000e040 || a==0x1000e050;
    const bool output=a==0x10009000 || a==0x1000a000 || a==0x10003010 || a==0x10005000;
    if ((!from && !to && !global && !output) || (width!=4 && !(a==0x10005000 && width==8))) return;
    const auto get=[&](uint32_t reg){
        const auto found=hardware_responses.find({reg,4});
        return found==hardware_responses.end()?0u:uint32_t(found->second);
    };
    const auto set=[&](uint32_t reg,uint32_t v){
        hardware_responses[{reg,4}]=v;
        for(unsigned i=0;i<4;++i)hardware_responses[{reg+i,1}]=(v>>(8*i))&255;
        hardware_responses[{reg,2}]=v&0xffff;hardware_responses[{reg+2,2}]=v>>16;
        const uint32_t aligned=reg&~7u;const unsigned shift=(reg&7)*8;
        auto& full=hardware_responses[{aligned,8}];full=(full&~(uint64_t(0xffffffff)<<shift))|(uint64_t(v)<<shift);
        for(auto key:{std::pair{reg,4u},std::pair{reg,2u},std::pair{reg+2,2u},std::pair{aligned,8u},
                      std::pair{reg,1u},std::pair{reg+1,1u},std::pair{reg+2,1u},std::pair{reg+3,1u}})
            hardware_updates[key]=hardware_responses[key];
    };
    if(output){
        // Output-only device completion profile. This exposes control/FIFO
        // acknowledgements; render payloads are recorded and discarded.
        auto status=get(0x10003020);
        if(a==0x10005000 && (uint32_t(value)&0x7fff0000)==0x06000000)
            status=(status&~2u)|((value&0x8000)?2u:0u); // VIF MSKPATH3
        if(a==0x10003010)status=(status&~4u)|(uint32_t(value)&4);
        if(a==0x1000a000 && (value&0x100))status=(status&~0x1f000000u)|0x1000000;
        if(a==0x10009000 && (value&0x100))status&=~0x1f000000u;
        set(0x10003020,status);return;
    }
    set(a,uint32_t(value));if(global)return;
    const uint32_t base=from?0x1000d000:0x1000d400;
    if(a!=base || !(value&0x100))return;
    const unsigned mode=(value>>2)&3;
    if(mode==1 || mode==3)throw Fault("scratchpad chain/reserved DMA needs a replay backend");
    uint32_t ram=get(base+0x10)&0x1ffffff0;
    uint32_t spr=get(base+0x80)&0x3ff0;
    const uint32_t length=(get(base+0x20)&0xffff)*16;
    const uint32_t control=get(0x1000e000),mask=get(0x1000e040),ring=get(0x1000e050);
    const uint32_t interleave=get(0x1000e030);
    const unsigned take=(interleave>>16)&255,skip=interleave&255;
    if(mode==2 && !take)throw Fault("zero transfer size in interleaved scratchpad DMA");
    for(uint32_t i=0;i<length;i+=16){
        if(from){
            const uint32_t dest=(control&0xc)?ring|(ram&mask):ram;
            write_quad_physical(dest,read_quad_physical(0x70000000|spr),trace,pc);
        }else write_quad_physical(0x70000000|spr,read_quad_physical(ram),trace,pc);
        ram+=16;spr=(spr+16)&0x3fff;
        if(mode==2 && ((i/16+1)%take)==0)ram+=skip*16;
    }
    set(base,uint32_t(value)&~0x100u);set(base+0x20,0);set(base+0x10,ram);set(base+0x80,spr);
}
Quad Memory::read_quad(uint32_t a, Trace* trace, uint32_t pc) {
    return read_quad_physical(physical(a),trace,pc);
}
Quad Memory::read_quad_physical(uint32_t a, Trace* trace, uint32_t pc) {
    Quad q;
    q.low(read_physical(a, 8, trace, pc));
    q.high(read_physical(a+8, 8, trace, pc));
    return q;
}
void Memory::write_quad(uint32_t a, const Quad& q, Trace* trace, uint32_t pc) {
    write_quad_physical(physical(a),q,trace,pc);
}
void Memory::write_quad_physical(uint32_t a, const Quad& q, Trace* trace, uint32_t pc) {
    // Validate the entire range before changing any byte.
    if (!hardware(a, 16)) (void)offset(a, 16);
    write_physical(a, 8, q.low(), trace, pc);
    write_physical(a+8, 8, q.high(), trace, pc);
}
void Memory::load(uint32_t a, std::span<const uint8_t> data) {
    if (data.size() > std::numeric_limits<uint32_t>::max()) throw Fault("oversize input");
    const auto off = offset(physical(a), unsigned(data.size()));
    for (size_t i = 0; i < data.size(); ++i) byte(off + uint32_t(i), data[i]);
}
std::vector<uint8_t> Memory::bytes(uint32_t a, uint32_t size) const {
    const auto off = offset(physical(a), size);
    std::vector<uint8_t> out(size);
    for (uint32_t i = 0; i < size; ++i) out[i] = byte(off + i);
    return out;
}

void load_elf(Memory& memory, std::span<const uint8_t> data) {
    const auto get = [&](size_t off, unsigned width) {
        if (off > data.size() || width > data.size() - off) throw Fault("truncated ELF");
        uint32_t v = 0;
        for (unsigned i = 0; i < width; ++i) v |= uint32_t(data[off+i]) << (8*i);
        return v;
    };
    if (data.size() < 52 || get(0, 4) != 0x464c457f || data[4] != 1 || data[5] != 1 || get(18, 2) != 8)
        throw Fault("expected little-endian MIPS ELF32");
    const size_t table = get(28, 4), stride = get(42, 2), count = get(44, 2);
    if (stride < 32 || table > data.size() || count > (data.size()-table)/stride)
        throw Fault("invalid ELF program header table");
    for (size_t i = 0; i < count; ++i) {
        const size_t p = table + stride*i;
        if (get(p, 4) != 1) continue;
        const uint32_t off = get(p+4, 4), address = get(p+8, 4);
        const uint32_t filesz = get(p+16, 4), memsz = get(p+20, 4);
        if (memsz > Memory::ram_size || filesz > memsz || off > data.size() || filesz > data.size()-off)
            throw Fault("invalid ELF load segment");
        memory.load(address, std::vector<uint8_t>(memsz));
        memory.load(address, data.subspan(off, filesz));
    }
}

} // namespace ee
