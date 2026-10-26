#include "include_asm.h"
#include "ps2/prelude.h"
#include "animation/index_tree.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/inline/linkonce_394e90", func_00394E90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/inline/linkonce_394e90", func_00394EE0);
void func_00395078(Recovered_AnimationIndexTree* tree, Recovered_AnimationIndexNode* node) {
    if (node->left)
        func_00395078(tree, node->left);
    if (node->right)
        func_00395078(tree, node->right);
    tree->allocator->table->release((char*)tree->allocator + tree->allocator->table->adjust, node, 0);
    --tree->count;
}
