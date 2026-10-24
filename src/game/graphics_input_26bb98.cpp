#include "include_asm.h"

#include "game/camera/pad.hpp"
using namespace CampaignGraphics;
struct PressureView {EeU8 prefix[0x4c];float values[28];};

float Controller::Pressure(unsigned index) const {
    if(index>=28)return 0.0f;
    return ((const PressureView *)this)->values[index];
}
