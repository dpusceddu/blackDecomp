#include "game/graphics/sound_envelopes.hpp"
#include "ps2/prelude.h"
using namespace CampaignGraphics;
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
