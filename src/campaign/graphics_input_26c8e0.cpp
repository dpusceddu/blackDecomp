#include "campaign/graphics/pad_backend.hpp"
// Unmatched: 8 instruction differences after native layout, argument-bank and helper probes.
using namespace CampaignGraphics;
extern "C" void func_0026CBA8(PadBackend *,int);
void PadBackend::Poll() {
    func_0026CBA8(this,0);
    if(!singlePort)func_0026CBA8(this,1);
    Controller **it=controllers;
    int i=0;
    do {if(*it)(*it)->Update();++i;++it;}while(i<2);
    if(!lastMode){if(controllers[1])controllers[1]->UpdateMotors();lastMode=1;}
    else {if(controllers[0])controllers[0]->UpdateMotors();lastMode=0;}
}
