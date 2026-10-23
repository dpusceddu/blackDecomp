#include "ee.hpp"
#include "fpu.hpp"
#include "vu.hpp"
#include "replay.hpp"
#include "differential.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

void vu_probe(std::istream&,std::ostream&);
void run_fixture(std::span<const uint8_t>,uint32_t,uint32_t,uint32_t,uint64_t,std::ostream&);

namespace {
std::vector<uint8_t> read_file(const char* path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) throw ee::Fault(std::string("cannot read ")+path);
    return {std::istreambuf_iterator<char>(in),std::istreambuf_iterator<char>()};
}
unsigned long long number(const char* s) {
    size_t end = 0;
    auto value = std::stoull(s,&end,0);
    if (s[end]) throw ee::Fault("invalid number");
    return value;
}
}

int main(int argc, char** argv) {
    try {
        if(argc>=2 && std::string(argv[1])=="differential") {ee::differential_main(argc,argv);return 0;}
        if (argc >= 2 && (std::string(argv[1]) == "replay" || std::string(argv[1]) == "replay-entry" || std::string(argv[1]) == "replay-fuzz")) {
            ee::replay_main(argc,argv);return 0;
        }
        if (argc == 7 && std::string(argv[1]) == "fixture") {
            run_fixture(read_file(argv[2]),uint32_t(number(argv[3])),uint32_t(number(argv[4])),uint32_t(number(argv[5])),number(argv[6]),std::cout);
            return 0;
        }
        if (argc == 2 && std::string(argv[1]) == "decode-vu") {
            std::array<uint8_t,8> bytes{};
            while (std::cin.read(reinterpret_cast<char*>(bytes.data()),8)) {
                uint32_t lo = 0, hi = 0;
                for (unsigned i = 0; i < 4; ++i) { lo |= uint32_t(bytes[i]) << (i*8); hi |= uint32_t(bytes[i+4]) << (i*8); }
                const auto up = ee::decode(0x4a000000 | (hi&0x1ffffff)), down = ee::VuEngine::decode_lower(lo);
                std::cout << up.name << '\t' << (hi&0x80000000 ? "loi" : down.name) << '\t'
                          << ((hi&0x80000000) || ee::VuEngine::lower_supported(down)) << '\n';
            }
            if (std::cin.gcount()) throw ee::Fault("partial VU instruction pair");
            return 0;
        }
        if (argc == 2 && std::string(argv[1]) == "vu") {
            vu_probe(std::cin,std::cout);
            return 0;
        }
        if (argc == 2 && std::string(argv[1]) == "vu-int") {
            uint32_t word, a, b;
            while (std::cin >> std::hex >> word >> a >> b) {
                ee::Machine machine;
                machine.memory.write(0x1000,4,word);
                machine.state.start(0x1000);
                machine.state.vi[1] = 0x1337;
                machine.state.vi[2] = a & 0xffff; machine.state.vi[3] = b & 0xffff;
                machine.state.vi[16] = 0x5a3; machine.state.vi[17] = 0xabcd; machine.state.vi[18] = 0x123456;
                machine.step();
                const auto d = ee::decode(word);
                const unsigned dest = d.name == "viaddi" ? d.rt&15 : d.sa&15;
                std::cout << std::hex << machine.state.vi[dest] << ' ' << machine.state.vi[16] << ' '
                          << machine.state.vi[17] << ' ' << machine.state.vi[18] << '\n';
            }
            return 0;
        }
        if (argc == 2 && std::string(argv[1]) == "integer") {
            uint32_t word = 0;
            unsigned observe = 0, shift = 0;
            while (std::cin >> std::hex >> word >> observe >> shift) {
                if (observe > 31) throw ee::Fault("invalid integer observation register");
                ee::Machine machine;
                for (auto* value : {&machine.state.gpr[4],&machine.state.gpr[5],&machine.state.gpr[2],&machine.state.hi,&machine.state.lo})
                    for (auto& lane : value->w) std::cin >> lane;
                if (!std::cin) throw ee::Fault("partial integer fixture");
                machine.state.sa = shift;
                machine.memory.write(0x1000,4,word); machine.state.start(0x1000);
                try { machine.step(); }
                catch (const ee::Fault& error) { std::cout << "fault " << error.what() << '\n'; continue; }
                for (const auto* value : {&machine.state.gpr[observe],&machine.state.hi,&machine.state.lo})
                    for (auto lane : value->w) std::cout << std::hex << lane << ' ';
                std::cout << machine.state.sa << '\n';
            }
            return 0;
        }
        if (argc == 2 && std::string(argv[1]) == "cop1") {
            uint32_t word, a, b, acc, status;
            unsigned acc_overflow;
            while (std::cin >> std::hex >> word >> a >> b >> acc >> status >> acc_overflow) {
                ee::Machine machine;
                machine.memory.write(0x1000,4,word);
                machine.state.start(0x1000);
                machine.state.fpr[4] = a; machine.state.fpr[5] = b;
                machine.state.facc = acc; machine.state.fcr[31] = status;
                machine.state.facc_overflow = acc_overflow;
                machine.step();
                std::cout << std::hex << machine.state.fpr[2] << ' ' << machine.state.facc << ' '
                          << machine.state.fcr[31] << ' ' << unsigned(machine.state.facc_overflow) << '\n';
            }
            return 0;
        }
        if (argc == 2 && std::string(argv[1]) == "fp") {
            std::string operation;
            uint32_t a, b;
            while (std::cin >> operation >> std::hex >> a >> b) {
                ee::fpu::Arithmetic value;
                if (operation == "add") value = ee::fpu::add(a,b);
                else if (operation == "sub") value = ee::fpu::subtract(a,b);
                else if (operation == "mul") value = ee::fpu::multiply(a,b);
                else if (operation == "div") value = ee::fpu::divide(a,b);
                else if (operation == "sqrt") value = ee::fpu::square_root(a);
                else if (operation == "rsqrt") value = ee::fpu::reciprocal_root(a,b);
                else throw ee::Fault("unsupported FP probe operation");
                std::cout << std::hex << value.bits << '\n';
            }
            return 0;
        }
        if (argc == 2 && std::string(argv[1]) == "decode") {
            uint32_t word;
            // A byte stream avoids command-length limits on the whole image.
            std::array<unsigned char,4> bytes{};
            while (std::cin.read(reinterpret_cast<char*>(bytes.data()),4)) {
                word = uint32_t(bytes[0]) | uint32_t(bytes[1]) << 8 | uint32_t(bytes[2]) << 16 | uint32_t(bytes[3]) << 24;
                const auto d = ee::decode(word);
                std::cout << d.name << '\t' << d.supported << '\n';
            }
            if (std::cin.gcount()) throw ee::Fault("partial instruction word");
            return 0;
        }
        if (argc >= 5 && std::string(argv[1]) == "compare") {
            ee::Machine original, source;
            ee::load_elf(original.memory,read_file(argv[2]));
            ee::load_elf(source.memory,read_file(argv[3]));
            uint64_t tested = 0;
            for (int i = 4; i < argc; ++i) {
                const uint32_t address = uint32_t(number(argv[i]));
                // These are deliberately bounded synthetic controls, not real
                // gameplay input states and not evidence for `equivalent`.
                for (unsigned seed = 0; seed < 32; ++seed) {
                    auto a = original, b = source;
                    a.state.gpr[29].low(0x01ff0000);
                    a.state.gpr[4].low(seed);
                    a.state.gpr[5].low(seed*17);
                    a.state.gpr[6].low(0x2000);
                    a.state.gpr[7].low(0x3000);
                    constexpr std::array<uint32_t,16> float_inputs = {
                        0,0x80000000,1,0x800000,0x3f800000,0xbf800000,0x3fffffff,0x40400000,
                        0x00800001,0x3f800001,0x7f7fffff,0x7f800000,0x7f800001,0x7fffffff,0xffffffff,0xdeadbeef
                    };
                    for (unsigned reg = 12; reg < 20; ++reg) a.state.fpr[reg] = float_inputs[(seed+reg-12)%float_inputs.size()];
                    b.state = a.state;
                    const auto ar = a.call(address,10000), br = b.call(address,10000);
                    if (ar.stop != ee::Stop::returned || br.stop != ee::Stop::returned)
                        throw ee::Fault("incomplete control at "+std::to_string(address)+": "+ar.error+" / "+br.error);
                    const std::array<unsigned,2> returns = {2,3};
                    const std::array<unsigned,2> floats = {0,2};
                    const auto diff = ee::difference(a,b,returns,floats);
                    if (!diff.empty()) throw ee::Fault("DIFFERENCE at "+std::to_string(address)+": "+diff);
                    ++tested;
                }
            }
            std::cout << "OK " << tested << " exact-source control executions\n";
            return 0;
        }
        std::cerr << "usage: eeharness decode < words.bin\n"
                     "       eeharness compare ORIGINAL.elf SOURCE.elf ADDRESS...\n";
        return 2;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
