#include "include_asm.h"

#include "game/actor/prop_state.hpp"
namespace CampaignActor {
using namespace BlackGame;
using BlackPS2::VU0::Matrix4;
extern "C" {
RuntimeConfig *func_00151E60(void *);
int func_001AFDA8(PropSelector *);
void func_00151B40(void *, int, int);
void func_001B1728(PositionArg, PositionArg, Matrix4 *);
void func_001B7A00(void *, const Matrix4 *, unsigned long, int);
extern char *D_0040F4D8;
}

Position4*PropState::StateBounds(){RuntimeConfig*r=func_00151E60(this);if(!r)return 0;return(Position4*)((char*)r+0xB0);}
bool PropState::Contact(const ContactData*contact){
 if(!ready)return false;RuntimeConfig*r=func_00151E60(this);int state=func_001AFDA8(&selector);if(!r)return false;if(contacted)return false;{
 if(Y(Load(contact->normal))>0.9f){if(r->flags&4)func_00151B40(this,1,0);else if(r->flags&8)func_00151B40(this,0,0);}
 if(r->sound){Matrix4 transform;func_001B1728(Load(contact->point),Load(contact->normal),&transform);func_001B7A00(D_0040F4D8+0x696F0,&transform,r->sound,1);}
 unsigned short flags=r->flags;bool result=false;if(flags&0x1000)result=true;if(flags&0x40){previousState=state;spawnEffect=1;}contacted=1;return result;
 }return false;
}
}
// Unmatched: 0x14FEE0 matrix storage copy and RGB initialization.
// Unmatched: 0x1507E8 detail thresholds and render-mask loop allocation.
// Unmatched: 0x150B00 effect vector/spill lifetime.
// Unmatched: 0x150D68 inverse matrix and collision interface.
// Unmatched: 0x150F98 inverse matrix and output record copies.
// Unmatched: 0x151288 query descriptor layout and store order.
// Unmatched: 0x1513A8 damage flags and callback ABI.
// Unmatched: 0x1515F8 probability conversion and wide argument allocation.
// Unmatched: 0x1517E0 launch vector locals and helper contracts.
// Unmatched: 0x151E80 inertia vector constructor and component reads.
// Unmatched: 0x152000 activation predicate callback register lifetime.
// Unmatched: 0x152698 bounds predicate branch and spill reuse.

