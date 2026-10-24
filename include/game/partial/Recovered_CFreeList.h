/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CFREELIST_H
#define RECOVERED_CFREELIST_H
#include "ps2/prelude.h"

typedef struct Recovered_CFreeList {
    u8 opaque_0[12];
    s32 field_C; /* PS2 +0xC */
} Recovered_CFreeList;
typedef char assert_Recovered_CFreeList_C[(((int)&((Recovered_CFreeList *)0)->field_C) == 12) ? 1 : -1];
#endif
