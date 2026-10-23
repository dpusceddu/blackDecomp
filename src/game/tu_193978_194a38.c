#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_Vtable_003DF5D0.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00193988();
extern s32 func_00180CC8(void *, s32);
extern s32 * func_001825B0(void *);

s32 * func_00194A38(Recovered_Vtable_003DF5D0 *arg0) {
    func_00193988();
    func_00180CC8((void *) (((s8 *) arg0->field_0) + 0xB30), 0);
    M2C_FIELD(arg0->field_0, s8 *, 0x845) = 0;
    return func_001825B0((void *) (((s8 *) arg0->field_0) + 0x810));
}
