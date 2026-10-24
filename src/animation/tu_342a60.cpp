#include "include_asm.h"

#include "animation/graph.h"
#include "animation/collection_indices.h"

/* Names describe the recovered PS2 container operations. */
extern unsigned int AnimationString_Hash(const char *) __asm__("func_00352A30");

unsigned int AnimationCollection_Hash(const char *name) ANIMATION_FUNCTION(00342A60);

unsigned int AnimationCollection_Hash(const char *name) {
    return AnimationString_Hash(name);
}

void AnimationCollection_RemoveNamedGraph(AnimationCollectionIndices *collection, const char *name)
    ANIMATION_FUNCTION(003430D8);
void AnimationCollection_RemoveNamedGraph(AnimationCollectionIndices *collection, const char *name) {
    int hash = AnimationCollection_Hash(name);
    AnimationIndex_RemoveName(collection->graphNames, &hash);
    AnimationIndex_RemoveGraph(collection->graphs, &hash);
}

void AnimationCollection_RemoveClipValue(AnimationCollectionIndices *collection, int hash)
    ANIMATION_FUNCTION(00343120);
void AnimationCollection_RemoveClipValue(AnimationCollectionIndices *collection, int hash) {
    AnimationIndex_RemoveClip(collection->clips, &hash);
}

int AnimationCollection_NameCount(AnimationCollectionIndices *collection) ANIMATION_FUNCTION(003434D8);
int AnimationCollection_NameCount(AnimationCollectionIndices *collection) {
    return collection->graphNames->count;
}

int AnimationCollection_GraphCount(AnimationCollectionIndices *collection) ANIMATION_FUNCTION(003434E8);
int AnimationCollection_GraphCount(AnimationCollectionIndices *collection) {
    return collection->graphs->count;
}

int AnimationCollection_ClipCount(AnimationCollectionIndices *collection) ANIMATION_FUNCTION(003434F8);
int AnimationCollection_ClipCount(AnimationCollectionIndices *collection) {
    return collection->clips->count;
}

int AnimationCollection_CountTransitions(AnimationCollectionIndices *collection) ANIMATION_FUNCTION(00343508);
int AnimationCollection_CountTransitions(AnimationCollectionIndices *collection) {
    return collection->transitions->count;
}

