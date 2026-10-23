#include "auto/prelude.h"
typedef struct { char p[0x74]; float speed; char q[8]; int kind; } BkActorMovementPS2;
typedef struct { char p[0x2e0]; float speed; } BkActorRatePS2;
extern BkActorRatePS2 **func_001AC040(void *);
extern BkActorMovementPS2 *func_00135550(BkActorRatePS2 *);
extern float func_0018D9F8(void *);
float func_001AC278(void *context) {
 BkActorRatePS2 **actor=func_001AC040(context); float rate;
 if(func_00135550(*actor)) {
  if(func_00135550(*actor)->kind==1) {
   BkActorMovementPS2 *movement=func_00135550(*actor);
   float speed=movement->speed;
   float limit=func_0018D9F8((char *)movement+0xc94);
   __asm__("max.s %0, %1, %2" : "=&f"(rate) : "f"(speed), "f"(0.0f));
   __asm__("min.s %0, %0, %1" : "+f"(rate) : "f"(limit));
  } else {
   float speed=(*actor)->speed;
   rate=0.0f;
   __asm__("max.s %0, %1, %0" : "+f"(rate) : "f"(speed));
   __asm__("min.s %0, %0, %1" : "+f"(rate) : "f"(6.519989967346191f));
  }
 } else rate=1.6f;
 return rate;
}
