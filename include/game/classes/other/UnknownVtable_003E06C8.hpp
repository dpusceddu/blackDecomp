// Class view from RTTI and the vtable, edited by hand: UNVERIFIED parts are marked; sizes and inheritance layouts are not claimed. A fresh skeleton is in build/classes/include/.
#ifndef BLACK_CLASSES_UNKNOWNVTABLE_003E06C8_HPP
#define BLACK_CLASSES_UNKNOWNVTABLE_003E06C8_HPP
#include "game/classes/support.hpp"
#include "game/classes/hierarchy.hpp"

namespace BlackPS2Classes {

// UnknownVtable_003E06C8
// Identity: unverified vtable owner. Complete size and inheritance layout are UNVERIFIED.
struct UnknownVtable_003E06C8 {
    // Field references address the original object; sizeof(this view) is not the allocation size.
    // 0x001CCF48: UNVERIFIED signature (PS2 register/type inference; unverified unused parameters).
    int Function_001CCF48(void * argument0, void * argument1);
    // 0x001CD650: UNVERIFIED signature (PS2 register/type inference; unverified unused parameters).
    int Function_001CD650(void * argument0, unsigned int argument1, int argument2);
    // 0x001CDA00: code-compatible exact source signature; original semantic types UNVERIFIED (PS2 exact source probe; full-build status recorded separately).
    void Function_001CDA00(void * argument0);
    // 0x001CDA28: UNVERIFIED signature (PS2 register/type inference; unverified unused parameters).
    void * Function_001CDA28(void * argument0, unsigned int argument1);
    // 0x001CDAA8: UNVERIFIED signature (src/game/unsorted/tu_1cdaa8.c).
    unsigned int Function_001CDAA8();
    // 0x00384630: UNVERIFIED signature (src/game/inline/linkonce_384630.c).
    unsigned int Function_00384630();

    // Vtable 0x003E06C8; vptr field offset unknown; referenced zero RTTI header.
    // Separate interface preserves slot order without claiming this object's C++ inheritance layout.
    struct VirtualInterface0 {
        // slot 0, table+0x8, this delta 0, function 0x001CCF48; UNVERIFIED signature.
        virtual int Slot000(void * argument0, void * argument1);
        // slot 1, table+0x10, this delta 0, function 0x001CD650; UNVERIFIED signature.
        virtual int Slot001(void * argument0, unsigned int argument1, int argument2);
        // slot 2, table+0x18, this delta 0, function 0x00384630; UNVERIFIED signature.
        virtual unsigned int Slot002();
        // slot 3, table+0x20, this delta 0, function 0x001CDA00; code-compatible exact source signature; original semantic types UNVERIFIED.
        virtual void Slot003(void * argument0);
        // slot 4, table+0x28, this delta 0, function 0x001CDA28; UNVERIFIED signature.
        virtual void * Slot004(void * argument0, unsigned int argument1);
        // slot 5, table+0x30, this delta 0, function 0x001CDAA8; UNVERIFIED signature.
        virtual unsigned int Slot005();
    };
};

} // namespace BlackPS2Classes

#endif
