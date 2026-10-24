// Class view from RTTI and the vtable, edited by hand: UNVERIFIED parts are marked; sizes and inheritance layouts are not claimed. A fresh skeleton is in build/classes/include/.
#ifndef BLACK_CLASSES_KAIM_CFOLLOWERAGENT_HPP
#define BLACK_CLASSES_KAIM_CFOLLOWERAGENT_HPP
#include "game/classes/support.hpp"
#include "game/classes/hierarchy.hpp"

namespace BlackPS2Classes {

// Kaim::CFollowerAgent
// Identity: RTTI. Complete size and inheritance layout are UNVERIFIED.
// RTTI getters: 0x00389480.
// RTTI base: Kaim_CAgent; offset 0; public nonvirtual.
struct Kaim_CFollowerAgent {
    typedef Hierarchy_Kaim_CFollowerAgent Hierarchy; // Semantic bases, not an object layout.
    // Destructor identity: 0x002D3560.
    // Field references address the original object; sizeof(this view) is not the allocation size.
    // 0x0: UNVERIFIED type; PS2 access offset.
    inline unsigned int & Field_0000() { return *(unsigned int *)((unsigned char *)this + 0x0); }
    // 0x4: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline void * & Field_0004() { return *(void * *)((unsigned char *)this + 0x4); }
    // 0x8: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline void * & Field_0008() { return *(void * *)((unsigned char *)this + 0x8); }
    // 0xC: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline void * & Field_000C() { return *(void * *)((unsigned char *)this + 0xC); }
    // 0x10: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline void * & Field_0010() { return *(void * *)((unsigned char *)this + 0x10); }
    // 0x14: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline float & Field_0014() { return *(float *)((unsigned char *)this + 0x14); }
    // 0x18: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline float & Field_0018() { return *(float *)((unsigned char *)this + 0x18); }
    // 0x1C: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline float & Field_001C() { return *(float *)((unsigned char *)this + 0x1C); }
    // 0x2C: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline int & Field_002C() { return *(int *)((unsigned char *)this + 0x2C); }
    // 0x34: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline float & Field_0034() { return *(float *)((unsigned char *)this + 0x34); }
    // 0x38: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline unsigned char & Field_0038() { return *(unsigned char *)((unsigned char *)this + 0x38); }
    // 0x3C: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline void * & Field_003C() { return *(void * *)((unsigned char *)this + 0x3C); }
    // 0x40: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline float & Field_0040() { return *(float *)((unsigned char *)this + 0x40); }
    // 0x44: VERIFIED PS2 offset/access; semantic field type UNVERIFIED.
    inline float & Field_0044() { return *(float *)((unsigned char *)this + 0x44); }
    // 0x002D30A0: UNVERIFIED signature (src/kynapse/behaviors_follower.cpp).
    unsigned char Function_002D30A0(void * argument0);
    // 0x002D31F0: UNVERIFIED signature (src/kynapse/behaviors_follower_2d31f0.cpp).
    unsigned char Function_002D31F0(void * argument0);
    // 0x002D3300: UNVERIFIED signature (include/kynapse/behaviors/follower.hpp).
    unsigned int Function_002D3300();
    // 0x002D3560: UNVERIFIED signature (PS2 in-charge flag and conditional release; hidden destructor flag omitted).
    void Function_002D3560();
    // 0x002D35B8: UNVERIFIED signature (src/kynapse/predicates_2d35b8.cpp).
    unsigned char Function_002D35B8();
    // 0x002D35C8: UNVERIFIED signature (src/kynapse/predicates_2d35b8.cpp).
    unsigned char Function_002D35C8();
    // 0x002D35D8: UNVERIFIED signature (src/kynapse/behaviors_follower.cpp).
    unsigned char Function_002D35D8();
    // 0x002D3610: UNVERIFIED signature (src/kynapse/behaviors_follower_2d31f0.cpp).
    unsigned char Function_002D3610();
    // 0x002D36A8: UNVERIFIED signature (src/kynapse/behaviors_follower_2d31f0.cpp).
    void Function_002D36A8(void * argument0);
    // 0x003894D0: UNVERIFIED signature (src/kynapse/inline/class_info_3894d0.cpp).
    void * Function_003894D0();
    // 0x0038BB28: UNVERIFIED signature (src/kynapse/inline/small_misc_38bb28.cpp).
    void Function_0038BB28();

    // Vtable 0x003E3130; vptr field offset unknown; RTTI header.
    // Separate interface preserves slot order without claiming this object's C++ inheritance layout.
    struct VirtualInterface0 {
        // slot 0, table+0x8, this delta 0, function 0x002D3560; UNVERIFIED signature.
        virtual ~VirtualInterface0();
        // slot 1, table+0x10, this delta 0, function 0x002D31F0; UNVERIFIED signature.
        virtual unsigned char Slot001(void * argument0);
        // slot 2, table+0x18, this delta 0, function 0x002D30A0; UNVERIFIED signature.
        virtual unsigned char Slot002(void * argument0);
        // slot 3, table+0x20, this delta 0, function 0x0038BB28; UNVERIFIED signature.
        virtual void Slot003();
        // slot 4, table+0x28, this delta 0, function 0x003894D0; UNVERIFIED signature.
        virtual void * Slot004();
        // slot 5, table+0x30, this delta 0, function 0x002D35D8; UNVERIFIED signature.
        virtual unsigned char Slot005();
        // slot 6, table+0x38, this delta 0, function 0x002D3610; UNVERIFIED signature.
        virtual unsigned char Slot006();
        // slot 7, table+0x40, this delta 0, function 0x002D35B8; UNVERIFIED signature.
        virtual unsigned char Slot007();
        // slot 8, table+0x48, this delta 0, function 0x002D35C8; UNVERIFIED signature.
        virtual unsigned char Slot008();
        // slot 9, table+0x50, this delta 0, function 0x002D3300; UNVERIFIED signature.
        virtual unsigned int Slot009();
        // slot 10, table+0x58, this delta 0, function 0x002D36A8; UNVERIFIED signature.
        virtual void Slot010(void * argument0);
    };
};

} // namespace BlackPS2Classes

#endif
