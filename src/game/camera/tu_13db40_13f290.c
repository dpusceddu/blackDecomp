#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0013EE28();
extern s32 func_0013EE30();

extern s32 func_0013EC38(void*, void*);
extern void func_0013EC10(void*, s32);
extern s128 D_004432A0;
extern void* D_0040F0E0;
extern void* D_0040F0E8;
extern s8* D_003C09E8;
extern void func_0027B950(void*, void*, const char*, const char*, const char*, s32, f32, f32, s32);
// Native label order and alignment for the Controls_PS2 registration.
const char D_003F4A08[] __attribute__((section(".rodata.003F4A08"), aligned(8))) = "Max Hold Modifier Increment";
const char D_003F4A28[] __attribute__((section(".rodata.003F4A08"), aligned(8))) = "Controls_PS2";
const char D_003F4A38[] __attribute__((section(".rodata.003F4A08"), aligned(8))) =
    "../Export/ValueDB/Controls/Controls_PS2.cfg";
const char D_003F4A68[] __attribute__((section(".rodata.003F4A08"), aligned(8))) = "Max Hold Modifier";
const char D_003F4A80[] __attribute__((section(".rodata.003F4A08"), aligned(8))) = "Analogue Control Power";
const char D_003F4A98[] __attribute__((section(".rodata.003F4A08"), aligned(8))) = "Percentage Catch Up";

void func_0013F290(void) {

}

s32 func_0013F298(void *arg0)
{
  int new_var;
  new_var = 0x98;
  func_0013EE28();
  M2C_FIELD(arg0, s8 *, 0x9D) = (*((s32 *) (((s8 *) arg0) + new_var)) = 0);
  return 1;
}

void func_0013F2C8(void) {
    func_0013EE30();
}

void func_0013F2E8(void *arg0) {
    void *temp_2;

    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    temp_2 = M2C_FIELD(arg0, void **, 0x7C);
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(temp_2, f32 *, 0x4F8);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) M2C_FIELD(temp_2, f32 *, 0x4FC);
}

void func_0013F308(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_13db40_13f290", func_0013F310);

void func_0013F328(void* self) {
    func_0013EC10(self, 0);
    M2C_FIELD(self, s32*, 0x98) = 0;
    M2C_FIELD(self, s8*, 0xF0) = 0;
    M2C_FIELD(self, s8*, 0xF1) = 0;
    M2C_FIELD(self, s8*, 0xF9) = 0;
    M2C_FIELD(self, s8*, 0xF6) = 0;
    M2C_FIELD(self, s8*, 0xF7) = 0;
    M2C_FIELD(self, s32*, 0xD8) = 0;
    M2C_FIELD(self, s128*, 0xE0) = (s128)D_004432A0;
    M2C_FIELD(self, s128*, 0x110) = (s128)D_004432A0;
    M2C_FIELD(self, s8*, 0xDC) = -1;
    M2C_FIELD(self, f32*, 0xA8) = 70.0f;
    M2C_FIELD(self, f32*, 0xAC) = 25.0f;
    M2C_FIELD(self, f32*, 0xB8) = 3.0f;
    M2C_FIELD(self, s32*, 0x108) = 0;
    M2C_FIELD(self, s8*, 0x120) = 0;
    M2C_FIELD(self, s32*, 0xC0) = 0;
    M2C_FIELD(self, s32*, 0xC4) = 0;
    M2C_FIELD(self, s32*, 0x90) = 0;
    M2C_FIELD(self, s32*, 0x94) = 0;
    M2C_FIELD(self, f32*, 0xBC) = M2C_FIELD(self, f32*, 0xB4) = M2C_FIELD(self, f32*, 0xB0) = 0.5f;
}

s32 func_0013F3E0(void* self, s32 index, void* actor) {
    u8 enabled;
    s32 entries, offset;
    s8 playerIndex;

    if (M2C_FIELD(self, u8*, 0x120) != 0) {
        return 1;
    }
    enabled = 1;
    func_0013EC38(self, actor);
    playerIndex = (s8)index;
    M2C_FIELD(self, s128*, 0x110) = (s128)D_004432A0;
    M2C_FIELD(self, s32*, 0x108) = 0;
    M2C_FIELD(self, s32*, 0xC0) = 0;
    M2C_FIELD(self, s32*, 0xC4) = 0;
    M2C_FIELD(self, s32*, 0x90) = 0;
    M2C_FIELD(self, s32*, 0x94) = 0;
    M2C_FIELD(self, s128*, 0xE0) = (s128)D_004432A0;
    M2C_FIELD(self, s32*, 0xC8) = 0;
    M2C_FIELD(self, s32*, 0xCC) = 0;
    M2C_FIELD(self, s32*, 0xD0) = 0;
    M2C_FIELD(self, s32*, 0xD4) = 0;
    M2C_FIELD(self, s32*, 0xD8) = 0;
    M2C_FIELD(self, u8*, 0xF1) = (u8)M2C_FIELD(D_0040F0E0, u8*, 0x20167);
    M2C_FIELD(self, u8*, 0xF2) = (u8)M2C_FIELD(D_0040F0E0, u8*, 0x20165);
    M2C_FIELD(self, u8*, 0xF3) = (u8)M2C_FIELD(D_0040F0E0, u8*, 0x20166);
    M2C_FIELD(((s8*)D_0040F0E8 + playerIndex), s8*, 0x77C) = (s8)(M2C_FIELD(D_0040F0E0, u8*, 0x20168) != 0);
    M2C_FIELD(self, s8*, 0xF4) = 0;
    M2C_FIELD(self, s8*, 0xF5) = 0;
    M2C_FIELD(self, s8*, 0xF6) = 0;
    M2C_FIELD(self, s8*, 0xF7) = 0;
    M2C_FIELD(self, s8*, 0xFA) = 0;
    M2C_FIELD(self, s8*, 0xFB) = 0;
    M2C_FIELD(self, s8*, 0xFC) = 0;
    entries = (s32)D_0040F0E0 + 0x20000;
    offset = index * 12;
    M2C_FIELD(self, s32*, 0x98) = M2C_FIELD(entries + offset, s32*, 0x1060);
    M2C_FIELD(self, s32*, 0x100) = 0;
    if (M2C_FIELD(self, u8*, 0xF9) == 0) {
        func_0027B950(D_003C09E8 + 4, &M2C_FIELD(self, f32*, 0xB0), D_003F4A08, D_003F4A28,
                      D_003F4A38, 0, 0.0f, 0.0f, 0);
        func_0027B950(D_003C09E8 + 4, &M2C_FIELD(self, f32*, 0xB4), D_003F4A68, D_003F4A28,
                      D_003F4A38, 0, 0.0f, 0.0f, 0);
        func_0027B950(D_003C09E8 + 4, &M2C_FIELD(self, f32*, 0xB8), D_003F4A80, D_003F4A28,
                      D_003F4A38, 0, 0.0f, 0.0f, 0);
        func_0027B950(D_003C09E8 + 4, &M2C_FIELD(self, f32*, 0xBC), D_003F4A98, D_003F4A28,
                      D_003F4A38, 0, 0.0f, 0.0f, 0);
        M2C_FIELD(self, u8*, 0xF9) = enabled;
    }
    M2C_FIELD(self, u8*, 0x120) = enabled;
    M2C_FIELD(self, s32*, 0x104) = 0;
    return enabled;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_13db40_13f290", func_0013F618);
