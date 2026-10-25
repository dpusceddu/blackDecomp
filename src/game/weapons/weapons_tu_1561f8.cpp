#include "include_asm.h"

#include "game/weapons/controller.hpp"

namespace Weapons {

void Weapon::Update(int fire,int alternate,int grenade,int reload,int aim,int special,int change,Action *action){
 float dt=frame->delta;cooldown-=dt;if(phase==1)elapsed+=dt;else elapsed=0;
 Advance(fire,alternate,grenade,reload,aim,special,change,action);
 if(owner->kind==2)UpdateAim(dt);
 func_00159120(dt,primary);if(secondary)func_00159120(dt,secondary);
 flags100[9]=(EeU8)fire;
}
void Weapon::SetPose(int secondaryPose){
 if(owner->kind==2){void *pose;int ready;
 if(secondaryPose){pose=poseManager->pair->secondary;ready=0;}else{pose=poseManager->pair->primary;ready=func_0015A948(primary);}
 Field<EeU8>(presentation->animation->state,0x28c)=secondaryPose;
 func_001D6E78(presentation->animation->graph,pose,*Field<EeU64*>(this,0xe8),ready);
 }
}
}
// Unmatched: 00156450: cleanup return scheduling.
// Unmatched: 001564D0: VU reflection helpers and hit layout.
// Unmatched: 00156A20: callback scalar allocation.
// Unmatched: 00156A88: query ownership and VU helper context.
// Unmatched: 00156CA0: aggregate copy allocation.
// Unmatched: 00156FD0: nested state dispatch and definition helpers.
// Unmatched: 00157E10: scoped cleanup scheduling.
// Unmatched: 00157EA0: zoom flag widths and shared arithmetic tails.
// Unmatched: 001580F0: random and VU basis helpers.
// Unmatched: 001583D8: ballistic VU basis helpers.
// Unmatched: 00158668: hit callback signature and matrix temporaries.
// Unmatched: 001588F0: virtual hit arguments and aggregate lifetime.
// Unmatched: 00158AE0: event resource layout and event hash dispatch.

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00156F10);
