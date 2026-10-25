// Class view from RTTI and the vtable, edited by hand: UNVERIFIED parts are marked; sizes and inheritance layouts are not claimed. A fresh skeleton is in build/classes/include/.
#ifndef BLACK_CLASSES_FINDNEARESTVERTEXTRAVERSAL_HPP
#define BLACK_CLASSES_FINDNEARESTVERTEXTRAVERSAL_HPP
#include "game/classes/support.hpp"
#include "game/classes/hierarchy.hpp"

namespace Unnamed {

// FindNearestVertexTraversal
// Identity: RTTI. Complete size and inheritance layout are UNVERIFIED.
// RTTI getters: 0x00391E58.
// RTTI base: Kaim_CGraphTraversal; offset 0; public nonvirtual.
struct FindNearestVertexTraversal {
    typedef Hierarchy_FindNearestVertexTraversal Hierarchy; // Semantic bases, not an object layout.
    // Destructor identity: 0x00391E20.
    // Field references address the original object; sizeof(this view) is not the allocation size.
    // 0x0: UNVERIFIED type; PS2 access offset.
    inline unsigned int & Field_0000() { return *(unsigned int *)((unsigned char *)this + 0x0); }
    // 0x8: UNVERIFIED type; PS2 access offset.
    inline long & Field_0008() { return *(long *)((unsigned char *)this + 0x8); }
    // 0x10: UNVERIFIED type; PS2 access offset.
    inline unsigned int & Field_0010() { return *(unsigned int *)((unsigned char *)this + 0x10); }
    // 0x14: UNVERIFIED type; PS2 access offset.
    inline float & Field_0014() { return *(float *)((unsigned char *)this + 0x14); }
    // 0x18: UNVERIFIED type; PS2 access offset.
    inline float & Field_0018() { return *(float *)((unsigned char *)this + 0x18); }
    // 0x1C: UNVERIFIED type; PS2 access offset.
    inline float & Field_001C() { return *(float *)((unsigned char *)this + 0x1C); }
    // 0x20: UNVERIFIED type; PS2 access offset.
    inline unsigned char & Field_0020() { return *(unsigned char *)((unsigned char *)this + 0x20); }
    // 0x21: UNVERIFIED type; PS2 access offset.
    inline unsigned char & Field_0021() { return *(unsigned char *)((unsigned char *)this + 0x21); }
    // 0x003915C8: UNVERIFIED signature (include/kynapse/graph/spatial.hpp).
    unsigned int Function_003915C8(void * argument0);
    // 0x00391E18: UNVERIFIED signature (src/kynapse/inline/linkonce_391e10.c).
    int Function_00391E18();
    // 0x00391E20: UNVERIFIED signature (PS2 in-charge flag and conditional release; hidden destructor flag omitted).
    void Function_00391E20();
    // 0x00391F00: UNVERIFIED signature (PS2 register/type inference; unverified unused parameters).
    int Function_00391F00(void * argument0);
    // 0x003921A0: UNVERIFIED signature (src/kynapse/inline/nearest_node_3921a0.cpp).
    void Function_003921A0(void * argument0);

    // Vtable 0x003EED38; vptr field offset unknown; RTTI header.
    // Separate interface preserves slot order without claiming this object's C++ inheritance layout.
    struct VirtualInterface0 {
        // slot 0, table+0x8, this delta 0, function 0x00391E20; UNVERIFIED signature.
        virtual ~VirtualInterface0();
        // slot 1, table+0x10, this delta 0, function 0x003921A0; UNVERIFIED signature.
        virtual void Slot001(void * argument0);
        // slot 2, table+0x18, this delta 0, function 0x003915C8; UNVERIFIED signature.
        virtual unsigned int Slot002(void * argument0);
        // slot 3, table+0x20, this delta 0, function 0x00391F00; UNVERIFIED signature.
        virtual int Slot003(void * argument0);
        // slot 4, table+0x28, this delta 0, function 0x00391E18; UNVERIFIED signature.
        virtual int Slot004();
    };
};

} // namespace Unnamed

#endif
