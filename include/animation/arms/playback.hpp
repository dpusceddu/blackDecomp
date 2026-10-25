#ifndef BLACK_ARMS_PLAYBACK_HPP
#define BLACK_ARMS_PLAYBACK_HPP
#include "animation/arms/instance.hpp"
namespace ArmsAnimation {
// Scoped method names. PlaybackState offsets are shared PS2 exact-backed views.
struct Playback : PlaybackState {
    template<class T>T& At(int offset){return *(T*)((char*)this+offset);}
    void Reset(void*,void*) __asm__("func_0034EAE0");
    float ChangedSpan(float,float,float,AnimationGraphNode*,AnimationParameters*,unsigned) __asm__("func_0034EDB8");
    long Advance(float) __asm__("func_0034EE90");
    Pose* Evaluate(Pose*) __asm__("func_0034F080");
    void EvaluateHeader(Pose*) __asm__("func_0034F1C0");
};
extern float Wrap(float,float) __asm__("func_0034B498");
extern long Scan(Playback*,int) __asm__("func_00350650");
extern void Accumulate(float) __asm__("func_0034ED88");
extern float* Parameter(AnimationParameters*,int) __asm__("func_003500E0");
extern Pose* RootMotion(Playback*,void*,void*,float,float,unsigned,short) __asm__("func_00350F28");
extern void RefreshSpan(Playback*,void*,void*) __asm__("func_00351030");
extern float gSubtraction __asm__("D_003D4460"),gAccumulation __asm__("D_003D4464");
}
#endif
