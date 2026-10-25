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


#ifdef NON_MATCHING
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
void __attribute__((section(".text.func_00342A80"))) AnimationCollection_CreateIndices(AnimationCollectionIndices *collection, AnimationContainerAllocator *allocator) __asm__("func_00342A80");
void __attribute__((section(".text.func_00342D48"))) AnimationCollection_DestroyIndices(AnimationCollectionIndices *collection, AnimationContainerAllocator *allocator) __asm__("func_00342D48");
void __attribute__((section(".text.func_00342ED8"))) AnimationCollection_AddNamedGraph(AnimationCollectionIndices *collection, const char *name, void *graph) __asm__("func_00342ED8");
void __attribute__((section(".text.func_00342FA8"))) AnimationCollection_AddClipValue(AnimationCollectionIndices *collection, int hash, void *clip) __asm__("func_00342FA8");
void __attribute__((section(".text.func_00343030"))) AnimationCollection_AddTransitionRow(AnimationCollectionIndices *collection, void *transition) __asm__("func_00343030");
void __attribute__((section(".text.func_00343148"))) AnimationCollection_RemoveTransitionRow(AnimationCollectionIndices *collection, int index) __asm__("func_00343148");
void __attribute__((section(".text.func_00343278"))) *AnimationCollection_FindName(AnimationCollectionIndices *collection, int hash) __asm__("func_00343278");
void __attribute__((section(".text.func_003432E8"))) *AnimationCollection_FindGraphValue(AnimationCollectionIndices *collection, int hash) __asm__("func_003432E8");
void __attribute__((section(".text.func_00343358"))) *AnimationCollection_FindClipValue(AnimationCollectionIndices *collection, int hash) __asm__("func_00343358");
void __attribute__((section(".text.func_003433C8"))) *AnimationCollection_TransitionAt(AnimationCollectionIndices *collection, int index) __asm__("func_003433C8");
int __attribute__((section(".text.func_00343470"))) AnimationCollection_HasGraph(AnimationCollectionIndices *collection, int hash) __asm__("func_00343470");
void __attribute__((section(".text.func_00343518"))) AnimationCollection_VisitNames(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) __asm__("func_00343518");
void __attribute__((section(".text.func_00343658"))) AnimationCollection_VisitGraphs(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) __asm__("func_00343658");
void __attribute__((section(".text.func_00343798"))) AnimationCollection_VisitClips(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) __asm__("func_00343798");
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
void AnimationCollection_CreateIndices(AnimationCollectionIndices *collection, AnimationContainerAllocator *allocator) {
    collection->graphs = new(allocator)AnimationGraphIndex(allocator, &AnimationAllocationTag());
    collection->graphNames = new(allocator)AnimationNameIndex(allocator, &AnimationAllocationTag());
    collection->clips = new(allocator)AnimationClipIndex(allocator, &AnimationAllocationTag());
    collection->transitions=(AnimationTransitionList *)new(allocator)AnimationTransitionContainer(allocator, &AnimationAllocationTag());
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00342A80);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00342D48);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
void AnimationCollection_AddNamedGraph(AnimationCollectionIndices *collection, const char *name, void *graph) {
    int hash = AnimationCollection_Hash(name);
    AnimationIndexIterator found = collection->graphs->Find(&hash);
    if (!(found != collection->graphs->End())) {
        AnimationIndex_InsertName(collection->graphNames, &hash, &name);
        AnimationIndex_InsertGraph(collection->graphs, &hash, &graph);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00342ED8);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
void AnimationCollection_AddClipValue(AnimationCollectionIndices *collection, int hash, void *clip) {
    AnimationIndex *index = collection->clips;
    AnimationIndexIterator found = index->Find(&hash);
    if (!(found != index->End())) AnimationIndex_InsertClip(index, &hash, &clip);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00342FA8);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00343030);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00343148);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
void *AnimationCollection_FindName(AnimationCollectionIndices *collection, int hash) {
    AnimationIndexIterator found = collection->graphNames->Find(&hash);
    return found != collection->graphNames->End() ? found.node->value : 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00343278);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
void *AnimationCollection_FindGraphValue(AnimationCollectionIndices *collection, int hash) {
    AnimationIndexIterator found = collection->graphs->Find(&hash);
    return found != collection->graphs->End() ? found.node->value : 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_003432E8);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
void *AnimationCollection_FindClipValue(AnimationCollectionIndices *collection, int hash) {
    AnimationIndexIterator found = collection->clips->Find(&hash);
    return found != collection->clips->End() ? found.node->value : 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00343358);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_003433C8);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
int AnimationCollection_HasGraph(AnimationCollectionIndices *collection, int hash) {
    return collection->graphs->Find(&hash) != collection->graphs->End();
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00343470);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
void AnimationCollection_VisitNames(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) {
    AnimationIndexIterator current = collection->graphNames->Begin();
    AnimationIndexIterator end = collection->graphNames->End();
    while (current != end) {
        if (!visitor(current.node->key, current.node->value, context)) break;
        ++current;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00343518);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
void AnimationCollection_VisitGraphs(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) {
    AnimationIndexIterator current = collection->graphs->Begin();
    AnimationIndexIterator end = collection->graphs->End();
    while (current != end) {
        if (!visitor(current.node->key, current.node->value, context)) break;
        ++current;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00343658);
#endif
#ifdef NON_MATCHING
// Unmatched: placement construction, tag-chain inlining and exception cleanup shape.
void AnimationCollection_VisitClips(AnimationCollectionIndices *collection, int (*visitor)(int, void *, void *), void *context) {
    AnimationIndexIterator current = collection->clips->Begin();
    AnimationIndexIterator end = collection->clips->End();
    while (current != end) {
        if (!visitor(current.node->key, current.node->value, context)) break;
        ++current;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_342a60", func_00343798);
#endif
