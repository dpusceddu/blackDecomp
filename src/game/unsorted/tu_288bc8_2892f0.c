#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00288E28();
extern s32 func_00289028();
extern s32 func_00288FB0();
extern void * func_0035E7D8(M2C_UNK);
extern s32 func_002F4A48();
extern M2C_UNK D_003E28D8;

s32 func_002892F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[24] __attribute__((aligned(16)));

    func_00288E28((s32) sp, arg1 + 0x10, arg2, 0, (s32) "Periodic", 1);
    func_00289028((s32) (sp + 16), (s32) sp, (s32) "Period", arg3);
    M2C_FIELD(arg0, s32 *, 0) = *(s32 *)(sp + 0);
    return arg0;
}

s32 func_00289360(s32 arg0, s32 arg1, s32 arg2) {
    func_00288FB0(arg0, arg1 + 0x28, arg2);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_2892f0", func_00289390);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_2892f0", func_00289398);
void func_00289480(void* asset, void* instance) {
    s32 entryOffset;
    s32 slotOffset;
    u32 more;
    u32 slotIndex;
    u32 linkIndex;

    M2C_FIELD(instance, s32*, 0x18) = (s32)M2C_FIELD(asset, s32*, 0x14);
    M2C_FIELD(instance, s32*, 0x34) = (s32)M2C_FIELD(asset, s32*, 0x30);
    M2C_FIELD(instance, s32*, 0x1C) = (s32)M2C_FIELD(asset, s32*, 0x18);
    M2C_FIELD(instance, s32*, 0x38) = (s32)M2C_FIELD(asset, s32*, 0x34);
    M2C_FIELD(instance, s32*, 0x3C) = (s32)M2C_FIELD(asset, s32*, 0x38);
    M2C_FIELD(instance, s32*, 0x48) = (s32)M2C_FIELD(asset, s32*, 0x44);
    M2C_FIELD(instance, s32*, 0x4C) = (s32)M2C_FIELD(asset, s32*, 0x48);
    M2C_FIELD(instance, s32*, 0x50) = (s32)M2C_FIELD(asset, s32*, 0x4C);
    M2C_FIELD(instance, s32*, 0x40) = (s32)M2C_FIELD(asset, s32*, 0x3C);
    M2C_FIELD(instance, s32*, 0x44) = (s32)M2C_FIELD(asset, s32*, 0x40);
    M2C_FIELD(instance, s32*, 0x20) = (s32)M2C_FIELD(asset, s32*, 0x1C);
    M2C_FIELD(instance, s32*, 0x24) = (s32)M2C_FIELD(asset, s32*, 0x20);
    M2C_FIELD(instance, s32*, 4) = (s32)M2C_FIELD(asset, s32*, 0);
    M2C_FIELD(instance, f32*, 8) = (f32)M2C_FIELD(asset, f32*, 4);
    M2C_FIELD(instance, s32*, 0xC) = (s32)M2C_FIELD(asset, s32*, 8);
    M2C_FIELD(instance, s32*, 0x10) = (s32)M2C_FIELD(asset, s32*, 0xC);
    M2C_FIELD(instance, u32*, 0x14) = (u32)M2C_FIELD(asset, u32*, 0x10);
    M2C_FIELD(instance, s32*, 0x28) = (s32)M2C_FIELD(asset, s32*, 0x24);
    M2C_FIELD(instance, s32*, 0x2C) = (s32)M2C_FIELD(asset, s32*, 0x28);
    M2C_FIELD(instance, u32*, 0x30) = (u32)M2C_FIELD(asset, u32*, 0x2C);
    M2C_FIELD(instance, s32*, 0x54) = 0;
    M2C_FIELD(instance, s32*, 0x58) = 0;
    slotIndex = 0;
    if (M2C_FIELD(asset, u32*, 0x10) != 0) {
        slotOffset = 0;
        do {
            slotIndex += 1;
            M2C_FIELD((slotOffset + M2C_FIELD(instance, s32*, 0x18)), void**, 0x10) = instance;
            slotOffset += 0x14;
        } while (slotIndex < (u32)M2C_FIELD(asset, u32*, 0x10));
    }
    more = M2C_FIELD(asset, u32*, 0x2C);
    linkIndex = 0;
    if (more != 0) {
        do {
            entryOffset = linkIndex * 8;
            linkIndex += 1;
            M2C_FIELD((entryOffset + M2C_FIELD(instance, s32*, 0x34)), void**, 4) = instance;
            more = linkIndex < (u32)M2C_FIELD(asset, u32*, 0x2C);
        } while (more != 0);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_2892f0", func_00289590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_2892f0", func_002895E0);

void func_00289660(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x6C) = 0x7F;
    M2C_FIELD(arg0, void **, 0x60) = func_0035E7D8(0x7F0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_2892f0", func_00289698);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_2892f0", func_00289798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_2892f0", func_002897D8);

void func_00289948(void) {

}

M2C_UNK ** func_00289950(M2C_UNK **arg0) {
    func_002F4A48();
    *arg0 = &D_003E28D8;
    return arg0;
}

s32 func_00289988(void) {
    return 1;
}

s32 func_00289990(void) {
    return 0;
}

s32 func_00289998(void) {
    return 0;
}
