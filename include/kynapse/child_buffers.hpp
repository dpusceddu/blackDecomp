// Declarations of the Kynapse source module "child_buffers" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_CHILD_BUFFERS_HPP
#define BLACK_KYNAPSE_MODULE_CHILD_BUFFERS_HPP
#include "kynapse/compat.hpp"

// ChildBuffers: a node with three owned strings and a growing array of child nodes
// (see owned_arrays.cpp for its constructor, destructor and DeleteChildren).
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);  // Ghidra /default.xbe 0x297f10

#pragma intrinsic(strcmp, strlen, strcpy)

namespace Kaim {

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
};

struct ChildBuffers : ObjectBase {
    int unknown04;
    int unknown08;
    char* first;
    char* second;
    char* third;
    ChildBuffers** items;
    unsigned int capacity;
    unsigned int count;

    ChildBuffers()
    {
        unknown04 = 0;
        capacity = 0;
        count = 0;
        unknown08 = 0;
        items = 0;
        first = 0;
        second = 0;
        third = 0;
    }
    ChildBuffers(const char* text);
    ChildBuffers(const ChildBuffers& other);
    ChildBuffers& operator=(const ChildBuffers& other);
    void DeleteChildren();
    virtual ~ChildBuffers();

    ChildBuffers* SetFirst(const char* text);
    ChildBuffers* SetSecond(const char* text);
    ChildBuffers* SetThird(const char* text);
    const char* GetSecond() const;
    ChildBuffers* FindChild(const char* second, const char* first) const;
    ChildBuffers* FindBySecond(const char* second) const;
    const char* FindThirdBySecond(const char* second) const;
    ChildBuffers* GetChild(unsigned int index) const;
    ChildBuffers* AddChild();
    ChildBuffers* AddText(const char* text) __asm__("func_002E2B78");
    ChildBuffers* AddCopy(const ChildBuffers* other) __asm__("func_002E2EF0");
    ChildBuffers* FindByFirst(const char* key) const __asm__("func_002E3288");
    void RemoveChild(ChildBuffers* child) __asm__("func_002E3828");
    const char* GetValue() const __asm__("func_002E3918");
};

// Replaces an owned string with a copy of `text` (inline strlen/strcpy).
#define KAIM_REPLACE_STRING(member) \
    if (member) \
        memoryRelease(member); \
    member = (char*)KaimAllocate(strlen(text) + 1); \
    strcpy(member, text); \
    return this;

}  // namespace Kaim

#endif
