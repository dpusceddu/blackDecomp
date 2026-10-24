/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_WEIGHTCOMMAND_H
#define RECOVERED_WEIGHTCOMMAND_H
#include "ps2/prelude.h"

typedef struct Recovered_WeightCommand {
    u8 opaque_0[36];
    void * field_24; /* PS2 +0x24 */
} Recovered_WeightCommand;
typedef char assert_Recovered_WeightCommand_24[(((int)&((Recovered_WeightCommand *)0)->field_24) == 36) ? 1 : -1];
#endif
