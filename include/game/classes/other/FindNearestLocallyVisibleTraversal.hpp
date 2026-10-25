// Class view from RTTI and the vtable, edited by hand: UNVERIFIED parts are marked; sizes and inheritance layouts are not claimed. A fresh skeleton is in build/classes/include/.
#ifndef BLACK_CLASSES_FINDNEARESTLOCALLYVISIBLETRAVERSAL_HPP
#define BLACK_CLASSES_FINDNEARESTLOCALLYVISIBLETRAVERSAL_HPP
#include "game/classes/support.hpp"
#include "game/classes/hierarchy.hpp"

namespace Unnamed {

// FindNearestLocallyVisibleTraversal
// Identity: RTTI. Complete size and inheritance layout are UNVERIFIED.
// RTTI getters: 0x003925A0.
// RTTI base: Kaim_CGraphTraversal; offset 0; public nonvirtual.
struct FindNearestLocallyVisibleTraversal {
    typedef Hierarchy_FindNearestLocallyVisibleTraversal Hierarchy; // Semantic bases, not an object layout.
    // Destructor identity: 0x00392568.
    // Field references address the original object; sizeof(this view) is not the allocation size.
    // 0x0: UNVERIFIED type; PS2 access offset.
    inline unsigned int & Field_0000() { return *(unsigned int *)((unsigned char *)this + 0x0); }
    // 0x8: UNVERIFIED type; PS2 access offset.
    inline long & Field_0008() { return *(long *)((unsigned char *)this + 0x8); }
    // 0x10: UNVERIFIED type; PS2 access offset.
    inline float & Field_0010() { return *(float *)((unsigned char *)this + 0x10); }
    // 0x14: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline unsigned int & Field_0014() { return *(unsigned int *)((unsigned char *)this + 0x14); }
    // 0x18: UNVERIFIED type; PS2 access offset.
    inline unsigned int & Field_0018() { return *(unsigned int *)((unsigned char *)this + 0x18); }
    // 0x1C: UNVERIFIED type; PS2 access offset.
    inline float & Field_001C() { return *(float *)((unsigned char *)this + 0x1C); }
    // 0x20: UNVERIFIED type; PS2 access offset.
    inline float & Field_0020() { return *(float *)((unsigned char *)this + 0x20); }
    // 0x24: UNVERIFIED type; PS2 access offset.
    inline float & Field_0024() { return *(float *)((unsigned char *)this + 0x24); }
    // 0x28: UNVERIFIED type; PS2 access offset.
    inline float & Field_0028() { return *(float *)((unsigned char *)this + 0x28); }
    // 0x2C: UNVERIFIED type; PS2 access offset.
    inline int & Field_002C() { return *(int *)((unsigned char *)this + 0x2C); }
    // 0x30: UNVERIFIED type; PS2 access offset.
    inline unsigned char & Field_0030() { return *(unsigned char *)((unsigned char *)this + 0x30); }
    // 0x31: UNVERIFIED type; PS2 access offset.
    inline unsigned char & Field_0031() { return *(unsigned char *)((unsigned char *)this + 0x31); }
    // 0x34: UNVERIFIED type; PS2 access offset.
    inline float & Field_0034() { return *(float *)((unsigned char *)this + 0x34); }
    // 0x38: UNVERIFIED type; PS2 access offset.
    inline unsigned char & Field_0038() { return *(unsigned char *)((unsigned char *)this + 0x38); }
    // 0x39: UNVERIFIED type; PS2 access offset.
    inline unsigned char & Field_0039() { return *(unsigned char *)((unsigned char *)this + 0x39); }
    // 0x003915C8: UNVERIFIED signature (include/kynapse/graph/spatial.hpp).
    unsigned int Function_003915C8(void * argument0);
    // 0x00391E18: UNVERIFIED signature (src/kynapse/linkonce_391e10.c).
    int Function_00391E18();
    // 0x00392568: UNVERIFIED signature (PS2 in-charge flag and conditional release; hidden destructor flag omitted).
    void Function_00392568();
    // 0x00392648: UNVERIFIED signature (PS2 register/type inference; unverified unused parameters).
    int Function_00392648(void * argument0);
    // 0x00392A50: UNVERIFIED signature (src/kynapse/inline/nearest_node_392a50.cpp).
    void Function_00392A50(void * argument0);

    // Vtable 0x003EECC8; vptr field offset unknown; RTTI header.
    // Separate interface preserves slot order without claiming this object's C++ inheritance layout.
    struct VirtualInterface0 {
        // slot 0, table+0x8, this delta 0, function 0x00392568; UNVERIFIED signature.
        virtual ~VirtualInterface0();
        // slot 1, table+0x10, this delta 0, function 0x00392A50; UNVERIFIED signature.
        virtual void Slot001(void * argument0);
        // slot 2, table+0x18, this delta 0, function 0x003915C8; UNVERIFIED signature.
        virtual unsigned int Slot002(void * argument0);
        // slot 3, table+0x20, this delta 0, function 0x00392648; UNVERIFIED signature.
        virtual int Slot003(void * argument0);
        // slot 4, table+0x28, this delta 0, function 0x00391E18; UNVERIFIED signature.
        virtual int Slot004();
    };
};

} // namespace Unnamed

#endif
