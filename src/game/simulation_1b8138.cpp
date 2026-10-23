#include "game/effects/mod_simulation.hpp"
void ModEffects::GeometryNodes::Clear(){int i=11;BkEffectGeometryBucketPS2**p=heads;do{((void**)p)[-12]=0;--i;*p++=0;}while(i>=0);BkEffectGeometryBucketPS2*b=nodes,*end=nodes+8;do{b->count=0;b->next=0;b++;}while((int)b<(int)end);}
