/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FORMATIONMODE_H
#define RECOVERED_FORMATIONMODE_H
#include "ps2/prelude.h"

typedef struct Recovered_FormationMode {
    u8 opaque_0[48];
    s32 field_30; /* PS2 +0x30 */
    void * field_34; /* PS2 +0x34 */
    u8 opaque_38[24];
    u8 field_50; /* PS2 +0x50 */
} Recovered_FormationMode;
typedef char assert_Recovered_FormationMode_30[(((int)&((Recovered_FormationMode *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_FormationMode_34[(((int)&((Recovered_FormationMode *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_FormationMode_50[(((int)&((Recovered_FormationMode *)0)->field_50) == 80) ? 1 : -1];
#endif
