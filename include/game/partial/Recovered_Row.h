/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ROW_H
#define RECOVERED_ROW_H
#include "ps2/prelude.h"

typedef struct Recovered_Row {
    void * field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
    u8 opaque_C[4];
    s32 field_10; /* PS2 +0x10 */
    u8 opaque_14[12];
    s32 field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    s32 field_2C; /* PS2 +0x2C */
} Recovered_Row;
typedef char assert_Recovered_Row_0[(((int)&((Recovered_Row *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Row_4[(((int)&((Recovered_Row *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Row_8[(((int)&((Recovered_Row *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_Row_10[(((int)&((Recovered_Row *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Row_20[(((int)&((Recovered_Row *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Row_24[(((int)&((Recovered_Row *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_Row_28[(((int)&((Recovered_Row *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_Row_2C[(((int)&((Recovered_Row *)0)->field_2C) == 44) ? 1 : -1];
#endif
