/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RECOVEREDROUTEREQUEST_H
#define RECOVERED_RECOVEREDROUTEREQUEST_H
#include "ps2/prelude.h"

typedef struct Recovered_RecoveredRouteRequest {
    u8 opaque_0[32];
    u128 field_20; /* PS2 +0x20 */
    u8 opaque_30[4];
    void * field_34; /* PS2 +0x34 */
    u8 opaque_38[12];
    f32 field_44; /* PS2 +0x44 */
    f32 field_48; /* PS2 +0x48 */
    f32 field_4C; /* PS2 +0x4C */
    void * field_50; /* PS2 +0x50 */
} Recovered_RecoveredRouteRequest;
typedef char assert_Recovered_RecoveredRouteRequest_20[(((int)&((Recovered_RecoveredRouteRequest *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_RecoveredRouteRequest_34[(((int)&((Recovered_RecoveredRouteRequest *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_RecoveredRouteRequest_44[(((int)&((Recovered_RecoveredRouteRequest *)0)->field_44) == 68) ? 1 : -1];
typedef char assert_Recovered_RecoveredRouteRequest_48[(((int)&((Recovered_RecoveredRouteRequest *)0)->field_48) == 72) ? 1 : -1];
typedef char assert_Recovered_RecoveredRouteRequest_4C[(((int)&((Recovered_RecoveredRouteRequest *)0)->field_4C) == 76) ? 1 : -1];
typedef char assert_Recovered_RecoveredRouteRequest_50[(((int)&((Recovered_RecoveredRouteRequest *)0)->field_50) == 80) ? 1 : -1];
#endif
