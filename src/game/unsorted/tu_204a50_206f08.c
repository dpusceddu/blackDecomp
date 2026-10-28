#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002050B0();
extern s32 func_00278F00();
extern void * D_003BDCC8;
extern s32 func_00204FF0();
extern void func_00276728(void*, const void*, const void*, const void*, s128, s32, const void*, const void*, s32);
extern s32 func_00208D00(M2C_UNK, M2C_UNK);
extern s32 D_003BE718;
extern s32 func_0020D188(s32);
extern s32 D_0040F544;
extern s32 func_00205000(void*, s32, s32, s32);
extern void* func_00278EC0(void*, s32, s32);
extern void func_00277530(void*, f32, const void*, const void*, s128, void*, const u16*, const void*, s32);
extern void* D_0040F0E0;
extern s32* D_0040F4C0;
extern s128 D_00438CE0;
extern void func_00276610(void*, const void*, const void*, const void*, s128);
extern void* func_00275448(void*, s32, s32, s32);
extern s32 func_00384CF0(void*, const void*, const void*, const void*);

static inline void SetFrontendVec2(f32* value, f32 x, f32 y) {
    value[0] = x;
    value[1] = y;
}

s32 func_00206F08(void) {
    func_002050B0();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00206F28);
s32 func_00207110(void* self, const void* scale, const void* position) {
    f32 extent[2];
    void* command;
    func_00205000(self, 1, 30, 30);
    SetFrontendVec2(extent, (f32)D_0040F4C0[0], (f32)D_0040F4C0[1] / 6.0f);
    command = func_00278EC0(D_003BDCC8, 0, M2C_FIELD(self, s32*, 0xC));
    M2C_FIELD(self, void**, 0x18) = command;
    func_00276610(command, position, scale, extent, D_00438CE0);
    return 1;
}

void func_002071C0(void) {

}

s32 func_002071C8(void *arg0) {
    func_00278F00(D_003BDCC8, 0, M2C_FIELD(arg0, s32 *, 0x18));
    return 1;
}

void func_002071F8(void) {
    func_00204FF0();
}

s32 func_00207218(void* self, s32 index, s32 arg2, s32 arg3, s32 arg4) {
    void* command;
    func_00205000(self, arg2, arg3, arg4);
    M2C_FIELD(self, s32*, 0x78) = index;
    M2C_FIELD(self, s32*, 0x7C) = 0;
    command = func_00278EC0(M2C_FIELD(self, void**, 8), index, M2C_FIELD(self, s32*, 0xC));
    M2C_FIELD(self, void**, 0x84) = command;
    func_00276728(command, (s8*)self + 0x40, (s8*)self + 0x50, (s8*)self + 0x58, M2C_FIELD(self, s128*, 0x20),
                  M2C_FIELD(self, s32*, 0x88), (s8*)self + 0x68, (s8*)self + 0x70, 0);
    return 1;
}

void func_002072A0(void *arg0) {
    func_00276728(M2C_FIELD(arg0, void **, 0x84), arg0 + 0x40, arg0 + 0x50, arg0 + 0x58, M2C_FIELD(arg0, s128 *, 0x20), M2C_FIELD(arg0, s32 *, 0x88), arg0 + 0x68, arg0 + 0x70, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_002072E0);

void func_002075F0(void) {
    func_00204FF0();
}

s32 func_00207610(void* self, s32 index, s32 arg2, s32 arg3, s32 arg4) {
    void* command;
    func_00205000(self, arg2, arg3, arg4);
    M2C_FIELD(self, s32*, 0x74) = 0;
    command = func_00278EC0(M2C_FIELD(self, void**, 8), index, M2C_FIELD(self, s32*, 0xC));
    M2C_FIELD(self, s32*, 0x64) = index;
    M2C_FIELD(self, void**, 0x7C) = command;
    func_00277530(command, M2C_FIELD(self, f32*, 0x6C), (s8*)self + 0x40, (s8*)self + 0x50,
                  M2C_FIELD(self, s128*, 0x20), M2C_FIELD(D_0040F0E0, void**, 0x2107C),
                  M2C_FIELD(self, const u16**, 0x60), (s8*)self + 0x58, M2C_FIELD(self, s32*, 0x68));
    return 1;
}
void func_002076A8(void* self) {
    func_00277530(M2C_FIELD(self, void**, 0x7C), M2C_FIELD(self, f32*, 0x6C), (s8*)self + 0x40, (s8*)self + 0x50,
                  M2C_FIELD(self, s128*, 0x20), M2C_FIELD(D_0040F0E0, void**, 0x2107C),
                  M2C_FIELD(self, const u16**, 0x60), (s8*)self + 0x58, M2C_FIELD(self, s32*, 0x68));
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_002076F8);

s32 func_00207938(void *arg0)
{
  s8 *new_var;
  new_var = (s8 *) arg0;
  func_002050B0();
  func_00278F00(*((void **) (new_var + 8)), *((s32 *) (new_var + 0x64)), *((s32 *) (new_var + 0x7C)));
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00207970);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00207978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00207B80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00208140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00208AF8);
s32 func_00208BF0(void* self) {
    s8 i;
    for (i = 0; i < 5; i++) {
        func_00207938((s8*)M2C_FIELD(self, void**, 0x14) + i * 0x80);
    }
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00208C58);
// Native adjacent constants; the SDK marker's original owner and identifier are UNVERIFIED.
const u16 D_003FA270[] = {'%', '1', ':', '%', '2', 0};
const char D_003FA280[] = "DirtyXSDK";

s32 func_00208C60(void* destination, f32 time) {
    u16 minutes[8];
    u16 seconds[8];
    s32 wholeMinutes = (s32)(time / 60.0f);
    s32 remaining = (s32)(time - (f32)wholeMinutes * 60.0f);
    func_00275448(minutes, wholeMinutes, 1, 0);
    func_00275448(seconds, remaining, 2, 0);
    return func_00384CF0(destination, D_003FA270, minutes, seconds);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00208D00);

void func_002092B8(void) {
    func_00208D00(1, 0xFFFF);
}

void func_002092D8(s32 arg0) {
    D_003BE718 = arg0;
}

void func_002092E8(void) {
    func_0020D188(D_0040F544 + 0xE90);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00209310);
