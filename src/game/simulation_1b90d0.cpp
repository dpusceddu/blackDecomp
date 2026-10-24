#include "game/effects/simulation.hpp"
extern "C" {void func_001C3E10(),func_001C4130(int),func_001B7FC8(void*,int),func_001B82E0(void*,int),func_001C45C0(),func_001C45E0(),func_001B7F08(void*),func_001B8138(void*),func_001C3E08();}
int ModEffects::Simulation::Clear(){count=0;func_001B7F08((char*)this+0x11604);func_001B8138((char*)this+0x11164);func_001C3E08();unsigned short i=0;do{pending[i]=0;batches[i]=0;indices[i]=-1;timeout[i]=0;scales[i]=0;kinds[i]=0;i++;next=0;}while(i<32);return 1;}
