/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_GRIDCONSTRAINT_H
#define RECOVERED_GRIDCONSTRAINT_H
#include "ps2/prelude.h"

typedef struct Recovered_GridConstraint {
    u8 opaque_0[4];
    void * field_4; /* PS2 +0x4 */
} Recovered_GridConstraint;
typedef char assert_Recovered_GridConstraint_4[(((int)&((Recovered_GridConstraint *)0)->field_4) == 4) ? 1 : -1];
#endif
