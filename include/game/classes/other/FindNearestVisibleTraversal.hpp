// Class view from RTTI and the vtable, edited by hand: UNVERIFIED parts are marked; sizes and inheritance layouts are not claimed. A fresh skeleton is in build/classes/include/.
#ifndef BLACK_CLASSES_FINDNEARESTVISIBLETRAVERSAL_HPP
#define BLACK_CLASSES_FINDNEARESTVISIBLETRAVERSAL_HPP
#include "game/classes/support.hpp"
#include "game/classes/hierarchy.hpp"

namespace Unnamed {

// FindNearestVisibleTraversal
// Identity: RTTI. Complete size and inheritance layout are UNVERIFIED.
// RTTI getters: 0x003921F0.
// RTTI base: Kaim_CGraphTraversal; offset 0; public nonvirtual.
struct FindNearestVisibleTraversal {
    typedef Hierarchy_FindNearestVisibleTraversal Hierarchy; // Semantic bases, not an object layout.
    // Destructor identity: 0x003921B8.
    // Field references address the original object; sizeof(this view) is not the allocation size.
    // 0x0: UNVERIFIED type; PS2 access offset.
    inline unsigned int & Field_0000() { return *(unsigned int *)((unsigned char *)this + 0x0); }
    // 0x003915C8: UNVERIFIED signature (include/kynapse/graph/spatial.hpp).
    unsigned int Function_003915C8(void * argument0);
    // 0x00391E18: UNVERIFIED signature (src/kynapse/linkonce_391e10.c).
    int Function_00391E18();
    // 0x003921B8: UNVERIFIED signature (PS2 in-charge flag and conditional release; hidden destructor flag omitted).
    void Function_003921B8();
    // 0x00392298: UNVERIFIED signature (include/kynapse/graph/node_queries.hpp).
    int Function_00392298(void * argument0);
    // 0x00392550: UNVERIFIED signature (include/kynapse/graph/node_queries.hpp).
    long Function_00392550(void * argument0);

    // Vtable 0x003EED00; vptr field offset unknown; RTTI header.
    // Separate interface preserves slot order without claiming this object's C++ inheritance layout.
    struct VirtualInterface0 {
        // slot 0, table+0x8, this delta 0, function 0x003921B8; UNVERIFIED signature.
        virtual ~VirtualInterface0();
        // slot 1, table+0x10, this delta 0, function 0x00392550; UNVERIFIED signature.
        virtual long Slot001(void * argument0);
        // slot 2, table+0x18, this delta 0, function 0x003915C8; UNVERIFIED signature.
        virtual unsigned int Slot002(void * argument0);
        // slot 3, table+0x20, this delta 0, function 0x00392298; UNVERIFIED signature.
        virtual int Slot003(void * argument0);
        // slot 4, table+0x28, this delta 0, function 0x00391E18; UNVERIFIED signature.
        virtual int Slot004();
    };
};

} // namespace Unnamed

#endif
