/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PATHOBJECT_H
#define RECOVERED_PATHOBJECT_H
#include "ps2/prelude.h"

typedef struct Recovered_PathObject {
    u8 opaque_0[112];
    s32 field_70; /* PS2 +0x70 */
    s32 field_74; /* PS2 +0x74 */
    void * field_78; /* PS2 +0x78 */
    void * field_7C; /* PS2 +0x7C */
} Recovered_PathObject;
typedef char assert_Recovered_PathObject_70[(((int)&((Recovered_PathObject *)0)->field_70) == 112) ? 1 : -1];
typedef char assert_Recovered_PathObject_74[(((int)&((Recovered_PathObject *)0)->field_74) == 116) ? 1 : -1];
typedef char assert_Recovered_PathObject_78[(((int)&((Recovered_PathObject *)0)->field_78) == 120) ? 1 : -1];
typedef char assert_Recovered_PathObject_7C[(((int)&((Recovered_PathObject *)0)->field_7C) == 124) ? 1 : -1];
#endif
