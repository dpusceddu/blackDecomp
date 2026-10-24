#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00193980();
extern s32 func_00193A60(RecoveredAIActionHeader *, M2C_UNK, f32);

void func_00197A88(RecoveredAIActionHeader *arg0) {
    func_00193980();
    func_00193A60(arg0, 1, 2.0f);
}
