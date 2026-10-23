#include "ee.hpp"

#include <algorithm>
#include <iostream>
#include <ostream>

// Adapter for external, compiled instruction-test ELFs. Only the supplied
// standard write(fd, buffer, length) endpoint is replaced. Formatting and all
// tested instruction sequences execute as MIPS code in our own interpreter.
// This adapter is never enabled for game replay or equivalence comparisons.
void run_fixture(std::span<const uint8_t> elf,uint32_t entry,uint32_t io_write,uint32_t gp,
                 uint64_t budget,std::ostream& output) {
    ee::Machine m;
    ee::load_elf(m.memory,elf);
    m.state.fcr[0] = 0x2e30; // configured hardware revision of the published fixture logs
    constexpr uint32_t sentinel = 0xfffffffc;
    m.state.start(entry);
    m.state.gpr[31].low(uint64_t(int64_t(-4)));
    m.state.gpr[29].low(0x01fff000); m.state.gpr[28].low(gp);
    for (uint64_t executed = 0; executed < budget; ++executed) {
        if (m.state.pc == sentinel && !m.state.delay_slot) {
            std::cerr << "fixture returned after " << m.state.instructions << " instructions; "
                      << m.trace.instructions.size() << " distinct PCs\n";
            return;
        }
        if (m.state.pc == io_write && !m.state.delay_slot) {
            if (!m.state.pending_call || m.state.call_target != io_write) throw ee::Fault("fixture I/O requires a normal call entry");
            const auto fd = uint32_t(m.state.gpr[4].low()), address = uint32_t(m.state.gpr[5].low()), length = uint32_t(m.state.gpr[6].low());
            if ((fd != 1 && fd != 2) || length > 1024*1024) throw ee::Fault("fixture write outside stdout/stderr contract");
            ee::Event call{ee::EventKind::call,m.state.call_site,io_write};
            std::copy_n(m.state.gpr.begin()+4,8,call.arguments.begin());
            std::copy_n(m.state.fpr.begin()+12,8,call.float_arguments.begin());
            m.trace.events.push_back(call);
            ee::Event io{ee::EventKind::hardware_write,m.state.call_site,fd};
            for (uint32_t i = 0; i < length; ++i) {
                const auto byte = uint8_t(m.memory.read(address+i,1));
                io.bytes.push_back(byte); output.put(char(byte));
            }
            m.trace.events.push_back(std::move(io));
            if (!output) throw ee::Fault("fixture output stream failed");
            const auto resume = uint32_t(m.state.gpr[31].low());
            m.state.gpr[2].low(length); m.state.start(resume);
        } else {
            const uint32_t pc = m.state.pc;
            try { m.step(); }
            catch (const ee::Fault& error) {
                throw ee::Fault("fixture at "+std::to_string(pc)+": "+error.what());
            }
        }
    }
    throw ee::Fault("compiled instruction fixture exceeded its execution budget");
}
