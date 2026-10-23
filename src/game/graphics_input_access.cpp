#include "campaign/graphics/pad_backend.hpp"

using namespace CampaignGraphics;

unsigned char Controller::Button(unsigned index) const {if(index>=28)return 0;return *((const EeU8*)this+index+42);}

bool Controller::Pressed(unsigned index)const {if(index>=28)return false;bool result=false;if(*((const EeU8*)this+index+42))result=previousStates[index]==0;return result;}

bool Controller::Released(unsigned index)const {if(index>=28)return false;bool result=false;if(!*((const EeU8*)this+index+42))result=previousStates[index]!=0;return result;}

int PadBackend::GetState(unsigned port){if(port>=2)return 0;return state[port];}

int PadBackend::GetHandle(unsigned port){if(port>=2)return 0;return handles[port];}

void PadBackend::SetFeedback(int enabled){if(enabled!=feedback){Controller **it=controllers;feedback=enabled;int i=1;do{if(*it)(*it)->SetFeedback(feedback);--i;++it;}while(i>=0);}}
