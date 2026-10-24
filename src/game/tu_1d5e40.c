#include "ps2/prelude.h"

extern s32 func_00281B88(void *);
extern s32 func_001D6230(void *, M2C_UNK, M2C_UNK);

s32 func_001D5E40(void) {
    return 0;
}

s32 func_001D5E48(void) {
    return 0;
}

void func_001D5E50(void) {

}

void func_001D5E58(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x1B4) = 0;
    M2C_FIELD(arg0, s32 *, 0x78) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    func_00281B88(arg0 + 0x94);
    func_001D6230(arg0, 0, 0);
}
