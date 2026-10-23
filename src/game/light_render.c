#include "game/effects/emitter.h"
extern void func_001D0B20(int,int),func_001D0D10(void *),func_001D0D80(void);
void func_001C1930(BkEffectLightsPS2 *pool) {
 u16 index=0;func_001D0B20(0,0);
 if(pool->definitionCount)do {func_001D0D10(pool->definitions+index*0x90);index++;}while(index<pool->definitionCount);
 func_001D0D80();
}
