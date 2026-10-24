#include "ps2/prelude.h"
typedef struct { char padding[0x2e0]; float speed; } BkActorRatePS2;
extern BkActorRatePS2 **func_001AC040(void *);
extern void *func_00135550(BkActorRatePS2 *);
extern float func_0013EE68(void *), D_003BD18C;
float func_001AC4B8(void *context) {
 BkActorRatePS2 **actor=func_001AC040(context); float pitch=0.0f;
 if(func_00135550(*actor)) {
  float angle=func_0013EE68(func_00135550(*actor));
  pitch=angle;
  if((*actor)->speed>1.0f) pitch+=D_003BD18C;
  pitch*=1.3f;
  __asm__("max.s %0, %0, %1" : "+f" (pitch) : "f" (-90.0f));
  __asm__("min.s %0, %0, %1" : "+f" (pitch) : "f" (90.0f));
 }
 return -pitch;
}
