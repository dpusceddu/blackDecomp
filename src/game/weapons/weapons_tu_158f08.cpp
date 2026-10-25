#include "include_asm.h"

#include "game/weapons/instance.hpp"

namespace Weapons {
extern "C" {
void func_001551C8(void*,int,EeU16);
EeU16 func_00155140(void*,int,EeU8);
}

static inline bool IsObject(const BkWeaponOwnerPS2*entity){int kind=entity->kind;return (unsigned)(kind-3)<2||kind==7;}
void Instance::Reload(){
 if(weapon->owner->kind==2){int index=definition->reserveIndex;func_001551C8(weapon->inventory,index,(EeU16)clip);clip=func_00155140(weapon->inventory,index,(EeU8)definition->capacity);}
 else clip=(EeS16)definition->capacity;
 if(mode!=2)burstCount=Field<int>(definition,0x98);else burstCount=1;
}
void HitCollector::Add(float damage,float distance,Vec point,BkWeaponOwnerPS2*entity,unsigned char component){
 if(count<16){(*(EeS128*)(count*sizeof(CollectedHit)+(char*)this))=point;records[count].entity=entity;records[count].damage=damage;records[count].distance=distance;records[count].component=component;++count;return;}
 int lowest=0;float minimum=records[0].distance;bool object=IsObject(records[0].entity);
 for(int i=1;i<16;++i){if(!object||(unsigned)(records[i].entity->kind-1)>1){float candidate=records[i].distance;if(candidate<minimum){minimum=candidate;lowest=i;object=IsObject(records[i].entity);}}}
 if(IsObject(entity)&&!object)return;if(distance<minimum)return;
 CollectedHit*r=(CollectedHit*)(lowest*sizeof(CollectedHit)+(unsigned)this);r->point=point;r->entity=entity;r->damage=damage;r->distance=distance;r->component=component;
}
void HitCollector::Dispatch(Vec direction,signed char weaponId,BkWeaponOwnerPS2*source,signed char flags){
 for(int i=0;i<count;++i){CollectedHit*r=&records[i];void*vt=Field<void*>(r->entity,0x10);typedef void(*Receive)(void*,Vec,Vec,float,unsigned char,signed char,BkWeaponOwnerPS2*,signed char);
  Field<Receive>(vt,0x4c)((char*)r->entity+Field<short>(vt,0x48),r->point,direction,r->damage,r->component,weaponId,source,flags);
 }
}
}
// Unmatched: 00158F50: initializer resource and signed counter context.
// Unmatched: 00159198: emission matrices, query and resource helper contexts.
// Unmatched: 00159938: scoped VU normalization and impact callback context.
// Unmatched: 00159AE8: ricochet VU arithmetic and impact resource contexts.
// Unmatched: 0015A098: random cone and matrix helper temporaries.
// Unmatched: 0015A400: targeted projectile basis and VU lifetime.
// Unmatched: 0015A990: mode display allocation and integer division flags.
// Unmatched: 0015AA60: world collision query and vector temporaries.
// Unmatched: 0015ADA8: virtual filter helpers and duplicated nearest-hit tails.
// Unmatched: 0015B028: effect argument and sound resource scheduling.
// Unmatched: 0015B118: damage and virtual receive source context.
// Unmatched: 0015B360: spread helpers and VU basis temporaries.

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/weapons_tu_158f08", func_0015A990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/weapons_tu_158f08", func_0015AA60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/weapons_tu_158f08", func_0015ADA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/weapons_tu_158f08", func_0015B028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/weapons_tu_158f08", func_0015B118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/weapons_tu_158f08", func_0015B360);
