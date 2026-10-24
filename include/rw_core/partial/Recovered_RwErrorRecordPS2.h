/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWERRORRECORDPS2_H
#define RECOVERED_RWERRORRECORDPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_RwErrorRecordPS2 {
    s32 field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
} Recovered_RwErrorRecordPS2;
typedef char assert_Recovered_RwErrorRecordPS2_0[(((int)&((Recovered_RwErrorRecordPS2 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_RwErrorRecordPS2_4[(((int)&((Recovered_RwErrorRecordPS2 *)0)->field_4) == 4) ? 1 : -1];
#endif
