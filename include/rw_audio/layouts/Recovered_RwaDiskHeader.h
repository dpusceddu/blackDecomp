/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWADISKHEADER_H
#define RECOVERED_RWADISKHEADER_H
#include "ps2/prelude.h"

typedef struct Recovered_RwaDiskHeader {
    u8 opaque_0[4];
    u8 field_4; /* PS2 +0x4 */
    u8 field_5; /* PS2 +0x5 */
    u8 field_6; /* PS2 +0x6 */
    u8 field_7; /* PS2 +0x7 */
    u8 opaque_8[32];
    u32 field_28; /* PS2 +0x28 */
} Recovered_RwaDiskHeader;
typedef char assert_Recovered_RwaDiskHeader_4[(((int)&((Recovered_RwaDiskHeader *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_RwaDiskHeader_5[(((int)&((Recovered_RwaDiskHeader *)0)->field_5) == 5) ? 1 : -1];
typedef char assert_Recovered_RwaDiskHeader_6[(((int)&((Recovered_RwaDiskHeader *)0)->field_6) == 6) ? 1 : -1];
typedef char assert_Recovered_RwaDiskHeader_7[(((int)&((Recovered_RwaDiskHeader *)0)->field_7) == 7) ? 1 : -1];
typedef char assert_Recovered_RwaDiskHeader_28[(((int)&((Recovered_RwaDiskHeader *)0)->field_28) == 40) ? 1 : -1];
#endif
