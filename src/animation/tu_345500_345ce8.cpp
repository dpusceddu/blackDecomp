#include "animation/graph.h"
#include "animation/instance_state.h"
#include "ps2/vu0_micro.hpp"

/* Names describe the recovered PS2 behavior. */
static inline unsigned char *AnimationSource_Offset(unsigned char *base, unsigned char *field) {
    return base + *(unsigned int *)field;
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

const char *AnimationInstance_GetName(AnimationInstanceView *instance) ANIMATION_FUNCTION(00345E60);
const char *AnimationInstance_GetName(AnimationInstanceView *instance) {
    const char *name;
    if (!instance)
        name = AnimationInstance_NoName;
    else
        name = AnimationCollection_GraphName(instance->graphHash, instance);
    return name;
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

int AnimationSource_InstallTracks(AnimationSourceClip *clip) ANIMATION_FUNCTION(00345F98);
int AnimationSource_InstallTracks(AnimationSourceClip *clip) {
    if (clip->tracks)
        return 0;
    clip->tracks = clip->inlineTracks;
    return 1;
}

#ifdef NONMATCHING

/* Irreducible EE matrix primitives within the recovered initialization. */
static inline void Matrix_Identity(AnimationMatrix *matrix) {
    __asm__ volatile("pand $8,$0,$0\n\tlui $8,0x3f80\n\tsq $8,0x0(%0)\n\tpextlw $8,$8,$0\n\tsq $8,0x10(%0)\n\tpextlw $9,$0,$8\n\tsq $9,0x20(%0)\n\tpextlw $9,$8,$0\n\tsq $9,0x30(%0)": :"r"(matrix):"$8","$9","memory");
}
static inline void Matrix_MultiplyParent(AnimationMatrix *matrix,const AnimationMatrix *parent) {
    BlackPS2::AnimationMicro::Multiply4x4(matrix, matrix, parent);
}
static inline float Ee_Sqrt(float value) { float result; __asm__("sqrt.s %0,%1":"=f"(result):"f"(value));return result; }
static inline float Ee_Abs(float value) { float result; __asm__("abs.s %0,%1":"=f"(result):"f"(value));return result; }

// Unmatched: EE matrix primitives and temporary/register allocation; 206 differing words.
int AnimationInstance_Initialize(AnimationInstanceView *instance, void *owner, AnimationCollectionView *collection, int trackJoints) __asm__("func_00345510");
int AnimationInstance_Initialize(AnimationInstanceView *instance, void *owner, AnimationCollectionView *collection, int trackJoints) {
    instance->next = 0;
    instance->time = instance->previousTime = 0.0f;
    for (int i = 11; i >= 0; --i) *(int *)((char *) instance+0x1d0+i*0xa0) = 0;
    AnimationInstance_Reset(instance, collection, owner);
    int banks = AnimationInstance_AllocateBanks(instance, AnimationAllocator_Get());
    AnimationInstance_ResetHistory(instance);
    if (!banks) {
        instance->auxiliary = 0;
        instance->matrixBase = 0;
        instance->selectedMatrices = 0;
        return 0;
    }
    int eventCount = AnimationEvents_Count();
    int bytes = eventCount * 8;
    if (bytes) {
        instance->eventStorage = (AnimationEventSlot *) AnimationAllocator_Allocate(bytes);
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
    instance->unknown6c = 0;
    instance->rootScale = instance->collection->rootScale;
    instance->inverseRootScale = 1.0f / instance->collection->rootScale;
    if (instance->collection->skeletons) {
        for (int i = 0; i < instance->collection->skeletonCount; ++i)
            if (instance->maximumBones < instance->collection->skeletons[i].boneCount)
                instance->maximumBones = (short) instance->collection->skeletons[i].boneCount;
        instance->selectedMatrices = instance->matrixBase = (AnimationMatrix *) AnimationAllocator_Allocate(instance->maximumBones << 7);
        /* The PS2 binary retains this empty per-bone walk. */
        for (int i = 0; i < instance->collection->skeletonCount; ++i)
            for (int bone = 1; bone < instance->collection->skeletons[i].boneCount; ++bone) { }
        if (trackJoints) {
            instance->flags |= 0x100000;
            instance->auxiliary = AnimationAllocator_Allocate((instance->maximumBones << 7)+0x140);
            if (instance->auxiliary) AnimationAuxiliary_Init(instance->auxiliary, instance->maximumBones);
        } else instance->auxiliary = 0;
        if (instance->matrixBase)
            for (int i = 0; i < instance->maximumBones * 2; ++i) Matrix_Identity(instance->matrixBase+i);
    } else {
        instance->matrixBase = 0;
        instance->selectedMatrices = 0;
        instance->auxiliary = 0;
    }
    instance->flags |= 0x200;
    if (!instance->matrixBase) return 0;
    bytes = instance->maximumBones * 4;
    instance->jointCache = (AnimationBind **) AnimationAllocator_Allocate(bytes);
    AnimationMemory_Set(instance->jointCache, 0, bytes);
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
                bind->matrix = matrix;
                float scale[4] __attribute__((aligned(16)));
                for (int row = 0; row < 3; ++row) {
                    float *v = matrix.v + row*4;
                    scale[row] = ((v[0]*v[0]+v[1]*v[1])+v[2]*v[2])+v[3]*v[3];
                    if (scale[row] > 0.0f) scale[row] = Ee_Sqrt(scale[row]);
                }
                scale[3] = Ee_Abs(matrix.v[15]);
                for (int row = 0; row < 4; ++row) bind->scale[row] = scale[row];
            }
        }
    }
    AnimationEvents_Clear(instance);
    instance->eventsActive = 0;
    return 1;
}

