#include "include_asm.h"

#include "game/graphics/sound_envelopes.hpp"
using namespace Graphics;

void SoundEnvelope::Register(const char *name,int includeHold)
{
    RegisterEnvelopeParameter(D_003C09E8+4,&high,"Start Frequency",name,D_003BDA08,0,0.0f,0.0f,0);
    RegisterEnvelopeParameter(D_003C09E8+4,&low,"End Frequency",name,D_003BDA08,0,0.0f,0.0f,0);
    RegisterEnvelopeParameter(D_003C09E8+4,&multiplier,"StartingQ",name,D_003BDA08,0,0.0f,0.0f,0);
    RegisterEnvelopeParameter(D_003C09E8+4,&unknown2c,"FinalQ",name,D_003BDA08,0,0.0f,0.0f,0);
    RegisterEnvelopeParameter(D_003C09E8+4,&attack,"Attack Time",name,D_003BDA08,0,0.0f,0.0f,0);
    if(includeHold)
        RegisterEnvelopeParameter(D_003C09E8+4,&hold,"Hold Time",name,D_003BDA08,0,0.0f,0.0f,0);
    RegisterEnvelopeParameter(D_003C09E8+4,&release,"Release Time",name,D_003BDA08,0,0.0f,0.0f,0);
    initialized=1;
}
