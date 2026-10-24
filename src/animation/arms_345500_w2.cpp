#include "animation/arms/lifecycle.hpp"
#include "ps2/vu0_micro.hpp"
#include "ps2/ee_fpu.h"
#include "animation/graph.h"
#include "ps2/prelude.h"
namespace ArmsAnimation {
/* Irreducible EE matrix primitives within the recovered initialization. */
static inline void EmptyBone(AnimationHierarchy*) {}
static inline void Matrix_Identity(AnimationMatrix *matrix) {
    __asm__ volatile("pand $8,$0,$0\n\tlui $8,0x3f80\n\tsq $8,0x0(%0)\n\tpextlw $8,$8,$0\n\tsq $8,0x10(%0)\n\tpextlw $9,$0,$8\n\tsq $9,0x20(%0)\n\tpextlw $9,$8,$0\n\tsq $9,0x30(%0)": :"r"(matrix):"$8","$9","memory");
}
static inline void Scale_Copy(void* output,const void* input) {
    asm volatile("lq $8,0(%0)\n\tsq $8,0(%1)" : : "r"(input), "r"(output) : "$8", "memory");
}
static inline void Matrix_Copy(AnimationMatrix* output,const AnimationMatrix* input) {
    asm volatile("lq $8,0(%0)\n\tlq $9,16(%0)\n\tsq $8,0(%1)\n\tlq $8,32(%0)\n\tsq $9,16(%1)\n\tlq $9,48(%0)\n\tsq $8,32(%1)\n\tsq $9,48(%1)" : : "r"(input), "r"(output) : "$8", "$9", "memory");
}
static inline void Matrix_MultiplyParent(AnimationMatrix *matrix,const AnimationMatrix *parent) {
    BlackPS2::AnimationMicro::Multiply4x4(matrix, matrix, parent);
}
static inline float Ee_Sqrt(float value) { float result; __asm__("sqrt.s %0,%1":"=f"(result):"f"(value));return result; }
static inline float Ee_Abs(float value) { float result; __asm__("abs.s %0,%1":"=f"(result):"f"(value));return result; }


static inline unsigned int& RetirementQueueIndex() {return AnimationRetire_Current;}

}
static inline unsigned char *AnimationSource_Offset(unsigned char *base, unsigned char *field) {
    return base + *(unsigned int *)field;
}


namespace Fragment345500 {




void func_00345500(void) __asm__("func_00345500") __attribute__((section(".text.func_00345500")));
void func_00345500(void) {

}
}

namespace Fragment345508 {




void func_00345508(void) __asm__("func_00345508") __attribute__((section(".text.func_00345508")));
void func_00345508(void) {

}
}

