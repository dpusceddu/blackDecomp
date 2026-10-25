#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/graphics/audio_provider.hpp"
using namespace CampaignGraphics;
using namespace BlackGame;
extern "C" {
extern unsigned func_003107E0(void *,int,int,int);
extern void func_00319DE0(Voice *,int);
extern unsigned func_002851E0(AudioProvider *);
extern void func_00310640(void *,int,int,unsigned);
extern void func_00310590(void *,int,int,const Point3 *);
extern void func_003106F0(void *,int,int);
extern void func_003105E8(void *,int,int);
}
// Unmatched: 51 differences: flag helper and state/control-flow lifetimes.
float AudioProvider::Transition()
{
    switch(state){case 1:{
        if(count<5){
            bool pending=true;
            if(flags&0x80){if(!(flags&0x100))pending=false;}
            else pending=(voice->flags&2)!=0;
            if(pending){unsigned char old=count++;return 1.0f-(float)old/5.0f;}
            state=2;count=0;flags&=0xfff7;return 1.0f;
        }
        Voice *current=voice;
        if(current->active){
            flags|=8;
            unsigned result;
            if(!current->channel||(current->flags&2)==0)result=voice->playback;
            else result=func_003107E0(current->channel,9,2,0);
            current->playback=result;savedPlayback=result;
            func_00319DE0(voice,0);
        }
        count=0;state=2;return 0.0f;
    }
    case 2:return 0.0f;
    case 3:{
        if(flags&8){
            if(!count){func_00319DE0(voice,1);voice->playback=savedPlayback;
                if(voice->channel)func_00310640(voice->channel,9,1,savedPlayback);savedPlayback=0;}
            if(count<5){if(func_002851E0(this)){unsigned char old=count++;return (float)old/5.0f;}count=0;}else count=0;
            state=0;return 1.0f;
        }
        state=0;
    }
    }return 1.0f;
}
// Unmatched: 23 differences: vector argument spill and local copy lifetime.
void AudioProvider::SetPosition(Vec v)
{
    Position4 p;Store(p,v);Point3 value;value.x=p.x;value.y=p.y;value.z=p.z;voice->position=value;
    if(voice->channel)func_00310590(voice->channel,0,1,&value);
}
// Unmatched: 23 differences: vector argument spill and local copy lifetime.
void AudioProvider::SetVelocity(Vec v)
{
    Position4 p;Store(p,v);Point3 value;value.x=p.x;value.y=p.y;value.z=p.z;voice->velocity=value;
    if(voice->channel)func_00310590(voice->channel,1,1,&value);
}
// Unmatched: 9 differences: floating register allocation and scheduling.
void AudioProvider::SetGain(float value)
{
    voice->gain=(int)(value*255.0f);
    if(voice->channel)func_003106F0(voice->channel,13,1);
}
// Unmatched: 9 differences: floating register allocation and scheduling.
void AudioProvider::SetPan(float value)
{
    voice->pan=(int)(value*127.0f);
    if(voice->channel)func_003106F0(voice->channel,12,1);
}
// Unmatched: 2 differences: NOP and branch displacement.
void AudioProvider::SetPlayback(unsigned value)
{
    voice->playback=value;
    if(voice->channel)func_00310640(voice->channel,9,1,value);
}
// Unmatched: 5 differences: condition and scheduling.
void AudioProvider::SetFlag(unsigned value)
{
    if(value)voice->flags|=4;else voice->flags&=0xfb;
    if(voice->channel)func_003105E8(voice->channel,10,1);
    if(value)flags|=0x80;else flags&=0xff7f;
}
// Unmatched: 3 differences: result-register lifetime.
bool AudioProvider::IsStopped()
{
    bool result=false;
    if((((unsigned char *)&flags)[0]&1)==0)result=func_002851E0(this)==0;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002848A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284920);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002849C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284A10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284AE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284B28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00388DD8);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00286CA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00286DB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00287D08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00287D70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00287DF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00287E30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00287E88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00287EC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00288020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00288078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002880C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00288108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00288150);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002881A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00288470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289DD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289EC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289F78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028A368);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028A470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028A478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028A4D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028A520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028A598);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028A688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028AFF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028B1F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028B2A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028B3E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028B3E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028B638);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028BD80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028BEB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028BEC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028BF90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028C028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028EED8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299038);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002991B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002992C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299450);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299500);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002995B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002996B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002997B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299850);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299900);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002999E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299BA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299C70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299D90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00299EA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029B1D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029B500);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029B558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029B7F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029B868);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029B998);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029BA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029BBC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029BCC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029BCE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029BE90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029BFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029C110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A7930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A7B18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A7BB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A7D50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A7DD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A8688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A8860);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A8DA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AF778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0340);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C03F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C04F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C05F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C06D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0760);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C07B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C66A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C6828);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C7760);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C7C20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C7FB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C8438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C8530);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C8618);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CB3D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CB660);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CB858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CBA90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CBDF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CC700);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CCC48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CCD48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CCE80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CD230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CD640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CD840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CDB28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CDD70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CDEA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CDF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CE010);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CE0B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CE0E8);
