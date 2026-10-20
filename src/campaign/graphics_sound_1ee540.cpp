#include "campaign/graphics/sound_envelopes.hpp"
using namespace CampaignGraphics;
// Unmatched: 20 instruction differences after native layout, EE clamp and helper-context probes.
void LowHealthEnvelope::Reset()
{
    kind=3;high=24000.0f;low=200.0f;multiplier=1.2f;unknown2c=2.0f;gain=1.0f;
    release=0.75f;enabled=1;blend=1.0f/3.0f;
    state=0;mode=1;
    channels[0]=1;channels[1]=1;channels[2]=1;channels[3]=1;channels[4]=1;channels[5]=1;
    unknown4a=1;unknown4b=1;initialized=0;
}
