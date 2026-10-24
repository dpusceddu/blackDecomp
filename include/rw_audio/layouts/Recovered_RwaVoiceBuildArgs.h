/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWAVOICEBUILDARGS_H
#define RECOVERED_RWAVOICEBUILDARGS_H
#include "ps2/prelude.h"

typedef struct Recovered_RwaVoiceBuildArgs {
    u8 opaque_0[28];
    void * field_1C; /* PS2 +0x1C */
    u8 opaque_20[16];
    s32 field_30; /* PS2 +0x30 */
    s32 field_34; /* PS2 +0x34 */
} Recovered_RwaVoiceBuildArgs;
typedef char assert_Recovered_RwaVoiceBuildArgs_1C[(((int)&((Recovered_RwaVoiceBuildArgs *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_RwaVoiceBuildArgs_30[(((int)&((Recovered_RwaVoiceBuildArgs *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_RwaVoiceBuildArgs_34[(((int)&((Recovered_RwaVoiceBuildArgs *)0)->field_34) == 52) ? 1 : -1];
#endif
