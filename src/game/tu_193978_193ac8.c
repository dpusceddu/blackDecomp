#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern RecoveredAICompletionRecord * func_00193B40(RecoveredAIActionHeader *); /* AIAction_Record */
extern s32 func_00173690(f32 *);

s32 * func_00193AC8(RecoveredAIActionHeader *arg0) {
    RecoveredAICompletionRecord *temp_2;

    temp_2 = func_00193B40(arg0);
    temp_2->interval = -1.0f;
    return func_00173690((f32 *) (((s8 *) temp_2) + 4));
}
