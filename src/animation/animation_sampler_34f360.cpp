#include "include_asm.h"

#include "animation/views/sampler.hpp"
namespace AnimationViews {

static inline float SampleAbs(float value){return __builtin_fabsf(value);}
}
namespace AnimationViews {
__attribute__((section(".text.func_0034F360"))) SampleContext::SampleContext(int,int,int samples):first(0),last(samples-1),count(samples) {
    reference.Identity();current.Identity();previous.Identity();start.Identity();end.Identity();
}
}

namespace AnimationViews {
__attribute__((section(".text.func_0034F420"))) Sampler::Sampler(void* instance,SamplingClip* source){owner=instance;clip=source;}
}

namespace AnimationViews {
SampleHeader* __attribute__((section(".text.func_0034F430"))) Sampler::Whole(float current,float previous,float duration,int samples,float spacing,unsigned flags) {
    SamplePair cyclic,now,before;
    cyclic.Cyclic(current,duration,samples,spacing);
    now.Linear(current,duration,samples,spacing);
    before.Linear(previous,duration,samples,spacing);
    SampleContext context(now.first,before.first,samples);
    if(!Root(&context.reference,context.first,flags))return 0;
    if(!Extract(&context.start,&context.reference,&context.reference))return 0;
    if(!RootRelative(&context.end,&context.reference,context.last,flags))return 0;
    if(!HeaderPair(&context.current,&context.reference,&now,flags))return 0;
    SampleHeader* out=BodyPair(&context.reference,&cyclic,flags);
    if(!out)return 0;
    if(current!=0.0f||previous!=0.0f) {
        if(!HeaderPair(&context.previous,&context.reference,&before,flags))return 0;
        ExtractMotion(out,&context.current,&context.previous,&context.start,&context.end,0);
    }else out->Copy(&context.current);
    Scale(out);return out;
}
}

namespace Fragment34F668 {
extern SamplingPoseHeader *func_0034F730(SamplingPipeline *, SamplingPoseHeader *, f32, f32, f32, s32, f32, s32) __asm__("func_0034F730");

SamplingPoseHeader *func_0034F668(SamplingPipeline *context, f32 current, f32 previous, f32 rate, s32 count, f32 weight, s32 flags) __asm__("func_0034F668") __attribute__((section(".text.func_0034F668")));
SamplingPoseHeader *func_0034F668(SamplingPipeline *context, f32 current, f32 previous, f32 rate, s32 count, f32 weight, s32 flags) {
    SamplingPoseHeader temporary;
    SamplingPoseHeader *result = 0;
    func_00343FC8(&temporary);
    if (func_0034F730(context, &temporary, current, previous, rate, count, weight, flags)) {
        result = (SamplingPoseHeader *)func_003461F0();
        if (result != NULL) func_00344020(result, &temporary);
    }
    return result;
}
}

namespace AnimationViews {
SampleHeader* __attribute__((section(".text.func_0034F730"))) Sampler::Motion(SampleHeader* out,float current,float previous,float duration,int samples,float spacing,unsigned flags) {
    SamplePair cyclic,now,before;
    cyclic.Cyclic(current,duration,samples,spacing);
    now.Linear(current,duration,samples,spacing);
    before.Linear(previous,duration,samples,spacing);
    SampleContext context(now.first,before.first,samples);
    if(!Root(&context.reference,context.first,flags))return 0;
    if(!Extract(&context.start,&context.reference,&context.reference))return 0;
    if(!RootRelative(&context.end,&context.reference,context.last,flags))return 0;
    if(!HeaderPair(&context.current,&context.reference,&now,flags))return 0;
    if(current!=0.0f||previous!=0.0f) {
        if(!HeaderPair(&context.previous,&context.reference,&before,flags))return 0;
        ExtractMotion(out,&context.current,&context.previous,&context.start,&context.end,0);
    }else out->Copy(&context.current);
    Scale(out);return out;
}
}

namespace Fragment34F950 {
extern void* SamplePose(void*,SamplingClip*,f32,s32) __asm__("func_003474F8");
void* func_0034F950(SamplingPipeline* context,s32 frame,s32 flags) __asm__("func_0034F950") __attribute__((section(".text.func_0034F950")));
// The caller forwards flags in a2 and consumes the returned pose.
void* func_0034F950(SamplingPipeline* context,s32 frame,s32 flags) {
    return SamplePose(context->owner,context->clip,(f32)frame,flags);
}
}

namespace Fragment34F980 {

s32 func_0034F980(SamplingPipeline *context, SamplingPoseHeader *header, s32 index, s32 flags) __asm__("func_0034F980") __attribute__((section(".text.func_0034F980")));
s32 func_0034F980(SamplingPipeline *context, SamplingPoseHeader *header, s32 index, s32 flags) {
    SamplingClip *clip = context->clip;
    s32 root = clip->root_track;
    s32 result;
    if (root >= 0) result = func_00347558(header, context->owner, clip, (f32)index, flags, root);
    else result = func_00344008(header);
    return result;
}
}

namespace Fragment34F9D0 {

void *func_0034F9D0(SamplingPipeline *context, SamplingPoseHeader *header, s32 index, s32 flags) __asm__("func_0034F9D0") __attribute__((section(".text.func_0034F9D0")));
void *func_0034F9D0(SamplingPipeline *context, SamplingPoseHeader *header, s32 index, s32 flags) {
    u8 *pose = (u8 *)func_0034F950(context, index, flags);
    SamplingClip *clip;
    s32 root;
    if (pose == NULL) return NULL;
    clip = context->clip;
    root = clip->root_track;
    if (root < 0) func_00344008((SamplingPoseHeader *)pose);
    else func_003438E0((SamplingPoseHeader *)pose, (SamplingPoseHeader *)(pose + 0x20 + root * 0x20), header, clip->bone_count);
    return pose;
}
}

