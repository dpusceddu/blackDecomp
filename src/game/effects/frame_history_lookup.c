#include "ps2/prelude.h"

extern void* D_0040F4D0;

s32 func_001B0F70(void* object) {
    s32 frame = (s32)(M2C_FIELD(D_0040F4D0, f32*, 0x20) * M2C_FIELD(object, f32*, 0x164));
    object = (s8*)object + (frame % M2C_FIELD(object, s32*, 0x160)) * 4;
    return M2C_FIELD(object, s32*, 0xE0);
}
