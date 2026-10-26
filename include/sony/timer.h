#ifndef SONY_TIMER_H
#define SONY_TIMER_H
#include "ps2/prelude.h"

/* Native timer-counter views; names are corroborated by PS2SDK's timer.c.
 * IDs encode a 64-byte-aligned counter address and a ten-bit generation key.
 * https://github.com/ps2dev/ps2sdk/blob/master/ee/kernel/src/timer.c */
typedef u64 (*TimerAlarmHandler)(s32 id, u64 scheduled, u64 current, void* argument, void* interruptedPc);
typedef struct Recovered_TimerCounter {
    struct Recovered_TimerCounter* next;     // UNVERIFIED: not used by this batch.
    struct Recovered_TimerCounter* previous; // UNVERIFIED: not used by this batch.
    volatile u32 key;
    u32 mode;
    u64 baseTime;
    u64 baseCount;             // UNVERIFIED: not used by this batch.
    u64 scheduled;             // UNVERIFIED: only drafted handler setup uses this field.
    TimerAlarmHandler handler; // UNVERIFIED: callback setup/dispatch remain drafts.
    void* gp;                  // UNVERIFIED: architectural callback context in the setup draft.
    void* argument;            // UNVERIFIED: callback setup/dispatch remain drafts.
} __attribute__((aligned(64))) Recovered_TimerCounter;

typedef struct {
    u8 unk_00[0x1C];
    volatile s32 currentId;
} Recovered_TimerState;

typedef struct Recovered_AlarmNode {
    struct Recovered_AlarmNode* next;
    volatile s32 counterId;    // UNVERIFIED: allocation/dispatch remain drafts.
    TimerAlarmHandler handler; // UNVERIFIED: callback setup/dispatch remain drafts.
    void* argument;            // UNVERIFIED: callback setup/dispatch remain drafts.
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
#endif
