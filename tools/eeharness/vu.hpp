#pragma once
#include "ee.hpp"

namespace ee {

// VU0 issue-time model. Pending writes are part of State, so a snapshot also
// retains delayed flags, Q, register hazards and integer branch bypass state.
class VuEngine {
public:
    VuEngine(State& state, Memory& memory, Trace& trace) : s_(state), memory_(memory), trace_(trace) {}
    void start(uint32_t byte_address);
    void step();
    // Issue only before deadline. A dependency beyond it remains unissued;
    // future memory writes and external events must not escape into EE time.
    void catch_up(uint64_t deadline);
    Result run(uint64_t budget, bool stop_on_m = false);
    void advance(uint64_t cycle);
    void drain();
    void macro(const Decoded&);
    void interlock(bool allow_m = false);
    void reset();
    void force_break();
    void synchronize_vector(unsigned reg, bool macro_only = false);
    void synchronize_control(unsigned reg, bool macro_only = false);
    static Decoded decode_lower(uint32_t word);
    static bool lower_supported(const Decoded&);
private:
    struct Access {
        std::array<unsigned,32> vf{};
        uint16_t vi = 0;
        bool quotient = false;
    };
    struct Effect { unsigned reg = 0, mask = 0; Quad value{}; };
    State& s_;
    Memory& memory_;
    Trace& trace_;
    uint32_t access_pc_ = 0;
    Access upper_access(const Decoded&) const;
    Access lower_access(const Decoded&) const;
    uint32_t macro_registers(const Decoded&, bool upper_operation) const;
    uint64_t ready(const Access&, const Access&) const;
    bool step_until(uint64_t deadline);
    Effect upper(const Decoded&);
    Effect lower(const Decoded&, uint32_t pc, const std::array<Quad,32>& vf,
                 const std::array<uint32_t,32>& vi, bool macro = false);
    void vector_write(const Effect&);
    void integer_write(unsigned reg, uint32_t value, bool flag_bypass = false, bool load = false);
    uint32_t read_word(uint32_t qword, unsigned lane);
    void write_word(uint32_t qword, unsigned lane, uint32_t value);
    uint16_t branch_value(unsigned reg) const;
    void schedule_flags(uint32_t mac, uint32_t sticky);
};

} // namespace ee
