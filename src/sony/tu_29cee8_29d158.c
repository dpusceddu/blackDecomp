#include "include_asm.h"
#include "sony/clock.h"
#include "sony/osd_config.h"

typedef struct {
    char days[12];
} MonthLengths;
extern const MonthLengths D_00401FE0;

extern u8 func_0029D138(u8 bcd);
extern u8 func_0029D108(u8 binary);

void Clock_FromBcd(Recovered_Clock* clock) {
    clock->year = func_0029D138(clock->year);
    clock->month = func_0029D138(clock->month);
    clock->day = func_0029D138(clock->day);
    clock->hour = func_0029D138(clock->hour);
    clock->minute = func_0029D138(clock->minute);
    clock->second = func_0029D138(clock->second);
}
void Clock_ToBcd(Recovered_Clock* clock) {
    clock->year = func_0029D108(clock->year);
    clock->month = func_0029D108(clock->month);
    clock->day = func_0029D108(clock->day);
    clock->hour = func_0029D108(clock->hour);
    clock->minute = func_0029D108(clock->minute);
    clock->second = func_0029D108(clock->second);
}

void Clock_IncrementDate(Recovered_Clock* clock) {
    MonthLengths table = D_00401FE0;
    ++clock->day;
    if ((clock->year & 3) == 0) table.days[1] = 29;
    if (clock->day > table.days[clock->month - 1]) {
        clock->day = 1;
        if (++clock->month == 13) {
            if (clock->year == 99)
                clock->year = 0;
            else
                ++clock->year;
            clock->month = 1;
        }
    }
}

void Clock_DecrementDate(Recovered_Clock* clock) {
    MonthLengths table = D_00401FE0;
    --clock->day;
    if ((clock->year & 3) == 0) table.days[1] = 29;
    if (clock->day == 0) {
        if (--clock->month == 0) {
            if (clock->year == 0)
                clock->year = 99;
            else
                --clock->year;
            clock->month = 12;
        }
        clock->day = table.days[clock->month - 1];
    }
}

void Clock_IncrementHour(Recovered_Clock* clock) {
    if (++clock->hour == 24) {
        clock->hour = 0;
        Clock_IncrementDate(clock);
    }
}
void Clock_DecrementHour(Recovered_Clock* clock) {
    if (clock->hour == 0) {
        clock->hour = 23;
        Clock_DecrementDate(clock);
    } else
        --clock->hour;
}

void Clock_AdjustMinutes(Recovered_Clock* clock, s32 minutes) {
    s32 total;
    Clock_FromBcd(clock);
    total = clock->minute + minutes;
    minutes = total;
    if (minutes >= 0) {
        while (minutes >= 60) {
            minutes -= 60;
            Clock_IncrementHour(clock);
        }
    } else {
        while (minutes < 0) {
            minutes += 60;
            Clock_DecrementHour(clock);
        }
    }
    clock->minute = minutes;
    Clock_ToBcd(clock);
}
void Clock_ConvertToGmt(Recovered_Clock* clock) { Clock_AdjustMinutes(clock, -540); }
void Clock_ConvertToLocal(Recovered_Clock* clock) {
    s32 daylight;
    s32 timezone;
    timezone = OsdConfig_GetTimezone();
    daylight = OsdConfig_IsDaylightSavingEnabled();
    daylight = daylight * 60 - 540;
    Clock_AdjustMinutes(clock, timezone + daylight);
}
