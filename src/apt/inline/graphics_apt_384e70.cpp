#include "include_asm.h"

#include "apt/apt_value.hpp"
using namespace AptViews;

void Value::Dispose() { BeforeDispose(); Clear(); delete this; }
