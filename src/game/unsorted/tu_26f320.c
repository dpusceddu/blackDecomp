#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_002A5038(void *);
extern void func_0029D478(void *);
extern void func_0029D470(void *);

typedef struct {
    s16 year;
    s16 month;
    s16 day;
    s16 hour;
    s16 minute;
    s16 second;
} Recovered_CalendarTime;

typedef struct {
    u8 reserved_00;
    u8 second;
    u8 minute;
    u8 hour;
    u8 reserved_04;
    u8 day;
    u8 month;
    u8 year;
} Recovered_BcdClock;

s32 func_0026F320(s32 arg0)
{
  int new_var;
  if (arg0)
  {
  }
  arg0 = arg0 & 0xFF;
  new_var = 4;
  return (arg0 & 0xF) + (((arg0 >> new_var) & 0xFFFF) * 0xA);
}

void func_0026F340(Recovered_CalendarTime *time) {
    Recovered_BcdClock clock;
    func_002A5038(&clock);
    func_0029D478(&clock);
    time->year = func_0026F320(clock.year) + 2000;
    time->month = func_0026F320(clock.month);
    time->day = func_0026F320(clock.day);
    time->hour = func_0026F320(clock.hour);
    time->minute = func_0026F320(clock.minute);
    time->second = func_0026F320(clock.second);
}
void func_0026F3C0(Recovered_CalendarTime *time) {
    Recovered_BcdClock clock;
    func_002A5038(&clock);
    func_0029D470(&clock);
    time->year = func_0026F320(clock.year) + 2000;
    time->month = func_0026F320(clock.month);
    time->day = func_0026F320(clock.day);
    time->hour = func_0026F320(clock.hour);
    time->minute = func_0026F320(clock.minute);
    time->second = func_0026F320(clock.second);
}
