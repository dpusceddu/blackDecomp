#include "ps2/prelude.h"
extern void **func_001AC040(void *);
extern void *func_00135550(void *);
extern float func_0013EF08(void *);
float func_001AC440(void *context) {
 void **actor=func_001AC040(context); float bearing=0.0f;
 if(func_00135550(*actor)) {
 float angle=func_0013EF08(func_00135550(*actor));
 __asm__("max.s %0, %1, %2" : "=&f" (bearing) : "f" (angle), "f" (-90.0f));
 __asm__("min.s %0, %0, %1" : "+f" (bearing) : "f" (90.0f));
 }
 return bearing;
}
