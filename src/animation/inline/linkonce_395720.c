#include "include_asm.h"
#include "ps2/prelude.h"
#include "animation/index_tree.h"
#include "animation/collection_indices.h"

extern "C" void func_003956E8(AnimationIndex*);
extern "C" void func_00107D48(void*);
extern "C" void func_00395720(AnimationIndex* self, int flags) {
    func_003956E8(self);
    AnimationIndexTagView* storage = &self->tagStorage;
    self->allocator->Release();
    if (storage->tags)
        storage->allocator->Free(storage->tags, 0);
    storage->allocator->Release();
    if (flags & 1)
        func_00107D48(self);
}
extern "C" void func_003957C8(Recovered_AnimationIndexTree* tree, Recovered_AnimationIndexNode** slot) {
    AnimationIndex_RotateRight(tree, slot);
}
