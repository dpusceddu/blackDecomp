/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ANIMATIONCOLLECTIONINDICES_H
#define RECOVERED_ANIMATIONCOLLECTIONINDICES_H
#include "ps2/prelude.h"

typedef struct Recovered_AnimationCollectionIndices {
    u8 opaque_0[32];
    void * field_20; /* PS2 +0x20 */
    void * field_24; /* PS2 +0x24 */
    void * field_28; /* PS2 +0x28 */
    void * field_2C; /* PS2 +0x2C */
} Recovered_AnimationCollectionIndices;
typedef char assert_Recovered_AnimationCollectionIndices_20[(((int)&((Recovered_AnimationCollectionIndices *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_AnimationCollectionIndices_24[(((int)&((Recovered_AnimationCollectionIndices *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_AnimationCollectionIndices_28[(((int)&((Recovered_AnimationCollectionIndices *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_AnimationCollectionIndices_2C[(((int)&((Recovered_AnimationCollectionIndices *)0)->field_2C) == 44) ? 1 : -1];
#endif
