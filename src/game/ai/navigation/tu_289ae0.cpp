#include "include_asm.h"

#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/navigation/tu_289ae0", func_00289AE0);
#endif

#ifdef NON_MATCHING
#include "game/graphics/game_path.hpp"
#include "kynapse/graph/spatial.hpp"
namespace Kaim { inline SearchNode *SearchEdge::End() const { if(this==&graph->syntheticEdge)return &graph->syntheticEnd;return &graph->nodes[graph->ends[index]]; } }

using namespace GamePathPS2;
struct PathInputPosition {
 float x,y,z;
 PathInputPosition() {}
 PathInputPosition(const PathInputPosition &p):x(p.x),y(p.y),z(p.z){}
 PathInputPosition(float a,float b,float c):x(a),y(b),z(c){}
 PathInputPosition operator-(const PathInputPosition &p)const{return PathInputPosition(x-p.x,y-p.y,z-p.z);}
 float SquaredLength()const{return z*z+x*x+y*y;}
};

// Unmatched: 66 differences remain in vector value lifetimes and loop scheduling.
int PathObject::FindLinked(RouteNode *input)
{
    const PathInputPosition *point=(const PathInputPosition *)input;
    unsigned int index=0;
    unsigned int count=primaryCount;
    if(count) {
        Kaim::SearchEdge **edge=(Kaim::SearchEdge **)primary->identities;
        do {
            Kaim::SearchNode *node=(*edge)->End();
            PathInputPosition delta=*point-*(const PathInputPosition *)&node->x;
            if(delta.SquaredLength()<0.0001f)return index;
            ++index;++edge;
        }while(index<count);
    }
    index=0;
    count=unknown74;
    if(count) {
        Kaim::SearchEdge **edge=(Kaim::SearchEdge **)secondary->identities;
        do {
            Kaim::SearchNode *node=(*edge)->End();
            PathInputPosition delta=*point-*(const PathInputPosition *)&node->x;
            if(delta.SquaredLength()<0.0001f)return index+primaryCount;
            ++index;++edge;
        }while(index<count);
    }
    return -1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/navigation/tu_289ae0", func_00289C10);
#endif
