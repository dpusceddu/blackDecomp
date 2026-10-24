#ifndef BLACK_MOD_ARMS_SAMPLER_HPP
#define BLACK_MOD_ARMS_SAMPLER_HPP
#include "animation/runtime.h"
namespace ArmsAnimation {
// PS2 storage and caller contracts; original class identities remain inferred.
struct SampleHeader : SamplingPoseHeader {
    SampleHeader() __asm__("func_00343FC8");
    SampleHeader(const SampleHeader&) __asm__("func_00343FE0");
    SampleHeader* Identity() __asm__("func_00344008");
    SampleHeader* Copy(const SampleHeader*) __asm__("func_00344020");
};
struct SamplePair : SamplingPair {
    SamplePair() __asm__("func_0034FE70");
    void Cyclic(float,float,int,float) __asm__("func_0034FE88");
    void Linear(float,float,int,float) __asm__("func_0034FFA0");
};
struct SampleContext {
    int first,last,count,unknown0c;
    SampleHeader reference,current,previous,start,end;
    SampleContext(int,int,int) __asm__("func_0034F360");
};
struct Sampler : SamplingPipeline {
    Sampler(void*,SamplingClip*) __asm__("func_0034F420");
    SampleHeader* Whole(float,float,float,int,float,unsigned) __asm__("func_0034F430");
    SampleHeader* Motion(SampleHeader*,float,float,float,int,float,unsigned) __asm__("func_0034F730");
    SampleHeader* Body(const SampleHeader*,int,unsigned) __asm__("func_0034F9D0");
    SampleHeader* Root(SampleHeader*,int,unsigned) __asm__("func_0034F980");
    SampleHeader* RootRelative(SampleHeader*,const SampleHeader*,int,unsigned) __asm__("func_0034FA60");
    long Extract(SampleHeader*,SampleHeader*,const SampleHeader*) __asm__("func_0034FAF8");
    SampleHeader* BodyPair(const SampleHeader*,const SamplePair*,unsigned) __asm__("func_0034FB58");
    SampleHeader* HeaderPair(SampleHeader*,const SampleHeader*,const SamplePair*,unsigned) __asm__("func_0034FC80");
    SampleHeader* Scale(SampleHeader*) __asm__("func_0034FE10");
};
extern void ExtractMotion(SampleHeader*,const SampleHeader*,const SampleHeader*,const SampleHeader*,const SampleHeader*,int) __asm__("func_00343A30");
extern SampleHeader* BlendBody(void*,SampleHeader*,SampleHeader*,unsigned,float) __asm__("func_00346230");
extern SampleHeader* BlendHeader(SampleHeader*,const SampleHeader*,const SampleHeader*,float) __asm__("func_00344178");
typedef char SampleContext176[sizeof(SampleContext)==176?1:-1];
typedef char SamplePair16[sizeof(SamplePair)==16?1:-1];
}
#endif
