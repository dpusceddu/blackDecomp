#include "ps2/prelude.h"
#include "types_ghidra.h"

/* The action header's brain field is verified. Only the event's leading
   discriminator is used; its full object layout remains unverified. */
extern void func_00193980(RecoveredAIActionHeader *);
extern int func_00180BC0(void *);
extern void func_001998F8(RecoveredAIActionHeader *);

#if defined(ACTION_ENTER_ONLY)
void func_00199850(RecoveredAIActionHeader *action) {
    func_00193980(action);
    ((unsigned char *)action->brain)[0x104] = 0;
    func_001998F8(action);
}
#elif defined(ACTION_NOTIFY_ONLY)
void func_00199888(RecoveredAIActionHeader *action, int state) {
    if (state == 12) {
        func_00193A28(action, 0x37, 0);
        return;
    }
    func_001998F8(action);
}
#elif defined(ACTION_EVENT_ONLY)
int func_001998C0(RecoveredAIActionHeader *action, const unsigned int *eventKind) {
    if (*eventKind == 5) {
        func_001998F8(action);
        return 1;
    }
    return 0;
}
#else
void func_001998F8(RecoveredAIActionHeader *action) {
    if (func_00180BC0((char *)action->brain + 0xb30) == 0) {
        func_00193A28(action, 12, 0);
        return;
    }
    func_00193A28(action, 0x37, 0);
}
#endif

#ifdef ACTION_NOTIFY_ONLY
/* Native eight-byte dispatch entries. The empty edge entries and common
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
#endif
