#include "game/graphics/sound_envelopes.hpp"
#include "ps2/prelude.h"
using namespace CampaignGraphics;
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
