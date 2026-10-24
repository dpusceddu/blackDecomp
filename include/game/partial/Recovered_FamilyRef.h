/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FAMILYREF_H
#define RECOVERED_FAMILYREF_H
#include "ps2/prelude.h"

typedef struct Recovered_FamilyRef {
    u8 opaque_0[4];
    s32 field_4; /* PS2 +0x4 */
} Recovered_FamilyRef;
typedef char assert_Recovered_FamilyRef_4[(((int)&((Recovered_FamilyRef *)0)->field_4) == 4) ? 1 : -1];
#endif
