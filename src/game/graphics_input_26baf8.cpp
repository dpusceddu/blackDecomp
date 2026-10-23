#include "campaign/graphics/controller.hpp"
using namespace CampaignGraphics;
extern "C" int func_0026BCF8(Controller *,unsigned);
extern "C" int func_0026BC88(float,Controller *);
int Controller::Reset() {
    if(Connected()){func_0026BCF8(this,0);func_0026BC88(0.0f,this);}
    else{field_46=0;field_47=0;field_48=0;field_49=0;}
    field_4A=1;
    int i=0;
    EeU8 *previous=previousStates;
    EeU8 *current=&button0;
    float *pressure=&pressure0;
    do {previous[i]=0;current[i]=0;*pressure++=0.0f;++i;}while(i<28);
    field_4=3;
    return 1;
}
