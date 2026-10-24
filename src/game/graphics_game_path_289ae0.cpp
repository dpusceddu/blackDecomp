#include "game/graphics/game_path.hpp"
using namespace GamePathPS2;
// Unmatched: identity-load register allocation differs by two instructions.
int PathObject::UpdateUse(PathAgent* agent,RouteNode* node,int unused,unsigned char* stopped)
{
 GameActor* actor=func_00171CB0(agent);
 *stopped=0;
 if(actor->kind==1) {
  MovementGate* gate=func_00135550(actor)->Gate();
  int index=FindLinked(node);
  if(index>=0) {
   int* identity=Identity(index);
   SegmentRecord* record=Record(index);
   if(gate->identity==*identity) {
    if(func_0018C3C0(gate)) {func_0018C368(gate);*stopped=1;}
   } else Install(gate,record);
  }
 }
 return 0;
}
