#ifndef SONY_CLOCK_H
#define SONY_CLOCK_H
#include "ps2/prelude.h"

/* The same eight-byte clock transports BCD at the public conversion boundary
 * and binary fields inside calendar arithmetic; years wrap within 2000-2099. */
typedef struct {
    u8 status;
    u8 second;
    u8 minute;
    u8 hour;
    u8 unk_04;
    u8 day;
    u8 month;
    u8 year;
} Recovered_Clock;

void Clock_FromBcd(Recovered_Clock* clock);
void Clock_ToBcd(Recovered_Clock* clock);
void Clock_IncrementDate(Recovered_Clock* clock);
void Clock_DecrementDate(Recovered_Clock* clock);
void Clock_IncrementHour(Recovered_Clock* clock);
void Clock_DecrementHour(Recovered_Clock* clock);
void Clock_AdjustMinutes(Recovered_Clock* clock, s32 minutes);
void Clock_ConvertToGmt(Recovered_Clock* clock);
void Clock_ConvertToLocal(Recovered_Clock* clock);
#endif
