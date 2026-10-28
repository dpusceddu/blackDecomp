#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001E51C8(void*, s32);
extern void func_001E4D28(void*);
extern void* func_001E4A78(void*, s32);
s32 func_001E4650(void* self, void* source, s32 arg2) {
    s32 state = M2C_FIELD(self, s32*, 0);
    if (state == 1) goto initialize;
    if (state < 2) return 1;
    if (state == 2) goto update;
    if (state == 3) goto finish;
    return 1;
initialize:
        M2C_FIELD(self, s32*, 0x38) = 0;
        M2C_FIELD(self, s32*, 0x34) = 0;
        M2C_FIELD(self, s32*, 0x30) = 0;
        M2C_FIELD(self, s32*, 0x2C) = 0;
        M2C_FIELD(self, s32*, 0x40) = 0;
        M2C_FIELD(self, s32*, 0x28) = 0;
        M2C_FIELD(self, s32*, 4) = 0;
        M2C_FIELD(self, void**, 0x44) = source;
        M2C_FIELD(self, s32*, 0x4C) = M2C_FIELD(source, s32*, 0x4C);
        M2C_FIELD(self, s32*, 0x48) = func_001E51C8(source, arg2);
        M2C_FIELD(self, s32*, 0) = 2;
update:
        func_001E4D28(self);
        if (!func_001E4A78(self, M2C_FIELD(self, s32*, 0x34))) return 0;
        M2C_FIELD(self, s32*, 0) = 3;
finish:
        func_001E4D28(self);
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4650", func_001E4720);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4650", func_001E49D0);
void* func_001E4A78(void* self, s32 key) {
    u8* entry = (u8*)self + 8;
    u8* selected = entry;
    u32 i = 0;
    do {
        i++;
        if (M2C_FIELD(entry, s32*, 8) == key) {
            return M2C_FIELD(M2C_FIELD(entry, void**, 0), s32*, 0x14) == 4 ? selected : NULL;
        }
        selected += 0x10;
        entry += 0x10;
    } while (i < 2);
    return NULL;
}

void func_001E4AC8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x28) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 3;
}

extern s32 func_001DD728(void*);
extern void func_001DD6C0(void*);
void func_001E4AD8(void* self) {
    s32 state = M2C_FIELD(self, s32*, 4);
    if (state < 5) {
      if (state > 0) {
        if (func_001DD728(M2C_FIELD(M2C_FIELD(self, void**, 0x28), void**, 0xB8))) {
            func_001DD6C0(M2C_FIELD(M2C_FIELD(self, void**, 0x28), void**, 0xB8));
        }
        M2C_FIELD(self, s32*, 4) = 5;
      }
    }
}


s32 func_001E4B38(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 4);
    var_4 = 0;
    if ((temp_3 == 1) || (temp_3 == 3) || (temp_3 == 2) || (temp_3 == 4)) {
        var_4 = 1;
    }
    return var_4;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4650", func_001E4B70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4650", func_001E4CA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4650", func_001E4D28);
