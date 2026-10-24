#ifndef BLACK_MOD_ARMS_LIFECYCLE_HPP
#define BLACK_MOD_ARMS_LIFECYCLE_HPP
#include "animation/runtime.h"
namespace ArmsAnimation {
// Scoped native methods over the established PS2 instance/source-bank views.
struct Lifecycle : AnimationInstanceView {
    template<class T>T& At(int offset){return *(T*)((char*)this+offset);}
    int Initialize(void*,AnimationCollectionView*,int) __asm__("func_00345510");
    void Retire() __asm__("func_00345AC8");
    void DeferRetire() __asm__("func_00345DC0");
    void ReleaseIfOwned() __asm__("func_00345E30");
};
struct SourceClip : AnimationSourceClip {
    int ClearTracks() __asm__("func_00345FB8");
};
struct SourceBank : AnimationSourceBank {
    void Import(AnimationCollectionView*) __asm__("func_00345FD8");
    void Remove(AnimationCollectionView*) __asm__("func_003460E8");
};
// Extra ignored arguments are a scoped PS2 caller recipe, not callee semantic evidence.
// Discarded result reproduces call-clobber behavior; semantic return unverified.
extern int ReleaseBanksRecipe(AnimationInstanceView*,void*) __asm__("func_0034ECD8");
extern int InstallWithContext(AnimationSourceClip*,SourceBank*,AnimationCollectionView*) __asm__("func_00345F98");
extern int ClearTracksWithContext(AnimationSourceClip*,SourceBank*,AnimationCollectionView*) __asm__("func_00345FB8");
extern int InstallTracks(AnimationSourceClip*) __asm__("func_00345F98");
}
#endif
