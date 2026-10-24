#include "include_asm.h"

#include "apt/apt_value.hpp"
using namespace AptPS2;

void Value::Cleanup() { delete this; }
