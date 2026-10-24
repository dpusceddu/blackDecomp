/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWADRIVERCONTEXT_H
#define RECOVERED_RWADRIVERCONTEXT_H
#include "ps2/prelude.h"

typedef struct Recovered_RwaDriverContext {
    u8 opaque_0[32];
    void * field_20; /* PS2 +0x20 */
    u8 opaque_24[68];
    u32 field_68; /* PS2 +0x68 */
} Recovered_RwaDriverContext;
typedef char assert_Recovered_RwaDriverContext_20[(((int)&((Recovered_RwaDriverContext *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_RwaDriverContext_68[(((int)&((Recovered_RwaDriverContext *)0)->field_68) == 104) ? 1 : -1];
#endif
