#ifndef BLACK_PATHWAY_VECTORS_HPP
#define BLACK_PATHWAY_VECTORS_HPP
#include "kynapse/behaviors/pathway.hpp"
namespace Kaim {
struct PathTurnVector {
    float x,y,z;
    PathTurnVector(float value){x=y=z=value;}
    PathTurnVector(float a,float b,float c):x(a),y(b),z(c){}
};
inline PathTurnVector operator-(const PathTurnVector& a,const Vec3& b) {
    return PathTurnVector(a.x-b.x,a.y-b.y,a.z-b.z);
}
}
#endif
