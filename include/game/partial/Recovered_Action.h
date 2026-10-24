/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ACTION_H
#define RECOVERED_ACTION_H
#include "ps2/prelude.h"

typedef struct Recovered_Action {
    void * field_0; /* PS2 +0x0 */
    u8 opaque_4[4];
    u8 field_8; /* PS2 +0x8 */
} Recovered_Action;
typedef char assert_Recovered_Action_0[(((int)&((Recovered_Action *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Action_8[(((int)&((Recovered_Action *)0)->field_8) == 8) ? 1 : -1];
#endif
