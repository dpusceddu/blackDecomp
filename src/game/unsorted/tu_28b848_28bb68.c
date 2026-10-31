#include "include_asm.h"
#include "ps2/prelude.h"

void func_0028BB68(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0xE) = (u8) (M2C_FIELD(arg0, u8 *, 0xE) | ((arg1 & 0xF) * 0x10));
}

void func_0028BB80(void *arg0, u32 arg1) {
    M2C_FIELD(arg0, u8 *, 0xE) = (u8) (M2C_FIELD(arg0, u8 *, 0xE) | (arg1 & 0xF));
}

// Empty element initializer retains its unused native receiver.
void func_0028BB98(void *element) {

}
