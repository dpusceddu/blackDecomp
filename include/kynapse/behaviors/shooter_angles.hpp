#ifndef BLACK_SHOOTER_ANGLES_HPP
#define BLACK_SHOOTER_ANGLES_HPP
#include "kynapse/behaviors/shooter.hpp"
namespace Kaim {
// This discarded-result call matches an integer-return declaration. It establishes
// a call-clobber recipe; the semantic return type and value remain unverified.
struct ShooterAimResult:ShooterAgent {ShooterAimResult(BehaviorContext*);int AimValue() __asm__("func_002D6CB0");};
// The PS2 turning path reads angle words at 0x3c, 0x40 and 0x44.
struct ShooterActorAngles {unsigned char unknown00[0x3c];Vec3 angles;};
struct TurnVector {
    float x,y,z;
    TurnVector(float v){x=y=z=v;}
    TurnVector(float a,float b,float c):x(a),y(b),z(c){}
};
inline TurnVector operator-(const TurnVector& a,const Vec3& b) {
    return TurnVector(a.x-b.x,a.y-b.y,a.z-b.z);
}
typedef char TurnVectorSize[sizeof(TurnVector)==12?1:-1];
typedef char ShooterAnglesOffset[(unsigned)&((ShooterActorAngles*)0)->angles==0x3c?1:-1];
}
#endif
