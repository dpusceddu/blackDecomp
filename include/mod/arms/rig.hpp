#ifndef BLACK_MOD_ARMS_RIG_HPP
#define BLACK_MOD_ARMS_RIG_HPP
#include "mod/arms/instance.hpp"

namespace ArmsAnimation {

union RigMatrix {
    s128 row[4];
    float v[16];
} __attribute__((aligned(16)));

// A scoped native view of the PS2 instance matrix operations. The common
// instance/skeleton offsets are inherited from their verified shared views.
struct Rig : AnimationInstanceView {
    void Build(Pose*) __asm__("func_003511D0");
    void Get(int, RigMatrix*) __asm__("func_00351968");
    void SetBind(int, const RigMatrix*) __asm__("func_003519A0");
};

// Only the override pointer is cleared when no record is found.
extern void FindOverride(AnimationInstanceView*, int, Pose**, unsigned*) __asm__("func_003478F0");

typedef char RigMatrix64[sizeof(RigMatrix) == 64 ? 1 : -1];

}
#endif
