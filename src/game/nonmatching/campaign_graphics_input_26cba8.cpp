#include "game/camera/pad_backend.hpp"
// Unmatched: 2 instruction differences after native layout, argument-bank and helper probes.
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
using namespace CampaignGraphics;
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