#ifdef NONMATCHING
static inline AnimationAllocationTag *CloneTags(const AnimationAllocationTag *source, AnimationContainerAllocator *allocator) {
    if (!source->first && !source->next)return 0;
    int count = 0;
    const AnimationAllocationTag *current = source;
    do {
        current = current->next;
        ++count;
    }
    while (current);
    AnimationAllocationTag *copy=(AnimationAllocationTag *)allocator->Allocate(count*12, &AnimationAllocationTag());
    AnimationAllocationTag *out = copy;
    current = source;
    do {
        *out = *current;
        current = current->next;
        if (current) {
            out->next = out+1;
            ++out;
        }
        else out->next = 0;
    }
    while (current);
    return copy;
}
struct AnimationTagStorage {
    AnimationAllocationTag *tags;
    AnimationContainerAllocator *allocator;
    AnimationTagStorage(const AnimationAllocationTag *source, AnimationContainerAllocator *owner):allocator(owner) {
        owner->AddRef();
        tags = CloneTags(source, owner);
    }
    ~AnimationTagStorage() {
        if (tags)allocator->Free(tags, 0);
        allocator->Release();
    }
};
struct AnimationGraphIndex:AnimationIndex {
    AnimationGraphIndex(AnimationContainerAllocator *, const AnimationAllocationTag *) __asm__("func_00394EE0");
};
struct AnimationNameIndex:AnimationIndex {
    AnimationNameIndex(AnimationContainerAllocator *, const AnimationAllocationTag *) __asm__("func_003951D8");
};
struct AnimationClipIndex:AnimationIndex {
    AnimationClipIndex(AnimationContainerAllocator *, const AnimationAllocationTag *) __asm__("func_003954D0");
};
struct AnimationTransitionContainer {
    AnimationTransitionNode *head, *tail;
    int count;
    AnimationContainerAllocator *allocator;
    AnimationTagStorage tags;
    AnimationTransitionContainer(AnimationContainerAllocator *owner, const AnimationAllocationTag *source):tags(source, owner) {
        allocator = owner;
        owner->AddRef();
        tail = head = 0;
        count = 0;
    }
};
inline void *operator new(unsigned int size, AnimationContainerAllocator *allocator) {
    return allocator->Allocate(size, &AnimationAllocationTag());
}
inline void operator delete(void *block, AnimationContainerAllocator *allocator) {
    allocator->Free(block, 0);
}
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
void AnimationCollection_CreateIndices(AnimationCollectionIndices *collection, AnimationContainerAllocator *allocator) __asm__("func_00342A80");
void AnimationCollection_CreateIndices(AnimationCollectionIndices *collection, AnimationContainerAllocator *allocator) {
    collection->graphs = new(allocator)AnimationGraphIndex(allocator, &AnimationAllocationTag());
    collection->graphNames = new(allocator)AnimationNameIndex(allocator, &AnimationAllocationTag());
    collection->clips = new(allocator)AnimationClipIndex(allocator, &AnimationAllocationTag());
    collection->transitions=(AnimationTransitionList *)new(allocator)AnimationTransitionContainer(allocator, &AnimationAllocationTag());
}
// Unmatched: allocator virtual-call scheduling and list/tag teardown allocation.
void AnimationCollection_DestroyIndices(AnimationCollectionIndices *collection, AnimationContainerAllocator *allocator) __asm__("func_00342D48");
void AnimationCollection_DestroyIndices(AnimationCollectionIndices *collection, AnimationContainerAllocator *allocator) {
    AnimationIndex_DestroyGraph(collection->graphs, 2);
    AnimationIndex_DestroyName(collection->graphNames, 2);
    AnimationIndex_DestroyClip(collection->clips, 2);
    AnimationTransitionList *list = collection->transitions;
    while (list->head) {
        AnimationTransitionNode *node = list->head;
        list->tail = node->next;
        list->allocator->Free(node, 0);
        list->head = list->tail;
    }
    list->tail = 0;
    list->head = 0;
    list->count = 0;
    list->allocator->Release();
    if (list->tags)list->tagAllocator->Free(list->tags, 0);
    list->tagAllocator->Release();
    allocator->Free(collection->graphs, 0);
    collection->graphs = 0;
    allocator->Free(collection->graphNames, 0);
    collection->graphNames = 0;
    allocator->Free(collection->clips, 0);
    collection->clips = 0;
    allocator->Free(collection->transitions, 0);
    collection->transitions = 0;
}
// Unmatched: inlined iterator temporaries and callback argument allocation.
void AnimationCollection_AddNamedGraph(AnimationCollectionIndices *collection, const char *name, void *graph) __asm__("func_00342ED8");
void AnimationCollection_AddNamedGraph(AnimationCollectionIndices *collection, const char *name, void *graph) {
    int hash = AnimationCollection_Hash(name);
    AnimationIndexIterator found = collection->graphs->Find(&hash);
    if (!(found != collection->graphs->End())) {
        AnimationIndex_InsertName(collection->graphNames, &hash, &name);
        AnimationIndex_InsertGraph(collection->graphs, &hash, &graph);
    }
}
// Unmatched: inlined iterator temporaries and callback argument allocation.
void AnimationCollection_AddClipValue(AnimationCollectionIndices *collection, int hash, void *clip) __asm__("func_00342FA8");
void AnimationCollection_AddClipValue(AnimationCollectionIndices *collection, int hash, void *clip) {
    AnimationIndex *index = collection->clips;
    AnimationIndexIterator found = index->Find(&hash);
    if (!(found != index->End())) AnimationIndex_InsertClip(index, &hash, &clip);
}
// Unmatched: virtual allocation and list append scheduling.
void AnimationCollection_AddTransitionRow(AnimationCollectionIndices *collection, void *transition) __asm__("func_00343030");
void AnimationCollection_AddTransitionRow(AnimationCollectionIndices *collection, void *transition) {
    AnimationTransitionList *list = collection->transitions;
    AnimationTransitionNode *node=(AnimationTransitionNode *)list->allocator->Allocate(12, list->tags ? list->tags : &AnimationContainer_DefaultTag);
    if (node) {
        node->previous = 0;
        node->value = transition;
        node->next = 0;
    }
    if (list->tail) {
        list->tail->next = node;
        list->tail->next->previous = list->tail;
        list->tail = list->tail->next;
    }
    else {
        list->head = node;
        list->tail = node;
    }
    ++list->count;
}
// Unmatched: inlined list iterator and erase register allocation.
void AnimationCollection_RemoveTransitionRow(AnimationCollectionIndices *collection, int index) __asm__("func_00343148");
void AnimationCollection_RemoveTransitionRow(AnimationCollectionIndices *collection, int index) {
    void *value = AnimationCollection_GetTransition(collection, index);
    AnimationTransitionList *list = collection->transitions;
    AnimationTransitionIterator current(list->head);
    AnimationTransitionIterator end;
    while (current != end) {
        AnimationTransitionNode *node = current.node;
        if (node->value == value) {
            ++current;
            if (node == list->head) {
                if (node == list->tail) {
                    list->tail = 0;
                    list->head = 0;
                }
                else {
                    list->head = node->next;
                    if (list->head)list->head->previous = 0;
                }
            }
            else if (node == list->tail) {
                list->tail = node->previous;
                list->tail->next = 0;
            }
            else {
                node->previous->next = node->next;
                node->next->previous = node->previous;
            }
            list->allocator->Free(node, 0);
            --list->count;
            current = current;
        }
        else ++current;
    }
}
// Unmatched: inlined AVL search iterator temporary layout.
void *AnimationCollection_FindName(AnimationCollectionIndices *collection, int hash) __asm__("func_00343278");
void *AnimationCollection_FindName(AnimationCollectionIndices *collection, int hash) {
    AnimationIndexIterator found = collection->graphNames->Find(&hash);
    return found != collection->graphNames->End() ? found.node->value : 0;
}
// Unmatched: inlined AVL search iterator temporary layout.
void *AnimationCollection_FindGraphValue(AnimationCollectionIndices *collection, int hash) __asm__("func_003432E8");
void *AnimationCollection_FindGraphValue(AnimationCollectionIndices *collection, int hash) {
    AnimationIndexIterator found = collection->graphs->Find(&hash);
    return found != collection->graphs->End() ? found.node->value : 0;
}
// Unmatched: inlined AVL search iterator temporary layout.
void *AnimationCollection_FindClipValue(AnimationCollectionIndices *collection, int hash) __asm__("func_00343358");
void *AnimationCollection_FindClipValue(AnimationCollectionIndices *collection, int hash) {
    AnimationIndexIterator found = collection->clips->Find(&hash);
    return found != collection->clips->End() ? found.node->value : 0;
}
// Unmatched: inlined list iterator temporary layout and loop scheduling.
void *AnimationCollection_TransitionAt(AnimationCollectionIndices *collection, int index) __asm__("func_003433C8");
void *AnimationCollection_TransitionAt(AnimationCollectionIndices *collection, int index) {
    if (index < 0 || index >= AnimationCollection_CountTransitions(collection)) return 0;
    AnimationTransitionIterator current(collection->transitions->head);
    int step = 0;
    while (current != AnimationTransitionIterator() && step < index) {
        ++current;
        ++step;
    }
    return current.node->value;
}
// Unmatched: inlined iterator copies and stack stores.
int AnimationCollection_HasGraph(AnimationCollectionIndices *collection, int hash) __asm__("func_00343470");
int AnimationCollection_HasGraph(AnimationCollectionIndices *collection, int hash) {
    return collection->graphs->Find(&hash) != collection->graphs->End();
}
// Unmatched: inlined AVL iterator traversal and callback scheduling.
void AnimationCollection_VisitNames(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) __asm__("func_00343518");
void AnimationCollection_VisitNames(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) {
    AnimationIndexIterator current = collection->graphNames->Begin();
    AnimationIndexIterator end = collection->graphNames->End();
    while (current != end) {
        if (!visitor(current.node->key, current.node->value, context)) break;
        ++current;
    }
}
// Unmatched: inlined AVL iterator traversal and callback scheduling.
void AnimationCollection_VisitGraphs(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) __asm__("func_00343658");
void AnimationCollection_VisitGraphs(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) {
    AnimationIndexIterator current = collection->graphs->Begin();
    AnimationIndexIterator end = collection->graphs->End();
    while (current != end) {
        if (!visitor(current.node->key, current.node->value, context)) break;
        ++current;
    }
}
// Unmatched: inlined AVL iterator traversal and callback scheduling.
void AnimationCollection_VisitClips(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) __asm__("func_00343798");
void AnimationCollection_VisitClips(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) {
    AnimationIndexIterator current = collection->clips->Begin();
    AnimationIndexIterator end = collection->clips->End();
    while (current != end) {
        if (!visitor(current.node->key, current.node->value, context)) break;
        ++current;
    }
}
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00342A80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00342D48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00342ED8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00342FA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343030);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003432E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343358);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003433C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343518);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343658);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343798);
