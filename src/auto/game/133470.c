#include "auto/prelude.h"

extern s32 func_0015BBD8();
extern s32 func_001A6330();

void func_00133470(void *arg0) {
    void *temp_2;

    if (M2C_FIELD(arg0, s32 *, 0x2A4) != 0) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x32C), s32 *, 0x40) = 0;
        temp_2 = M2C_FIELD(arg0, void **, 0x32C);
        func_0015BBD8(arg0 + 0x280, M2C_FIELD(temp_2, u8 *, 0x31), M2C_FIELD(temp_2, u8 *, 0x32), M2C_FIELD(temp_2, u8 *, 0x33), M2C_FIELD(temp_2, u8 *, 0x34), M2C_FIELD(temp_2, u8 *, 0x35), M2C_FIELD(temp_2, u8 *, 0x3B), M2C_FIELD(temp_2, u8 *, 0x3C), arg0 + 0x334);
    }
    func_001A6330(M2C_FIELD(arg0, s32 *, 0x330), arg0 + 0x334);
}
