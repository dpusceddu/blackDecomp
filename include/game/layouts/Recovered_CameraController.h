/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CAMERACONTROLLER_H
#define RECOVERED_CAMERACONTROLLER_H
#include "ps2/prelude.h"

typedef struct Recovered_CameraController {
    u8 opaque_0[124];
    void * field_7C; /* PS2 +0x7C */
    u8 opaque_80[1040];
    void * field_490; /* PS2 +0x490 */
    void * field_494; /* PS2 +0x494 */
    void * field_498; /* PS2 +0x498 */
    void * field_49C; /* PS2 +0x49C */
    void * field_4A0; /* PS2 +0x4A0 */
    void * field_4A4; /* PS2 +0x4A4 */
    void * field_4A8; /* PS2 +0x4A8 */
    void * field_4AC; /* PS2 +0x4AC */
    s32 field_4B0; /* PS2 +0x4B0 */
    s32 field_4B4; /* PS2 +0x4B4 */
    s32 field_4B8; /* PS2 +0x4B8 */
    s32 field_4BC; /* PS2 +0x4BC */
    s32 field_4C0; /* PS2 +0x4C0 */
    s32 field_4C4; /* PS2 +0x4C4 */
    s32 field_4C8; /* PS2 +0x4C8 */
    s32 field_4CC; /* PS2 +0x4CC */
    s32 field_4D0; /* PS2 +0x4D0 */
    s32 field_4D4; /* PS2 +0x4D4 */
    u8 opaque_4D8[4];
    s32 field_4DC; /* PS2 +0x4DC */
} Recovered_CameraController;
typedef char assert_Recovered_CameraController_7C[(((int)&((Recovered_CameraController *)0)->field_7C) == 124) ? 1 : -1];
typedef char assert_Recovered_CameraController_490[(((int)&((Recovered_CameraController *)0)->field_490) == 1168) ? 1 : -1];
typedef char assert_Recovered_CameraController_494[(((int)&((Recovered_CameraController *)0)->field_494) == 1172) ? 1 : -1];
typedef char assert_Recovered_CameraController_498[(((int)&((Recovered_CameraController *)0)->field_498) == 1176) ? 1 : -1];
typedef char assert_Recovered_CameraController_49C[(((int)&((Recovered_CameraController *)0)->field_49C) == 1180) ? 1 : -1];
typedef char assert_Recovered_CameraController_4A0[(((int)&((Recovered_CameraController *)0)->field_4A0) == 1184) ? 1 : -1];
typedef char assert_Recovered_CameraController_4A4[(((int)&((Recovered_CameraController *)0)->field_4A4) == 1188) ? 1 : -1];
typedef char assert_Recovered_CameraController_4A8[(((int)&((Recovered_CameraController *)0)->field_4A8) == 1192) ? 1 : -1];
typedef char assert_Recovered_CameraController_4AC[(((int)&((Recovered_CameraController *)0)->field_4AC) == 1196) ? 1 : -1];
typedef char assert_Recovered_CameraController_4B0[(((int)&((Recovered_CameraController *)0)->field_4B0) == 1200) ? 1 : -1];
typedef char assert_Recovered_CameraController_4B4[(((int)&((Recovered_CameraController *)0)->field_4B4) == 1204) ? 1 : -1];
typedef char assert_Recovered_CameraController_4B8[(((int)&((Recovered_CameraController *)0)->field_4B8) == 1208) ? 1 : -1];
typedef char assert_Recovered_CameraController_4BC[(((int)&((Recovered_CameraController *)0)->field_4BC) == 1212) ? 1 : -1];
typedef char assert_Recovered_CameraController_4C0[(((int)&((Recovered_CameraController *)0)->field_4C0) == 1216) ? 1 : -1];
typedef char assert_Recovered_CameraController_4C4[(((int)&((Recovered_CameraController *)0)->field_4C4) == 1220) ? 1 : -1];
typedef char assert_Recovered_CameraController_4C8[(((int)&((Recovered_CameraController *)0)->field_4C8) == 1224) ? 1 : -1];
typedef char assert_Recovered_CameraController_4CC[(((int)&((Recovered_CameraController *)0)->field_4CC) == 1228) ? 1 : -1];
typedef char assert_Recovered_CameraController_4D0[(((int)&((Recovered_CameraController *)0)->field_4D0) == 1232) ? 1 : -1];
typedef char assert_Recovered_CameraController_4D4[(((int)&((Recovered_CameraController *)0)->field_4D4) == 1236) ? 1 : -1];
typedef char assert_Recovered_CameraController_4DC[(((int)&((Recovered_CameraController *)0)->field_4DC) == 1244) ? 1 : -1];
#endif
