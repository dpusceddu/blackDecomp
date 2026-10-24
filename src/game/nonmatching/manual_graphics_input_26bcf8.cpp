#include "game/camera/pad.hpp"
// Unmatched: 5 instruction differences remain in branch layout and return merging.
using namespace CampaignGraphics;
int Controller::Rumble(unsigned enabled) {
    if(!Connected())return 0;
    if(!enabled){field_49=0;return 0;}
    field_49=1;return 1;
}
