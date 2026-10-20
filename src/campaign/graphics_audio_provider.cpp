#include "campaign/graphics/audio_provider.hpp"
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
