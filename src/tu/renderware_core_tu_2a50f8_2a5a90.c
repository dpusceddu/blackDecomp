#include "ps2/renderware_inline.h"
extern u8 D_00449444[];extern s32 D_0040E5A8;
s32 func_002A5A90(const RwMatrixTolerancePS2 *tolerance) {
 RwCopyMatrixTolerancePS2((RwMatrixTolerancePS2 *)(D_00449444+D_0040E5A8),tolerance);return 1;
}
