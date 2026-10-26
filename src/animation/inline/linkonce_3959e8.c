#include "include_asm.h"
#include "ps2/prelude.h"

#ifdef NON_MATCHING
/* Partial views; complete object extents and allocator/tag semantics are UNVERIFIED. */
typedef struct Recovered_AnimationInsertNode Recovered_AnimationInsertNode;
typedef struct Recovered_AnimationAllocator Recovered_AnimationAllocator;
typedef struct Recovered_AnimationAllocationVtable {
    char unknown[8];
    short adjust;
    short pad;
    void* (*allocate)(void*, int, const void*);
} Recovered_AnimationAllocationVtable;
struct Recovered_AnimationAllocator {
    Recovered_AnimationAllocationVtable* vtable;
};
struct Recovered_AnimationInsertNode {
    int height;
    Recovered_AnimationInsertNode *parent, *left, *right;
    int key;
    void* value;
};
typedef struct Recovered_AnimationInsertTree {
    Recovered_AnimationInsertNode* root;
    int count;
    Recovered_AnimationAllocator* allocator;
    const void* tags;
} Recovered_AnimationInsertTree;
extern char D_0046C608;
extern void func_003957C8(Recovered_AnimationInsertTree*, Recovered_AnimationInsertNode**);
extern void func_00395890(Recovered_AnimationInsertTree*, Recovered_AnimationInsertNode**);
extern void func_00395958(Recovered_AnimationInsertTree*, Recovered_AnimationInsertNode**);
extern void func_003959A0(Recovered_AnimationInsertTree*, Recovered_AnimationInsertNode**);
// Unmatched: allocation scheduling and branch/register lifetimes differ.
Recovered_AnimationInsertNode* func_003959E8(Recovered_AnimationInsertTree* tree, Recovered_AnimationInsertNode** slot,
                                             const int* key, void* const* value) {
    Recovered_AnimationInsertNode* result;
    if (!*slot) {
        Recovered_AnimationAllocator* allocator = tree->allocator;
        Recovered_AnimationAllocationVtable* vtable = allocator->vtable;
        const void* tags = tree->tags;
        if (!tags) tags = &D_0046C608;
        result = vtable->allocate((char*)allocator + vtable->adjust, 24, tags);
        if (result) {
            result->key = *key;
            result->value = *value;
            result->height = 0;
            result->parent = 0;
            result->left = 0;
            result->right = 0;
        }
        *slot = result;
        ++tree->count;
        return result;
    }
    if (*key < (*slot)->key) {
        result = func_003959E8(tree, &(*slot)->left, key, value);
        if (!result->parent) result->parent = *slot;
        {
            Recovered_AnimationInsertNode* node = *slot;
            int lh = node->left ? node->left->height : -1;
            int rh = node->right ? node->right->height : -1;
            if (rh == lh - 2) {
                if (*key < node->left->key)
                    func_003957C8(tree, slot);
                else
                    func_00395958(tree, slot);
                return result;
            }
        }
    } else if ((*slot)->key < *key) {
        result = func_003959E8(tree, &(*slot)->right, key, value);
        if (!result->parent) result->parent = *slot;
        {
            Recovered_AnimationInsertNode* node = *slot;
            int rh = node->right ? node->right->height : -1;
            int lh = node->left ? node->left->height : -1;
            if (lh == rh - 2) {
                if (node->right->key < *key)
                    func_00395890(tree, slot);
                else
                    func_003959A0(tree, slot);
                return result;
            }
        }
    } else {
        (*slot)->value = *value;
        return *slot;
    }
    {
        Recovered_AnimationInsertNode* node = *slot;
        int lh = node->left ? node->left->height : -1;
        int rh = node->right ? node->right->height : -1;
        node->height = (lh < rh ? rh : lh) + 1;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/inline/linkonce_3959e8", func_003959E8);
#endif
