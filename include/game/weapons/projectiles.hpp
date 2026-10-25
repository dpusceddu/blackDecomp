#ifndef BLACK_WEAPON_PROJECTILES_HPP
#define BLACK_WEAPON_PROJECTILES_HPP
#include "game/weapons/instance.hpp"
namespace Weapons {
/* PS2 instruction-derived partial views. Original class names are unknown;
   no placed method yet verifies this view. Activation return type is tentative. */
struct Projectile {
    EeU8 unknown00[0x10]; void *vtable;
    EeU8 unknown14[0x5c]; Matrix world;
    EeU8 unknownB0[0x14]; int kind;
    EeU8 unknownC8[0x14]; void *resource;
    EeU8 unknownE0[0x10]; Vec velocity, angularVelocity;
    float remaining110; EeU8 ballistic, thrown, flag116, special, ownerFlag, unknown119[7];
    inline void Activate(float delta) {
        typedef void (*Update)(float,void*);
        Field<Update>(vtable,0xc)(delta,(char*)this+Field<short>(vtable,8));
    }
};
struct ProjectilePool {
    Projectile grenades[32], other[16];
    int handles[32], otherHandles[16];
    EeU8 unknown36c0[0x40], active[32], otherActive[16];
    void *thrownResource, *ballisticResource; EeU64 sound;
    void Initialize();
    void Throw(const Matrix*,Vec,int,int);
    void Retire(Projectile*);
    void RetireOther(Projectile*,int,int);
    void Fire(const Matrix*,Vec,unsigned);
};
typedef char ProjectileSize120[sizeof(Projectile)==0x120?1:-1];
typedef char ProjectilePoolHandles3600[(unsigned)&((ProjectilePool*)0)->handles==0x3600?1:-1];
typedef char ProjectilePoolActive3700[(unsigned)&((ProjectilePool*)0)->active==0x3700?1:-1];
}
#endif
