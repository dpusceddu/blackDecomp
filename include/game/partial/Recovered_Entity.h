/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ENTITY_H
#define RECOVERED_ENTITY_H
#include "ps2/prelude.h"

typedef struct Recovered_Entity {
    void * field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
    u32 field_8; /* PS2 +0x8 */
    void * field_C; /* PS2 +0xC */
    u32 field_10; /* PS2 +0x10 */
    s32 field_14; /* PS2 +0x14 */
    void * field_18; /* PS2 +0x18 */
    u8 opaque_1C[4];
    u32 field_20; /* PS2 +0x20 */
    u32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    void * field_2C; /* PS2 +0x2C */
    u8 opaque_30[40];
    s32 field_58; /* PS2 +0x58 */
    s32 field_5C; /* PS2 +0x5C */
} Recovered_Entity;
typedef char assert_Recovered_Entity_0[(((int)&((Recovered_Entity *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Entity_4[(((int)&((Recovered_Entity *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Entity_8[(((int)&((Recovered_Entity *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_Entity_C[(((int)&((Recovered_Entity *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Entity_10[(((int)&((Recovered_Entity *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Entity_14[(((int)&((Recovered_Entity *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_Entity_18[(((int)&((Recovered_Entity *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_Entity_20[(((int)&((Recovered_Entity *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Entity_24[(((int)&((Recovered_Entity *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_Entity_28[(((int)&((Recovered_Entity *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_Entity_2C[(((int)&((Recovered_Entity *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_Entity_58[(((int)&((Recovered_Entity *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_Entity_5C[(((int)&((Recovered_Entity *)0)->field_5C) == 92) ? 1 : -1];
#endif
