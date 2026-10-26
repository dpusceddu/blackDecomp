#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/inline/linkonce_395720", func_00395720);
typedef struct Recovered_AnimationIndexNode Recovered_AnimationIndexNode;
struct Recovered_AnimationIndexNode {
    int height;
    Recovered_AnimationIndexNode *parent, *left, *right;
};
typedef struct {
    Recovered_AnimationIndexNode* root;
} Recovered_AnimationIndexTree;
/* Rotate the left child up, updating both heights and the parent link. */
void func_003957C8(Recovered_AnimationIndexTree* tree, Recovered_AnimationIndexNode** slot) {
    Recovered_AnimationIndexNode* left = (*slot)->left;
    Recovered_AnimationIndexNode* parent = (*slot)->parent;
    (*slot)->left = left->right;
    if (left->right) left->right->parent = *slot;
    left->right = *slot;
    (*slot)->parent = left;
    {
        Recovered_AnimationIndexNode* node = *slot;
        int lh = node->left ? node->left->height : -1;
        int rh = node->right ? node->right->height : -1;
        node->height = (lh < rh ? rh : lh) + 1;
    }
    {
        int lh = left->left ? left->left->height : -1;
        int rh = *slot ? (*slot)->height : -1;
        left->parent = parent;
        left->height = (lh < rh ? rh : lh) + 1;
    }
    if (parent) {
        if (parent->left == *slot)
            parent->left = left;
        else
            parent->right = left;
    } else
        tree->root = left;
    *slot = left;
}
