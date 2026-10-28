#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00204F00(void *);
extern void * D_003BDCC8;
extern s32 * func_00107D20(s32);
extern M2C_UNK D_003E0CA8;
extern s32 * func_00107CF8(void *);
extern void func_00204FF0(void *, void *);
extern void func_00207978(void *);

void func_00205A00(void *arg0) {
    s32 *temp_2;
    s32 *var_3;
    s32 var_4;

    func_00204F00(arg0);
    D_003BDCC8 = arg0;
    temp_2 = func_00107D20(0x38);
    var_3 = temp_2;
    var_4 = 1;
    do {
        M2C_FIELD(var_3, M2C_UNK **, 0x14) = &D_003E0CA8;
        var_4 -= 1;
        var_3 = (s32 *) (((s8 *) var_3) + 0x1C);
    } while (var_4 != -1);
    M2C_FIELD(arg0, s32 **, 0x60) = temp_2;
    M2C_FIELD(arg0, s32 **, 0x64) = func_00107CF8((void *)0x2C);
    func_00204FF0(M2C_FIELD(arg0, s32 **, 0x60), arg0);
    func_00204FF0((s32 *) (((s8 *) M2C_FIELD(arg0, s32 **, 0x60)) + 0x1C), arg0);
    func_00207978(M2C_FIELD(arg0, s32 **, 0x64));
}
