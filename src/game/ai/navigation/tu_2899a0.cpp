#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/graphics/game_path.hpp"
using namespace GamePathPS2;
// Unmatched: two callback-argument and byte-bool scheduling instructions.
unsigned int PathObject::CanUse(PathAgent* agent,RouteNode* node,Callback* callback,unsigned int reason)
{
 GameActor* actor=func_00171CB0(agent);
 if(actor->kind!=1)return 0;
 int index=Find(node);
 if(index<0)return 0;
 unsigned long allowed=Record(index)->allowedActors;
 unsigned long active=allowed>>func_00138320(func_00135570(actor));
 if((active&1UL)!=0) {
  bool result=false;
  int identity;
  if(callback->Filter(agent,node,reason) || (identity=node->identity,identity==func_0016DD68(D_0040F4D4,1)))result=true;
  return result;
 }
 return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002899A0);
#endif
