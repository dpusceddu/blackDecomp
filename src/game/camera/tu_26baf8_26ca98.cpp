#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/camera/pad_backend.hpp"
// Unmatched: 10 instruction differences after original layout, argument-bank and helper probes.
using namespace Graphics;
bool PadBackend::Attach(Controller *controller,unsigned port) {
    bool valid=controller!=0;
    if(port<2){if(!valid)return false;valid=controller->field_4==state[port];}
    if(!valid||port>=2)return false;
    if(controllers[port])return false;
    controllers[port]=controller;++count;
    controller->Open((unsigned)this,port);
    return true;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_26baf8_26ca98", func_0026CA98);
#endif

#ifdef NON_MATCHING
#include "game/camera/pad_backend.hpp"
// Unmatched: 12 instruction differences after original layout, argument-bank and helper probes.
using namespace Graphics;
void PadBackend::Detach(Controller *controller,unsigned port) {
    bool valid=controller!=0;
    if(port<2){if(!valid)return;valid=controllers[port]==controller;}
    if(valid&&port<2){controllers[port]=0;--count;controller->Close();}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_26baf8_26ca98", func_0026CB38);
#endif

#ifdef NON_MATCHING
#include "game/camera/pad_backend.hpp"
// Unmatched: 2 instruction differences after original layout, argument-bank and helper probes.
extern "C" {
void *func_0035C6EC(void *,int,unsigned int);
int func_0029B558();
int func_0029C6C8(int);
int func_0029C708(const void*,void*);
long func_0029CA10(int);
long func_0029C940(int,void*);
int func_0029C868(int,void*);
int func_0029C810(int);
}
struct PadOpenParameters {int kind,port;EeS64 reserved[3];} __attribute__((packed));
extern const PadOpenParameters defaultPadParameters __asm__("D_004001D0");
using namespace Graphics;
static inline int *Slot(int *array,int index){return array+index;}
void PadBackend::PollPort(int port){
 unsigned int info[4];PadOpenParameters config=defaultPadParameters;
 switch(port){case 0:config.port=0;break;case 1:config.port=1;break;default:return;}
 int *handle=Slot(handles,port);
 if(*handle<0){*handle=func_0029C708(&config,buffers[port]);}
 else{
  long status=func_0029CA10(*handle);
  if(status==1){int *mode=Slot(state,port);if(*mode==0){if(func_0029C940(*handle,info)>0){if(info[0]==0xffffffffu)*mode=4;else if(info[0]==0xffff0f00u)*mode=3;}}
   else func_0029C868(*handle,packets[port]);
  }else if(status==0){func_0029C810(*handle);*handle=-1;state[port]=0;}
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_26baf8_26ca98", func_0026CBA8);
#endif
