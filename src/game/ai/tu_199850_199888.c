#include "ps2/prelude.h"
#include "ps2/prototypes.h"

/* The action header's brain field is verified. */
extern void func_001998F8(RecoveredAIActionHeader *);

void func_00199888(RecoveredAIActionHeader *action, int state) {
    if (state == 12) {
        func_00193A28(action, 0x37, 0);
        return;
    }
    func_001998F8(action);
}

/* Eight-byte dispatch entries. The empty edge entries and common
   callback roles remain unverified; the three action callbacks are identified. */
struct ActionDispatchEntry {
    short adjustment;
    unsigned short reserved;
    void (*function)(void);
};
typedef char ActionDispatchEntrySize[sizeof(struct ActionDispatchEntry) == 8 ? 1 : -1];
extern void func_00193970(void), func_00193978(void), func_00193988(void);
extern void func_00383DB0(void), func_00383DC8(void), func_00383DD0(void);
extern void func_00383DD8(void), func_00383DE0(void), func_00383DE8(void);
extern void func_00199850(RecoveredAIActionHeader *);
extern int func_001998C0(RecoveredAIActionHeader *, const unsigned int *);
struct ActionDispatchEntry D_003DE6D8[14]
    __attribute__((section(".data.action_dispatch"), aligned(8))) = {
    {0,0,0},
    {0,0,func_00193970}, {0,0,func_00193978}, {0,0,func_00383DB0},
    {0,0,(void (*)(void))func_00199850}, {0,0,func_00193988},
    {0,0,(void (*)(void))func_00199888}, {0,0,(void (*)(void))func_001998C0},
    {0,0,func_00383DC8}, {0,0,func_00383DD0}, {0,0,func_00383DD8},
    {0,0,func_00383DE0}, {0,0,func_00383DE8}, {0,0,0}
};
