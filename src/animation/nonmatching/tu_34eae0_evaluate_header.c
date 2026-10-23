#ifdef NONMATCHING
// Unmatched: service return lifetime and scale-store scheduling differ.
#include "auto/prelude.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern f32 D_003D4460;
extern f32 D_003D4464;
extern s32 func_003461E0();
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
    temp_3 = arg0 + 0x960;
    M2C_FIELD(arg0, s16 *, 8) = -1;
    M2C_FIELD(arg0, f32 *, 0x960) = 1.0f;
    M2C_FIELD(temp_3, f32 *, 8) = 1.0f;
    M2C_FIELD(temp_3, f32 *, 4) = 1.0f;
    temp_5 = func_00350F28(arg0, M2C_FIELD(arg0, void **, 0xC), M2C_FIELD(arg0, void **, 0x98C), M2C_FIELD(arg0, f32 *, 0x14), M2C_FIELD(arg0, f32 *, 0x18), (temp_16 & 1) | 4, M2C_FIELD(arg0, s16 *, 0x1C8));
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
    M2C_FIELD(arg0, f32 *, 0x18) = temp_f0;
    M2C_FIELD(arg0, f32 *, 0x14) = temp_f0;

}
#endif
