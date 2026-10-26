#ifndef ANIMATION_INDEX_TREE_H
#define ANIMATION_INDEX_TREE_H

typedef struct Recovered_AnimationIndexNode Recovered_AnimationIndexNode;
struct Recovered_AnimationIndexNode {
    int height;
    Recovered_AnimationIndexNode *parent, *left, *right;
};
typedef struct Recovered_AnimationIndexAllocatorVtable {
    char unk_00[16];
    short adjust;
    short unk_12;
    void (*release)(void*, Recovered_AnimationIndexNode*, int);
} Recovered_AnimationIndexAllocatorVtable;
typedef struct Recovered_AnimationIndexAllocator {
    Recovered_AnimationIndexAllocatorVtable* table;
} Recovered_AnimationIndexAllocator;
typedef struct {
    Recovered_AnimationIndexNode* root;
    int count;
    Recovered_AnimationIndexAllocator* allocator;
} Recovered_AnimationIndexTree;
/* Only the tree count, allocator dispatch and node links used here are confirmed; other fields are UNVERIFIED. */
/* Rotate the left child up, updating both heights and the parent link. */
static inline void AnimationIndex_RotateRight(Recovered_AnimationIndexTree* tree, Recovered_AnimationIndexNode** slot) {
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

#endif