namespace ArmsAnimation {
int __attribute__((section(".text.func_00345510"))) Lifecycle::Initialize(void *owner, AnimationCollectionView *collection, int trackJoints) {
    AnimationInstanceView* instance=this;
    instance->next = 0;
    instance->time = instance->previousTime = 0.0f;
    for (int i = 11; i >= 0; --i) *(int *)((char *) instance+0x1d0+i*0xa0) = 0;
    AnimationInstance_Reset(instance, collection, owner);
    int banks = AnimationInstance_AllocateBanks(instance, AnimationAllocator_Get());
    AnimationInstance_ResetHistory(instance);
    if (!banks) {
        instance->selectedMatrices=instance->matrixBase=0;
        instance->auxiliary=0;
        return 0;
    }
    int eventCount = AnimationEvents_Count();
    if (eventCount * 8) {
        instance->eventStorage = (AnimationEventSlot *) AnimationAllocator_Allocate(eventCount * 8);
        for (int i = 0; i < eventCount; ++i) instance->eventStorage[i].cooldown = 0;
    } else instance->eventStorage = 0;
    for (int row = AnimationCollection_TransitionCount(collection)-1; row >= 0; --row) {
        int hash = *AnimationCollection_TransitionRow(collection, row);
        if (hash != -1 && !AnimationCollection_FindGraph(collection, hash)) AnimationCollection_RemoveTransition(collection, row);
    }
    instance->jointOverrides = AnimationAllocator_Allocate(0x78);
    AnimationMemory_Set(instance->jointOverrides, 0, 0x78);
    instance->skeletonIndex = 0;
    instance->jointOverrideCount = 0;
    instance->maximumBones = 0;
    float rootScale = instance->collection->rootScale;
    instance->unknown6c = 0;
    float inverseScale=BkEeDividePipelineGuarded(1.0f,rootScale);
    instance->rootScale=rootScale;
    instance->inverseRootScale=inverseScale;
    int i;
    if (instance->collection->skeletons) {
        for (i = 0; i < instance->collection->skeletonCount; ++i)
            if (instance->maximumBones < instance->collection->skeletons[i].boneCount)
                instance->maximumBones = (short) instance->collection->skeletons[i].boneCount;
        instance->selectedMatrices = instance->matrixBase = (AnimationMatrix *) AnimationAllocator_Allocate(instance->maximumBones << 7);
        /* The PS2 binary retains this empty per-bone walk. */
        for (i = 0; i < instance->collection->skeletonCount; ++i)
            for (int bone = 1; bone < instance->collection->skeletons[i].boneCount; ++bone) EmptyBone(instance->collection->skeletons[i].hierarchy + bone);
        if (trackJoints) {
            instance->flags |= 0x100000;
            instance->auxiliary = AnimationAllocator_Allocate((instance->maximumBones << 7)+0x140);
            if (instance->auxiliary) AnimationAuxiliary_Init(instance->auxiliary, instance->maximumBones);
        } else instance->auxiliary = 0;
        if (instance->matrixBase)
            for (i = 0; i < instance->maximumBones * 2; ++i) Matrix_Identity(instance->matrixBase+i);
    } else {
        instance->matrixBase = 0;
        instance->selectedMatrices = 0;
        instance->auxiliary = 0;
    }
    instance->flags |= 0x200;
    if (!instance->matrixBase) return 0;
    instance->jointCache = (AnimationBind **) AnimationAllocator_Allocate(instance->maximumBones * 4);
    AnimationMemory_Set(instance->jointCache, 0, instance->maximumBones * 4);
    if (instance->jointCache) {
        AnimationSkeleton *skeleton = AnimationInstance_Skeleton(instance);
        for (int i = 0; i < instance->maximumBones; ++i) {
            const AnimationHierarchy *entry = skeleton->hierarchy + i;
            if (entry->flags & 0xc) {
                instance->jointCache[i] = (AnimationBind *) AnimationAllocator_Allocate(0x50);
                AnimationBind *bind = instance->jointCache[i];
                AnimationMatrix matrix;
                AnimationMatrix_Load(skeleton->bindMatrices + i, &matrix);
                if (entry->parent >= 0) Matrix_MultiplyParent(&matrix, skeleton->bindMatrices + entry->parent);
                Matrix_Copy(&bind->matrix,&matrix);
                union {EeS128 native; float v[4];} scale __attribute__((aligned(16)));
                const float* m=matrix.v;
                scale.v[0]=((m[0]*m[0]+m[1]*m[1])+m[2]*m[2])+m[3]*m[3];
                scale.v[1]=((m[4]*m[4]+m[5]*m[5])+m[6]*m[6])+m[7]*m[7];
                scale.v[2]=((m[8]*m[8]+m[9]*m[9])+m[10]*m[10])+m[11]*m[11];
                if(scale.v[0]>0.0f)scale.v[0]=Ee_Sqrt(scale.v[0]);
                if(scale.v[1]>0.0f)scale.v[1]=Ee_Sqrt(scale.v[1]);
                if(scale.v[2]>0.0f)scale.v[2]=Ee_Sqrt(scale.v[2]);
                scale.v[3]=Ee_Abs(matrix.v[15]);
                Scale_Copy(bind->scale,&scale);
            }
        }
    }
    AnimationEvents_Clear(instance);
    instance->eventsActive = 0;
    return 1;
}
}

namespace ArmsAnimation {
void __attribute__((section(".text.func_00345AC8"))) Lifecycle::Retire() {
    AnimationInstanceView* instance=this;
    ReleaseBanksRecipe(instance, AnimationAllocator_Get());
    if (instance->jointCache) {
        for (int i = 0; i < instance->maximumBones; ++i) if (instance->jointCache[i]) AnimationAllocator_Free(instance->jointCache[i]);
        AnimationAllocator_Free(instance->jointCache);
    }
    if (instance->jointOverrides) {
        AnimationAllocator_Free(instance->jointOverrides);
        instance->jointOverrides = 0;
    }
    if (instance->eventStorage) AnimationAllocator_Free(instance->eventStorage);
    if (!(instance->flags & 0x80000)) {
        if (instance->auxiliary) {
            AnimationAllocator_Free(instance->auxiliary);
            instance->auxiliary = 0;
        }
        if (instance->matrixBase) {
            AnimationAllocator_Free(instance->matrixBase);
            instance->matrixBase = 0;
            instance->selectedMatrices = 0;
        }
    }
}
}

