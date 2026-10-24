#include "include_asm.h"

#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_002060D8(s32);
extern s32 func_002059A0(void *);
extern s32 func_00205C10(void *);
extern s32 func_00204EC0(void *);
extern s32 func_00205808();
extern s32 func_00205CA0(void *);
extern s32 func_002053E0(void *);
extern s32 func_00205878(void *, s32);
extern s32 func_00205AA0(void *);
extern s32 func_00204AF8(void *);

void func_002052A0(void *arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_2 != arg1) {
        switch (temp_2) {                           /* switch 1 */
        case 1:                                     /* switch 1 */
            func_002060D8(M2C_FIELD(arg0, s32 *, 0xC));
            break;
        case 2:                                     /* switch 1 */
            func_002059A0(M2C_FIELD(arg0, void **, 8));
            break;
        case 3:                                     /* switch 1 */
            func_00205C10(M2C_FIELD(arg0, void **, 0x10));
            break;
        case 4:                                     /* switch 1 */
            func_00204EC0(M2C_FIELD(arg0, void **, 0x14));
            break;
        case 5:                                     /* switch 1 */
            func_00205808(M2C_FIELD(arg0, void **, 0x18));
            break;
        }
        switch (arg1) {                             /* switch 2 */
        case 1:                                     /* switch 2 */
            func_00205CA0((void *) M2C_FIELD(arg0, s32 *, 0xC));
            break;
        case 5:                                     /* switch 2 */
            func_002053E0(M2C_FIELD(arg0, void **, 0x18));
            break;
        case 2:                                     /* switch 2 */
            func_00205878(M2C_FIELD(arg0, void **, 8), M2C_FIELD(arg0, s32 *, 4));
            break;
        case 3:                                     /* switch 2 */
            func_00205AA0(M2C_FIELD(arg0, void **, 0x10));
            break;
        case 4:                                     /* switch 2 */
            func_00204AF8(M2C_FIELD(arg0, void **, 0x14));
            break;
        }
        M2C_FIELD(arg0, s32 *, 4) = arg1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002053C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002053E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00205798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00205808);
