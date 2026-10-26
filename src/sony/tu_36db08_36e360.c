#include "include_asm.h"
#include "sony/timer.h"

static inline Recovered_TimerCounter* CounterFromId(s32 id) { return (Recovered_TimerCounter*)(((u32)id >> 10) << 6); }

s32 AllocTimerCounter(void) {
    s32 enabled = DIntr();
    s32 result = iAllocTimerCounter();
    if (enabled) EIntr();
    return result;
}
/* Native cleanup islands are retained as assembly, rather than treated as functions. */
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36e360", func_0036E3A8);

s32 iStartTimerCounter(s32 id) {
    Recovered_TimerCounter* counter = CounterFromId(id);
    u64 current;
    if (id < 0 || (id & 0x3FF) != counter->key) return 0x80008002;
    if (gTimerState.currentId == id) return 0x80000010;
    if (counter->mode & 1) return 1;
    current = iGetTimerSystemTime();
    counter->baseTime = current;
    counter->mode |= 1;
    if (counter->mode & 2) {
        Timer_InsertAlarm(counter);
        Timer_SetNextCompare(current);
    }
    return 0;
}

s32 StartTimerCounter(s32 id) {
    s32 enabled = DIntr();
    s32 result = iStartTimerCounter(id);
    if (enabled) EIntr();
    return result;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36e360", func_0036E4B8);

#ifdef NON_MATCHING
// Unmatched: callback setup retains different argument registers and omits the native mode reload.
s32 iSetTimerHandler(s32 id, u64 scheduled, TimerAlarmHandler handler, void* argument) {
    Recovered_TimerCounter* counter = CounterFromId(id);
    void* savedArgument = argument;
    if (id < 0 || (id & 0x3FF) != counter->key) return 0x80008002;
    if (gTimerState.currentId == id) return 0x80000010;
    if (counter->mode & 2) Timer_UnlinkAlarm(counter);
    counter->handler = handler;
    if (!handler)
        counter->mode &= ~2;
    else {
        counter->scheduled = scheduled;
        counter->mode |= 2;
        /* Save the architectural GP used when invoking this callback. */
        __asm__ volatile("sw $gp, %0" : "=m"(counter->gp));
        counter->argument = savedArgument;
        if (counter->mode & 1) Timer_InsertAlarm(counter);
    }
    Timer_SetNextCompare(iGetTimerSystemTime());
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36e360", func_0036E4E8);
#endif

s32 SetTimerHandler(s32 id, u64 scheduled, TimerAlarmHandler handler, void* argument) {
    s32 enabled = DIntr();
    s32 result = iSetTimerHandler(id, scheduled, handler, argument);
    if (enabled) EIntr();
    return result;
}

u64 TimerUSec2BusClock(u32 seconds, u32 microseconds) {
    return (u64)seconds * 147456000U + (u64)microseconds * 147456000U / 1000000U;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36e360", func_0036E6D0);

s32 Timer_InitAlarmPool(void) {
    s32 index;
    gFreeAlarmNodes = gAlarmNodes;
    for (index = 63; index >= 0; --index) gAlarmNodes[index].next = &gAlarmNodes[index + 1];
    gAlarmNodes[63].next = 0;
    return 0;
}

static inline Recovered_AlarmNode* AllocateAlarmNode(void) {
    Recovered_AlarmNode* node = gFreeAlarmNodes;
    if (node) gFreeAlarmNodes = node->next;
    return node;
}

static inline void ReleaseAlarmNode(Recovered_AlarmNode* node) {
    node->next = gFreeAlarmNodes;
    node->counterId = 0;
    gFreeAlarmNodes = node;
}

u64 Timer_DispatchAlarm(s32 id, u64 scheduled, u64 current, void* argument, void* interruptedPc) {
    Recovered_AlarmNode* node = argument;
    u64 result = node->handler(((u32)node << 4) | (id & 0xFE) | 1, scheduled, current, node->argument, interruptedPc);
    if (result == 0) {
        ReleaseAlarmNode(node);
        return (u64)-1;
    } else {
        return result;
    }
}

s32 SetAlarm(u64 scheduled, TimerAlarmHandler handler, void* argument) {
    s32 enabled, counterId;
    Recovered_AlarmNode* node;
    if (!handler) return 0x80000016;
    enabled = DIntr();
    node = AllocateAlarmNode();
    if (!node) {
        if (enabled) EIntr();
        return 0x80008005;
    }
    counterId = AllocTimerCounter();
    if (counterId < 0) {
        ReleaseAlarmNode(node);
        if (enabled) EIntr();
        return counterId;
    } else {
        node->handler = handler;
        node->argument = argument;
        node->counterId = counterId;
        SetTimerHandler(counterId, scheduled, Timer_DispatchAlarm, node);
        StartTimerCounter(counterId);
        if (enabled) EIntr();
        return ((u32)node << 4) | (counterId & 0xFE) | 1;
    }
}

s32 iSetAlarm(u64 scheduled, TimerAlarmHandler handler, void* argument) {
    s32 counterId;
    Recovered_AlarmNode* node;
    if (!handler) return 0x80000016;
    node = AllocateAlarmNode();
    if (!node) return 0x80008005;
    counterId = iAllocTimerCounter();
    if (counterId < 0) {
        ReleaseAlarmNode(node);
        return counterId;
    } else {
        node->handler = handler;
        node->argument = argument;
        node->counterId = counterId;
        iSetTimerHandler(counterId, scheduled, Timer_DispatchAlarm, node);
        iStartTimerCounter(counterId);
        return ((u32)node << 4) | (counterId & 0xFE) | 1;
    }
}
