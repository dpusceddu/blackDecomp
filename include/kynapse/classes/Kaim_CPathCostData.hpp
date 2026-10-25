// Class view from RTTI and the vtable, edited by hand: UNVERIFIED parts are marked; sizes and inheritance layouts are not claimed. A fresh skeleton is in build/classes/include/.
#ifndef BLACK_CLASSES_KAIM_CPATHCOSTDATA_HPP
#define BLACK_CLASSES_KAIM_CPATHCOSTDATA_HPP
#include "game/classes/support.hpp"
#include "game/classes/hierarchy.hpp"

namespace Unnamed {

// Kaim::CPathCostData
// Identity: RTTI. Complete size and inheritance layout are UNVERIFIED.
// RTTI getters: 0x003910D0.
// RTTI base: Kaim_CGraphData; offset 0; public nonvirtual.
struct Kaim_CPathCostData {
    typedef Hierarchy_Kaim_CPathCostData Hierarchy; // Semantic bases, not an object layout.
    // Constructor identity: 0x002F36A8; source-exact C++ special-member symbol and bound class vtable.
    // Destructor identity: 0x002F42B8.
    // Destructor identity: 0x002F42B8.
    // Field references address the original object; sizeof(this view) is not the allocation size.
    // 0x4: UNVERIFIED type; PS2 access offset.
    inline void * & Field_0004() { return *(void * *)((unsigned char *)this + 0x4); }
    // 0x8: UNVERIFIED type; PS2 access offset.
    inline int & Field_0008() { return *(int *)((unsigned char *)this + 0x8); }
    // 0xC: UNVERIFIED type; PS2 access offset.
    inline int & Field_000C() { return *(int *)((unsigned char *)this + 0xC); }
    // 0x10: UNVERIFIED type; PS2 access offset.
    inline float & Field_0010() { return *(float *)((unsigned char *)this + 0x10); }
    // 0x14: UNVERIFIED type; PS2 access offset.
    inline int & Field_0014() { return *(int *)((unsigned char *)this + 0x14); }
    // 0x002F3770: UNVERIFIED signature (PS2 register/type inference; unverified unused parameters).
    int Function_002F3770(void * argument0);
    // 0x002F3AB0: UNVERIFIED signature (PS2 register/type inference; unverified unused parameters).
    int Function_002F3AB0();
    // 0x002F4100: UNVERIFIED signature (src/kynapse/graph_cpathcostdata.cpp).
    int Function_002F4100(void * argument0);
    // 0x002F42B8: UNVERIFIED signature (PS2 in-charge flag and conditional release; hidden destructor flag omitted).
    void Function_002F42B8();
    // 0x00391120: UNVERIFIED signature (src/kynapse/inline/class_info_391120.cpp).
    void * Function_00391120();

    // Vtable 0x003EDE90; vptr field offset unknown; RTTI header.
    // Separate interface preserves slot order without claiming this object's C++ inheritance layout.
    struct VirtualInterface0 {
        // slot 0, table+0x8, this delta 0, function 0x002F42B8; UNVERIFIED signature.
        virtual ~VirtualInterface0();
        // slot 1, table+0x10, this delta 0, function 0x002F3770; UNVERIFIED signature.
        virtual int Slot001(void * argument0);
        // slot 2, table+0x18, this delta 0, function 0x00391120; UNVERIFIED signature.
        virtual void * Slot002();
        // slot 3, table+0x20, this delta 0, function 0x002F3AB0; UNVERIFIED signature.
        virtual int Slot003();
        // slot 4, table+0x28, this delta 0, function 0x002F4100; UNVERIFIED signature.
        virtual int Slot004(void * argument0);
    };
};

} // namespace Unnamed

#endif
