#ifndef BLACK_ANIMATION_POSE_CAMPAIGN_HPP
#define BLACK_ANIMATION_POSE_CAMPAIGN_HPP
#include "mod/animation/pose_cache.h"
#include "mod/animation/instance.h"
#include "animation/graph.h"
namespace ArmsPose {
// Scoped PS2 behavior views; original class identities remain unverified.
struct Pose {
    union { float quaternion[4];s128 rotation; };
    union { float translation[4];s128 position; };
    Pose() __asm__("func_00343FC8");
    Pose* Copy(const Pose*) __asm__("func_00344020");
};
struct Slot { Pose root,bones[50];unsigned char unknown660[16]; };
struct Cache {
    static void Enable(s8) __asm__("func_003461D0");
    static void Clear() __asm__("func_003461E0");
    static Pose* Allocate() __asm__("func_003461F0");
    static void ForceBone(int) __asm__("func_00346F38");
    static void ClearBone() __asm__("func_00346F48");
    static void Construct(int,int) __asm__("func_00347738");
    static void Initialize() __asm__("func_003477D0");
};
struct Operations : BkModAnimationInstancePS2 {
    Pose* Blend(Pose*,Pose*,unsigned,float) __asm__("func_00346230");
    Pose* Select(Pose*,Pose*,unsigned) __asm__("func_00346510");
    Pose* Compose(Pose*,Pose*,unsigned) __asm__("func_00346668");
    Pose* Difference(Pose*,Pose*,unsigned) __asm__("func_00346940");
    Pose* Weight(Pose*,unsigned,float) __asm__("func_00346CB0");
    Pose* Overlay(Pose*,Pose*,float) __asm__("func_00347600");
};
struct ClipOperations {
    static Pose* Default(Operations*,BkModSourceClipPS2*,unsigned,float) __asm__("func_003474F8");
    static Pose* Root(Pose*,Operations*,BkModSourceClipPS2*,unsigned,int,float) __asm__("func_00347558");
};
struct GraphOperations {
    static float* Scaled(void*,AnimationGraphNode*,AnimationParameters*,unsigned,float,float,float,float) __asm__("func_00347238");
};
extern Slot slots[28] __asm__("D_0045F0C0");
extern Pose* BlendRoot(Pose*,const Pose*,const Pose*,float) __asm__("func_00344178");
extern Pose* ComposeRoot(Pose*,const Pose*,const Pose*) __asm__("func_003440B8");
extern Pose* DifferenceRoot(Pose*,const Pose*,const Pose*) __asm__("func_00344118");
struct Skeleton { int count;void* hierarchy,*matrices,*names; };
struct Collection {unsigned char unknown00[0x1c];Skeleton* skeletons;};
static inline int BoneCount(const Operations* op) {return ((Collection*)op->collection)->skeletons[op->skeleton].count;}
typedef char PoseSize32[sizeof(Pose)==32?1:-1];
typedef char SlotSize670[sizeof(Slot)==0x670?1:-1];
}
#endif
