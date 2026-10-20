#include "mod/arms/sampler.hpp"
namespace ArmsAnimation {
SampleContext::SampleContext(int,int,int samples):first(0),last(samples-1),count(samples) {
    reference.Identity();current.Identity();previous.Identity();start.Identity();end.Identity();
}
Sampler::Sampler(void* instance,SamplingClip* source){owner=instance;clip=source;}
SampleHeader* Sampler::Whole(float current,float previous,float duration,int samples,float spacing,unsigned flags) {
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
SampleHeader* Sampler::Motion(SampleHeader* out,float current,float previous,float duration,int samples,float spacing,unsigned flags) {
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
// Unmatched: BodyPair endpoint call scheduling retains one extra context move.
// Unmatched: HeaderPair endpoint call scheduling retains one extra context move.
}
