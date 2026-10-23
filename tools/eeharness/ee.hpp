#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <span>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace ee {

struct Quad {
    std::array<uint32_t, 4> w{};
    uint64_t low() const { return uint64_t(w[0]) | uint64_t(w[1]) << 32; }
    uint64_t high() const { return uint64_t(w[2]) | uint64_t(w[3]) << 32; }
    void low(uint64_t x) { w[0] = uint32_t(x); w[1] = uint32_t(x >> 32); }
    void high(uint64_t x) { w[2] = uint32_t(x); w[3] = uint32_t(x >> 32); }
    uint32_t lane(unsigned index, unsigned bits) const;
    void lane(unsigned index, unsigned bits, uint32_t value);
    bool operator==(const Quad&) const = default;
};

enum class VuWriteKind { vector, integer, mac, clip, status, quotient };
struct VuWrite {
    VuWriteKind kind{};
    uint64_t ready = 0;
    unsigned reg = 0, mask = 0;
    Quad value{};
    uint32_t flags = 0, sticky = 0;
    bool macro = false;
    bool operator==(const VuWrite&) const = default;
};
struct VuPipeline {
    uint64_t cycle = 0, issued = 0;
    uint32_t pc = 0, next_pc = 8, clip_history = 0;
    bool end_delay = false, debug_delay = false, m_seen = false, stopped = false;
    uint32_t debug_bits = 0;
    std::array<std::array<uint64_t,4>,32> vector_ready{};
    std::array<uint64_t,16> integer_ready{}, branch_ready{};
    std::array<uint16_t,16> branch_previous{};
    std::array<bool,4> accumulator_overflow{};
    std::vector<VuWrite> pending;
    bool operator==(const VuPipeline&) const = default;
};

struct TlbEntry {
    uint32_t page_mask = 0, entry_hi = 0;
    std::array<uint32_t,2> entry_lo{};
    bool initialized = false;
    bool operator==(const TlbEntry&) const = default;
};
struct ReplayInterrupt {
    uint64_t ready = 0;
    uint32_t handler = 0, argument = 0;
    bool operator==(const ReplayInterrupt&) const = default;
};

struct State {
    std::array<Quad, 32> gpr{};
    Quad hi{}, lo{};
    std::array<uint32_t, 32> cop0{}, fpr{}, fcr{};
    std::array<Quad, 32> vf{};
    std::array<uint32_t, 32> vi{};
    Quad vacc{};
    uint32_t facc = 0, pc = 0, next_pc = 4, sa = 0;
    bool facc_overflow = false;
    bool vu_micro_running = false;
    VuPipeline vu;
    std::array<TlbEntry,48> tlb{};
    // Synthetic instruction fixtures use the flat RAM profile. Saved hardware
    // states use MMU translation with the supplied COP0/TLB contents.
    bool mmu_enabled = false;
    bool delay_slot = false;
    bool pending_call = false;
    uint32_t call_target = 0, call_site = 0;
    // Deterministic issue clock; this is not a superscalar EE timing model.
    uint64_t instructions = 0, ee_cycle = 0;
    // Optional recorded external-completion profile, separate from EE decode.
    uint64_t next_vblank = 0;
    std::vector<ReplayInterrupt> replay_interrupts;
    State();
    void start(uint32_t address);
    bool operator==(const State&) const = default;
};

enum class EventKind { hardware_read, hardware_write, syscall, cache, sync, call, vu1_read, vu1_write, vu_debug, vu_control, cop0_read, interrupt };
struct Event {
    EventKind kind{};
    uint32_t pc = 0, address = 0;
    std::vector<uint8_t> bytes;
    // A call records all argument banks, including native 128-bit GPR arguments.
    std::array<Quad, 8> arguments{};
    std::array<uint32_t, 8> float_arguments{};
    bool default_response = false;
    bool operator==(const Event&) const = default;
};
struct Trace {
    // Final written bytes are compared independently of compiler store grouping.
    std::unordered_map<uint32_t, uint8_t> writes;
    std::vector<Event> events;
    std::unordered_set<uint32_t> instructions;
    std::unordered_set<uint32_t> micro_instructions;
    struct EdgeHash {
        size_t operator()(const std::pair<uint32_t,uint32_t>& edge) const {
            return std::hash<uint64_t>{}(uint64_t(edge.first)<<32 | edge.second);
        }
    };
    std::unordered_set<std::pair<uint32_t, uint32_t>,EdgeHash> edges;
    bool operator==(const Trace&) const = default;
};

