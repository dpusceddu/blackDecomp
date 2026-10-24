/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BUFFERAT4_H
#define RECOVERED_BUFFERAT4_H
#include "ps2/prelude.h"

typedef struct Recovered_BufferAt4 {
    u32 field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
    u32 field_8; /* PS2 +0x8 */
} Recovered_BufferAt4;
typedef char assert_Recovered_BufferAt4_0[(((int)&((Recovered_BufferAt4 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_BufferAt4_4[(((int)&((Recovered_BufferAt4 *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_BufferAt4_8[(((int)&((Recovered_BufferAt4 *)0)->field_8) == 8) ? 1 : -1];
#endif
