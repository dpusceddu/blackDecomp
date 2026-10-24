/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ENTITYOBJECT_H
#define RECOVERED_ENTITYOBJECT_H
#include "ps2/prelude.h"

typedef struct Recovered_EntityObject {
    u8 opaque_0[20];
    void * field_14; /* PS2 +0x14 */
} Recovered_EntityObject;
typedef char assert_Recovered_EntityObject_14[(((int)&((Recovered_EntityObject *)0)->field_14) == 20) ? 1 : -1];
#endif
