#include "campaign/graphics/sound_envelopes.hpp"
using namespace CampaignGraphics;
void SoundEnvelope::Register(const char *name,int includeHold)
{
    RegisterEnvelopeParameter(D_003C09E8+4,&high,D_003F8A88,name,D_003BDA08,0,0.0f,0.0f,0);
    RegisterEnvelopeParameter(D_003C09E8+4,&low,D_003F8A98,name,D_003BDA08,0,0.0f,0.0f,0);
    RegisterEnvelopeParameter(D_003C09E8+4,&multiplier,D_003F8AA8,name,D_003BDA08,0,0.0f,0.0f,0);
    RegisterEnvelopeParameter(D_003C09E8+4,&unknown2c,D_003F8AB8,name,D_003BDA08,0,0.0f,0.0f,0);
    RegisterEnvelopeParameter(D_003C09E8+4,&attack,D_003F8AC0,name,D_003BDA08,0,0.0f,0.0f,0);
    if(includeHold)
        RegisterEnvelopeParameter(D_003C09E8+4,&hold,D_003F8AD0,name,D_003BDA08,0,0.0f,0.0f,0);
    RegisterEnvelopeParameter(D_003C09E8+4,&release,D_003F8AE0,name,D_003BDA08,0,0.0f,0.0f,0);
    initialized=1;
}
