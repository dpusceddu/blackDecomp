#include "include_asm.h"

#include "game/effects/damage.hpp"

void Effects::DamageWindows::Clear(){short i=0;BkEffectDamageWindowPS2*p=records;do{p->effect=0;p->actor=0;p->begin=1e9f;p->end=0;p->damage=0;p++;i++;}while(i<32);}
int Effects::DamageWindows::Initialize(){Clear();return 1;}
int Effects::DamageWindows::Reset(){Clear();return 1;}

#ifdef NON_MATCHING
#include "game/effects/attachments.h"
// The remaining effect functions are INCLUDE_ASM lines.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BE960);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BEB48);
