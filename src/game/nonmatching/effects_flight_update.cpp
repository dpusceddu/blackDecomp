#include "game/effects/flight.h"
#include "game/effects/geometry.h"
extern "C" {extern char *D_0040F4D0,*D_0040F4D8;void func_001B15A0(BkEffectEntryPS2 *),func_001B1518(BkEffectEntryPS2 *),func_001B11A0(BkEffectEntryPS2 *);int func_001B1340(BkEffectEntryPS2 *,void *,f32,f32);}
// Unmatched: flight vector y/w lanes and matrix multiplication temporary lifetimes.
#ifdef NONMATCHING
extern "C" void func_001BECD0(BkEffectFlightPS2 *flights) {
 f32 now=*(f32 *)(D_0040F4D0+0x20),elapsedFrame=now-*(f32 *)(D_0040F4D0+0x1c);
 for(u16 index=0;index<44;index++) {
  BkEffectFlightPS2 *flight=flights+index;
  if(flight->active) {
   f32 elapsed=now-flight->origin.w;
   if(flight->lifetime<elapsed) {flight->active=0;if(flight->child.resource) {func_001B15A0(&flight->child);func_001B1518(&flight->child);}}
   else if(!flight->child.resource)flight->active=0;
   else {
    BkEffectPointPS2 position={flight->origin.x+flight->velocity.x*elapsed,flight->origin.y+flight->velocity.y*elapsed+0.5f*flight->velocity.w*elapsed*elapsed,flight->origin.z+flight->velocity.z*elapsed,0};
    flight->world[3]=*(s128 *)&position;
    if(flight->relative) {
     s128 combined[4];flight->world[3]=BkEffectTransformPS2(flight->world,flight->localOffset);
     for(int i=0;i<3;i++)combined[i]=BkEffectRotatePS2(flight->world,flight->initial[i]);combined[3]=BkEffectTransformPS2(flight->world,flight->initial[3]);
     for(int i=0;i<4;i++)flight->world[i]=combined[i];
    }
    func_001B11A0(&flight->child);if(!func_001B1340(&flight->child,D_0040F4D8,now,elapsedFrame))func_001B1518(&flight->child);
   }
  }
 }
}
#endif // NONMATCHING
