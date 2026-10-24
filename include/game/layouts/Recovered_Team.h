/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_TEAM_H
#define RECOVERED_TEAM_H
#include "ps2/prelude.h"

typedef struct Recovered_Team {
    void * field_0; /* PS2 +0x0 */
    u8 opaque_4[4];
    void * field_8; /* PS2 +0x8 */
    u8 opaque_C[4];
    void * field_10; /* PS2 +0x10 */
} Recovered_Team;
typedef char assert_Recovered_Team_0[(((int)&((Recovered_Team *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Team_8[(((int)&((Recovered_Team *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_Team_10[(((int)&((Recovered_Team *)0)->field_10) == 16) ? 1 : -1];
#endif
