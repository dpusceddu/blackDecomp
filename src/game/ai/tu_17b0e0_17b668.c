#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

extern s32 func_00174210();
extern s32 func_00174218();
extern void func_0017B3C0(void *arg0);
extern void func_0017B930(void*);
extern void func_0017B998(void*);
extern s32 *func_0017B6F8();
extern s32 func_00179650();
extern void *D_0040F4D4;
extern s32 func_00174228();
extern s32 func_001742B8();
extern s32 func_00174320();
extern void func_001743A0(void*);
extern void* func_00174398(void*);
extern void func_0017B3D0(RecoveredNodeSearch*, s128);
extern u8 func_0017B3F0(RecoveredNodeSearch*);

s32 func_0017B668(s32 arg0) {
    return func_00174210(arg0, 0x20);
}

s32 func_0017B688(void *arg0) {
    func_00174218();
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    func_0017B3C0(arg0 + 0x10);
    return 1;
}

void func_0017B6C0(s32 arg0) {
    func_0017B930((void*)arg0);
    func_0017B998((void*)arg0);
}

s32 func_0017B6F0(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17b0e0_17b668", func_0017B6F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17b0e0_17b668", func_0017B7D0);

s32 func_0017B8A8(void)
{
  s32 *temp_2;
  temp_2 = func_0017B6F8();
  if (temp_2 != NULL)
  {
    if (temp_2)
    {
      return func_00179650(D_0040F4D4, *temp_2);
    }
    else
    {
      return func_00179650(D_0040F4D4, *temp_2);
    }
  }
  return 0;
}

void func_0017B8E8(void) {
    func_00174228();
}

void func_0017B908(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, s32 *, 0xC) == arg1) {
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
    }
    func_001742B8();
}

void func_0017B930(void* self) {
    void* request = M2C_FIELD(self, void**, 0xC);
    if (request) {
        if ((u32)(M2C_FIELD(request, s32*, 0x24) - 1) >= 2u) {
            func_001743A0(self);
            M2C_FIELD(self, void**, 0xC) = NULL;
            goto acquire;
        }
    } else {
acquire:
        request = func_00174398(self);
        M2C_FIELD(self, void**, 0xC) = request;
        if (request) func_0017B3D0((RecoveredNodeSearch*)((u8*)self + 0x10), M2C_FIELD(request, s128*, 0x10));
    }
}
void func_0017B998(void* self) {
    if (M2C_FIELD(self, void**, 0xC)) {
        if (func_0017B3F0((RecoveredNodeSearch*)((u8*)self + 0x10))) {
            s32 result = M2C_FIELD(self, s32*, 0x10);
            void* request = M2C_FIELD(self, void**, 0xC);
            M2C_FIELD(request, s32*, 0x20) = result;
            if (M2C_FIELD(M2C_FIELD(self, void**, 0xC), s32*, 0x20)) {
                M2C_FIELD(M2C_FIELD(self, void**, 0xC), s32*, 0x24) = 3;
            } else {
                M2C_FIELD(M2C_FIELD(self, void**, 0xC), s32*, 0x24) = 4;
            }
            M2C_FIELD(self, void**, 0xC) = NULL;
        }
    }
}

void func_0017BA00(void *arg0, s32 arg1) {
    s32 *temp_2;

    temp_2 = M2C_FIELD(arg0, s32 **, 0xC);
    if ((temp_2 != NULL) && (*temp_2 == arg1)) {
        M2C_FIELD(arg0, s32 **, 0xC) = NULL;
    }
    func_00174320();
}

void func_0017BA38(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xC) != 0) {
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
    }
    func_0017B3C0(arg0 + 0x10);
}

s32 func_0017BA60(void* left, void* right) {
    f32 delta = M2C_FIELD(left, f32*, 4) - M2C_FIELD(right, f32*, 4);
    if (delta < 0.0f) return -1;
    if (delta > 0.0f) return 1;
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17b0e0_17b668", func_0017BAA0);
