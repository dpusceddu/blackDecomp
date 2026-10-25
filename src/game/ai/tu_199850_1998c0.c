#include "ps2/prelude.h"
#include "ps2/prototypes.h"

/* Only the event's leading discriminator is used; its full object layout remains unverified. */
extern void func_001998F8(RecoveredAIActionHeader *);

int func_001998C0(RecoveredAIActionHeader *action, const unsigned int *eventKind) {
    if (*eventKind == 5) {
        func_001998F8(action);
        return 1;
    }
    return 0;
}
