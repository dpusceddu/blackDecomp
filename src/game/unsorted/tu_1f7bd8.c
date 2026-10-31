#include "include_asm.h"
#include "ps2/prelude.h"


extern s32 func_001F1C10(void*, s32, s32, s32, s32, s32, s32);
extern void func_001F7C40(void*);

s32 func_001F7BD8(void* self, s32 arg1, s32 arg2, s32 arg3) {
    func_001F1C10(self, 1, 2, 0, (s32)(s8)arg1, arg2, arg3);
    M2C_FIELD(self, s32*, 0x24) = 0x13;
    M2C_FIELD(self, s32*, 0x2C) = 0;
    M2C_FIELD(self, s32*, 0x20) = M2C_FIELD(self, s32*, 0x28) = -1;
    func_001F7C40(self);
    return 1;
}


void func_001F7C40(void* self) {

}
