#include "include_asm.h"

extern unsigned char poseCacheStorage[] __asm__("D_0045F0C0") __attribute__((aligned(16)));
#include "ps2/ee_fpu.h"
#include "ps2/prelude.h"
#include "animation/animation_graph_node.h"
#include "animation/animation_parameters.h"
/* Recovered_OverlayBinding: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_OverlayBinding {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
} Recovered_OverlayBinding;

#include "ps2/recovered_types.h"
#include "ps2/vu0_micro.hpp"
#include "ps2/vu0_quaternion.hpp"
#include "animation/pose_operations.hpp"

// Cache configuration, sampler limit and explicit arena storage. Construction
// remains in Cache::Construct; a typed Slot definition would add a second init.
u8 D_003D20D0 __attribute__((section(".data.pose_cache"))) = 1;
s32 D_003D20D4 __attribute__((section(".data.pose_cache"))) = 28;
u8* D_003D20D8 __attribute__((section(".data.pose_cache"))) = 0;
s32 D_003D20DC __attribute__((section(".data.pose_cache"))) = 64;
s32 D_003D20E0 __attribute__((section(".data.pose_cache"))) = -1;
s32 D_0046A500;
unsigned char poseCacheStorage[sizeof(ArmsPose::Slot)*28]
    __asm__("D_0045F0C0") __attribute__((aligned(16)));

namespace ArmsPose { extern Skeleton* GetSkeleton(Operations*) __asm__("func_003489A8");
extern void SampleBone(Pose*, const void*, int, float) __asm__("func_00345480"); }

// Branch-local native captures preserve independent rotation/position lifetimes.
// Float aliases at the public pose boundary retain the original load scheduling.
extern f32* SelectCopy(f32*,f32*) __asm__("func_00344020");

namespace ArmsPose {

static inline void BlendCopyBone(Pose* destination,const Pose* source) {
    destination->rotation=source->rotation;
    destination->position=source->position;
}

}
namespace ArmsPose {
// Fixed VF9/10 translation family observed in both loops. All XYZW lanes
// participate; MAC/status are overwritten, ACC/Q/I/R/VI/clip are preserved.
static inline void ComposeAddPositionXYZW(void* out,const void* first,const void* second) {
    asm volatile("lqc2 vf9,0(%0)\n\tlqc2 vf10,0(%1)\n\tvadd.xyzw vf10,vf9,vf10\n\tsqc2 vf10,0(%2)"
                 : : "r"(first),"r"(second),"r"(out):"vf9","vf10","memory");
}
static inline int& ComposeUsedCount(){return D_0046A500;}
static inline void ComposeCopyBone(Pose* out,const Pose* source){out->rotation=source->rotation;out->position=source->position;}
static inline void ComposeBone(Pose* out,const Pose* first,const Pose* second) {
    BlackPS2::AnimationMath::Multiply(out,first,second);
    float* firstPosition=(float*)first->translation;
    float* secondPosition=(float*)second->translation;
    float* outputPosition=out->translation;
    ComposeAddPositionXYZW(outputPosition,firstPosition,secondPosition);
}

}
namespace ArmsPose {
static inline void DifferenceSubtractPositionXYZW(void* out,const void* first,const void* second) {
    asm volatile("lqc2 vf9,0(%0)\n\tlqc2 vf10,0(%1)\n\tvsub.xyzw vf10,vf9,vf10\n\tsqc2 vf10,0(%2)"
                 : : "r"(first),"r"(second),"r"(out):"vf9","vf10","memory");
}
static inline int& DifferenceUsedCount(){return D_0046A500;}
static inline void DifferenceCopyBone(Pose* out,const Pose* source){out->rotation=source->rotation;out->position=source->position;}
// Inverse(second) * first uses a native quadword scratch, preserving the
// observed FPR readback and VU store/load boundary. The complete operation
// overwrites VF1..4, VF9/10, VF31.x, ACC, Q and arithmetic MAC/status flags.
// T0 is the observed transfer scratch; pointer/FPR operands allocate normally.
// R/I/VI/clip are preserved. The local assembler scope retains the observed
// immediate MTC1/MFC1 roundtrip, then restores ordinary scheduling.
static inline void DifferenceRotation(void* out,const void* first,const void* second,void* inverse) {
    float norm;
    asm volatile(".set push\n\t.set noreorder\n\tlqc2 vf9,0(%1)\n\tlqc2 vf10,0(%1)\n\tvaddw.x vf31,vf0,vf0w\n\t"
                 "vmul.xyzw vf10,vf9,vf10\n\tvadday.x ACC,vf10,vf10y\n\t"
                 "vmaddaz.x ACC,vf31,vf10z\n\tvmaddw.x vf10,vf31,vf10w\n\t"
                 "qmfc2.ni $8,vf10\n\tmtc1 $8,%0\n\tmfc1 $8,%0\n\t"
                 "qmtc2.ni $8,vf2\n\tvdiv Q,vf0w,vf2x\n\t"
                 "lqc2 vf1,0(%1)\n\tvsub.xyz vf1,vf0,vf1\n\tvwaitq\n\t"
                 "vmulq.xyzw vf1,vf1,Q\n\tsqc2 vf1,0(%2)\n\t.set pop" "\n\t" "lqc2 vf1,0(%2)\n\t"
                 "lqc2 vf2,0(%3)\n\t"
                 "vmul.xyzw vf4,vf1,vf2\n\t"
                 "vsubay.w ACC,vf4,vf4y\n\t"
                 "vmsubaz.w ACC,vf0,vf4z\n\t"
                 "vmsubx.w vf3,vf0,vf4x\n\t"
                 "vopmula.xyz ACC,vf1,vf2\n\t"
                 "vopmsub.xyz vf3,vf2,vf1\n\t"
                 "vmulaw.xyz ACC,vf2,vf1w\n\t"
                 "vmaddaw.xyz ACC,vf1,vf2w\n\t"
                 "vmaddw.xyz vf3,vf3,vf0w\n\t"
                 "sqc2 vf3,0(%4)"
                 : "=&f"(norm) : "r"(second),"r"(inverse),"r"(first),"r"(out)
                 :"$8","vf1","vf2","vf3","vf4","vf9","vf10","vf31","memory");
}
static inline void DifferenceBone(Pose* out,const Pose* first,const Pose* second,void* inverse) {
    DifferenceRotation(out,first,second,inverse);
    const float* firstPosition=first->translation;
    const float* secondPosition=second->translation;
    float* outputPosition=out->translation;
    DifferenceSubtractPositionXYZW(outputPosition,firstPosition,secondPosition);
}

}
namespace ArmsPose {
static inline int& WeightUsedCount(){return D_0046A500;}
static inline float WeightZero(){return 0.0f;}
static inline void WeightCopyBone(Pose* out,const Pose* source){out->rotation=source->rotation;out->position=source->position;}
// Whole XYZW scaling family; T0/VF9/11/12 are the observed transfer roles.
// MAC/status are overwritten; ACC/Q/I/R/VI/clip remain untouched.
static inline void WeightScalePositionXYZW(void* out,const void* source,float strength) {
    asm volatile("lqc2 vf9,0(%0)\n\tmfc1 $8,%2\n\tqmtc2.ni $8,vf11\n\t"
                 "vmulx.xyzw vf12,vf9,vf11x\n\tsqc2 vf12,0(%1)"
                 : : "r"(source),"r"(out),"f"(strength):"$8","vf9","vf11","vf12","memory");
}
static inline void WeightBone(Pose* out,const Pose* source,const void* identity,float strength) {
    BlackPS2::AnimationMicro::Slerp(out,identity,source,strength);
    const float* input=source->translation;
    float* output=out->translation;
    WeightScalePositionXYZW(output,input,strength);
}

}
namespace ArmsPose {
static inline int& ClipBuildUsedCount(){return D_0046A500;}
struct TrackSuffix {int frames,skeleton,format;void* tracks;};
extern const TrackSuffix* ClipFrameSlot(BkModSourceClipPS2*) __asm__("func_003487E8");
extern int CacheReserve(void*,unsigned,void*,int,int,Pose**) __asm__("func_00342478");
extern void* CurrentCache __asm__("D_003F15B4");
extern float WrapFrame(float,float) __asm__("func_0034B498");
extern void SampleMasked(Pose*,const void*,int,int,float) __asm__("func_003452B0");
// Raw rotation transport uses the observed native quadword macro. XYZ retains
// its separate64+32 bit reads; the fourth source translation lane is not copied.
static inline void ClipBuildCopyRotation(void* out,const void* source) {
    asm volatile("lq $8,0(%0)\n\tsq $8,0(%1)" : : "r"(source),"r"(out):"$8","memory");
}
// Copy the bone following each header. Native loads and precise quadword stores
// preserve the real header bases; scratch registers allocate normally.
static inline void ClipBuildCopyHeader(const Pose* in,Pose* out) {
    s128 rotation=in[1].rotation;
    asm("sq %1,32(%2)" : "=m"(out[1].rotation) : "r"(rotation),"r"(out));
    s128 position=in[1].position;
    asm("sq %1,48(%2)" : "=m"(out[1].position) : "r"(position),"r"(out));
}
static inline void ClipBuildCopyXYZValues(float* out,unsigned long xy,unsigned z) {
    *(unsigned long*)out=xy;
    *(unsigned*)((char*)out+8)=z;
}
static inline void ClipBuildIdentity(float* lanes) {
    ((volatile float*)lanes)[3]=1.0f;
    ((volatile float*)lanes)[0]=0.0f;
    ((volatile float*)lanes)[1]=0.0f;
    ((volatile float*)lanes)[2]=0.0f;
}

}
namespace ArmsPose {
static inline int& OverlayUsedCount(){return D_0046A500;}

}
inline void* operator new[](unsigned,void* storage){return storage;}
namespace OffsetViews {

// Partial PS2 animation transform views, not recovered original class identities.
struct Transform { BkVuVector rotation, position; };
struct Offset { BkVuVector rotation; float position[3]; int index; };
struct Record { unsigned token; int count; Offset *offsets; };
struct Owner { char pad[0x44]; int count; Record *records; };
struct Query { unsigned unknown; Owner *owner; };
struct Key { unsigned unknown[2]; unsigned *token; };

}
namespace DiscreteViews {

extern f32 * func_003500E0(Recovered_AnimationParameters *, s32) __asm__("func_003500E0");
extern f32 func_0029DB30(f32) __asm__("func_0029DB30");
extern void * func_0034FE70(void *) __asm__("func_0034FE70");
extern s32 func_0034FE88(void *, f32, f32, s32, f32) __asm__("func_0034FE88");
extern f32 * func_0034D9B0(s32 *, Recovered_AnimationGraphNode *, Recovered_AnimationParameters *, Recovered_OverlayBinding *, s32, f32, f32, f32) __asm__("func_0034D9B0");
extern s32 func_0034FFA0(void *, f32, f32, s32, f32) __asm__("func_0034FFA0");
extern f32 * func_00344020(f32 *, f32 *) __asm__("func_00344020");

}
namespace DiscreteViews { f32 * func_00347280(s32 *arg0, Recovered_AnimationGraphNode *arg1, Recovered_AnimationParameters *arg2, u32 arg3, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) __asm__("func_00347280"); }
namespace ArmsPose {
__attribute__((section(".text.func_003461D0"))) void Cache::Enable(s8 enabled) { BkModPoseCacheEnablePS2(enabled); }
}

namespace ArmsPose {
__attribute__((section(".text.func_003461E0"))) void Cache::Clear() { BkModPoseCacheClearPS2(); }
}

namespace ArmsPose {
__attribute__((section(".text.func_003461F0"))) Pose* Cache::Allocate()
{
    if (D_0046A500 >= D_003D20D4) return 0;
    return &slots[D_0046A500++].root;
}
}

namespace ArmsPose {
// The next output cursor is the consumed result of each complete bone operation.
static inline Pose* BlendCopyAdvance(Pose* out,const Pose* source) {
    BlendCopyBone(out,source);
    out->translation[3]=0.0f;
    return out+1;
}
static inline Pose* BlendBoneAdvance(Pose* out,const Pose* first,const Pose* second,float weight) {
    BlackPS2::AnimationMicro::Slerp(out,first,second,weight);
    const float* firstPosition=first->translation;
    const float* secondPosition=second->translation;
    float* outPosition=out->translation;
    BlackPS2::AnimationMicro::InterpolateXYZW(outPosition,firstPosition,secondPosition,weight);
    out->translation[3]=0.0f;
    return out+1;
}

// Unmatched: two reversed input-setup instructions and five cursor-step instructions; native unwind exact.
__attribute__((section(".text.func_00346230"))) Pose* Operations::Blend(Pose* first,Pose* second,unsigned flags,float weight) {
    if(!first || !second)return 0;
    int used=D_0046A500;
    if(used>=D_003D20D4){if(weight<0.5f)return first;return second;}
    Pose* out=(Pose*)((used*0x670)+(char*)slots);
    D_0046A500=used+1;
    if(flags&0x80)out->Copy(second);
    else BlendRoot(out,first,second,weight);
    if(!(flags&4)) {
        void* collection=this->collection;
        Skeleton* skeletons=((Collection*)collection)->skeletons;
        Skeleton* selected=skeletons+this->skeleton;
        int count=selected->count;
        Pose* b=second+1;
        Pose* a=first+1;
        Pose* result=out+1;
        if(D_003D20D8) {
            for(int i=0;i<count;++i,++b,++a) {
                if(D_003D20D8[i] && !(b->quaternion[3]>1.5f)) {
                    if(a->quaternion[3]>1.5f)
                        result=BlendCopyAdvance(result,b);
                    else
                        result=BlendBoneAdvance(result,a,b,weight);
                } else
                    result=BlendCopyAdvance(result,a);
            }
        } else if(count>0) {
            int remaining=count;
            do {
                if(b->quaternion[3]>1.5f)
                    result=BlendCopyAdvance(result,a);
                else if(a->quaternion[3]>1.5f)
                    result=BlendCopyAdvance(result,b);
                else
                    result=BlendBoneAdvance(result,a,b,weight);
                ++b;
                ++a;
            } while(--remaining);
        }
    }
    return out;
}
}

extern "C" f32 * func_00346510(void *owner, f32 *first, f32 *second, s32 flags) {
    f32 *out;
    f32 *secondBone;
    f32 *firstBone;
    f32 *outputBone;
    s32 count;
    s32 used;
    s32 remaining;

    if ((first == 0) || (second == 0)) {
        return 0;
    }
    used = D_0046A500;
    if (used >= D_003D20D4) {
        return first;
    }
    D_0046A500 = used + 1;
    out = (f32 *) ((used * 0x670) + ((s8 *) poseCacheStorage));
    if (M2C_FIELD(second, f32 *, 0xC) > 1.5f) {
        SelectCopy(out, first);
    } else {
        SelectCopy(out, second);
    }
    if (!(flags & 4)) {
        void* collection = M2C_FIELD(owner, void **, 4);
        void* skeletons = M2C_FIELD(collection, void **, 0x1C);
        firstBone = (f32 *) (((s8 *) first) + 0x20);
        secondBone = (f32 *) (((s8 *) second) + 0x20);
        count = M2C_FIELD(((s8*)skeletons+(M2C_FIELD(owner,s16*,8)<<4)),s32*,0);
        outputBone = (f32 *) (((s8 *) out) + 0x20);
        if (count > 0) {
            remaining = count;
            do {
                if (M2C_FIELD(secondBone, f32 *, 0xC) > 1.5f) {
                    s128 rotation = M2C_FIELD(firstBone, s128 *, 0);
                    M2C_FIELD(outputBone,s128*,0)=rotation;
                    s128 position=M2C_FIELD(firstBone,s128*,0x10);
                    M2C_FIELD(outputBone,s128*,0x10)=position;
                } else {
                    s128 rotation = M2C_FIELD(secondBone, s128 *, 0);
                    M2C_FIELD(outputBone,s128*,0)=rotation;
                    s128 position=M2C_FIELD(secondBone,s128*,0x10);
                    M2C_FIELD(outputBone,s128*,0x10)=position;
                }

                firstBone = (f32 *) (((s8 *) firstBone) + 0x20);
                secondBone = (f32 *) (((s8 *) secondBone) + 0x20);
                remaining -= 1;
                outputBone = (f32 *) (((s8 *) outputBone) + 0x20);
            } while (remaining != 0);
        }
    }
    return out;
}

namespace ArmsPose {
// Unmatched: first/second bone-address setup ordering (2 instructions).
__attribute__((section(".text.func_00346668"))) Pose* Operations::Compose(Pose* first,Pose* second,unsigned flags) {
    if(!first || !second)return 0;
    int used=ComposeUsedCount();
    if(used>=D_003D20D4)return first;
    ComposeUsedCount()=used+1;
    Pose* out=(Pose*)((used*0x670)+(char*)slots);
    if(second->quaternion[3]>1.5f)out->Copy(first);
    else if(first->quaternion[3]>1.5f)out->Copy(second);
    else ComposeRoot(out,first,second);
    if(!(flags&4)) {
        void* collection=this->collection;
        Skeleton* skeletons=((Collection*)collection)->skeletons;
        Skeleton* skeleton=skeletons+this->skeleton;
        int count=skeleton->count;
        Pose* b=second+1;
        Pose* a=first+1;
        Pose* result=out+1;
        if(D_003D20D8) {
            for(int i=0;i<count;++i,++a,++b,++result) {
                if(D_003D20D8[i] && !(b->quaternion[3]>1.5f)) {
                    if(a->quaternion[3]>1.5f)ComposeCopyBone(result,b);
                    else ComposeBone(result,a,b);
                } else ComposeCopyBone(result,a);
            }
        } else if(count>0) {
            int remaining=count;
            do {
                if(b->quaternion[3]>1.5f)ComposeCopyBone(result,a);
                else if(a->quaternion[3]>1.5f)ComposeCopyBone(result,b);
                else ComposeBone(result,a,b);
                ++a;++b;++result;
            } while(--remaining);
        }
    }
    return out;
}
}

namespace ArmsPose {
__attribute__((section(".text.func_00346940"))) Pose* Operations::Difference(Pose* first,Pose* second,unsigned flags) {
    if(!first || !second)return 0;
    int used=DifferenceUsedCount();
    if(used>=D_003D20D4)return first;
    DifferenceUsedCount()=used+1;
    Pose* out=(Pose*)((used*0x670)+(char*)slots);
    if(second->quaternion[3]>1.5f)out->Copy(first);
    else if(first->quaternion[3]>1.5f)out->Copy(second);
    else DifferenceRoot(out,first,second);
    if(!(flags&4)) {
        s128 inverse;
        void* collection=this->collection;
        Skeleton* skeletons=((Collection*)collection)->skeletons;
        Skeleton* skeleton=skeletons+this->skeleton;
        int count=skeleton->count;
        Pose* a=first+1;
        Pose* b=second+1;
        Pose* result=out+1;
        if(D_003D20D8) {
            for(int i=0;i<count;++i,++a,++b,++result) {
                if(D_003D20D8[i] && !(b->quaternion[3]>1.5f)) {
                    if(a->quaternion[3]>1.5f)DifferenceCopyBone(result,b);
                    else DifferenceBone(result,a,b,&inverse);
                } else DifferenceCopyBone(result,a);
            }
        } else if(count>0) {
            int remaining=count;
            do {
                if(b->quaternion[3]>1.5f)DifferenceCopyBone(result,a);
                else if(a->quaternion[3]>1.5f)DifferenceCopyBone(result,b);
                else DifferenceBone(result,a,b,&inverse);
                ++a;++b;++result;
            } while(--remaining);
        }
    }
    return out;
}
}

namespace ArmsPose {
__attribute__((section(".text.func_00346CB0"))) Pose* Operations::Weight(Pose* pose,unsigned flags,float strength) {
    if(!pose)return 0;
    int used=WeightUsedCount();
    if(used>=D_003D20D4)return pose;
    WeightUsedCount()=used+1;
    Pose* out=(Pose*)((used*0x670)+(char*)slots);
    float* rootRotation=out->quaternion;
    float zero=WeightZero();
    float identity[4] __attribute__((aligned(16)));
    identity[3]=1.0f;
    identity[2]=zero;
    identity[1]=zero;
    identity[0]=zero;
    if(pose->quaternion[3]>1.5f)out->Copy(pose);
    else {
        BlackPS2::AnimationMicro::Slerp(rootRotation,identity,pose,strength);
        const float* input=pose->translation;
        float* output=out->translation;
        WeightScalePositionXYZW(output,input,strength);
    }
    if(!(flags&4)) {
        void* collection=this->collection;
        Skeleton* skeletons=((Collection*)collection)->skeletons;
        Skeleton* skeleton=skeletons+this->skeleton;
        int count=skeleton->count;
        Pose* bone=pose+1;
        Pose* result=out+1;
        if(D_003D20D8) {
            for(int i=0;i<count;++i,++bone,++result) {
                if(D_003D20D8[i] && !(bone->quaternion[3]>1.5f))WeightBone(result,bone,identity,strength);
                else WeightCopyBone(result,bone);
            }
        } else if(count>0) {
            int remaining=count;
            do {
                if(bone->quaternion[3]>1.5f)WeightCopyBone(result,bone);
                else WeightBone(result,bone,identity,strength);
                ++bone;++result;
            } while(--remaining);
        }
    }
    return out;
}
}

namespace ArmsPose {
__attribute__((section(".text.func_00346F38"))) void Cache::ForceBone(int index) { BkModPoseCacheForceBonePS2(index); }
}

extern "C" __attribute__((section(".text.func_00346F48"))) void func_00346F48(void) {
    D_003D20E0 = -1;
}

namespace ArmsPose {
extern "C" __attribute__((section(".text.func_00346F58"))) Pose* func_00346F58(Operations* owner,BkModSourceClipPS2* clip,Skeleton* skeleton,float frame,unsigned flags) {
    const TrackSuffix* source=ClipFrameSlot(clip);
    if(!source || !skeleton)return 0;
    int used=ClipBuildUsedCount();
    if(used>=D_003D20D4)return 0;
    ClipBuildUsedCount()=used+1;
    Pose* block=(Pose*)((used*0x670)+(char*)slots);
    owner->selectedClip=clip;
    owner->evaluationFlags|=clip->flags;
    if(!clip->flags) {
        if((float)(source->frames-1)<=frame)frame=(float)(source->frames-1);
    } else frame=WrapFrame(frame,(float)source->frames);
    if(!source->tracks)return 0;
    int hit=0;
    Pose* scratch=block;
    if(D_003D20D0)hit=CacheReserve(CurrentCache,clip->hash,source->tracks,(int)frame,skeleton->count,&block);
    if(!hit) {
        switch((int)(clip->trackFormat&0x7fffffff)) {
        case 3: {
            int rawIndex=0;
            const Pose* input=(const Pose*)source->tracks;
            input+=skeleton->count*(int)frame;
            if(skeleton->count>0) {
                do {
                    ClipBuildCopyXYZValues(block[rawIndex+1].translation,*(const unsigned long*)input->translation,*(const unsigned*)(input->translation+2));
                    ClipBuildCopyRotation((block+rawIndex)+1,input);
                    ++rawIndex;
                    ++input;
                } while(rawIndex<skeleton->count);
            }
            break;
        }
        case 4:SampleMasked(block,source->tracks,skeleton->count,*(short*)((char*)owner+0x6c),frame);break;
        case 0:case 1:case 2:break;
        }
    }
    if(D_003D20D0) {
        int i=0;
        if(i<skeleton->count) {
            Pose* result=scratch;
            do {
                ClipBuildCopyHeader(block+i,result);
                ++i;
                ++result;
            } while(i<skeleton->count);
        }
        block=scratch;
    }
    if(D_003D20E0!=-1) {
        ClipBuildIdentity(block[D_003D20E0+1].quaternion);
        ClipBuildIdentity(block[D_003D20E0+1].translation);
    }
    return block;
}
}

namespace ArmsPose {
__attribute__((section(".text.func_00347238"))) float* GraphOperations::Scaled(void* owner, AnimationGraphNode* node,
                               AnimationParameters* parameters, unsigned flags,
                               float current, float previous, float factor,
                               float coefficient)
{
    return AnimationGraph_EvaluateNode(owner, node, parameters, current / factor,
        previous / factor, flags, coefficient / factor, 1.0f);
}
}

namespace DiscreteViews {
// Unmatched: conversion scratch and boundary scheduling (19 instructions); closest 7-difference draft is 4 bytes longer.
__attribute__((section(".text.func_00347280"))) f32 * func_00347280(s32 *arg0, Recovered_AnimationGraphNode *arg1, Recovered_AnimationParameters *arg2, u32 arg3, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    u8 sp[32] __attribute__((aligned(16)));
    f32 *temp_2;
    f32 *temp_2_2;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_f24;
    f32 var_f20;
    s32 temp_20;

    temp_f24 = *func_003500E0(arg2, (s32) arg1->unk_2);
    temp_f23 = BkEeDividePipelineGuarded(fparg0,fparg2);
    if (fparg0 == fparg1) {
        var_f20 = func_0029DB30(temp_f23);
    } else {
        var_f20 = ((fparg1 + fparg2) / fparg2) - 1.0f;
    }
    temp_f22 = BkEeDividePipelineGuarded(fparg3,fparg2);
    temp_20 = (s32) temp_f24;
    func_0034FE70(sp);
    func_0034FE88(sp, temp_f23, temp_f24, temp_20, 1.0f);
    temp_2 = func_0034D9B0(arg0, arg1, arg2, (Recovered_OverlayBinding*)sp, (s32) arg3, var_f20, temp_f22, 1.0f);
    if (temp_2 != 0) {
        func_0034FE70((sp + 16));
        func_0034FFA0((sp + 16), temp_f23, temp_f24, temp_20, 1.0f);
        temp_2_2 = func_0034D9B0(arg0, arg1, arg2, (Recovered_OverlayBinding*)(sp + 16), 4, var_f20, temp_f22, 1.0f);
        if (temp_2_2 != 0) {
            func_00344020(temp_2, temp_2_2);
            return temp_2;
        }
    }
    return 0;
}
}

namespace OffsetViews {
extern "C" __attribute__((section(".text.func_00347430"))) void *func_00347430(Query *query, void *poses, Key *key)
{
    Owner *owner = query->owner;
    unsigned *token = key->token;
    int count = owner->count;
    Record *r = owner->records;
    for (int i = 0; i < count; ++i, ++r) {
        if (r->token == *token) {
            Offset *o = r->offsets;
            for (int j = 0; j < r->count; ++j, ++o) {
                Transform *p = (Transform *)((char *)poses + 0x20 + (o->index << 5));
                BlackPS2::AnimationMath::Multiply(&p->rotation, &o->rotation, &p->rotation);
                BlackPS2::AnimationMath::Add(&p->position, &o->position, &p->position);
            }
            return poses;
        }
    }
    return poses;
}
}

namespace ArmsPose {
__attribute__((section(".text.func_003474F8"))) Pose* ClipOperations::Default(Operations* owner, BkModSourceClipPS2* clip,
                              unsigned flags, float frame)
{
    Skeleton* skeleton = GetSkeleton(owner);
    // This argument order is a scoped, exact caller recipe for the same ABI.
    extern Pose* BuildOrdered(Operations*, BkModSourceClipPS2*, Skeleton*, float,
                              unsigned) __asm__("func_00346F58");
    return BuildOrdered(owner, clip, skeleton, frame, flags);
}
}

namespace ArmsPose {
__attribute__((section(".text.func_00347558"))) Pose* ClipOperations::Root(Pose* out, Operations* owner, BkModSourceClipPS2* clip,
                           unsigned flags, int index, float time)
{
    if (!clip || !clip->tracks) return 0;
    int format = clip->trackFormat & 0x7fffffff;
    switch (format) {
    case 3: {
        char* offset = (char*)(index << 5);
        char* base = (char*)clip->tracks;
        Pose* in = (Pose*)((int)offset + (int)base);
        asm volatile("lq $8,0(%0)\n\tsq $8,0(%1)"
                     : : "r"(in), "r"(out) : "$8", "memory");
        // Raw tracks copy XYZ as 8+4 bytes; destination W is set below.
        unsigned long xy = *(unsigned long*)in->translation;
        unsigned z = *(unsigned*)(in->translation + 2);
        *(unsigned*)(out->translation + 2) = z;
        *(unsigned long*)out->translation = xy;
        break;
    }
    case 4:
        SampleBone(out, clip->tracks, index, time);
        break;
    case 0:
    case 1:
    case 2:
        break;
    }
    out->translation[3] = 1;
    return out;
}
}

namespace ArmsPose {
__attribute__((section(".text.func_00347600"))) Pose* Operations::Overlay(Pose* first, Pose* second, float blend)
{
    if (!first || !second) return 0;
    int used = OverlayUsedCount();
    if (used >= D_003D20D4) return first;
    OverlayUsedCount() = used + 1;
    Pose* out = (Pose*)((used * 0x670) + (char*)slots);
    Pose* firstBase = first + 1;
    Pose* secondBase = second + 1;
    Skeleton* skeleton = ((Collection*)collection)->skeletons + this->skeleton;
    Pose* outputBase = out + 1;
    // Capture translation views before the distinct rotation loop iterators.
    // This bone-only overlay leaves the cached root header untouched.
    int index = 0;
    if (skeleton->count > 0) {
        float* firstPosition = firstBase->translation;
        float* secondPosition = secondBase->translation;
        float* outputPosition = outputBase->translation;
        Pose* outputBone = outputBase;
        Pose* firstBone = firstBase;
        Pose* secondBone = secondBase;
        do {
            if (secondBone->quaternion[3] > 1.5f) {
                outputBone->rotation = firstBone->rotation;
                outputBone->position = firstBone->position;
            } else {
                BlackPS2::AnimationMicro::Slerp(outputBone, firstBone, secondBone, blend);
                BlackPS2::AnimationMicro::InterpolateXYZW(outputPosition, firstPosition, secondPosition, blend);
            }
            ++index;
            outputPosition += 8;
            secondPosition += 8;
            firstPosition += 8;
            ++outputBone;
            ++firstBone;
            ++secondBone;
        } while (index < skeleton->count);
    }
    return out;
}
}

namespace ArmsPose {
__attribute__((section(".text.func_00347738"))) void Cache::Construct(int initialize, int priority)
{
    if (priority == 0xffff && initialize) new(slots) Slot[28];
}
}

namespace ArmsPose {
__attribute__((section(".text.func_003477D0"))) void Cache::Initialize() { Construct(1, 0xffff); }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00346230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00346668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347280);
