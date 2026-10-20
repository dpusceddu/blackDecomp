#ifndef BLACK_CAMPAIGN_WEAPONS_INSTANCE_HPP
#define BLACK_CAMPAIGN_WEAPONS_INSTANCE_HPP
#include "mod/weapons/controller.hpp"
namespace ModWeapons {
// Qualified instruction views; only consumers placed in source verify their accesses.
struct Hit {Position4 point,normal;float fraction;BkModWeaponOwnerPS2*entity;unsigned mask;unsigned char component,pad2d[3];unsigned unknown30[4];};
struct Matrix {Position4 x,y,z,p;};
struct WorldCollision {Position4 point,normal;unsigned char unknown20[0x30];float fraction;unsigned char unknown54[0xc];void*material;};
struct Instance: BkModWeaponInstancePS2 {
 int Initialize(Weapon*,BkModWeaponDefinitionPS2*,EeU64) __asm__("func_00158F50");
 void EmitRay() __asm__("func_00159198");
 void EmitScoped() __asm__("func_00159938");
 int Impact(float,Hit*,Position4*,Position4*,Position4*,signed char*,signed char*,int,unsigned char,signed char,signed char) __asm__("func_00159AE8");
 void EmitProjectile() __asm__("func_0015A098");
 void EmitTargetedProjectile() __asm__("func_0015A400");
 void Reload() __asm__("func_0015A830");
 int CycleMode() __asm__("func_0015A990");
 int TracePath(float,Vec,Vec,unsigned,BkModWeaponOwnerPS2*,int,Instance*,Hit*,signed char) __asm__("func_0015AA60");
 void FinishEmission() __asm__("func_0015B028");
 int ApplyHit(float,Hit*,Vec,signed char,int,int,unsigned char) __asm__("func_0015B118");
 void Direction(Position4*,Vec,int) __asm__("func_0015B360");
 inline Weapon*Controller(){return (Weapon*)weapon;}
};
struct CollectedHit {EeS128 point;BkModWeaponOwnerPS2*entity;float damage,distance;unsigned char component,pad1d[3];};
struct HitCollector {CollectedHit records[16];int count;void Add(float,float,Vec,BkModWeaponOwnerPS2*,unsigned char) __asm__("func_0015B8F8");void Dispatch(Vec,signed char,BkModWeaponOwnerPS2*,signed char) __asm__("func_0015BA80");};
struct RayContext {Position4 start,end;unsigned mask;BkModWeaponOwnerPS2*owner;unsigned char player,hit,pad2a[6];Hit result;int kind;Instance*instance;float initialDistance,remaining;Position4 direction;unsigned char flags;};
struct Candidate {unsigned char unknown00[0x34];BkModWeaponOwnerPS2*actor;};
int TraceActor(Candidate*,int,RayContext*) __asm__("func_0015ADA8");
extern HitCollector collector __asm__("D_00414AD0");
}
#endif
