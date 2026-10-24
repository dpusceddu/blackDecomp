/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWTEXTUREVIEW_H
#define RECOVERED_RWTEXTUREVIEW_H
#include "ps2/prelude.h"

typedef struct Recovered_RwTextureView {
    u8 opaque_0[47];
    u8 field_2F; /* PS2 +0x2F */
    u8 opaque_30[31];
    u8 field_4F; /* PS2 +0x4F */
} Recovered_RwTextureView;
typedef char assert_Recovered_RwTextureView_2F[(((int)&((Recovered_RwTextureView *)0)->field_2F) == 47) ? 1 : -1];
typedef char assert_Recovered_RwTextureView_4F[(((int)&((Recovered_RwTextureView *)0)->field_4F) == 79) ? 1 : -1];
#endif
