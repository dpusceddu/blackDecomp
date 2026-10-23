#include "campaign/graphics/sound_envelopes.hpp"
using namespace CampaignGraphics;
// Unmatched: 5 instruction differences after native layout, EE clamp and helper-context probes.
void SoundEnvelope::Release()
{
    state=3;
    float now=SoundClock();
    endpoint=low;
    ratio=high/low;
    deadline=now+release;
}
