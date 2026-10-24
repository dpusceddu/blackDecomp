#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Vtable_003E0B90: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003E0B90 {
    s32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u8 unk_10[4];
    u32 unk_14;
    void * unk_18;
    void * unk_1C;
    void * unk_20;
    void * unk_24;
    void * unk_28;
    u8 unk_2C[4];
    void * unk_30;
    void * unk_34;
} Recovered_Vtable_003E0B90;

#include "ps2/recovered_types.h"
extern s32 func_001F1C08(void *);

s32 func_001F7B90(Recovered_Vtable_003E0B90 *arg0) {
    s32 var_2;
    void **var_16;

    func_001F1C08(arg0);
    var_16 = &arg0->unk_1C;
    var_2 = 1;
    do {
        *var_16 = NULL;
        var_2 -= 1;
        var_16 = (void **) (((s8 *) var_16) + -4);
    } while (var_2 >= 0);
    return var_2;
}
