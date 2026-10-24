/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CLIPVIEW_H
#define RECOVERED_CLIPVIEW_H
#include "ps2/prelude.h"

typedef struct Recovered_ClipView {
    u8 opaque_0[24];
    s32 field_18; /* PS2 +0x18 */
    u8 opaque_1C[8];
    s32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
} Recovered_ClipView;
typedef char assert_Recovered_ClipView_18[(((int)&((Recovered_ClipView *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_ClipView_24[(((int)&((Recovered_ClipView *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_ClipView_28[(((int)&((Recovered_ClipView *)0)->field_28) == 40) ? 1 : -1];
#endif
