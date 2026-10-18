#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00193980();
extern s32 func_00195F08();
extern s32 func_00195D48();
extern s32 func_00193A60(RecoveredAIActionHeader *, M2C_UNK, f32);

void func_00195D98(RecoveredAIActionHeader *arg0) {
    func_00193980();
    arg0->phase = 0;
    if (func_00195F08(arg0) == 0) {
        func_00195D48(arg0);
        return;
    }
    func_00193A60(arg0, 0, 10.0f);
}
