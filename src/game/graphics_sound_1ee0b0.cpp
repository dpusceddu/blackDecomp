#include "game/graphics/sound_envelopes.hpp"
using namespace CampaignGraphics;
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