namespace Fragment345BC8 {

extern s32 func_00343F48(...) __asm__("func_00343F48");
extern s32 func_00343F90(...) __asm__("func_00343F90");
extern s32 func_00349C38(...) __asm__("func_00349C38");




void func_00345BC8(void *arg0) __asm__("func_00345BC8") __attribute__((section(".text.func_00345BC8")));
void func_00345BC8(void *arg0) {
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;

    if ((M2C_FIELD(arg0, s32 *, 0) & 0x480000) && (temp_2 = func_00343F48(M2C_FIELD(arg0, s16 *, 0x5E) << 7), M2C_FIELD(arg0, s32 *, 0x54) = temp_2, M2C_FIELD(arg0, s32 *, 0x50) = temp_2, (temp_2 != 0))) {
        temp_2_2 = M2C_FIELD(arg0, s32 *, 0) | 0x04000000;
        M2C_FIELD(arg0, s32 *, 0) = temp_2_2;
        if (temp_2_2 & 0x100000) {
            temp_2_3 = func_00343F48((M2C_FIELD(arg0, s16 *, 0x5E) << 7) + 0xC0);
            M2C_FIELD(arg0, s32 *, 0x68) = temp_2_3;
            if (temp_2_3 == 0) {
                func_00343F90(M2C_FIELD(arg0, s32 *, 0x54));
                return;
            }
            func_00349C38(temp_2_3, M2C_FIELD(arg0, s16 *, 0x5E));
            goto block_6;
        }
block_6:
        M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFF7FFFF);
    }
}
}

namespace Fragment345C78 {

extern s32 func_00343F48(...) __asm__("func_00343F48");
extern s32 func_00343F90(...) __asm__("func_00343F90");
extern s32 func_00349C38(...) __asm__("func_00349C38");




void func_00345C78(void *arg0) __asm__("func_00345C78") __attribute__((section(".text.func_00345C78")));
void func_00345C78(void *arg0)
{
  s32 temp_4;
  s32 temp_5;
  temp_5 = M2C_FIELD(arg0, s32 *, 0x68);
  M2C_FIELD(arg0, s32 *, 0) = (s32) (((M2C_FIELD(arg0, s32 *, 0)) | 0x80000) & 0xFFBFFFFF);
  if (temp_5 != 0)
  {
    func_00343F90(temp_5, temp_5);
    M2C_FIELD(arg0, s32 *, 0x68) = 0;
  }
  temp_4 = M2C_FIELD(arg0, s32 *, 0x54);
  if (temp_4 != 0)
  {
    func_00343F90(temp_4);
    M2C_FIELD(arg0, s32 *, 0x50) = (M2C_FIELD(arg0, s32 *, 0x54) = 0);
  }
}
}

void AnimationInstance_DrainRetired(void) ANIMATION_FUNCTION(00345CE8);
void AnimationInstance_DrainRetired(void) {
    int i = 0;
    while (i < AnimationRetire_Counts[AnimationRetire_Current]) {
        AnimationInstance_Destroy(AnimationRetire_Pending[AnimationRetire_Current][i]);
        ++i;
    }
    AnimationRetire_Counts[AnimationRetire_Current] = 0;
    AnimationRetire_Current ^= 1;
}

namespace ArmsAnimation {
void __attribute__((section(".text.func_00345DC0"))) Lifecycle::DeferRetire() {
    AnimationInstanceView* instance=this;
    if (!(instance->flags & 0x480000)) {
        instance->flags |= 0x400000;
        unsigned pending=RetirementQueueIndex() ^ 1;
        AnimationRetire_Pending[pending][AnimationRetire_Counts[pending]++]=instance;
    }
}
}

namespace ArmsAnimation {
void __attribute__((section(".text.func_00345E30"))) Lifecycle::ReleaseIfOwned(){if(!(flags&0x480000))AnimationInstance_Destroy(this);}
}

const char *AnimationInstance_GetName(AnimationInstanceView *instance) ANIMATION_FUNCTION(00345E60);
const char *AnimationInstance_GetName(AnimationInstanceView *instance) {
    const char *name;
    if (!instance)
        name = AnimationInstance_NoName;
    else
        name = AnimationCollection_GraphName(instance->graphHash, instance);
    return name;
}

namespace Fragment345E90 {

extern M2C_UNK * func_00343278(s32, s32) __asm__("func_00343278");
extern M2C_UNK D_003D1E30 __asm__("D_003D1E30");


M2C_UNK * func_00345E90(s32 arg0, void *arg1) __asm__("func_00345E90") __attribute__((section(".text.func_00345E90")));
M2C_UNK * func_00345E90(s32 arg0, void *arg1) {
    M2C_UNK *var_2;
    s32 temp_4;

    if ((arg1 == NULL) || (temp_4 = M2C_FIELD(arg1, s32 *, 4), (temp_4 == 0)) || (var_2 = func_00343278(temp_4, arg0), (var_2 == NULL))) {
        var_2 = &D_003D1E30;
    }
    return var_2;
}
}

