#include "include_asm.h"
#include "game/effects/runtime.hpp"
#include "ps2/vu0_lowering.h"

using Effects::Matrix;
using Ps2Math::VU0::Value;
extern "C" {
extern Value D_004432A0;
extern Value D_004432C0;
void func_0014B8A0(void*);
void func_0014B8E0(void*, int, int);
}
struct ResourceState {
    Matrix world;
    Value position;
    unsigned char unknown50[0x10];
    unsigned char flag;
};
struct ParticleState {
    unsigned char unknown00[0xC4];
    int kind;
    unsigned char unknownC8[0x28];
    Value point, up;
    unsigned char unknown110[6];
    unsigned char a, b, c;
};
extern "C" void func_0014CDB8(ResourceState* self) {
    Effects::IdentityXYZ(self->world);
    self->position = D_004432A0;
    self->flag = 0;
}

extern "C" void func_0014CE00(ResourceState* self) {
    Effects::IdentityXYZ(self->world);
    self->position = D_004432A0;
}

extern "C" void func_0014D358(void* self, Value value) {
    float length = __ee_vu_read_x(BkVuSqrtX(BkVuSumXYZ(BkVuMulXYZ(value, value), BkVuOneX())));
    if (length < 50.0f) *(Value*)((char*)self + 0x50) = value;
}

#ifdef NON_MATCHING
// Unmatched: sphere snapshot spill and scalar-result allocation differ.
extern "C" int func_0014EC40(Value* sphere, Value point) {
    Value original = *sphere;
    Value delta = BkVuSubXYZ(point, original);
    Game::Position4 snapshot;
    int result = 0;
    Game::Store(snapshot, original);
    float distance = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(delta, delta), BkVuOneX()));
    if (!(snapshot.w * snapshot.w < distance)) result = 1;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/resource_state", func_0014EC40);
#endif

extern "C" void func_0014F7F8(ParticleState* self) {
    func_0014B8A0(self);
    self->kind = 6;
    self->point = D_004432A0;
}

extern "C" void func_0014F838(ParticleState* self, int arg) {
    self->point = D_004432A0;
    self->up = D_004432C0;
    self->a = 0;
    self->b = 0;
    self->c = 0;
    func_0014B8E0(self, arg, 0);
}

extern "C" int func_00165AF8(void*);
struct OrientationDefinition {
    unsigned char unknown00[0x10];
    Value point, first, second;
    unsigned char enabled;
};
struct OrientationAction {
    unsigned long id;
    unsigned char unknown08[0x10];
    OrientationDefinition* definition;
    unsigned char unknown1C[4];
    Value first, second;
    Matrix world;
    unsigned char enabled;
};
extern "C" int func_00163D08(OrientationAction* self, unsigned long id, OrientationDefinition* definition) {
    func_00165AF8(self);
    self->definition = definition;
    self->id = id;
    self->second = definition->second;
    self->first = definition->first;
    Effects::IdentityXYZ(self->world);
    self->world.row[3] = self->definition->point;
    self->enabled = self->definition->enabled != 0;
    return 1;
}

typedef char VerifyStateSize[sizeof(ResourceState) == 0x70 ? 1 : -1];
typedef char VerifyStateFlag[(unsigned)&((ResourceState*)0)->flag == 0x60 ? 1 : -1];
typedef char VerifyParticlePoint[(unsigned)&((ParticleState*)0)->point == 0xF0 ? 1 : -1];
typedef char VerifyParticleFlag[(unsigned)&((ParticleState*)0)->a == 0x116 ? 1 : -1];
typedef char VerifyOrientationWorld[(unsigned)&((OrientationAction*)0)->world == 0x40 ? 1 : -1];
