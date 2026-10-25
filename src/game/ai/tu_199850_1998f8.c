#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern int func_00180BC0(void *);

void func_001998F8(RecoveredAIActionHeader *action) {
    if (func_00180BC0((char *)action->brain + 0xb30) == 0) {
        func_00193A28(action, 12, 0);
        return;
    }
    func_00193A28(action, 0x37, 0);
}
