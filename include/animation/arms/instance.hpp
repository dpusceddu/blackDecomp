#ifndef BLACK_ARMS_INSTANCE_HPP
#define BLACK_ARMS_INSTANCE_HPP
#include "animation/runtime.h"
#include "ps2/vu0.hpp"
namespace ArmsAnimation {
// Scoped behavior names; only the accessed PS2 fields are established.
struct Pose : BkAnimationPoseHeaderPS2 {
    Pose() __asm__("func_00343FC8");
};
struct Instance : BkAnimationInstancePS2 {
    template<class T> T& At(int offset) {return *(T*)((char*)this+offset);}
    long SetGraph(int,int,int,float) __asm__("func_00347A90");
    long SetGraphFlags(int,int,int) __asm__("func_00347B40");
    long Activate(int) __asm__("func_00347C70");
    void Matrices(Pose*) __asm__("func_00347E18");
    Pose* Evaluate() __asm__("func_00347E80");
    long Advance(float*,float) __asm__("func_00348070");
    Pose* Update(float) __asm__("func_00348288");
    void Scale(float) __asm__("func_003484D0");
    void ScaleMatrix(const Game::Position4*,Game::Position4*) __asm__("func_003484F0");
};
extern long TryTransition(Instance*,int,int,float) __asm__("func_00350890");
extern void BindGraph(Instance*,int,int,float) __asm__("func_00350570");
extern long SwitchGraph(Instance*,int,int,float) __asm__("func_00347C08");
extern AnimationSkeleton* Skeleton(Instance*) __asm__("func_003489A8");
extern void BuildMatrices(Instance*,Pose*) __asm__("func_003511D0");
extern void ScratchReset() __asm__("func_003461E0");
extern Pose* EvaluateGraph(Instance*,Pose*) __asm__("func_0034F080");
extern float BlendWeight(Instance*,float) __asm__("func_00348D00");
extern Pose* SelectPresent(Instance*,Pose*,Pose*,int) __asm__("func_00346510");
extern Pose* BlendOverlay(Instance*,Pose*,Pose*,float) __asm__("func_00347600");
extern Pose* Compose(Instance*,Pose*,Pose*,int) __asm__("func_00346668");
extern void ResetTransition(Instance*) __asm__("func_00348018");
extern float Rate(Instance*) __asm__("func_0034F2E0");
extern void AdvanceCoordinate(Instance*,float) __asm__("func_0034EE90");
extern Pose* CopyIfPresent(Pose*,const Pose*) __asm__("func_00343C28");
}
#endif
