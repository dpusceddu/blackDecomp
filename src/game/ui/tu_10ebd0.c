#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010EBD0);

/* Recovered_FrontendProfilePool: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_FrontendProfilePool {
    u32 unk_0;
} Recovered_FrontendProfilePool;

#include "ps2/recovered_types.h"
extern s32 func_00122AF0();

s32 func_0010F188(Recovered_FrontendProfilePool *arg0) {
    Recovered_FrontendProfilePool *temp_2;
    Recovered_FrontendProfilePool *var_16;
    s32 var_17;

    var_16 = (Recovered_FrontendProfilePool *) (((s8 *) arg0) + 8);
    var_17 = 0;
    do {
        var_17 -= 1;
        func_00122AF0(var_16);
        var_16 = (Recovered_FrontendProfilePool *) (((s8 *) var_16) + 0x6A8);
    } while (var_17 >= 0);
    temp_2 = (Recovered_FrontendProfilePool *) (((s8 *) arg0) + 8);
    arg0->unk_0 = (u32) temp_2;
    return (s32) temp_2;
}

#include "ps2/recovered_types.h"
extern s32 func_00122B10(void *);

s32 func_0010F1E0(Recovered_FrontendProfilePool *arg0) {
    Recovered_FrontendProfilePool *var_16;
    s32 var_17;

    var_16 = (Recovered_FrontendProfilePool *) (((s8 *) arg0) + 8);
    var_17 = 0;
    do {
        var_17 -= 1;
        func_00122B10(var_16);
        var_16 = (Recovered_FrontendProfilePool *) (((s8 *) var_16) + 0x6A8);
    } while (var_17 >= 0);
    arg0->unk_0 = (u32) ((Recovered_FrontendProfilePool *) (((s8 *) arg0) + 8));
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010F240);
