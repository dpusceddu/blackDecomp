#include "campaign/graphics/sound_envelopes.hpp"
using namespace CampaignGraphics;
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
