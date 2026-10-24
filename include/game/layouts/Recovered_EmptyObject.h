/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_EMPTYOBJECT_H
#define RECOVERED_EMPTYOBJECT_H
#include "ps2/prelude.h"

typedef struct Recovered_EmptyObject {
    u32 field_0; /* PS2 +0x0 */
} Recovered_EmptyObject;
typedef char assert_Recovered_EmptyObject_0[(((int)&((Recovered_EmptyObject *)0)->field_0) == 0) ? 1 : -1];
#endif
