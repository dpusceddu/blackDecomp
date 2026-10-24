/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RECORD_H
#define RECOVERED_RECORD_H
#include "ps2/prelude.h"

typedef struct Recovered_Record {
    u32 field_0; /* PS2 +0x0 */
    u8 opaque_4[128];
    void * field_84; /* PS2 +0x84 */
} Recovered_Record;
typedef char assert_Recovered_Record_0[(((int)&((Recovered_Record *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Record_84[(((int)&((Recovered_Record *)0)->field_84) == 132) ? 1 : -1];
#endif
