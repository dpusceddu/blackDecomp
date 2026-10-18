#ifndef BLACK_ANIMATION_INSTANCE_STATE_H
#define BLACK_ANIMATION_INSTANCE_STATE_H

/* Inferred names; offsets below are checked against PS2 initialization and retirement. */
struct AnimationMatrix { float v[16]; } __attribute__((aligned(16)));
struct AnimationBind { AnimationMatrix matrix; float scale[4]; } __attribute__((aligned(16)));
struct AnimationHierarchy { int parent; unsigned int flags; };
struct AnimationSkeleton {
    int boneCount;
    AnimationHierarchy *hierarchy;
    AnimationMatrix *bindMatrices;
    void *nameMap;
};
struct AnimationCollectionView {
    unsigned char unknown00[0x18];
    int skeletonCount;
    AnimationSkeleton *skeletons;
    unsigned char unknown20[0x10];
    float rootScale;
};
struct AnimationEventSlot { int cooldown, unknown04; };
struct AnimationInstanceView {
    unsigned int flags;
    AnimationCollectionView *collection;
    short skeletonIndex;
    unsigned char unknown0a[6];
    unsigned int graphHash;
    unsigned char unknown14[0xc];
    float time, previousTime;
    unsigned char unknown28[0x28];
    AnimationMatrix *selectedMatrices, *matrixBase;
    void *jointOverrides;
    short jointOverrideCount, maximumBones;
    float rootScale, inverseRootScale;
    void *auxiliary;
    short unknown6c;
    unsigned char unknown6e[2];
    AnimationBind **jointCache;
    unsigned char unknown74[0x9ac - 0x74];
    AnimationInstanceView *next;
    AnimationEventSlot *eventStorage;
    unsigned char unknown9b4[8];
    unsigned char eventsActive;
};
struct AnimationSourceClip {
    unsigned int hash;
    unsigned char unknown04[0x1c];
    void *tracks;
    unsigned char unknown24[0xc];
    unsigned char inlineTracks[1];
};
struct AnimationNamedGraph { const char *name; void *graph; };
struct AnimationSourceBank {
    unsigned char unknown00[0x24];
    int namedGraphCount;
    AnimationNamedGraph **namedGraphs;
    int clipCount;
    AnimationSourceClip **clips;
    int transitionCount;
    void **transitions;
};
extern void *AnimationAllocator_Get(void) __asm__("func_00343F38");
extern void *AnimationAllocator_Allocate(int) __asm__("func_00343F48");
extern void AnimationAllocator_Free(void *) __asm__("func_00343F90");
extern void *AnimationMemory_Set(void *, int, unsigned int) __asm__("func_0035C6EC");
extern void AnimationInstance_Reset(AnimationInstanceView *, AnimationCollectionView *, void *) __asm__("func_0034EAE0");
extern int AnimationInstance_AllocateBanks(AnimationInstanceView *, void *) __asm__("func_0034EB88");
extern void AnimationInstance_ReleaseBanks(AnimationInstanceView *, void *) __asm__("func_0034ECD8");
extern void AnimationInstance_ResetHistory(AnimationInstanceView *) __asm__("func_00350140");
extern int AnimationEvents_Count(void) __asm__("func_00348A28");
extern void AnimationEvents_Clear(AnimationInstanceView *) __asm__("func_00347A28");
extern int AnimationCollection_TransitionCount(AnimationCollectionView *) __asm__("func_00343508");
extern int *AnimationCollection_TransitionRow(AnimationCollectionView *, int) __asm__("func_003433C8");
extern void *AnimationCollection_FindGraph(AnimationCollectionView *, int) __asm__("func_003432E8");
extern void AnimationCollection_RemoveTransition(AnimationCollectionView *, int) __asm__("func_00343148");
extern void AnimationAuxiliary_Init(void *, int) __asm__("func_00349C38");
extern AnimationSkeleton *AnimationInstance_Skeleton(AnimationInstanceView *) __asm__("func_003489A8");
extern AnimationMatrix *AnimationMatrix_Load(const AnimationMatrix *, AnimationMatrix *) __asm__("func_00352770");
extern void AnimationInstance_Destroy(AnimationInstanceView *) __asm__("func_00345C78");
extern unsigned int AnimationRetire_Current __asm__("D_0045ECB0");
extern int AnimationRetire_Counts[2] __asm__("D_0045ECB8");
extern AnimationInstanceView *AnimationRetire_Pending[2][128] __asm__("D_0045ECC0");
extern const char AnimationInstance_NoName[] __asm__("D_003D1E18");
extern const char *AnimationCollection_GraphName(unsigned int, AnimationInstanceView *) __asm__("func_00345E90");
extern void AnimationCollection_AddNamed(AnimationCollectionView *, const char *, void *) __asm__("func_00342ED8");
extern void AnimationCollection_AddClip(AnimationCollectionView *, unsigned int, AnimationSourceClip *) __asm__("func_00342FA8");
extern void AnimationCollection_AddTransition(AnimationCollectionView *, void *) __asm__("func_00343030");
extern void AnimationCollection_RemoveClip(AnimationCollectionView *, unsigned int) __asm__("func_00343120");
extern void AnimationCollection_RemoveNamed(AnimationCollectionView *, const char *) __asm__("func_003430D8");
extern int AnimationSource_ClearTracks(AnimationSourceClip *) __asm__("func_00345FB8");
#endif