int AnimationSource_Relocate(unsigned char *base) ANIMATION_FUNCTION(00345ED0);
int AnimationSource_Relocate(unsigned char *base) {
    unsigned int *locations = (unsigned int *)AnimationSource_Offset(base, base);
    while (*locations) {
        unsigned int location = *locations++;
        *(unsigned int *)(base + location) += (unsigned int)base;
    }
    locations = (unsigned int *)AnimationSource_Offset(base, base);
    *locations = 0;
    return 1;
}

namespace Fragment345F28 {

extern s32 func_00352A30(...) __asm__("func_00352A30");
extern s32 func_00343470(...) __asm__("func_00343470");


s32 func_00345F28(s32 arg0, void *arg1, s32 *arg2) __asm__("func_00345F28") __attribute__((section(".text.func_00345F28")));
s32 func_00345F28(s32 arg0, void *arg1, s32 *arg2) {
    s32 temp_2;

    if (arg1 != NULL) {
        if (M2C_FIELD(arg1, void **, 4) != NULL) {
            temp_2 = func_00352A30();
            if (func_00343470(M2C_FIELD(arg1, void **, 4), temp_2) != 0) {
                *arg2 = temp_2;
                return 1;
            }
            goto block_4;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return 0;
    }
block_4:
    return 0;
}
}

int AnimationSource_InstallTracks(AnimationSourceClip *clip) ANIMATION_FUNCTION(00345F98);
int AnimationSource_InstallTracks(AnimationSourceClip *clip) {
    if (clip->tracks)
        return 0;
    clip->tracks = clip->inlineTracks;
    return 1;
}

namespace Fragment345FB8 {


s32 func_00345FB8(void *arg0) __asm__("func_00345FB8") __attribute__((section(".text.func_00345FB8")));
s32 func_00345FB8(void *arg0)
{
  if ((M2C_FIELD(arg0, s32 *, 0x20)) != 0)
  {
    if (arg0)
    {
      M2C_FIELD(arg0, s32 *, 0x20) = 0;
      return 1;
    }
    else
    {
      M2C_FIELD(arg0, s32 *, 0x20) = 0;
      return 1;
    }
  }
  return 0;
}
}

namespace ArmsAnimation {
void __attribute__((section(".text.func_00345FD8"))) SourceBank::Import(AnimationCollectionView* collection) {
    AnimationSourceBank* bank=this;
    int i=0;
    for (; i < bank->namedGraphCount; ++i) {
        AnimationNamedGraph *row = bank->namedGraphs[i];
        AnimationCollection_AddNamed(collection, row->name, row->graph);
    }
    i=0;
    for (; i < bank->clipCount; ++i) {
        AnimationSourceClip *clip = bank->clips[i];
        AnimationCollection_AddClip(collection, clip->hash, clip);
        if (!InstallWithContext(bank->clips[i],this,collection))
            break;
    }
    i=0;
    for (; i < bank->transitionCount; ++i) AnimationCollection_AddTransition(collection, bank->transitions[i]);
}
}

namespace ArmsAnimation {
void __attribute__((section(".text.func_003460E8"))) SourceBank::Remove(AnimationCollectionView* collection) {
    AnimationSourceBank* bank=this;
    for (int i = 0; i < bank->clipCount; ++i) AnimationCollection_RemoveClip(collection, bank->clips[i]->hash);
    for (int i = 0; i < bank->namedGraphCount; ++i) AnimationCollection_RemoveNamed(collection, bank->namedGraphs[i]->name);
    for (int i = 0; i < bank->clipCount; ++i) if (!ClearTracksWithContext(bank->clips[i],this,collection)) break;
}
}

// Fixed PS2 source-name storage and the two deferred-retirement queues.
const char AnimationInstance_NoName[24]
    __attribute__((section(".data.animation_null_name"),aligned(8))) = "null animViewInfo";
extern const char D_003D1E30[8];
const char D_003D1E30[8]
    __attribute__((section(".data.animation_none_name"),aligned(8))) = "none";
unsigned int AnimationRetire_Current __attribute__((aligned(8)));
int AnimationRetire_Counts[2] __attribute__((aligned(8)));
AnimationInstanceView* AnimationRetire_Pending[2][128] __attribute__((aligned(8)));
