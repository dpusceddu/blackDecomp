#include "include_asm.h"

#include "game/effects/mod_asset_views.hpp"
extern "C" {void func_001C6AA0(void *);int func_001C6AB8(void *,unsigned,unsigned);unsigned func_001AFDB8(int);extern unsigned *D_0040F4C0;}

void ModEffects::Regions::Initialize(){Region *first=regions,*current=first;int end=(int)first+0x70;do{func_001C6AA0(current);++current;}while((int)current<end);func_001C6AA0((char *)this+0x70);}
