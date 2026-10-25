#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/pathfinder.hpp"
#endif

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char CPathFinder_GenerateSteeringMove(CPathFinder*self,float*out,const float*point)
{
 Vec3f direction;
 if(!CPathFinder_SelectSteeringProbe(self,&self->position.x,point,&direction.x)){out[1]=direction.x;out[3]=0;out[2]=0;out[2]=direction.y;out[3]=direction.z;out[0]=0;}
 else {Vec3f normalized=direction/sqrtf(direction.Squared());*(Vec3f*)(out+1)=normalized;out[0]=self->speeds->speed;}
 self->waypointPosition=self->position;return 1;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00301C68);
#endif