class Fault : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class Memory {
public:
    static constexpr uint32_t ram_size = 32 * 1024 * 1024;
    static constexpr uint32_t scratch_size = 16 * 1024;
    static constexpr uint32_t vu_size = 4096;
    Memory();
    // Shared pages make entry-state snapshots independent after later writes.
    uint64_t read(uint32_t address, unsigned width, Trace* trace = nullptr, uint32_t pc = 0);
    Quad read_quad(uint32_t address, Trace* trace = nullptr, uint32_t pc = 0);
    void write(uint32_t address, unsigned width, uint64_t value, Trace* trace = nullptr, uint32_t pc = 0);
    void write_quad(uint32_t address, const Quad&, Trace* trace = nullptr, uint32_t pc = 0);
    uint64_t read_physical(uint32_t address, unsigned width, Trace* trace = nullptr, uint32_t pc = 0);
    Quad read_quad_physical(uint32_t address, Trace* trace = nullptr, uint32_t pc = 0);
    void write_physical(uint32_t address, unsigned width, uint64_t value, Trace* trace = nullptr, uint32_t pc = 0);
    void write_quad_physical(uint32_t address, const Quad&, Trace* trace = nullptr, uint32_t pc = 0);
    void load(uint32_t address, std::span<const uint8_t> bytes);
    std::vector<uint8_t> bytes(uint32_t address, uint32_t size) const;
    // Hardware defaults are zero and explicitly marked in the trace. A caller
    // can supply captured/control-register responses, never gameplay objects.
    std::map<std::pair<uint32_t, unsigned>, uint64_t> hardware_responses;
    // Replay-only local memory transfers. Other DMA endpoints remain recorded
    // stubs. No IOP or device payload is synthesized.
    bool scratch_dma = false;
    // Differential pilot only: immutable candidate text/constants in a separate
    // address range. This is not EE RAM or a deployable nonmatching ELF layout.
    std::map<uint32_t, std::vector<uint8_t>> candidate_regions;
    bool candidate_address(uint32_t address, unsigned width = 1) const;
    std::map<std::pair<uint32_t,unsigned>,uint64_t> hardware_updates;
    static uint32_t physical(uint32_t address);
private:
    using Page = std::array<uint8_t, 4096>;
    std::vector<std::shared_ptr<Page>> pages_;
    static uint32_t offset(uint32_t physical, unsigned width);
    uint8_t byte(uint32_t offset) const;
    void byte(uint32_t offset, uint8_t value);
    void scratch_dma_write(uint32_t address, unsigned width, uint64_t value, Trace*, uint32_t pc);
};

struct Decoded {
    std::string name;
    uint32_t word = 0;
    unsigned rs = 0, rt = 0, rd = 0, sa = 0;
    int16_t immediate = 0;
    bool supported = false;
};
Decoded decode(uint32_t word);
const Decoded& decode_cached(uint32_t word);

enum class Stop { returned, budget, fault };
struct Result {
    Stop stop = Stop::budget;
    std::string error;
    uint64_t executed = 0;
};

class Machine {
public:
    State state;
    Memory memory;
    Trace trace;
    Result outcome;
    uint32_t minimum_stack = 0xffffffff;
    std::set<uint32_t> capture_entries;
    std::function<void(uint32_t, const State&, const Memory&)> on_entry;
    void step();
    Result run(uint64_t budget, uint32_t return_pc = 0xffffffff);
    Result call(uint32_t address, uint64_t budget);
    enum class Access { read, write, execute };
    uint32_t translate(uint32_t address, Access access);
private:
    void integer(const Decoded&);
    void mmi(const Decoded&);
    void cop1(const Decoded&);
    void cop2(const Decoded&);
    void cop0(const Decoded&);
    void advance_cop0(uint64_t cycles, bool count_written, bool wired_written);
    void branch(bool condition, bool likely, uint32_t target);
    void call_event(uint32_t target);
    uint32_t current_pc_ = 0;
    bool was_delay_ = false;
};

// Comparison excludes scheduling/coverage and scratch registers. Callers supply
// the ABI return banks to compare; upper halves are never silently discarded.
std::string difference(const Machine& original, const Machine& candidate,
                       std::span<const unsigned> returns, std::span<const unsigned> float_returns);
void load_elf(Memory&, std::span<const uint8_t> elf);

} // namespace ee
