/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_MEMBERLIST_H
#define RECOVERED_MEMBERLIST_H
#include "ps2/prelude.h"

typedef struct Recovered_MemberList {
    u8 opaque_0[4];
    void * field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
} Recovered_MemberList;
typedef char assert_Recovered_MemberList_4[(((int)&((Recovered_MemberList *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_MemberList_8[(((int)&((Recovered_MemberList *)0)->field_8) == 8) ? 1 : -1];
#endif
