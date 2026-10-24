/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWIMAGEVIEW_H
#define RECOVERED_RWIMAGEVIEW_H
#include "ps2/prelude.h"

typedef struct Recovered_RwImageView {
    void * field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    void * field_8; /* PS2 +0x8 */
    void * field_C; /* PS2 +0xC */
    void * field_10; /* PS2 +0x10 */
    void * field_14; /* PS2 +0x14 */
    void * field_18; /* PS2 +0x18 */
    void * field_1C; /* PS2 +0x1C */
    void * field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    s32 field_2C; /* PS2 +0x2C */
    s32 field_30; /* PS2 +0x30 */
} Recovered_RwImageView;
typedef char assert_Recovered_RwImageView_0[(((int)&((Recovered_RwImageView *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_RwImageView_4[(((int)&((Recovered_RwImageView *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_RwImageView_8[(((int)&((Recovered_RwImageView *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_RwImageView_C[(((int)&((Recovered_RwImageView *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_RwImageView_10[(((int)&((Recovered_RwImageView *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_RwImageView_14[(((int)&((Recovered_RwImageView *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_RwImageView_18[(((int)&((Recovered_RwImageView *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_RwImageView_1C[(((int)&((Recovered_RwImageView *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_RwImageView_20[(((int)&((Recovered_RwImageView *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_RwImageView_24[(((int)&((Recovered_RwImageView *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_RwImageView_28[(((int)&((Recovered_RwImageView *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_RwImageView_2C[(((int)&((Recovered_RwImageView *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_RwImageView_30[(((int)&((Recovered_RwImageView *)0)->field_30) == 48) ? 1 : -1];
#endif
