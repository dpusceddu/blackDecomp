/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BKEFFECTSLOTPS2_H
#define RECOVERED_BKEFFECTSLOTPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_BkEffectSlotPS2 {
    u8 opaque_0[4];
    u16 field_4; /* PS2 +0x4 */
    u16 field_6; /* PS2 +0x6 */
    u32 field_8; /* PS2 +0x8 */
    u8 field_C; /* PS2 +0xC */
    u8 field_D; /* PS2 +0xD */
} Recovered_BkEffectSlotPS2;
typedef char assert_Recovered_BkEffectSlotPS2_4[(((int)&((Recovered_BkEffectSlotPS2 *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_BkEffectSlotPS2_6[(((int)&((Recovered_BkEffectSlotPS2 *)0)->field_6) == 6) ? 1 : -1];
typedef char assert_Recovered_BkEffectSlotPS2_8[(((int)&((Recovered_BkEffectSlotPS2 *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_BkEffectSlotPS2_C[(((int)&((Recovered_BkEffectSlotPS2 *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_BkEffectSlotPS2_D[(((int)&((Recovered_BkEffectSlotPS2 *)0)->field_D) == 13) ? 1 : -1];
#endif
