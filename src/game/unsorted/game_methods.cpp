#include "include_asm.h"

// Methods recovered through PS2 class views; unknown original names retain their addresses.
#include "game/classes/UnknownVtable_003DC838.hpp"
#include "game/classes/UnknownVtable_003DC5F8.hpp"
#include "game/classes/UnknownVtable_003DC100.hpp"
#include "game/classes/UnknownVtable_003DB1F8.hpp"
#include "game/classes/UnknownVtable_003DB828.hpp"
#include "game/classes/UnknownVtable_003DC130.hpp"
#include "game/classes/other/UnknownVtable_003E07F8.hpp"
#include "game/classes/other/UnknownVtable_003E06C8.hpp"
#include "game/classes/other/UnknownVtable_003E0688.hpp"
#include "game/classes/other/UnknownVtable_003E0058.hpp"
#include "game/classes/other/UnknownVtable_003E0140.hpp"

namespace Unnamed {

unsigned short* UnknownVtable_003DC838::Function_00149158(unsigned char index)
{
    unsigned short* entries = Field_01B0();
    entries[index] = 0xffff;
    return entries;
}

// Unmatched: exact body, but its section leaves an unexplained zero gap before the next function.
#if 0
void UnknownVtable_003DC5F8::Function_00383920()
{
    Field_00C4() = 2;
}
#endif

void UnknownVtable_003E07F8::Function_001EE278(int active)
{
    if (active)
        Field_0054() = 0.0f;
    else
        Field_0054() = 1.0f;
}

void UnknownVtable_003E06C8::Function_001CDA00(void* data)
{
    unsigned int* fields = (unsigned int*)data;
    if (fields[2])
        fields[2] += (unsigned int)data;
    if (fields[1])
        fields[1] += (unsigned int)data;
}

void UnknownVtable_003E0688::Function_001CDAB0(void* data)
{
    unsigned int* fields = (unsigned int*)data;
    if (fields[2])
        fields[2] += (unsigned int)data;
    if (fields[1])
        fields[1] += (unsigned int)data;
    if (fields[3])
        fields[3] += (unsigned int)data;
}

int UnknownVtable_003E0058::Function_00384360(int value)
{
    return ((ABI_UnknownVtable_003E0058*)this)->Slot007(value);
}

int UnknownVtable_003E0140::Function_001ADF98(int value)
{
    return ((ABI_UnknownVtable_003E0140*)this)->Slot005(value);
}

int UnknownVtable_003DC100::Function_001653A8()
{
    unsigned char result = Field_001C();
    if (!result) {
        ((ABI_UnknownVtable_003DC100*)this)->Slot001();
        result = 1;
        Field_001C() = 1;
    }
    return result;
}

void UnknownVtable_003DB1F8::Function_00114160()
{
    Field_0010() = 0;
}

void UnknownVtable_003DB828::Function_00163DA8()
{
    Field_0080() ^= 1;
}

void UnknownVtable_003DC130::Function_001652E0()
{
    Field_0018() = 1;
}

}


#ifdef NON_MATCHING
#include "game/graphics/sound_envelopes.hpp"
using namespace Graphics;
// Unmatched: 5 instruction differences after native layout, EE clamp and helper-context probes.
void SoundEnvelope::Release()
{
    state=3;
    float now=SoundClock();
    endpoint=low;
    ratio=high/low;
    deadline=now+release;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EDD80);
#endif


#ifdef NON_MATCHING
#include "game/graphics/sound_envelopes.hpp"
using namespace Graphics;
// Unmatched: 8 instruction differences after native layout, EE clamp and helper-context probes.
int DestructionEnvelope::Begin(float value,unsigned useEndpoint)
{
    if(!initialized)func_001ED9C8(this,D_003BDA14,0);
    if(useEndpoint)endpoint=value;else endpoint=high;
    state=1;
    float now=SoundClock();
    ratio=low/endpoint;
    deadline=now+attack;
    ActivateEnvelopeWithArguments(this,value,useEndpoint);
    func_001EFE70(this,1);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EDDE0);
#endif

#ifdef NON_MATCHING
#include "game/graphics/sound_envelopes.hpp"
#include "ps2/prelude.h"
using namespace Graphics;
// Unmatched: 20 instruction differences after native layout, EE clamp and helper-context probes.
void DestructionEnvelope::Update()
{
    if(state==1) {
        progress=1.0f-(deadline-SoundClock())/attack;
        level=endpoint*func_0029E688(ratio,__ee_min_s(progress,1.0f));
        func_00286120(level,multiplier,SoundFilter());
        func_001D7238(level,multiplier,gain,SoundObjects()[3]);
        if(progress<1.0f)return;
        func_001EDDB8(this);
    } else if(state<2)return;else if(state==2) {} else if(state==3)goto releaseState;else return;
    progress=1.0f-(deadline-SoundClock())/hold;
    func_001D7238(level,multiplier,gain,SoundObjects()[3]);
    if(progress<1.0f)return;
    ((EnvelopeInterface *)this)->Release();
releaseState:
    progress=1.0f-(deadline-SoundClock())/release;
    level=endpoint*func_0029E688(ratio,__ee_min_s(progress,1.0f));
    func_00286120(level,multiplier,SoundFilter());
    func_001D7238(level,multiplier,gain,SoundObjects()[3]);
    if(!(progress<1.0f))state=0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EDE98);
