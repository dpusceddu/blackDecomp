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
