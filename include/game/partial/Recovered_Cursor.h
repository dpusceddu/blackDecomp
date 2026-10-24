/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CURSOR_H
#define RECOVERED_CURSOR_H
#include "ps2/prelude.h"

typedef struct Recovered_Cursor {
    u8 opaque_0[56];
    void * field_38; /* PS2 +0x38 */
    s32 field_3C; /* PS2 +0x3C */
    u8 field_40; /* PS2 +0x40 */
    u8 field_41; /* PS2 +0x41 */
    u8 field_42; /* PS2 +0x42 */
    u8 field_43; /* PS2 +0x43 */
    u8 opaque_44[4];
    u8 field_48; /* PS2 +0x48 */
    u8 opaque_49[7];
    u8 field_50; /* PS2 +0x50 */
} Recovered_Cursor;
typedef char assert_Recovered_Cursor_38[(((int)&((Recovered_Cursor *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_Cursor_3C[(((int)&((Recovered_Cursor *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_Cursor_40[(((int)&((Recovered_Cursor *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_Cursor_41[(((int)&((Recovered_Cursor *)0)->field_41) == 65) ? 1 : -1];
typedef char assert_Recovered_Cursor_42[(((int)&((Recovered_Cursor *)0)->field_42) == 66) ? 1 : -1];
typedef char assert_Recovered_Cursor_43[(((int)&((Recovered_Cursor *)0)->field_43) == 67) ? 1 : -1];
typedef char assert_Recovered_Cursor_48[(((int)&((Recovered_Cursor *)0)->field_48) == 72) ? 1 : -1];
typedef char assert_Recovered_Cursor_50[(((int)&((Recovered_Cursor *)0)->field_50) == 80) ? 1 : -1];
#endif
