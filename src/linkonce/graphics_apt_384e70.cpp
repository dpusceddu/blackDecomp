#include "campaign/graphics/apt_value.hpp"
using namespace AptPS2;
void Value::Dispose() { BeforeDispose(); Clear(); delete this; }
