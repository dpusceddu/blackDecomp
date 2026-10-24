/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SLOTOWNER_H
#define RECOVERED_SLOTOWNER_H
#include "ps2/prelude.h"

typedef struct Recovered_SlotOwner {
    u32 field_0; /* PS2 +0x0 */
    u8 opaque_4[128];
    void * field_84; /* PS2 +0x84 */
    u8 opaque_88[4];
    void * field_8C; /* PS2 +0x8C */
    void * field_90; /* PS2 +0x90 */
    void * field_94; /* PS2 +0x94 */
    void * field_98; /* PS2 +0x98 */
    void * field_9C; /* PS2 +0x9C */
    void * field_A0; /* PS2 +0xA0 */
    void * field_A4; /* PS2 +0xA4 */
    void * field_A8; /* PS2 +0xA8 */
    u8 opaque_AC[96];
    s32 field_10C; /* PS2 +0x10C */
} Recovered_SlotOwner;
typedef char assert_Recovered_SlotOwner_0[(((int)&((Recovered_SlotOwner *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_SlotOwner_84[(((int)&((Recovered_SlotOwner *)0)->field_84) == 132) ? 1 : -1];
typedef char assert_Recovered_SlotOwner_8C[(((int)&((Recovered_SlotOwner *)0)->field_8C) == 140) ? 1 : -1];
typedef char assert_Recovered_SlotOwner_90[(((int)&((Recovered_SlotOwner *)0)->field_90) == 144) ? 1 : -1];
typedef char assert_Recovered_SlotOwner_94[(((int)&((Recovered_SlotOwner *)0)->field_94) == 148) ? 1 : -1];
typedef char assert_Recovered_SlotOwner_98[(((int)&((Recovered_SlotOwner *)0)->field_98) == 152) ? 1 : -1];
typedef char assert_Recovered_SlotOwner_9C[(((int)&((Recovered_SlotOwner *)0)->field_9C) == 156) ? 1 : -1];
typedef char assert_Recovered_SlotOwner_A0[(((int)&((Recovered_SlotOwner *)0)->field_A0) == 160) ? 1 : -1];
typedef char assert_Recovered_SlotOwner_A4[(((int)&((Recovered_SlotOwner *)0)->field_A4) == 164) ? 1 : -1];
typedef char assert_Recovered_SlotOwner_A8[(((int)&((Recovered_SlotOwner *)0)->field_A8) == 168) ? 1 : -1];
typedef char assert_Recovered_SlotOwner_10C[(((int)&((Recovered_SlotOwner *)0)->field_10C) == 268) ? 1 : -1];
#endif
