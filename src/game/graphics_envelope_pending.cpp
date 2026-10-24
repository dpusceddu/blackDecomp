#include "game/graphics/timed_envelope.hpp"
#include "ps2/prelude.h"
using namespace CampaignGraphics;
extern "C" {
extern unsigned char *D_0040F510,*D_0040F4D0,*D_003C09E8;
extern float D_003BDA0C;
extern const char *D_003BDA10,*D_003BDA08;
extern void func_001E1690(void *, unsigned, int);
extern void func_001E2C68(void *, unsigned, int);
extern void func_001D7198(void *, unsigned, int);
extern void func_001DC498(void *, unsigned, int);
extern void func_001EC9F0(void *, unsigned, int);
extern void func_001E4260(void *, unsigned, int);
extern void func_001E6208(void *, unsigned, int);
extern void func_0027B950(float,float,void *,void *,const char *,const char *,const char *,int,int);
extern void func_001ED9C8(void *,const char *,int);
extern void func_001EDB80(void *,float,unsigned);
extern void func_001EFE70(void *,int);
extern void func_001EDDB8(void *);
extern float func_0029E688(float,float);
extern void func_00286120(float,float,void *);
extern void func_001D7238(float,float,float,void *);
extern void func_001F07B8(float,void *);
}
static inline void **SoundObjects() { return *(void ***)(D_0040F510+0xcbd8); }
static inline float Clock() { return *(float *)(D_0040F4D0+0x20); }

// Unmatched: Reset retains 18 differences in field/constant ordering.
void TimedEnvelope::Reset()
{
    kind=2;high=24000.0f;low=400.0f;attack=0.5f;hold=3.0f;release=0.75f;
    enabled=1;scale=1.0f;state=0;mode=1;multiplier=1.0f;unknown2c=1.0f;gain=1.0f;
    channels[0]=1;channels[1]=1;channels[2]=1;channels[3]=1;channels[4]=1;channels[5]=1;
    unknown4a=0;unknown4b=0;initialized=0;
}

// Unmatched: Release retains 5 scheduling differences.
void TimedEnvelope::Release()
{
    state=3;
    float now=Clock();
    endpoint=low;
    ratio=high/low;
    deadline=now+release;
}

// Unmatched: Update retains 28 differences after state/FP helper reconstruction.
void TimedEnvelope::Update()
{
    switch(state){
    case 1: {
        progress=1.0f-(deadline-Clock())/attack;
        level=endpoint*func_0029E688(ratio,__ee_min_s(progress,1.0f));
        func_00286120(level,multiplier,*(void **)(D_0040F510+0xcbe0));
        func_001D7238(level,multiplier,gain,SoundObjects()[3]);
        func_001F07B8(progress*scale*D_003BDA0C,*(void **)((unsigned char *)SoundObjects()[3]+0x1be0));
        if(progress<1.0f)return;
        func_001EDDB8(this);
    } case 2: break;case 3:goto releaseState; default:return; }
    progress=1.0f-(deadline-Clock())/hold;
    func_001D7238(level,multiplier,gain,SoundObjects()[3]);
    func_001F07B8(scale*D_003BDA0C,*(void **)((unsigned char *)SoundObjects()[3]+0x1be0));
    if(progress<1.0f)return;
    Release();
releaseState:
    progress=1.0f-(deadline-Clock())/release;
    level=endpoint*func_0029E688(ratio,__ee_min_s(progress,1.0f));
    func_00286120(level,multiplier,*(void **)(D_0040F510+0xcbe0));
    func_001D7238(level,multiplier,gain,SoundObjects()[3]);
    func_001F07B8((1.0f-progress)*scale*D_003BDA0C,*(void **)((unsigned char *)SoundObjects()[3]+0x1be0));
    if(!(progress<1.0f))state=0;
}
