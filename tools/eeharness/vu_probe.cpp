#include "vu.hpp"
#include <istream>
#include <ostream>
#include <string>

// Text protocol for authored semantic fixtures. Programs and input snapshots
// are external files/streams; no game data is embedded in this executable.
void vu_probe(std::istream& in,std::ostream& out) {
    ee::Machine machine;
    std::string operation;
    while (in >> operation) {
        in >> std::hex;
        unsigned reg = 0;
        uint32_t address = 0, value = 0, hi = 0;
        if (operation == "case") machine = ee::Machine{};
        else if (operation == "vf") {
            in >> reg;
            if (reg > 31) throw ee::Fault("invalid fixture VF");
            for (auto& word : machine.state.vf[reg].w) in >> word;
        } else if (operation == "vi") {
            in >> reg >> value;
            machine.state.vi.at(reg) = value;
        } else if (operation == "acc") for (auto& word : machine.state.vacc.w) in >> word;
        else if (operation == "pair") {
            in >> address >> value >> hi;
            if (address >= 4096 || address&7) throw ee::Fault("invalid fixture micro PC");
            machine.memory.write(0x11000000+address,4,value);
            machine.memory.write(0x11000004+address,4,hi);
        } else if (operation == "data") {
            in >> address >> value;
            machine.memory.write(0x11004000+(address&0xfff),4,value);
        } else if (operation == "run" || operation == "run-ee" || operation == "run-ee-try") {
            uint64_t budget = 0;
            in >> address >> budget;
            if (!in || (address&7) || address >= 4096) throw ee::Fault("invalid fixture entry or budget");
            ee::Result result;
            bool replay_agreement = true;
            if (operation != "run") {
                // Launch through the EE call interface, then synchronize with
                // a read into GPR0 before returning through the normal ABI.
                machine.memory.write(0x1000,4,0x4a000038 | (address/8)<<6);
                machine.memory.write(0x1004,4,0x48200001);
                machine.memory.write(0x1008,4,0x03e00008);
                machine.memory.write(0x100c,4,0);
                if (operation == "run-ee-try") {
                    auto replay = machine;
                    result = machine.call(0x1000,budget);
                    const auto other = replay.call(0x1000,budget);
                    replay_agreement = machine.state == replay.state && machine.trace == replay.trace &&
                        result.stop == other.stop && result.error == other.error && result.executed == other.executed;
                } else result = machine.call(0x1000,budget);
            } else {
                ee::VuEngine engine(machine.state,machine.memory,machine.trace);
                engine.start(address);
                result = engine.run(budget);
            }
            if (operation == "run-ee-try") {
                out << "result " << (result.stop == ee::Stop::returned ? "returned" : result.stop == ee::Stop::budget ? "budget" : "fault")
                    << ' ' << std::dec << machine.state.vu.issued << ' ' << machine.trace.micro_instructions.size() << '\n';
                if (!result.error.empty()) out << "error " << result.error << '\n';
                out << "replay " << (replay_agreement ? "equal" : "diverged") << '\n';
            } else if (result.stop != ee::Stop::returned) throw ee::Fault("micro fixture did not return: "+result.error);
        } else if (operation == "printvf") {
            in >> reg;
            for (auto word : machine.state.vf.at(reg).w) out << std::hex << word << ' ';
            out << '\n';
        } else if (operation == "printvi") {
            in >> reg;
            out << std::hex << machine.state.vi.at(reg) << '\n';
        } else throw ee::Fault("unknown VU fixture operation: "+operation);
        if (!in) throw ee::Fault("truncated VU fixture input");
    }
}
