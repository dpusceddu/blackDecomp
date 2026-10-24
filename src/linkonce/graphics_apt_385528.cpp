#include "apt/apt_value.hpp"
using namespace AptPS2;
void Value::SetEnabled(int enabled) { int& bits=*(int*)((char*)this+0x1c);int setting=enabled!=0;bits=(bits&~0x100)|(setting<<8); }
