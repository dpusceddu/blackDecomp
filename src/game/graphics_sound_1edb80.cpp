#include "game/graphics/sound_envelopes.hpp"
using namespace CampaignGraphics;
int SoundEnvelope::ActivateChannels()
{
    func_001E1690(SoundObjects()[4],kind,channels[2]);
    func_001E2C68(SoundObjects()[5],kind,channels[3]);
    func_001D7198(SoundObjects()[3],kind,channels[0]);
    func_001DC498(SoundObjects()[8],kind,channels[1]);
    func_001EC9F0(SoundObjects()[9],kind,unknown4a);
    func_001E4260(SoundObjects()[7],kind,channels[4]);
    func_001E6208(SoundObjects()[1],kind,channels[5]);
    return 1;
}
