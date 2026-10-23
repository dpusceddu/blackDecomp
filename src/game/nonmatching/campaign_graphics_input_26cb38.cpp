#include "campaign/graphics/pad_backend.hpp"
// Unmatched: 12 instruction differences after native layout, argument-bank and helper probes.
using namespace CampaignGraphics;
void PadBackend::Detach(Controller *controller,unsigned port) {
    bool valid=controller!=0;
    if(port<2){if(!valid)return;valid=controllers[port]==controller;}
    if(valid&&port<2){controllers[port]=0;--count;controller->Close();}
}
