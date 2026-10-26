#include "include_asm.h"
#include "sony/timer.h"
extern void* memset(void* output, s32 value, u32 size);
extern s32 func_00367550(s32 interrupt, s32 (*handler)(s32, void*, void*), s32 priority, void* argument);
extern s32 func_003682D0(s32 interrupt);
extern s32 Timer_InterruptHandler(s32 cause, void* argument, void* interruptedPc);
extern Recovered_TimerCounter gTimerCounters[128];

extern void Timer_WriteRegister(u32 address, u32 value);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08", func_0036DB08);

void Timer_WriteCount(u32 arg0) { Timer_WriteRegister(0xB0001000, arg0); }

void Timer_WriteMode(u32 arg0) { Timer_WriteRegister(0xB0001010, arg0); }

void Timer_WriteCompare(u32 arg0) { Timer_WriteRegister(0xB0001020, arg0); }

s32 InitTimer(u32 requestedMode) {
    s32 handler, enabled, index;
    u32 mode;
    if (gTimerState.interruptHandler >= 0) return 0x80008001;
    gTimerState.overflowCount = 0;
    gTimerState.usedCounters = 0;
    memset(gTimerCounters, 0, sizeof(gTimerCounters));
    gTimerState.freeCounters = gTimerCounters;
    for (index = 127; index >= 0; --index) gTimerCounters[index].next = &gTimerCounters[index + 1];
    gTimerCounters[127].next = 0;
    Timer_InitAlarmPool();
    handler = func_00367550(11, Timer_InterruptHandler, 0, 0);
    if (handler < 0) return 0x80009021;
    gTimerState.interruptHandler = handler;
    enabled = DIntr();
    mode = *(volatile u32*)0x10001010;
    mode = (mode & ~3) | requestedMode;
    mode |= 0x300;
    if (!(mode & 0x80)) {
        mode |= 0xC80;
        Timer_WriteCount(0);
        Timer_WriteCompare(0xFFFF);
    }
    Timer_WriteMode(mode);
    func_003682D0(11);
    if (enabled) EIntr();
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08", func_0036DD00);
s32 StartTimerSystemTime(void) {
    s32 enabled = DIntr();
    u32 mode = *(volatile u32*)0x10001010;
    if (mode & 0x80) {
        if (enabled) EIntr();
        return 1;
    } else {
        Timer_WriteMode((mode & ~0xC00) | 0x80);
        Timer_SetNextCompare(iGetTimerSystemTime());
        if (enabled) EIntr();
        return 0;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08", func_0036DD98);
void Timer_SetNextCompare(u64 current) {
    Recovered_TimerCounter* counter;
    u64 deadline;
    u32 mode;
    u32 scale;
    counter = gTimerState.alarms;
    if (gTimerState.currentId >= 0) return;
    mode = *(volatile u32*)0x10001010;
    if (!counter) {
        Timer_WriteCompare(0);
        Timer_WriteMode(mode & ~0x800);
        return;
    }
    deadline = counter->scheduled + counter->baseTime - counter->baseCount;
    for (counter = counter->next; counter; counter = counter->next) {
        u64 nextDeadline = counter->scheduled + counter->baseTime - counter->baseCount;
        if (nextDeadline < deadline + 0x7333) {
            deadline = nextDeadline;
        } else {
            break;
        }
    }
    scale = mode & 3;
    /* Native near-deadline comparison treats the 64-bit difference as signed. */
    if ((s64)(deadline - current) < 0x7333) {
        Timer_WriteCompare(*(volatile u32*)0x10001000 + (u32)((u64)0x7333 >> (scale << 2)));
        Timer_WriteMode(mode & ~0x800);
        return;
    } else {
        Timer_WriteMode(mode & ~0x800);
        Timer_WriteCompare((u32)(deadline >> (scale << 2)));
    }
}
void Timer_InsertAlarm(Recovered_TimerCounter* counter) {
    Recovered_TimerCounter* previous = 0;
    Recovered_TimerCounter* next = gTimerState.alarms;
    u64 deadline = counter->scheduled + counter->baseTime - counter->baseCount;
    while (next) {
        u64 nextDeadline = next->scheduled + next->baseTime - next->baseCount;
        if (deadline < nextDeadline) break;
        previous = next;
        next = next->next;
    }
    counter->previous = previous;
    counter->next = next;
    if (next) next->previous = counter;
    if (previous)
        previous->next = counter;
    else
        gTimerState.alarms = counter;
}
