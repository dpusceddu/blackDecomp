/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SCRIPTMANAGER_H
#define RECOVERED_SCRIPTMANAGER_H
#include "ps2/prelude.h"

typedef struct Recovered_ScriptManager {
    u32 field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
} Recovered_ScriptManager;
typedef char assert_Recovered_ScriptManager_0[(((int)&((Recovered_ScriptManager *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_ScriptManager_4[(((int)&((Recovered_ScriptManager *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_ScriptManager_8[(((int)&((Recovered_ScriptManager *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_ScriptManager_C[(((int)&((Recovered_ScriptManager *)0)->field_C) == 12) ? 1 : -1];
#endif
