#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_0040E6B0;
extern void * D_0040E00C;
extern s32 func_002AC568(void *);
extern void * D_0040E008;

s32 func_002BFE68(void) {
    s32 temp_16;

    temp_16 = D_0040E6B0;
    if (temp_16 != 0) {
        if (D_0040E00C != NULL) {
            func_002AC568(D_0040E00C);
            D_0040E00C = NULL;
        }
        if (D_0040E008 != NULL) {
            func_002AC568(D_0040E008);
            D_0040E008 = NULL;
        }
    }
    return temp_16;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFEC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF50);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_0040E070;

s32 func_002BFF70(s32 arg0) {
    D_0040E070 = arg0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF88);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002AC850(s32, s32, s32, s32, s32);
extern s32 D_0040E688;
extern s32 func_002A93E0(s32, s32, s32, s32, s32);
extern s32 D_0040E68C;
extern s32 func_002AF5A8(s32, s32, s32, s32, s32);
extern s32 D_0040E6B8;
extern s32 func_002D0A18(s32, s32, s32, s32);
extern void * func_002C00F0(void *, s32, void *);
extern s32 func_002C0168(void *, s32, void *);
extern s32 func_002C01C0(s32 *);

s32 func_002C0038(void) {
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;
    s32 temp_2_4;
    u32 var_2;

    temp_2 = func_002AC850(0x5C, 0x40C, 0, 0, 0);
    D_0040E688 = temp_2;
    var_2 = (u32) ~temp_2 >> 0x1F;
    if (var_2 != 0) {
        temp_2_2 = func_002A93E0(0xD8, 0x40C, 0, 0, 0);
        D_0040E68C = temp_2_2;
        var_2 = (u32) ~temp_2_2 >> 0x1F;
        if (var_2 != 0) {
            temp_2_3 = func_002AF5A8(0, 0x110, 0, 0, 0);
            D_0040E6B8 = temp_2_3;
            var_2 = (u32) ~temp_2_3 >> 0x1F;
            if (var_2 != 0) {
                temp_2_4 = func_002D0A18(0x110, (s32) func_002C00F0, (s32) func_002C0168, (s32) func_002C01C0);
                D_0040E6B8 = temp_2_4;
                var_2 = (u32) ~temp_2_4 >> 0x1F;
            }
        }
    }
    return (s32) var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C00F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C01C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C01E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0298);
