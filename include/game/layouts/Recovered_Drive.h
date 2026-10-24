/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_DRIVE_H
#define RECOVERED_DRIVE_H
#include "ps2/prelude.h"

typedef struct Recovered_Drive {
    u8 opaque_0[20];
    u8 field_14; /* PS2 +0x14 */
    u8 opaque_15[3];
    f32 field_18; /* PS2 +0x18 */
    f32 field_1C; /* PS2 +0x1C */
} Recovered_Drive;
typedef char assert_Recovered_Drive_14[(((int)&((Recovered_Drive *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_Drive_18[(((int)&((Recovered_Drive *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_Drive_1C[(((int)&((Recovered_Drive *)0)->field_1C) == 28) ? 1 : -1];
#endif
