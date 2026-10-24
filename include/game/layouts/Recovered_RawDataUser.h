/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RAWDATAUSER_H
#define RECOVERED_RAWDATAUSER_H
#include "ps2/prelude.h"

typedef struct Recovered_RawDataUser {
    u8 opaque_0[4];
    void * field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    s16 field_10; /* PS2 +0x10 */
} Recovered_RawDataUser;
typedef char assert_Recovered_RawDataUser_4[(((int)&((Recovered_RawDataUser *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_RawDataUser_8[(((int)&((Recovered_RawDataUser *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_RawDataUser_C[(((int)&((Recovered_RawDataUser *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_RawDataUser_10[(((int)&((Recovered_RawDataUser *)0)->field_10) == 16) ? 1 : -1];
#endif
