#pragma once
#include "ee.hpp"
#include <iosfwd>

namespace ee {
Machine import_snapshot(std::istream&);
void save_state(std::ostream&, const State&);
State restore_state(std::istream&);
Result run_replay(Machine&, uint64_t budget, uint32_t return_pc);
void save_entry(std::ostream&, Machine&, uint32_t address, uint64_t ordinal);
bool restore_entry(std::istream&, Machine&, uint32_t& address, uint64_t& ordinal);
void replay_main(int argc, char** argv);
}
