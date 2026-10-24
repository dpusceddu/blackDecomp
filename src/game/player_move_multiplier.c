#include "ps2/prelude.h"
typedef struct { char padding[0x2e0]; float speed; } BkActorRatePS2;
extern BkActorRatePS2 **func_001AC040(void *);
extern void *func_00135550(BkActorRatePS2 *);
extern float D_003BD184, D_003BD188;
float func_001AC330(void *context) {
 BkActorRatePS2 **actor=func_001AC040(context);
 float rate;
 if(func_00135550(*actor)) rate=((*actor)->speed-D_003BD184)/D_003BD188;
 else rate=1.0f;
 return rate;
}
