#include "game/effects/mod_damage.hpp"
void ModEffects::DamageWindows::Clear(){short i=0;BkModEffectDamageWindowPS2*p=records;do{p->effect=0;p->actor=0;p->begin=1e9f;p->end=0;p->damage=0;p++;i++;}while(i<32);}
int ModEffects::DamageWindows::Initialize(){Clear();return 1;}
int ModEffects::DamageWindows::Reset(){Clear();return 1;}
