#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "ps2/recovered_types.h"
#endif

extern s32 D_0040E1D0;

void func_003178B8(s32 arg0) {
    D_0040E1D0 = arg0;
}

#ifdef NON_MATCHING
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
extern void * func_003176E0(void *, void *);
extern s32 D_0040E1D4;
extern M2C_UNK * D_0040E798;
extern f32 D_0040E1DC;
extern f32 (*D_0040E1D8)(void *, void *);
extern s32 func_0031B030(void *, void *, void *, s32, s32);

s32 func_003178F0(void *input, void *operation, void *length, void *event, s32 context, s32 flags) {
    s32 sp10;
    M2C_UNK *var_16;
    M2C_UNK *var_17;
    M2C_UNK *var_21;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    f32 var_f20;
    f32 var_f21;

    sp10 = flags;
    switch (D_0040E1D0) {                           /* irregular */
    case 2:
        func_003176E0(length, (void *) D_0040E1D4);
        break;
    case 3:
        var_17 = D_0040E798;
        var_f21 = D_0040E1DC;
        var_21 = NULL;
        if (var_17 != &D_0040E798) {
            var_16 = var_17 - 0x40;
            do {
                temp_f2 = M2C_FIELD(var_16, f32 *, 0x48) - M2C_FIELD(length, f32 *, 0);
                temp_f1 = M2C_FIELD(var_16, f32 *, 0x4C) - M2C_FIELD(length, f32 *, 4);
                temp_f0 = M2C_FIELD(var_16, f32 *, 0x50) - M2C_FIELD(length, f32 *, 8);
                var_f20 = (temp_f2 * temp_f2) + (temp_f1 * temp_f1) + (temp_f0 * temp_f0);
                if (D_0040E1D8 != NULL) {
                    var_f20 += D_0040E1D8(operation, var_16);
                }
                var_17 = *var_17;
                if (var_f20 < var_f21) {
                    var_21 = var_16;
                    var_f21 = var_f20;
                }
                var_16 = var_17 - 0x40;
            } while (var_17 != &D_0040E798);
        }
        func_003176E0(length, var_21);
        break;
    }
    return func_0031B030(input, length, event, context, sp10);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_3168c8_3178b8", func_003178F0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_3168c8_3178b8", func_00318078);
