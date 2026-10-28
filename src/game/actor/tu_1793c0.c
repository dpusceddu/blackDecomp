#include "ps2/prelude.h"

void func_001793C0(void* state) {
    s32 i;
    for (i = 0; i < 2; i++, state = (char*)state + 0x38) M2C_FIELD(state, u8*, 0x34) = i;
}
