#include "campaign/graphics/pad_backend.hpp"
// Unmatched: 27 instruction differences after native layout, argument-bank and helper probes.
extern "C" {
void *func_0035C6EC(void *,int,unsigned int);
int func_0029B558();
int func_0029C6C8(int);
int func_0029C708(const void*,void*);
long func_0029CA10();
long func_0029C940(int,void*);
int func_0029C868(int,void*);
int func_0029C810(int);
}
struct PadOpenParameters {int kind,port;EeS64 reserved[3];} __attribute__((packed));
extern const PadOpenParameters defaultPadParameters __asm__("D_004001D0");
using namespace CampaignGraphics;
void PadBackend::Initialize(EeU8 single){
 PadOpenParameters config=defaultPadParameters;
 { int i=1;Controller **controller=&controllers[1];
 do{*controller=0;--i;--controller;}while(i>=0); }
 singlePort=single;count=0;unsigned char *data=packets[0];feedback=0;int *current=state;int i=1;
 do{*current=0;func_0035C6EC(data,0,32);data+=32;--i;++current;}while(i>=0);
 func_0029B558();func_0029C6C8(0);handles[0]=func_0029C708(&config,buffers[0]);
 int second=-1;if(!singlePort){config.port=1;second=func_0029C708(&config,buffers[1]);}
 handles[1]=second;lastMode=-1;
}
