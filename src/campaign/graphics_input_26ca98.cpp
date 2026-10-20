#include "campaign/graphics/pad_backend.hpp"
// Unmatched: 10 instruction differences after native layout, argument-bank and helper probes.
using namespace CampaignGraphics;
bool PadBackend::Attach(Controller *controller,unsigned port) {
    bool valid=controller!=0;
    if(port<2){if(!valid)return false;valid=controller->field_4==state[port];}
    if(!valid||port>=2)return false;
    if(controllers[port])return false;
    controllers[port]=controller;++count;
    controller->Open((unsigned)this,port);
    return true;
}
