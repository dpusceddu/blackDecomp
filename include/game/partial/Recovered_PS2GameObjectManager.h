/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PS2GAMEOBJECTMANAGER_H
#define RECOVERED_PS2GAMEOBJECTMANAGER_H
#include "ps2/prelude.h"

typedef struct Recovered_PS2GameObjectManager {
    u8 opaque_0[23716];
    void * field_5CA4; /* PS2 +0x5CA4 */
} Recovered_PS2GameObjectManager;
typedef char assert_Recovered_PS2GameObjectManager_5CA4[(((int)&((Recovered_PS2GameObjectManager *)0)->field_5CA4) == 23716) ? 1 : -1];
#endif
