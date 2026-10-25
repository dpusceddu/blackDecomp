#include "include_asm.h"
#include "ps2/prelude.h"

extern f32 D_003D4460;
extern f32 D_003D4464;

void func_0034ED80(void) {

}

void func_0034ED88(f32 fparg0) {
    D_003D4460 += fparg0;
}

void func_0034EDA0(f32 fparg0) {
    D_003D4464 += fparg0;
}


#ifdef NON_MATCHING
#include "ps2/prelude.h"

// Unmatched: combine folds the header-bit OR into a3, omitting the original accumulator-to-argument copy (three differences).
extern f32 D_003D4460;
extern f32 D_003D4464;
extern void func_003461E0(void);
extern f32 * func_00350F28(void *, void *, void *, f32, f32, s32, s16);
extern f32 * func_00343C28(f32 *, f32 *);
extern void func_00351030(void *, void *, void *);

void func_0034F1C0(void *arg0, f32 *arg1) {
    f32 *temp_5;
    f32 temp_f0;
    f32 temp_f1;
    void *temp_3;
    s32 temp_16;
    s32 temp_2;

    D_003D4460 = 0.0f;
    D_003D4464 = 0.0f;
    temp_16 = (s32) M2C_FIELD(arg0, s32 *, 0) >> 6;
    func_003461E0();
    temp_16 &= 1;
    temp_16 |= 4;
    temp_3 = (char*)arg0 + 0x960;
    M2C_FIELD(arg0, s16 *, 8) = -1;
    M2C_FIELD(arg0, volatile f32 *, 0x960) = 1.0f;
    M2C_FIELD(temp_3, volatile f32 *, 8) = 1.0f;
    M2C_FIELD(temp_3, volatile f32 *, 4) = 1.0f;
    temp_5 = func_00350F28(arg0, M2C_FIELD(arg0, void **, 0xC), M2C_FIELD(arg0, void **, 0x98C), M2C_FIELD(arg0, f32 *, 0x14), M2C_FIELD(arg0, f32 *, 0x18), temp_16, M2C_FIELD(arg0, s16 *, 0x1C8));
    if (M2C_FIELD(arg0, s16 *, 8) == -1) {
        M2C_FIELD(arg0, s16 *, 8) = 0;
    }
    func_00343C28(arg1, temp_5);
    func_00351030(arg0, M2C_FIELD(arg0, void **, 0xC), M2C_FIELD(arg0, void **, 0x98C));
    temp_f1 = M2C_FIELD(arg0, f32 *, 0x14);
    if (temp_f1 != M2C_FIELD(arg0, f32 *, 0x18)) {
        M2C_FIELD(arg0, f32 *, 0x14) = (f32) (temp_f1 - D_003D4460);
    }
    temp_f0 = M2C_FIELD(arg0, f32 *, 0x14) + D_003D4464;
    M2C_FIELD(arg0, volatile f32 *, 0x18) = temp_f0;
    M2C_FIELD(arg0, volatile f32 *, 0x14) = temp_f0;

}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34eae0_34ed80", func_0034F1C0);
#endif

s32 func_0034F2D0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x998) != 0;
}

f32 func_0034F2E0(void *arg0)
{
  f32 temp_f1;
  temp_f1 = M2C_FIELD(arg0, f32 *, 0x9C8);
  if (temp_f1 == 0.0f)
  {
    return 59.94f;
  }
  if (temp_f1)
  {
    return temp_f1 * 59.94f;
  }
  else
  {
    return temp_f1 * 59.94f;
  }
}
