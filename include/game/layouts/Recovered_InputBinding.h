/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_INPUTBINDING_H
#define RECOVERED_INPUTBINDING_H
#include "ps2/prelude.h"

typedef struct Recovered_InputBinding {
    u8 opaque_0[152];
    u32 field_98; /* PS2 +0x98 */
    u8 opaque_9C[132];
    u8 field_120; /* PS2 +0x120 */
} Recovered_InputBinding;
typedef char assert_Recovered_InputBinding_98[(((int)&((Recovered_InputBinding *)0)->field_98) == 152) ? 1 : -1];
typedef char assert_Recovered_InputBinding_120[(((int)&((Recovered_InputBinding *)0)->field_120) == 288) ? 1 : -1];
#endif
