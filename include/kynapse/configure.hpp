// Declarations of the Kynapse source module "configure" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_CONFIGURE_HPP
#define BLACK_KYNAPSE_MODULE_CONFIGURE_HPP
#include "kynapse/compat.hpp"

// Configure handlers of path-related components: they accept one named entry (with a value
// and a nested block) and ignore entries whose name starts with an underscore.

extern "C" int __cdecl _stricmp(const char*, const char*);

namespace Kaim {

struct ChildBuffers {
    unsigned char unknown00[0x0c];
    char* first;
    unsigned char unknown10[0x10];
    unsigned int count;
    const char* GetSecond() const;
    ChildBuffers* FindBySecond(const char* name) const;
    ChildBuffers* GetChild(unsigned int index) const;
    const char* GetValue() const;
};

struct ClassInfo;
struct TypeRegistry {
    int FindId(const char* name);
};
struct EntityObject {
    TypeRegistry* FindByClass(ClassInfo* wanted);
};

// Base of configurable components: visits every child entry that is not the class entry.
struct ConfigHost {
    virtual void Slot0();
    virtual bool ConfigureAll(ChildBuffers* config);         // slot 1, Ghidra /default.xbe 0x54bf0
    virtual bool Configure(ChildBuffers* child);             // slot 2
};



struct ConfigHostB {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual bool ConfigureChild(ChildBuffers* child);        // slot 6
    bool ConfigureAll(ChildBuffers* config);
};



struct PathComponentA {
    bool Load(char* value, ChildBuffers* block);
    bool Configure(ChildBuffers* config);
};

struct PathComponentB {
    bool Load(char* value, ChildBuffers* block);
    bool Configure(ChildBuffers* config);
};





extern EntityObject* gEngine;
extern ClassInfo gTypeRegistryClass;

struct TypedComponent {
    void SetType(int id);
    bool Configure(ChildBuffers* config);
};

// Unmatched: the original calls GetSecond() before pushing the "Graph" literal.


struct ConfigHostC {
    bool ConfigureAll(ChildBuffers* config);
    bool Init(ChildBuffers* config);
};



struct RawDataUser {
    bool Load(ChildBuffers* block);
    bool Apply(ChildBuffers* config);
};



}  // namespace Kaim

#endif
