/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CREATABLECACHE_H
#define RECOVERED_CREATABLECACHE_H
#include "ps2/prelude.h"

typedef struct Recovered_CreatableCache {
    u8 opaque_0[24];
    s32 field_18; /* PS2 +0x18 */
    u32 field_1C; /* PS2 +0x1C */
    u8 opaque_20[68];
    s32 field_64; /* PS2 +0x64 */
} Recovered_CreatableCache;
typedef char assert_Recovered_CreatableCache_18[(((int)&((Recovered_CreatableCache *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_CreatableCache_1C[(((int)&((Recovered_CreatableCache *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_CreatableCache_64[(((int)&((Recovered_CreatableCache *)0)->field_64) == 100) ? 1 : -1];
#endif
