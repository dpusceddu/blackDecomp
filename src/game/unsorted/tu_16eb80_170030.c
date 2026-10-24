#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/object_56980.h"
#include "ps2/recovered_types.h"
extern void ** D_003C87E8;
extern s32 (*D_003C87EC)();
extern s32 ** func_00170090(s32 **);

s32 ** func_00170030(void) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 temp_6;
    void *temp_3;

    *(Recovered_Object56980 * *)(sp + 0) = NULL;
    temp_3 = *D_003C87E8;
    temp_6 = M2C_FIELD(temp_3, s32 (**)(void *, M2C_UNK, void *, void **), 0x34)((void *) (((s8 *) D_003C87E8) + M2C_FIELD(temp_3, s16 *, 0x30)), 0x14, sp, D_003C87E8);
    if (D_003C87EC != NULL) {
        D_003C87EC(*(Recovered_Object56980 * *)(sp + 0), 0x14, temp_6);
    }
    return func_00170090((s32 **) *(Recovered_Object56980 * *)(sp + 0));
}
