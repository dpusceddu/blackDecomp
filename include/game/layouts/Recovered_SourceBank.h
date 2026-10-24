/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SOURCEBANK_H
#define RECOVERED_SOURCEBANK_H
#include "ps2/prelude.h"

typedef struct Recovered_SourceBank {
    u8 opaque_0[36];
    s32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    s32 field_2C; /* PS2 +0x2C */
    s32 field_30; /* PS2 +0x30 */
    s32 field_34; /* PS2 +0x34 */
    s32 field_38; /* PS2 +0x38 */
} Recovered_SourceBank;
typedef char assert_Recovered_SourceBank_24[(((int)&((Recovered_SourceBank *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_SourceBank_28[(((int)&((Recovered_SourceBank *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_SourceBank_2C[(((int)&((Recovered_SourceBank *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_SourceBank_30[(((int)&((Recovered_SourceBank *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_SourceBank_34[(((int)&((Recovered_SourceBank *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_SourceBank_38[(((int)&((Recovered_SourceBank *)0)->field_38) == 56) ? 1 : -1];
#endif
