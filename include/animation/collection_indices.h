#ifndef BLACK_ANIMATION_COLLECTION_INDICES_H
#define BLACK_ANIMATION_COLLECTION_INDICES_H

/* Container names are inferred; field positions follow the PS2 container users. */
struct AnimationAllocationTag {
    int first, second;
    AnimationAllocationTag *next;
    AnimationAllocationTag() : first(0), second(0), next(0) {}
};
struct AnimationContainerAllocator {
    virtual void *Allocate(int, const AnimationAllocationTag *) = 0;
    virtual void Free(void *, const AnimationAllocationTag *) = 0;
    virtual void AddRef() = 0;
    virtual void Release() = 0;
};
struct AnimationIndexNode {
    int height;
    AnimationIndexNode *parent, *left, *right;
    int key;
    void *value;
};
struct AnimationIndexIterator {
    AnimationIndexNode *node;
    AnimationIndexIterator(AnimationIndexNode *value = 0) : node(value) {}
    int operator!=(const AnimationIndexIterator &other) const { return node != other.node; }
    AnimationIndexIterator &operator++() {
        if (node) {
            if (node->right) {
                node = node->right;
                while (node->left)
                    node = node->left;
            } else {
                AnimationIndexNode *parent = node->parent;
                if (!parent)
                    node = 0;
                else if (parent->left == node)
                    node = parent;
                else {
                    while (parent && parent->key < node->key)
                        parent = parent->parent;
                    node = parent;
                }
            }
        }
        return *this;
    }
};
struct AnimationIndex {
    AnimationIndexNode *root;
    int count;
    AnimationContainerAllocator *allocator;
    void *tags;
    AnimationContainerAllocator *tagAllocator;
    AnimationIndexIterator Find(const int *key) const {
        AnimationIndexNode *current = root, *found = 0;
        while (current && !found) {
            if (*key < current->key)
                current = current->left;
            else if (current->key < *key)
                current = current->right;
            else
                found = current;
        }
        return AnimationIndexIterator(found);
    }
    AnimationIndexIterator Begin() const {
        AnimationIndexNode *current = root;
        if (current)
            while (current->left)
                current = current->left;
        return AnimationIndexIterator(current);
    }
    AnimationIndexIterator End() const { return AnimationIndexIterator(); }
};
struct AnimationTransitionNode {
    void *value;
    AnimationTransitionNode *next, *previous;
};
struct AnimationTransitionIterator {
    AnimationTransitionNode *node;
    AnimationTransitionIterator(AnimationTransitionNode *value = 0) : node(value) {}
    AnimationTransitionIterator &operator++() { node = node ? node->next : 0; return *this; }
    int operator!=(const AnimationTransitionIterator &other) const { return node != other.node; }
};
struct AnimationTransitionList {
    AnimationTransitionNode *head, *tail;
    int count;
    AnimationContainerAllocator *allocator;
    AnimationAllocationTag *tags;
    AnimationContainerAllocator *tagAllocator;
};
struct AnimationCollectionIndices {
    unsigned char unknown00[0x18];
    int skeletonCount;
    void *skeletons;
    AnimationTransitionList *transitions;
    AnimationIndex *graphs, *graphNames, *clips;
};
extern unsigned int AnimationCollection_Hash(const char *) __asm__("func_00342A60");
extern void AnimationIndex_RemoveName(AnimationIndex *, const int *) __asm__("func_00396548");
extern void AnimationIndex_RemoveGraph(AnimationIndex *, const int *) __asm__("func_00396858");
extern void AnimationIndex_RemoveClip(AnimationIndex *, const int *) __asm__("func_00396B68");
extern AnimationIndexIterator AnimationIndex_InsertName(AnimationIndex *, const int *, const char *const *) __asm__("func_00395C18");
extern AnimationIndexIterator AnimationIndex_InsertGraph(AnimationIndex *, const int *, void *const *) __asm__("func_00396098");
extern AnimationIndexIterator AnimationIndex_InsertClip(AnimationIndex *, const int *, void *const *) __asm__("func_00396518");
extern int AnimationCollection_CountTransitions(AnimationCollectionIndices *) __asm__("func_00343508");
extern void *AnimationCollection_GetTransition(AnimationCollectionIndices *, int) __asm__("func_003433C8");
extern const AnimationAllocationTag AnimationContainer_DefaultTag __asm__("D_0046C608");
extern void AnimationIndex_DestroyGraph(AnimationIndex *, int) __asm__("func_00395130");
extern void AnimationIndex_DestroyName(AnimationIndex *, int) __asm__("func_00395428");
extern void AnimationIndex_DestroyClip(AnimationIndex *, int) __asm__("func_00395720");
extern void AnimationIndex_InitGraph(AnimationIndex *, AnimationContainerAllocator *, const AnimationAllocationTag *) __asm__("func_00394EE0");
extern void AnimationIndex_InitName(AnimationIndex *, AnimationContainerAllocator *, const AnimationAllocationTag *) __asm__("func_003951D8");
extern void AnimationIndex_InitClip(AnimationIndex *, AnimationContainerAllocator *, const AnimationAllocationTag *) __asm__("func_003954D0");
#endif
