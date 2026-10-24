#include "game/camera/pad.hpp"
// Unmatched: 2 instruction differences after native layout, argument-bank and helper probes.
using namespace CampaignGraphics;
float Controller::Smooth(float value,float step) {
    float limit=axisLimit;
    float threshold;
    if(value>0.0f) {
        if(value>limit)value=limit;
        threshold=deadZone+step;
        value-=threshold;
        if(value<0.0f)value=0.0f;
    } else {
        if(value<-limit)value=-limit;
        threshold=deadZone+step;
        value+=threshold;
        if(value>0.0f)value=0.0f;
    }
    return value*(1.0f/(limit-threshold));
}
