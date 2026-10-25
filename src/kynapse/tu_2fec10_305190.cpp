#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/pathfinder.hpp"
#endif

#ifdef NON_MATCHING
namespace Kaim {
extern "C" unsigned char func_002E27F8(float,const float*,const float*,Actor*,int);
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char CPathFinder_AcceptActorSegment(CPathFinder*self,const float*point)
{
 if(!func_002E27F8(self->radiusHolder->radius,&self->position.x,point,self->controller->actor,2))return false;
 return CPathFinder_HasUnsupportedGround(self,point)!=1;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00305190);
#endif
