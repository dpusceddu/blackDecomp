#include "campaign/graphics/timed_envelope.hpp"
#include "auto/prelude.h"
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

int TimedEnvelope::Unregister()
{
    func_001E1690(SoundObjects()[4],kind,0);
    func_001E2C68(SoundObjects()[5],kind,0);
    func_001D7198(SoundObjects()[3],kind,0);
    func_001DC498(SoundObjects()[8],kind,0);
    func_001EC9F0(SoundObjects()[9],kind,0);
    func_001E4260(SoundObjects()[7],kind,0);
    func_001E6208(SoundObjects()[1],kind,0);
    return 1;
}

int TimedEnvelope::Begin(float value,unsigned useEndpoint)
{
    if(!initialized){
        func_0027B950(0.0f,0.0f,D_003C09E8+4,&D_003BDA0C,"Whistle Gain",D_003BDA10,D_003BDA08,0,0);
        func_001ED9C8(this,D_003BDA10,1);
    }
    if(useEndpoint)endpoint=value;else endpoint=high;
    state=1;
    float now=Clock();
    ratio=low/endpoint;
    deadline=now+attack;
    SetMode(0);
    func_001EDB80(this,value,useEndpoint);
    func_001EFE70(this,1);
    return 1;
}
