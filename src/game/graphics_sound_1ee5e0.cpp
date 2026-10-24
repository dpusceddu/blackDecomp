#include "game/graphics/sound_envelopes.hpp"
using namespace CampaignGraphics;
int LowHealthEnvelope::Begin(float value,unsigned useEndpoint)
{
    if(!initialized)func_001ED9C8(this,D_003BDA18,0);
    endpoint=high;ratio=low/high;
    ActivateEnvelopeWithArguments(this,value,useEndpoint);
    func_001EFE70(this,1);
    state=1;
    return 1;
}
