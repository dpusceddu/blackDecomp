#include "mod/arms/lifecycle.hpp"
namespace ArmsAnimation {
// Unmatched: Initialize matrix-copy/empty-loop lifetimes and register allocation differ.
void Lifecycle::Retire() {
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
// Unmatched: DeferRetire deferred-array index allocation differs.
void SourceBank::Import(AnimationCollectionView* collection) {
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
void SourceBank::Remove(AnimationCollectionView* collection) {
    AnimationSourceBank* bank=this;
    for (int i = 0; i < bank->clipCount; ++i) AnimationCollection_RemoveClip(collection, bank->clips[i]->hash);
    for (int i = 0; i < bank->namedGraphCount; ++i) AnimationCollection_RemoveNamed(collection, bank->namedGraphs[i]->name);
    for (int i = 0; i < bank->clipCount; ++i) if (!ClearTracksWithContext(bank->clips[i],this,collection)) break;
}
void Lifecycle::ReleaseIfOwned(){if(!(flags&0x480000))AnimationInstance_Destroy(this);}
}
