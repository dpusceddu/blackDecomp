#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Vtable_003DF5D0: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003DF5D0 {
    void * unk_0;
} Recovered_Vtable_003DF5D0;

#include "ps2/recovered_types.h"
extern s32 func_00193988();
extern s32 func_00180CC8(void *, s32);
extern s32 * func_001825B0(void *);

s32 * func_00194A38(Recovered_Vtable_003DF5D0 *arg0) {
    func_00193988();
    func_00180CC8((void *) (((s8 *) arg0->unk_0) + 0xB30), 0);
    M2C_FIELD(arg0->unk_0, s8 *, 0x845) = 0;
    return func_001825B0((void *) (((s8 *) arg0->unk_0) + 0x810));
}
