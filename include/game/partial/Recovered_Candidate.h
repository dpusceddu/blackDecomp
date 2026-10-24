/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CANDIDATE_H
#define RECOVERED_CANDIDATE_H
#include "ps2/prelude.h"

typedef struct Recovered_Candidate {
    s32 field_0; /* PS2 +0x0 */
    f32 field_4; /* PS2 +0x4 */
    u8 opaque_8[4];
    f32 field_C; /* PS2 +0xC */
    u8 opaque_10[16];
    f32 field_20; /* PS2 +0x20 */
    u8 opaque_24[16];
    void * field_34; /* PS2 +0x34 */
} Recovered_Candidate;
typedef char assert_Recovered_Candidate_0[(((int)&((Recovered_Candidate *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Candidate_4[(((int)&((Recovered_Candidate *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Candidate_C[(((int)&((Recovered_Candidate *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Candidate_20[(((int)&((Recovered_Candidate *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Candidate_34[(((int)&((Recovered_Candidate *)0)->field_34) == 52) ? 1 : -1];
#endif
