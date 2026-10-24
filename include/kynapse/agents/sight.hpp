// Authored sight-cone views; offsets follow the PS2 scalar-copy consumers.
#ifndef BLACK_CONTEXT_BEHAVIORS_SIGHT_HPP
#define BLACK_CONTEXT_BEHAVIORS_SIGHT_HPP
namespace KaimSight {
struct Vec3 {
 float x,y,z;Vec3(){}Vec3(float a,float b,float c):x(a),y(b),z(c){}
 Vec3(const Vec3&p):x(p.x),y(p.y),z(p.z){}
 Vec3&operator=(const Vec3&p){x=p.x;y=p.y;z=p.z;return*this;}
};
struct Actor {char unknown00[0x30];Vec3 position;char unknown3c[12];Vec3 extent;void*GetAuthoredProperty(const void*) __asm__("func_002E4CE0");};
struct VectorProperty {char unknown00[4];Vec3 value;};struct FloatProperty {char unknown00[8];float value;};
extern const unsigned char gKeyRadius,gKeyPosition,gKeyExtent;
bool InCone(const Vec3*,const Vec3*,const Vec3*,float,float) __asm__("func_002E4E28");
bool InSightCone(const Vec3*,Actor*);
typedef char ActorPosition[(unsigned int)&((Actor*)0)->position==0x30?1:-1];typedef char ActorExtent[(unsigned int)&((Actor*)0)->extent==0x48?1:-1];
}
#endif
