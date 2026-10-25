// Class view from RTTI and the vtable, edited by hand: UNVERIFIED parts are marked; sizes and inheritance layouts are not claimed. A fresh skeleton is in build/classes/include/.
#ifndef BLACK_CLASSES_UNKNOWNVTABLE_003DC100_HPP
#define BLACK_CLASSES_UNKNOWNVTABLE_003DC100_HPP
#include "game/classes/support.hpp"
#include "game/classes/hierarchy.hpp"

namespace Unnamed {

// UnknownVtable_003DC100
// Identity: unverified vtable owner. Complete size and inheritance layout are UNVERIFIED.
struct UnknownVtable_003DC100 {
    // Field references address the original object; sizeof(this view) is not the allocation size.
    // 0x8: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline int & Field_0008() { return *(int *)((unsigned char *)this + 0x8); }
    // 0xC: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline unsigned char & Field_000C() { return *(unsigned char *)((unsigned char *)this + 0xC); }
    // 0x10: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline void * & Field_0010() { return *(void * *)((unsigned char *)this + 0x10); }
    // 0x1C: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline unsigned char & Field_001C() { return *(unsigned char *)((unsigned char *)this + 0x1C); }
    // 0x00165380: UNVERIFIED signature (src/game/weapons/tu_1448c8_149ac8.c).
    int Function_00165380();
    // 0x001653A8: code-compatible exact source signature; original semantic types UNVERIFIED (PS2 exact source probe; full-build status recorded separately).
    int Function_001653A8();
    // 0x00165B00: UNVERIFIED signature (src/game/actor/actor_event_fanout.cpp).
    void Function_00165B00(int argument0);
    // 0x00165B90: UNVERIFIED signature (src/game/actor/tu_1650b8_165af8.c).
    unsigned int Function_00165B90();

    // Vtable 0x003DC100; vptr field offset 0x10; referenced zero RTTI header.
    // Separate interface preserves slot order without claiming this object's C++ inheritance layout.
    struct VirtualInterface0 {
        // slot 0, table+0x8, this delta 0, function 0x00165B90; UNVERIFIED signature.
        virtual unsigned int Slot000();
        // slot 1, table+0x10, this delta 0, function 0x00165B00; UNVERIFIED signature.
        virtual void Slot001(int argument0);
        // slot 2, table+0x18, this delta 0, function 0x001653A8; code-compatible exact source signature; original semantic types UNVERIFIED.
        virtual int Slot002();
        // slot 3, table+0x20, this delta 0, function 0x00165380; UNVERIFIED signature.
        virtual int Slot003();
    };
};

} // namespace Unnamed

// Separate, source-probed virtual dispatch view; not a complete class layout.
namespace Unnamed {
struct ABI_UnknownVtable_003DC100 {
    unsigned char unknown_prefix[0x10];
    virtual void Slot000();
    virtual void Slot001();
    virtual void Slot002();
};
} // namespace Unnamed

#endif
