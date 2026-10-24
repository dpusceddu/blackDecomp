/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_POINTMAPPER_H
#define RECOVERED_POINTMAPPER_H
#include "ps2/prelude.h"

typedef struct Recovered_PointMapper {
    void * field_0; /* PS2 +0x0 */
    f32 field_4; /* PS2 +0x4 */
    f32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    s32 field_14; /* PS2 +0x14 */
    s32 field_18; /* PS2 +0x18 */
} Recovered_PointMapper;
typedef char assert_Recovered_PointMapper_0[(((int)&((Recovered_PointMapper *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PointMapper_4[(((int)&((Recovered_PointMapper *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_PointMapper_8[(((int)&((Recovered_PointMapper *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_PointMapper_C[(((int)&((Recovered_PointMapper *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_PointMapper_10[(((int)&((Recovered_PointMapper *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_PointMapper_14[(((int)&((Recovered_PointMapper *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_PointMapper_18[(((int)&((Recovered_PointMapper *)0)->field_18) == 24) ? 1 : -1];
#endif
