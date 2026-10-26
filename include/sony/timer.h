#ifndef SONY_TIMER_H
#define SONY_TIMER_H
#include "ps2/prelude.h"

/* Native timer-counter views; names are corroborated by PS2SDK's timer.c.
 * IDs encode a 64-byte-aligned counter address and a ten-bit generation key.
 * https://github.com/ps2dev/ps2sdk/blob/master/ee/kernel/src/timer.c */
typedef u64 (*TimerAlarmHandler)(s32 id, u64 scheduled, u64 current, void* argument, void* interruptedPc);
typedef struct Recovered_TimerCounter {
    struct Recovered_TimerCounter* next;
    struct Recovered_TimerCounter* previous;
    volatile u32 key;
    u32 mode;
    u64 baseTime;
    u64 baseCount;
    u64 scheduled;
    TimerAlarmHandler handler;
    void* gp;       // UNVERIFIED: architectural callback context in the setup draft.
    void* argument; // UNVERIFIED: callback setup/dispatch remain drafts.
} __attribute__((aligned(64))) Recovered_TimerCounter;

typedef struct {
    volatile u64 overflowCount;
    s32 interruptHandler;
    volatile u32 generation;
    volatile u32 usedCounters;
    Recovered_TimerCounter* freeCounters;
    Recovered_TimerCounter* alarms;
    volatile s32 currentId;
} Recovered_TimerState;

typedef struct Recovered_AlarmNode {
    struct Recovered_AlarmNode* next;
    volatile s32 counterId;
    TimerAlarmHandler handler;
    void* argument;
} Recovered_AlarmNode;

typedef char TimerCounterStride[sizeof(Recovered_TimerCounter) == 0x40 ? 1 : -1];
typedef char TimerCounterHandlerOffset[(u32) & ((Recovered_TimerCounter*)0)->handler == 0x28 ? 1 : -1];
typedef char AlarmNodeStride[sizeof(Recovered_AlarmNode) == 0x10 ? 1 : -1];

s32 AllocTimerCounter(void);
s32 iStartTimerCounter(s32 id);
s32 StartTimerCounter(s32 id);
s32 iSetTimerHandler(s32 id, u64 scheduled, TimerAlarmHandler handler, void* argument);
s32 SetTimerHandler(s32 id, u64 scheduled, TimerAlarmHandler handler, void* argument);
u64 TimerUSec2BusClock(u32 seconds, u32 microseconds);
s32 Timer_InitAlarmPool(void);
u64 Timer_DispatchAlarm(s32 id, u64 scheduled, u64 current, void* argument, void* interruptedPc);
s32 SetAlarm(u64 scheduled, TimerAlarmHandler handler, void* argument);
s32 iSetAlarm(u64 scheduled, TimerAlarmHandler handler, void* argument);

s32 DIntr(void);
s32 EIntr(void);
s32 iAllocTimerCounter(void);
u64 iGetTimerSystemTime(void);
void Timer_InsertAlarm(Recovered_TimerCounter* counter);
Recovered_TimerCounter* Timer_UnlinkAlarm(Recovered_TimerCounter* counter);
void Timer_SetNextCompare(u64 current);
extern Recovered_TimerState gTimerState;
extern Recovered_AlarmNode gAlarmNodes[64];
extern Recovered_AlarmNode* gFreeAlarmNodes;

void Timer_WriteRegister(u32 address, u32 value);
void Timer_WriteCount(u32 value);
void Timer_WriteMode(u32 value);
void Timer_WriteCompare(u32 value);
s32 InitTimer(u32 requestedMode);
s32 StartTimerSystemTime(void);
s32 Timer_InterruptHandler(s32 cause, void* argument, void* interruptedPc);
extern Recovered_TimerCounter gTimerCounters[128];
#endif
