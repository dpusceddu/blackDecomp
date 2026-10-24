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
