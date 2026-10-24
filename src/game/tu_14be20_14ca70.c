#include "ps2/prelude.h"

extern s32 func_00343ED0(void *);
extern s32 func_00274F80(s32);

void func_0014CA70(void *arg0) {
    func_00343ED0(M2C_FIELD(arg0, void **, 0x20));
    M2C_FIELD(arg0, void **, 0x20) = NULL;
}

void func_0014CAA0(s32 arg0) {
    func_00274F80(arg0 + 4);
}

void func_0014CAC0(void) {

}

void func_0014CAC8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + 1);
}

void func_0014CAD8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) - 1);
}
