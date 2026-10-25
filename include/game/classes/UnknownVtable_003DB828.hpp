// Class view from RTTI and the vtable, edited by hand: UNVERIFIED parts are marked; sizes and inheritance layouts are not claimed. A fresh skeleton is in build/classes/include/.
#ifndef BLACK_CLASSES_UNKNOWNVTABLE_003DB828_HPP
#define BLACK_CLASSES_UNKNOWNVTABLE_003DB828_HPP
#include "game/classes/support.hpp"
#include "game/classes/hierarchy.hpp"

namespace Unnamed {

// UnknownVtable_003DB828
// Identity: unverified vtable owner. Complete size and inheritance layout are UNVERIFIED.
struct UnknownVtable_003DB828 {
    // Field references address the original object; sizeof(this view) is not the allocation size.
    // 0x0: UNVERIFIED type; PS2 access offset.
    inline unsigned long & Field_0000() { return *(unsigned long *)((unsigned char *)this + 0x0); }
    // 0x8: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline int & Field_0008() { return *(int *)((unsigned char *)this + 0x8); }
    // 0xC: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline unsigned char & Field_000C() { return *(unsigned char *)((unsigned char *)this + 0xC); }
    // 0x18: UNVERIFIED type; PS2 access offset.
    inline void * & Field_0018() { return *(void * *)((unsigned char *)this + 0x18); }
    // 0x20: UNVERIFIED type; PS2 access offset.
    inline U128 & Field_0020() { return *(U128 *)((unsigned char *)this + 0x20); }
    // 0x30: UNVERIFIED type; PS2 access offset.
    inline U128 & Field_0030() { return *(U128 *)((unsigned char *)this + 0x30); }
    // 0x40: UNVERIFIED type; PS2 access offset.
    inline U128 & Field_0040() { return *(U128 *)((unsigned char *)this + 0x40); }
    // 0x50: UNVERIFIED type; PS2 access offset.
    inline U128 & Field_0050() { return *(U128 *)((unsigned char *)this + 0x50); }
    // 0x60: UNVERIFIED type; PS2 access offset.
    inline U128 & Field_0060() { return *(U128 *)((unsigned char *)this + 0x60); }
    // 0x70: UNVERIFIED type; PS2 access offset.
    inline U128 & Field_0070() { return *(U128 *)((unsigned char *)this + 0x70); }
    // 0x80: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline unsigned char & Field_0080() { return *(unsigned char *)((unsigned char *)this + 0x80); }
    // 0x00163D08: UNVERIFIED signature (PS2 register/type inference; unverified unused parameters).
    int Function_00163D08(unsigned long argument0, void * argument1);
    // 0x00163DA8: code-compatible exact source signature; original semantic types UNVERIFIED (PS2 exact source probe; full-build status recorded separately).
    void Function_00163DA8();
    // 0x00163DC0: UNVERIFIED signature (src/game/unsorted/tu_163dc0.c).
    int Function_00163DC0();
    // 0x00165B00: UNVERIFIED signature (src/game/actor/actor_event_fanout.cpp).
    void Function_00165B00(int argument0);
    // 0x00165B90: UNVERIFIED signature (src/game/actor/tu_1650b8_165af8.c).
    unsigned int Function_00165B90();

    // Vtable 0x003DB828; vptr field offset unknown; referenced zero RTTI header.
    // Separate interface preserves slot order without claiming this object's C++ inheritance layout.
    struct VirtualInterface0 {
        // slot 0, table+0x8, this delta 0, function 0x00165B90; UNVERIFIED signature.
        virtual unsigned int Slot000();
        // slot 1, table+0x10, this delta 0, function 0x00165B00; UNVERIFIED signature.
        virtual void Slot001(int argument0);
        // slot 2, table+0x18, this delta 0, function 0x00163DA8; code-compatible exact source signature; original semantic types UNVERIFIED.
        virtual void Slot002();
        // slot 3, table+0x20, this delta 0, function 0x00163DC0; UNVERIFIED signature.
        virtual int Slot003();
        // slot 4, table+0x28, this delta 0, function 0x00163D08; UNVERIFIED signature.
        virtual int Slot004(unsigned long argument0, void * argument1);
    };
};

} // namespace Unnamed

#endif
