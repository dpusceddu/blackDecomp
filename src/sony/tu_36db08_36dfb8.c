#include "include_asm.h"
#include "sony/timer.h"

Recovered_TimerCounter* Timer_UnlinkAlarm(Recovered_TimerCounter* counter) {
    Recovered_TimerCounter* next = counter->next;
    if (counter->previous)
        counter->previous->next = next;
    else
        gTimerState.alarms = counter->next;
    if (next) next->previous = counter->previous;
    counter->previous = 0;
    return next;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36dfb8", func_0036DFF0);

#ifdef NON_MATCHING
// Unmatched: MMIO zero-extension, prescale shifts and scheduling differ from the native leaf.
u64 iGetTimerSystemTime(void) {
    volatile u32* timer = (volatile u32*)0x10001000;
    u64 low = timer[0];
    u32 mode = timer[4];
    u64 high = gTimerState.overflowCount;
    u64 scale = 2;
    if (mode & 0x800) {
        ++high;
        low = timer[0];
    }
    mode &= 3;
    if (!mode) scale = 0;
    return (((u64)high << 16) | low) << (scale << mode);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36dfb8", func_0036E298);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36dfb8", func_0036E2E8);

s32 iAllocTimerCounter(void) {
    Recovered_TimerCounter* counter = gTimerState.freeCounters;
    if (!counter) return 0x80008005;
    gTimerState.freeCounters = counter->next;
    ++gTimerState.usedCounters;
    counter->mode = 0;
    counter->handler = 0;
    counter->baseCount = 0;
    ++gTimerState.generation;
    counter->key = ((gTimerState.generation << 1) & 0x3FE) | 1;
    return ((u32)counter << 4) | counter->key;
}
