#ifndef BLACK_WEAPONS_INSTANCE_HPP
#define BLACK_WEAPONS_INSTANCE_HPP
#include "game/weapons/controller.hpp"
namespace Weapons {
// Qualified instruction views; only consumers placed in source verify their accesses.
struct Hit {Position4 point,normal;float fraction;BkWeaponOwnerPS2*entity;unsigned mask;unsigned char component,pad2d[3];unsigned unknown30[4];};
struct Matrix {Position4 x,y,z,p;};
// Exact callback12B2A8 verifies these accessed fields; complete query extent and
// original class identity remain unknown. This differs from the actor Hit view.
struct WorldMaterial {unsigned unknown00,flags;};
struct WorldCollision {Position4 point,normal;unsigned char unknown20[0x30];float fraction;unsigned char unknown54[0xc];void*material;inline unsigned MaterialFlags()const{return ((const WorldMaterial*)material)->flags;}};
struct Instance: BkWeaponInstancePS2 {
 int Initialize(Weapon*,BkWeaponDefinitionPS2*,EeU64) __asm__("func_00158F50");
 void EmitRay() __asm__("func_00159198");
 void EmitScoped() __asm__("func_00159938");
 int Impact(float,Hit*,Position4*,Position4*,Position4*,signed char*,signed char*,int,unsigned char,signed char,signed char) __asm__("func_00159AE8");
 void EmitProjectile() __asm__("func_0015A098");
 void EmitTargetedProjectile() __asm__("func_0015A400");
 void Reload() __asm__("func_0015A830");
 int CycleMode() __asm__("func_0015A990");
 int TracePath(float,Vec,Vec,unsigned,BkWeaponOwnerPS2*,int,Instance*,Hit*,signed char) __asm__("func_0015AA60");
 void FinishEmission() __asm__("func_0015B028");
 int ApplyHit(float,Hit*,Vec,signed char,int,int,unsigned char) __asm__("func_0015B118");
 void Direction(Position4*,Vec,int) __asm__("func_0015B360");
 inline Weapon*Controller(){return (Weapon*)weapon;}
};
struct CollectedHit {EeS128 point;BkWeaponOwnerPS2*entity;float damage,distance;unsigned char component,pad1d[3];};
struct HitCollector {CollectedHit records[16];int count;void Add(float,float,Vec,BkWeaponOwnerPS2*,unsigned char) __asm__("func_0015B8F8");void Dispatch(Vec,signed char,BkWeaponOwnerPS2*,signed char) __asm__("func_0015BA80");};
struct RayContext {Position4 start,end;unsigned mask;BkWeaponOwnerPS2*owner;unsigned char player,hit,pad2a[6];Hit result;int kind;Instance*instance;float initialDistance,remaining;Position4 direction;unsigned char flags;};
struct Candidate {unsigned char unknown00[0x34];BkWeaponOwnerPS2*actor;};
int TraceActor(Candidate*,int,RayContext*) __asm__("func_0015ADA8");
extern HitCollector collector __asm__("D_00414AD0");
}
#endif
