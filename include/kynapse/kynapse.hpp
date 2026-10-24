// Ported from an unpublished companion project.
#ifndef BLACK_KYNAPSE_HPP
#include "kynapse/compat.hpp"
#define BLACK_KYNAPSE_HPP

// Kynogon Kynapse AI middleware (namespace Kaim in the original strings).
// Built without /arch:SSE: all float math is x87. The dynamic-avoidance part
// of this library is reconstructed separately.
#include "kynapse/alloc.hpp"

namespace Kaim {

// Base of Kynapse objects: a vtable with a virtual destructor. Deleting
// destructors release through the engine allocator hook.
struct Object {
    Object() {}
    virtual ~Object() {}
    static void* operator new(size_t size) { return KaimAllocate((unsigned int)size); }
};

struct Vec3 {
    float x, y, z;
};

// Bounded doubly linked list over a preallocated node array, used for search
// queues, intervals and candidates. Nodes return to a free chain; addresses
// stay stable. Node layout: vtable, value, previous, next, active flag.
template <class T> struct ListNode : Object {
    T value;
    ListNode* previous;
    ListNode* next;
    unsigned char active;
};

template <class T> struct ListIterator : Object {
    ListNode<T>* node;
    ListIterator(ListNode<T>* entry = 0) : node(entry) {}
};

template <class T> struct List : Object {
    List(unsigned int capacity);   // defined where the list is built (see owned_arrays.cpp)

    ListNode<T>* storage;
    ListNode<T>* head;
    ListNode<T>* tail;
    ListNode<T>* freeHead;
    unsigned int activeCount;
    unsigned int capacity;

    void Clear()
    {
        while (head != 0) {
            head->active = 0;
            ListNode<T>* next = head->next;
            head->next = freeHead;
            freeHead = head;
            head = next;
        }
        tail = 0;
        activeCount = 0;
    }

    void Remove(const ListIterator<T>& at)
    {
        ListNode<T>* node = at.node;
        node->active = 0;
        if (node == head) head = node->next;
        if (node == tail) tail = node->previous;
        if (node->previous) node->previous->next = node->next;
        if (node->next) node->next->previous = node->previous;
        node->next = freeHead;
        freeHead = node;
        --activeCount;
    }

    ListIterator<T> Insert(const T& value, ListIterator<T> before);

    ListIterator<T> At(unsigned int index)
    {
        if (index < capacity)
            return ListIterator<T>(&storage[index]);
        return ListIterator<T>(0);
    }
};

// Allocates a free node and links it before `before` (or appends). Kept out of line: callers
// in the original reach it through a call.
#pragma auto_inline(off)
template <class T>
ListIterator<T> List<T>::Insert(const T& value, ListIterator<T> before)
{
    ListNode<T>* entry = freeHead;
    if (entry == 0)
        return ListIterator<T>(0);
    ++activeCount;
    freeHead = entry->next;
    entry->value = value;
    entry->active = 1;
    if (before.node == 0) {
        if (tail == 0) {
            head = entry;
            tail = entry;
            entry->next = 0;
            head->previous = 0;
            tail->previous = 0;
            tail->next = 0;
            return ListIterator<T>(entry);
        }
        entry->previous = tail;
        entry->next = 0;
        tail->next = entry;
        tail = entry;
        return ListIterator<T>(entry);
    }
    ListNode<T>* previous = before.node->previous;
    entry->next = before.node;
    before.node->previous = entry;
    entry->previous = previous;
    if (previous)
        previous->next = entry;
    else
        head = entry;
    return ListIterator<T>(entry);
}
#pragma auto_inline(on)

}  // namespace Kaim

#endif
