#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#include "game/actor/control_view.h"

extern void* D_0040F4D0;
extern s32 func_0012D158(void*, s32, s32);
extern f32 func_0012D0D0(void*, f32, f32);

extern void * D_0040F4BC;
extern s32 D_003BD140;
extern unsigned char D_004147C0;
extern M2C_UNK D_003F5138;
const u32 rodata_003F5168[12] __asm__("D_003F5168") __attribute__((aligned(8))) = { 0x3DCCCCCD, 0x3E800000, 0x3E19999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D851EB8, 0x3D99999A, 0x3D851EB8, 0x00000000 };
extern volatile char D_003F5168;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00136F10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137010);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137018);

void func_00137318(s64 *arg0, s64 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137320);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137450);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137490);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_001374F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137718);

f32 func_001378F0(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0xC0) * M2C_FIELD(D_0040F4BC, f32 *, 0x1660);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137A78);

s32 func_00137AE0(void *arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x2A4);
    if (temp_2 != NULL) {
        return M2C_FIELD(M2C_FIELD(temp_2, void **, 0xE8), s32 *, 0xC) + 0x10;
    }
    return D_003BD140;
}

void func_00137B08(Recovered_ManagedActor* actor, u8 flag) {
    s32 integer;
    actor->unk_3AC = flag;
    integer = func_0012D158(D_0040F4D0, -128, 0);
    actor->unk_258 = integer - func_0012D0D0(D_0040F4D0, 0.6f, 0.9999f);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137B88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137CA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137E88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137FB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_001381E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00138298);

s32 func_00138320(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00138328);

void func_00138338(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

s32 func_00138340(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 8);
}

f32 func_00138348(s32 arg0) {
    return M2C_FIELD(((arg0 * 4) + ((s32) &D_003F5138)), f32 *, 0);
}

f32 func_00138360(s32 arg0)
{
  return *((f32 *) (((s8 *) ((arg0 * 4) + (&D_003F5168))) + 0));
}

void *func_00138378(s32 arg0)
{
  int new_var;
  new_var = arg0 & 0xFFFFFFFFFFFFFFFF;
  return (new_var << 6) + (&D_004147C0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00138390);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00138468);

void func_00138470(void *arg0, void *arg1) {
    f32 var_f1;

    var_f1 = 0.0f;
    M2C_FIELD(arg0, void **, 0) = arg1;
    if (M2C_FIELD(arg1, f32 *, 0x308) > 0.0f) {
        var_f1 = 1.0f / func_001378F0(arg1);
    }
    M2C_FIELD(arg0, f32 *, 4) = var_f1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_001384C8);
