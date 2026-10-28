#include "include_asm.h"
#include "game/audio/resource_owner.h"

// Only the first configuration element is accessed; original extents are UNVERIFIED.
extern void* D_0040F510[];
extern f32 D_003BD288[], D_003BD28C[], D_003BD290[];
extern u8 D_0040D9F8;
// SN needs the small-data byte's size before expanding its symbolic load.
__asm__(".extern D_0040D9F8, 1");
extern Recovered_ResourceEntry* func_001D6178(Recovered_ResourceOwner*);
extern void* func_00283E78(void*, Recovered_AudioParameters*, void*);

#ifdef NON_MATCHING
// Unmatched: float stores at offsets 0x8C, 0x90 and 0x94 are scheduled differently.
void* func_001D60B8(Recovered_ResourceOwner* owner) {
    Recovered_AudioParameters params;
    params.source = M2C_FIELD(owner, void**, 0x78);
    params.gain = M2C_FIELD(owner, f32*, 0x74);
    params.kind = 1;
    params.rate = M2C_FIELD(owner, f32*, 0x7C);
    params.flags = 0x85C;
    params.unk_60 = 0;
    if (M2C_FIELD(D_0040F510[0], u8*, 0xCB9D)) {
        params.field88 = D_003BD288[0];
        params.field8C = D_003BD290[0];
        params.field94 = M2C_FIELD(owner, f32*, 0x8C);
        params.field90 = D_003BD288[0];
        params.field98 = D_003BD28C[0];
        params.field9C = D_003BD28C[0];
        params.fieldAB = D_0040D9F8;
        params.flags |= 0x800000;
    }
    return func_00283E78(func_001D6178(owner)->resource, &params, 0);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e58_1d60b8", func_001D60B8);
#endif
