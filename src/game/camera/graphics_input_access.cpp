#include "include_asm.h"

#include "game/camera/pad_backend.hpp"

using namespace Graphics;

unsigned char Controller::Button(unsigned index) const {if(index>=28)return 0;return *((const EeU8*)this+index+42);}

bool Controller::Pressed(unsigned index)const {if(index>=28)return false;bool result=false;if(*((const EeU8*)this+index+42))result=previousStates[index]==0;return result;}

bool Controller::Released(unsigned index)const {if(index>=28)return false;bool result=false;if(!*((const EeU8*)this+index+42))result=previousStates[index]!=0;return result;}

int PadBackend::GetState(unsigned port){if(port>=2)return 0;return state[port];}

int PadBackend::GetHandle(unsigned port){if(port>=2)return 0;return handles[port];}

void PadBackend::SetFeedback(int enabled){if(enabled!=feedback){Controller **it=controllers;feedback=enabled;int i=1;do{if(*it)(*it)->SetFeedback(feedback);--i;++it;}while(i>=0);}}


#ifdef NON_MATCHING
// Unmatched: 0x26bcf8 original connected/enable branch-tail and return allocation.
// Unmatched: 0x26bd30 command byte/halfword lifetimes and cached motor flag allocation.
// Unmatched: 0x26bf60 original scalar return tail keeps product in F0 rather than F12.
// Unmatched: 0x26c798 packed parameter copy, argument width and short-loop/call scheduling.
// Unmatched: 0x26c8e0 original controller iterator and virtual-call scheduling.
// Unmatched: 0x26ca98 pointer validity predicate and virtual Open allocation.
// Unmatched: 0x26cb38 ownership predicate and virtual Close allocation.
// Unmatched: 0x26cba8 original indexed-lvalue base/scale instruction order.
#endif

#ifdef NON_MATCHING
#include "game/camera/pad.hpp"
// Unmatched: 5 instruction differences remain in branch layout and return merging.
using namespace Graphics;
int Controller::Rumble(unsigned enabled) {
    if(!Connected())return 0;
    if(!enabled){field_49=0;return 0;}
    field_49=1;return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0026BCF8);
#endif

#ifdef NON_MATCHING
// Unmatched: Reset needs loop shape and call scheduling recovery.
// Unmatched: Pressure has a commuted address addition.
// Unmatched: Rumble needs its original boolean/result convention.
// Unmatched: Smooth needs floating-point branch scheduling recovery.
// Unmatched: UpdateMotors retains 13 instruction differences in state checks and scheduling.
// Unmatched: Initialize retains 22 differences after packed aggregate and local-scope recovery.
// Unmatched: Poll retains 15 differences in virtual-loop register allocation and scheduling.
// Unmatched: Attach retains 29 differences in validity helpers and boolean flow.
// Unmatched: Detach retains 10 differences in validity helpers and register allocation.
// Unmatched: PollPort retains 32 differences after packed parameter recovery.
#endif


#ifdef NON_MATCHING
#include "ps2/prelude.h"
// Unmatched: 13 instruction differences after original layout, argument-bank and helper probes.
#include "game/camera/pad.hpp"
extern "C"{
extern s32 func_0026C9C0(void *, s32);
extern s32 func_0029D4C0(s32, s32, void *, s32, void *);
extern s32 func_0026C9E0(s32, s32);
}
void Graphics::Controller::UpdateMotors() {
    struct MotorCommand {u8 command;u8 padding;s16 flags;};
    struct Commands {MotorCommand first,second;} commands __attribute__((aligned(16)));
    s16 var_2;
    s32 temp_2_3;
    s32 temp_4;
    u8 temp_2;
    u8 temp_2_2;

    temp_4 = this->backend;
    if (temp_4 != 0) {
        temp_2 = func_0026C9C0((void *) temp_4, this->port) == this->field_4;
        this->connected = temp_2;
        if (!Connected()) {
            this->field_49 = 0;
            this->initialized = 0;
            goto block_13;
        }
        temp_2_2 = this->field_46;
        if (this->field_4A != 0) {
            if ((this->field_47 != temp_2_2) || (this->field_49 != this->field_48)) {
                temp_2_3 = this->field_47 * 2;
                commands.first.command = 3;
                if (this->field_49 != 0) {
                    var_2 = temp_2_3 | 1;
                } else {
                    var_2 = temp_2_3 & 0xFFFF;
                }
                commands.first.flags = var_2;
                func_0029D4C0(func_0026C9E0(this->backend, this->port), 1, &commands.first.command, 2, &commands.first.flags);
                this->field_46 = this->field_47;
                this->field_48 = this->field_49;
            }
        } else if ((temp_2_2 != 0) || (this->field_48 != 0)) {
            commands.second.command = 3;
            commands.second.flags = 0;
            func_0029D4C0(func_0026C9E0(this->backend, this->port), 1, &commands.second.command, 2, &commands.second.flags);
            this->field_49 = 0;
            this->field_46 = 0;
            this->field_48 = 0;
block_13:
            this->field_47 = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0026BD30);
#endif


#ifdef NON_MATCHING
#include "game/camera/pad.hpp"
// Unmatched: 2 instruction differences after original layout, argument-bank and helper probes.
using namespace Graphics;
float Controller::Smooth(float value,float step) {
    float limit=axisLimit;
    float threshold;
    if(value>0.0f) {
        if(value>limit)value=limit;
        threshold=deadZone+step;
        value-=threshold;
        if(value<0.0f)value=0.0f;
    } else {
        if(value<-limit)value=-limit;
        threshold=deadZone+step;
        value+=threshold;
        if(value>0.0f)value=0.0f;
    }
    return value*(1.0f/(limit-threshold));
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0026BF60);
#endif


#ifdef NON_MATCHING
#include "game/camera/pad_backend.hpp"
// Unmatched: 27 instruction differences after original layout, argument-bank and helper probes.
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
using namespace Graphics;
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0026C798);
#endif


#ifdef NON_MATCHING
#include "game/camera/pad_backend.hpp"
// Unmatched: 8 instruction differences after original layout, argument-bank and helper probes.
using namespace Graphics;
extern "C" void func_0026CBA8(PadBackend *,int);
void PadBackend::Poll() {
    func_0026CBA8(this,0);
    if(!singlePort)func_0026CBA8(this,1);
    Controller **it=controllers;
    int i=0;
    do {if(*it)(*it)->Update();++i;++it;}while(i<2);
    if(!lastMode){if(controllers[1])controllers[1]->UpdateMotors();lastMode=1;}
    else {if(controllers[0])controllers[0]->UpdateMotors();lastMode=0;}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0026C8E0);
#endif

