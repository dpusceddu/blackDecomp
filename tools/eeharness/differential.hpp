#pragma once
#include "ee.hpp"
#include <string>

namespace ee {
struct FunctionContract {
    uint32_t original=0, end=0, candidate=0;
    std::string returns;
};
std::string observable_difference(const Machine&, const Machine&, const FunctionContract&,uint32_t entry_stack);
void differential_main(int argc,char** argv);
}
