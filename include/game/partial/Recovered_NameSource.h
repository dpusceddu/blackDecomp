/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_NAMESOURCE_H
#define RECOVERED_NAMESOURCE_H
#include "ps2/prelude.h"

typedef struct Recovered_NameSource {
    u8 opaque_0[12];
    s32 field_C; /* PS2 +0xC */
} Recovered_NameSource;
typedef char assert_Recovered_NameSource_C[(((int)&((Recovered_NameSource *)0)->field_C) == 12) ? 1 : -1];
#endif
