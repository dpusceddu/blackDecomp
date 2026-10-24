/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWAVOICE_H
#define RECOVERED_RWAVOICE_H
#include "ps2/prelude.h"

typedef struct Recovered_RwaVoice {
    u8 opaque_0[144];
    void * field_90; /* PS2 +0x90 */
    u8 opaque_94[40];
    u16 field_BC; /* PS2 +0xBC */
} Recovered_RwaVoice;
typedef char assert_Recovered_RwaVoice_90[(((int)&((Recovered_RwaVoice *)0)->field_90) == 144) ? 1 : -1];
typedef char assert_Recovered_RwaVoice_BC[(((int)&((Recovered_RwaVoice *)0)->field_BC) == 188) ? 1 : -1];
#endif
