/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_TYPEINFO_H
#define RECOVERED_TYPEINFO_H
#include "ps2/prelude.h"

typedef struct Recovered_TypeInfo {
    s32 field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
} Recovered_TypeInfo;
typedef char assert_Recovered_TypeInfo_0[(((int)&((Recovered_TypeInfo *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_TypeInfo_4[(((int)&((Recovered_TypeInfo *)0)->field_4) == 4) ? 1 : -1];
#endif