namespace Fragment34FA60 {
extern s32 func_0034F980(SamplingPipeline *, SamplingPoseHeader *, s32, s32) __asm__("func_0034F980");

s32 func_0034FA60(SamplingPipeline *context, SamplingPoseHeader *out, SamplingPoseHeader *root, s32 index, s32 flags) __asm__("func_0034FA60") __attribute__((section(".text.func_0034FA60")));
s32 func_0034FA60(SamplingPipeline *context, SamplingPoseHeader *out, SamplingPoseHeader *root, s32 index, s32 flags) {
    SamplingPoseHeader sample;
    s32 result;
    func_00343FC8(&sample);
    if (func_0034F980(context, &sample, index, flags)) result = func_003438E0(out, &sample, root, context->clip->bone_count);
    else result = 0;
    return result;
}
}

namespace Fragment34FAF8 {

extern s32 func_00343FC8(...) __asm__("func_00343FC8");
extern s32 func_00344008(...) __asm__("func_00344008");
extern s32 func_003474F8(s32, s32, f32) __asm__("func_003474F8");
extern s32 func_00343FE0(...) __asm__("func_00343FE0");
extern s32 func_003438E0(...) __asm__("func_003438E0");
extern s32 func_00343BC0(s32, f32, f32, f32) __asm__("func_00343BC0");





/* Assembly between the functions: func_0034F430 (568 bytes), func_0034F668 (200 bytes), func_0034F730 (544 bytes) */



/* Assembly between the functions: func_0034F980 (80 bytes), func_0034F9D0 (144 bytes), func_0034FA60 (152 bytes) */



/* Assembly between the functions: func_0034FB58 (296 bytes), func_0034FC80 (400 bytes) */


s32 func_0034FAF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) __asm__("func_0034FAF8") __attribute__((section(".text.func_0034FAF8")));
s32 func_0034FAF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[24] __attribute__((aligned(16)));
    func_00343FE0((s32) sp, arg3);
    return func_003438E0(arg1, (s32) sp, arg2, M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0xC));
}
}

namespace AnimationViews {
SampleHeader* __attribute__((section(".text.func_0034FB58"))) Sampler::BodyPair(const SampleHeader* reference,const SamplePair* pair,unsigned flags) {
    if(pair->first==pair->second)return Body(reference,pair->first,flags);
    if(SampleAbs(0.0f-pair->weight)<0.001f)return Body(reference,pair->first,flags);
    else if(SampleAbs(1.0f-pair->weight)<0.001f)return Body(reference,pair->second,flags);
    SampleHeader* first=Body(reference,pair->first,flags);
    SampleHeader* second=Body(reference,pair->second,flags);
    if(!first)return second;
    if(!second)return first;
    return BlendBody(owner,first,second,flags,pair->weight);
}
}

namespace AnimationViews {
SampleHeader* __attribute__((section(".text.func_0034FC80"))) Sampler::HeaderPair(SampleHeader* out,const SampleHeader* reference,const SamplePair* pair,unsigned flags) {
    if(pair->first==pair->second)return RootRelative(out,reference,pair->second,flags);
    if(SampleAbs(0.0f-pair->weight)<0.001f)return RootRelative(out,reference,pair->first,flags);
    if(SampleAbs(1.0f-pair->weight)<0.001f)return RootRelative(out,reference,pair->second,flags);
    SampleHeader first,second;
    int a=RootRelative(&first,reference,pair->first,flags)!=0;
    int b=RootRelative(&second,reference,pair->second,flags)!=0;
    if(a) {
        if(b)return BlendHeader(out,&first,&second,pair->weight);
        return out->Copy(&first);
    }
    if(b)return out->Copy(&second);
    return 0;
}
}

namespace Fragment34FE10 {

extern s32 func_00343FC8(...) __asm__("func_00343FC8");
extern s32 func_00344008(...) __asm__("func_00344008");
extern s32 func_003474F8(s32, s32, f32) __asm__("func_003474F8");
extern s32 func_00343FE0(...) __asm__("func_00343FE0");
extern s32 func_003438E0(...) __asm__("func_003438E0");
extern s32 func_00343BC0(s32, f32, f32, f32) __asm__("func_00343BC0");





/* Assembly between the functions: func_0034F430 (568 bytes), func_0034F668 (200 bytes), func_0034F730 (544 bytes) */



/* Assembly between the functions: func_0034F980 (80 bytes), func_0034F9D0 (144 bytes), func_0034FA60 (152 bytes) */



/* Assembly between the functions: func_0034FB58 (296 bytes), func_0034FC80 (400 bytes) */


s32 func_0034FE10(void **arg0, s32 arg1) __asm__("func_0034FE10") __attribute__((section(".text.func_0034FE10")));
s32 func_0034FE10(void **arg0, s32 arg1) {
    f32 temp_f12;
    void *temp_4;

    temp_4 = *arg0;
    if (temp_4 != NULL) {
        temp_f12 = M2C_FIELD(temp_4, f32 *, 0x60);
        if (temp_f12 != 1.0f) {
            func_00343BC0(arg1, temp_f12, temp_f12, temp_f12);
        }
    }
    return arg1;
}
}
