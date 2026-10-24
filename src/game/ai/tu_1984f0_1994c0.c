#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Vtable_003DF170: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003DF170 {
    void * unk_0;
} Recovered_Vtable_003DF170;

#include "ps2/recovered_types.h"
extern s32 func_00198568();

s32 func_001994C0(Recovered_Vtable_003DF170 *arg0) {
    void *temp_2;

    func_00198568();
    temp_2 = arg0->unk_0;
    M2C_FIELD(M2C_FIELD(temp_2, void **, 0x694), s8 *, 0x30) = 0;
    return (s32) temp_2;
}