#endif

#ifdef NON_MATCHING
#include "game/graphics/sound_envelopes.hpp"
using namespace Graphics;
// Unmatched: 6 instruction differences after native layout, EE clamp and helper-context probes.
int DestructionEnvelope::Unregister()
{
    state=0;
    func_001EDB80(this);
    func_001EFE70(this,0);
    func_001D7258(1.0f,SoundObjects()[3]);
    func_002860D0(1.0f,SoundFilter());
    level=24000.0f;
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE0B0);
#endif


#ifdef NON_MATCHING
#include "game/graphics/sound_envelopes.hpp"
#include "ps2/prelude.h"
using namespace Graphics;
// Unmatched: 18 instruction differences after native layout, EE clamp and helper-context probes.
extern "C" float D_003BDA0C;
extern "C" void func_001F07B8(float,void *);
void TimedEnvelope::Update()
{
    if(state==1){
        progress=1.0f-(deadline-SoundClock())/attack;
        level=endpoint*func_0029E688(ratio,__ee_min_s(progress,1.0f));
        func_00286120(level,multiplier,SoundFilter());
        func_001D7238(level,multiplier,gain,SoundObjects()[3]);
        func_001F07B8(progress*scale*D_003BDA0C,*(void **)((unsigned char *)SoundObjects()[3]+0x1be0));
        if(progress<1.0f)return;
        func_001EDDB8(this);
    } else if(state<2)return;else if(state==2){}else if(state==3)goto releaseState;else return;
    progress=1.0f-(deadline-SoundClock())/hold;
    func_001D7238(level,multiplier,gain,SoundObjects()[3]);
    func_001F07B8(scale*D_003BDA0C,*(void **)((unsigned char *)SoundObjects()[3]+0x1be0));
    if(progress<1.0f)return;
    Release();
releaseState:
    progress=1.0f-(deadline-SoundClock())/release;
    level=endpoint*func_0029E688(ratio,__ee_min_s(progress,1.0f));
    func_00286120(level,multiplier,SoundFilter());
    func_001D7238(level,multiplier,gain,SoundObjects()[3]);
    func_001F07B8((1.0f-progress)*scale*D_003BDA0C,*(void **)((unsigned char *)SoundObjects()[3]+0x1be0));
    if(!(progress<1.0f))state=0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE298);
#endif

#ifdef NON_MATCHING
#include "game/graphics/sound_envelopes.hpp"
using namespace Graphics;
// Unmatched: 20 instruction differences after native layout, EE clamp and helper-context probes.
void LowHealthEnvelope::Reset()
{
    kind=3;high=24000.0f;low=200.0f;multiplier=1.2f;unknown2c=2.0f;gain=1.0f;
    release=0.75f;enabled=1;blend=1.0f/3.0f;
    state=0;mode=1;
    channels[0]=1;channels[1]=1;channels[2]=1;channels[3]=1;channels[4]=1;channels[5]=1;
    unknown4a=1;unknown4b=1;initialized=0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE540);
#endif


#ifdef NON_MATCHING
#include "game/graphics/sound_envelopes.hpp"
#include "ps2/prelude.h"
using namespace Graphics;
// Unmatched: 27 instruction differences after native layout, EE clamp and helper-context probes.
void LowHealthEnvelope::Update()
{
    if(state==1)state=2;else if(state<2)return;else if(state==2){}else if(state==3)goto releaseState;else return;
    {
        float mix;
        if(1.0f<=Blend()){level=endpoint;mix=multiplier;}
        else {
            level=endpoint*func_0029E688(ratio,1.0f-Blend());
            level=__ee_max_s(level,low);
            level=__ee_min_s(level,endpoint);
            mix=unknown2c+(multiplier-unknown2c)*Blend();
        }
        func_00286120(level,mix,SoundFilter());
        func_001D7238(level,mix,gain,SoundObjects()[3]);
        return;
    }
releaseState:
    progress=1.0f-(deadline-SoundClock())/release;
    level=endpoint*func_0029E688(ratio,__ee_min_s(progress,1.0f));
    float mix=unknown2c+(multiplier-unknown2c)*progress;
    func_00286120(level,mix,SoundFilter());
    func_001D7238(level,mix,gain,SoundObjects()[3]);
    if(progress<1.0f)return;
    state=0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE678);
#endif

