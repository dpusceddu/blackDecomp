#include "game/effects/mod_slot_views.hpp"
extern "C" void func_001B3D18(void *);
void ModEffects::Bank::RemoveBone(Actor *actor,unsigned char bone){
 unsigned short index=actor->indices[bone];unsigned count=actor->boneCount;
 if(index!=0xffff)func_001B3D18(&At(index));
 for(unsigned char i=bone+1;i<count;++i){index=actor->indices[i];if(index!=0xffff){--At(index).mode;actor->indices[(unsigned char)(i-1)]=index;}else actor->Release((unsigned char)(i-1));}
 if(count)actor->indices[(unsigned char)(count-1)]=0xffff;
}
