#include "campaign/graphics/controller.hpp"
// Unmatched: 9 instruction differences after native layout, argument-bank and helper probes.
using namespace CampaignGraphics;
int Controller::Rumble(unsigned enabled) {
    if(Connected()){if(enabled){field_49=1;return 1;}field_49=0;return 0;}
    return 0;
}
