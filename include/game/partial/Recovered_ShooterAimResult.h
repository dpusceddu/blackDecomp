/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SHOOTERAIMRESULT_H
#define RECOVERED_SHOOTERAIMRESULT_H
#include "ps2/prelude.h"

typedef struct Recovered_ShooterAimResult {
    void * field_0; /* PS2 +0x0 */
    u8 opaque_4[8];
    void * field_C; /* PS2 +0xC */
    u8 opaque_10[8];
    f32 field_18; /* PS2 +0x18 */
    u8 opaque_1C[4];
    f32 field_20; /* PS2 +0x20 */
    f32 field_24; /* PS2 +0x24 */
    f32 field_28; /* PS2 +0x28 */
    f32 field_2C; /* PS2 +0x2C */
    f32 field_30; /* PS2 +0x30 */
    f32 field_34; /* PS2 +0x34 */
    f32 field_38; /* PS2 +0x38 */
    u8 field_3C; /* PS2 +0x3C */
} Recovered_ShooterAimResult;
typedef char assert_Recovered_ShooterAimResult_0[(((int)&((Recovered_ShooterAimResult *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_ShooterAimResult_C[(((int)&((Recovered_ShooterAimResult *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_ShooterAimResult_18[(((int)&((Recovered_ShooterAimResult *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_ShooterAimResult_20[(((int)&((Recovered_ShooterAimResult *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_ShooterAimResult_24[(((int)&((Recovered_ShooterAimResult *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_ShooterAimResult_28[(((int)&((Recovered_ShooterAimResult *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_ShooterAimResult_2C[(((int)&((Recovered_ShooterAimResult *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_ShooterAimResult_30[(((int)&((Recovered_ShooterAimResult *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_ShooterAimResult_34[(((int)&((Recovered_ShooterAimResult *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_ShooterAimResult_38[(((int)&((Recovered_ShooterAimResult *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_ShooterAimResult_3C[(((int)&((Recovered_ShooterAimResult *)0)->field_3C) == 60) ? 1 : -1];
#endif
