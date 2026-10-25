#include "ps2/prelude.h"
#include "ps2/prototypes.h"

/* The action header's brain field is verified. */
extern void func_00193980(RecoveredAIActionHeader *);
extern void func_001998F8(RecoveredAIActionHeader *);

void func_00199850(RecoveredAIActionHeader *action) {
    func_00193980(action);
    ((unsigned char *)action->brain)[0x104] = 0;
    func_001998F8(action);
}