// Unmatched: retirement register allocation; two differing words.
void AnimationInstance_Retire(AnimationInstanceView *instance) __asm__("func_00345AC8");
void AnimationInstance_Retire(AnimationInstanceView *instance) {
    AnimationInstance_ReleaseBanks(instance, AnimationAllocator_Get());
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

// Unmatched: deferred-list index allocation and scheduling.
void AnimationInstance_DeferRetire(AnimationInstanceView *instance) __asm__("func_00345DC0");
void AnimationInstance_DeferRetire(AnimationInstanceView *instance) {
    if (!(instance->flags & 0x480000)) {
        instance->flags |= 0x400000;
        unsigned int pending = AnimationRetire_Current ^ 1;
        AnimationRetire_Pending[pending][AnimationRetire_Counts[pending]++] = instance;
    }
}

// Unmatched: collection iteration and callback argument scheduling.
void AnimationSource_Import(AnimationSourceBank *bank, AnimationCollectionView *collection) __asm__("func_00345FD8");
void AnimationSource_Import(AnimationSourceBank *bank, AnimationCollectionView *collection) {
    for (int i = 0; i < bank->namedGraphCount; ++i) {
        AnimationNamedGraph *row = bank->namedGraphs[i];
        AnimationCollection_AddNamed(collection, row->name, row->graph);
    }
    for (int i = 0; i < bank->clipCount; ++i) {
        AnimationSourceClip *clip = bank->clips[i];
        AnimationCollection_AddClip(collection, clip->hash, clip);
        if (!AnimationSource_InstallTracks(bank->clips[i]))
            break;
    }
    for (int i = 0; i < bank->transitionCount; ++i) AnimationCollection_AddTransition(collection, bank->transitions[i]);
}

// Unmatched: collection iteration register allocation; four differing words.
void AnimationSource_Remove(AnimationSourceBank *bank, AnimationCollectionView *collection) __asm__("func_003460E8");
void AnimationSource_Remove(AnimationSourceBank *bank, AnimationCollectionView *collection) {
    for (int i = 0; i < bank->clipCount; ++i) AnimationCollection_RemoveClip(collection, bank->clips[i]->hash);
    for (int i = 0; i < bank->namedGraphCount; ++i) AnimationCollection_RemoveNamed(collection, bank->namedGraphs[i]->name);
    for (int i = 0; i < bank->clipCount; ++i) if (!AnimationSource_ClearTracks(bank->clips[i])) break;
}

#endif
