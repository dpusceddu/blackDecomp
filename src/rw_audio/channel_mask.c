#include "include_asm.h"
#include "ps2/prelude.h"

extern void DIntr(void);
extern void EIntr(void);
extern u8 D_0040E298;

#ifdef NON_MATCHING
// Unmatched: GP load and mask temporary registers differ; source byte ownership is unresolved.
u32 func_00328FF0(u32 mask) {
    u32 used;
    DIntr();
    used = D_0040E298;
    if (mask & used) mask = 0;
    used |= mask;
    D_0040E298 = used;
    EIntr();
    return mask;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/channel_mask", func_00328FF0);
#endif
#ifdef NON_MATCHING
// Unmatched: GP load needs a local mask definition; its one-byte source data interval is unresolved.
u32 func_00329030(u32 mask) {
    u32 keep;
    u32 used;
    DIntr();
    used = D_0040E298;
    keep = ~(mask & used);
    D_0040E298 = used & keep;
    mask &= keep;
    EIntr();
    return mask;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/channel_mask", func_00329030);
#endif
