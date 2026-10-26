#include "include_asm.h"
#include "ps2/prelude.h"
#include "animation/index_tree.h"
#include "animation/collection_indices.h"

extern "C" void func_003950F8(AnimationIndex*);
extern "C" void func_00107D48(void*);
extern "C" void func_00395130(AnimationIndex* self, int flags) {
    func_003950F8(self);
    AnimationIndexTagView* storage = &self->tagStorage;
    self->allocator->Release();
    if (storage->tags)
        storage->allocator->Free(storage->tags, 0);
    storage->allocator->Release();
    if (flags & 1)
        func_00107D48(self);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/inline/linkonce_395130", func_003951D8);
extern "C" void func_00395370(Recovered_AnimationIndexTree* tree, Recovered_AnimationIndexNode* node) {
    if (node->left)
        func_00395370(tree, node->left);
    if (node->right)
        func_00395370(tree, node->right);
    tree->allocator->table->release((char*)tree->allocator + tree->allocator->table->adjust, node, 0);
    --tree->count;
}
