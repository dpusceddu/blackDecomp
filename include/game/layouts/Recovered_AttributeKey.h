/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ATTRIBUTEKEY_H
#define RECOVERED_ATTRIBUTEKEY_H
#include "ps2/prelude.h"

typedef struct Recovered_AttributeKey {
    s32 field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
} Recovered_AttributeKey;
typedef char assert_Recovered_AttributeKey_0[(((int)&((Recovered_AttributeKey *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_AttributeKey_4[(((int)&((Recovered_AttributeKey *)0)->field_4) == 4) ? 1 : -1];
#endif
