#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018BE88();

s32 func_0018C088(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_0018BE88(arg0, 0x16);
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    return temp_v0;
}

extern s32 func_0018BE60(void*, void*);
extern s32 func_0018BE90(void*, void*);
extern s32 func_0018BEE8(void*, void*);
extern s32 func_0018BFA8(void*, void*);
extern s32 func_0018C068(void*, void*);

s32 func_0018C0C0(s32* event, void* output) {
    if (*event < 0x12) return func_0018BE60(event, output);
    switch (*event) {
        case 0x13: return func_0018BE90(event, output);
        case 0x14: return func_0018BEE8(event, output);
        case 0x15: return func_0018BFA8(event, output);
        case 0x16: return func_0018C068(event, output);
        default: return 0;
    }
}
