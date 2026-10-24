/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CONSTRAINTMETA_H
#define RECOVERED_CONSTRAINTMETA_H
#include "ps2/prelude.h"

typedef struct Recovered_ConstraintMeta {
    u8 opaque_0[272];
    u32 field_110; /* PS2 +0x110 */
} Recovered_ConstraintMeta;
typedef char assert_Recovered_ConstraintMeta_110[(((int)&((Recovered_ConstraintMeta *)0)->field_110) == 272) ? 1 : -1];
#endif
