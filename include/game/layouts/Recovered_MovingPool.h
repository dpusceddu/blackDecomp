/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_MOVINGPOOL_H
#define RECOVERED_MOVINGPOOL_H
#include "ps2/prelude.h"

typedef struct Recovered_MovingPool {
    u8 opaque_0[1896];
    u8 field_768; /* PS2 +0x768 */
    u8 opaque_769[143];
    u8 field_7F8; /* PS2 +0x7F8 */
    u8 opaque_7F9[143];
    u8 field_888; /* PS2 +0x888 */
    u8 opaque_889[143];
    u8 field_918; /* PS2 +0x918 */
    u8 opaque_919[143];
    u8 field_9A8; /* PS2 +0x9A8 */
    u8 opaque_9A9[143];
    u8 field_A38; /* PS2 +0xA38 */
    u8 opaque_A39[143];
    u8 field_AC8; /* PS2 +0xAC8 */
    u8 opaque_AC9[143];
    u8 field_B58; /* PS2 +0xB58 */
} Recovered_MovingPool;
typedef char assert_Recovered_MovingPool_768[(((int)&((Recovered_MovingPool *)0)->field_768) == 1896) ? 1 : -1];
typedef char assert_Recovered_MovingPool_7F8[(((int)&((Recovered_MovingPool *)0)->field_7F8) == 2040) ? 1 : -1];
typedef char assert_Recovered_MovingPool_888[(((int)&((Recovered_MovingPool *)0)->field_888) == 2184) ? 1 : -1];
typedef char assert_Recovered_MovingPool_918[(((int)&((Recovered_MovingPool *)0)->field_918) == 2328) ? 1 : -1];
typedef char assert_Recovered_MovingPool_9A8[(((int)&((Recovered_MovingPool *)0)->field_9A8) == 2472) ? 1 : -1];
typedef char assert_Recovered_MovingPool_A38[(((int)&((Recovered_MovingPool *)0)->field_A38) == 2616) ? 1 : -1];
typedef char assert_Recovered_MovingPool_AC8[(((int)&((Recovered_MovingPool *)0)->field_AC8) == 2760) ? 1 : -1];
typedef char assert_Recovered_MovingPool_B58[(((int)&((Recovered_MovingPool *)0)->field_B58) == 2904) ? 1 : -1];
#endif
