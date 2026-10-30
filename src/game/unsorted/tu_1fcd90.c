#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001FD440();
extern s32 func_001FD648(void *);
extern s32 func_001FBA78(void *);
extern void func_001F1C08(void*);
extern s32 func_001F1F08();
extern s32 func_001F1E20();
extern M2C_UNK D_003F9DD8;

/* Native clock component offset; its original type is UNVERIFIED. */
extern void* D_0040F0E0;
void func_001FCD90(void* self) {
    void* clock = (u8*)D_0040F0E0 + 0x20120;
    f32 time = M2C_FIELD(clock, f32*, 0x20);
    M2C_FIELD(self, s32*, 0x134) = 1;
    M2C_FIELD(self, f32*, 0x130) = time;
}

void func_001FCDB8(void* self) {
    void* clock = (u8*)D_0040F0E0 + 0x20120;
    f32 time = M2C_FIELD(clock, f32*, 0x20);
    M2C_FIELD(self, s32*, 0x13C) = 1;
    M2C_FIELD(self, f32*, 0x138) = time;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90", func_001FCDE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90", func_001FCFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90", func_001FD178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90", func_001FD220);
extern void func_001FD8A0(void*);
extern s32 func_001FAC78(void*, f32);
void func_001FD230(void* self) {
    s32* entry;
    s32* values;
    u32 index;

    func_001F1C08(self);
    values = (s32*)((u8*)self + 0x18);
    index = 0;
    do {
        entry = &values[index];
        index = (index + 1) & 0xFF;
        *entry = 0;
    } while (index < 3U);
    func_001FD8A0((void*)(((s8*)self) + 0x30));
    func_001FAC78((void*)(((s8*)self) + 0xE0), 0.5f);
}

#ifdef NON_MATCHING
// Unmatched: key-copy registers and the final byte-test scheduling differ.
/* Native field layout and original class identities remain UNVERIFIED. */
extern void* D_0040F4D0;
extern s32* D_00414D54;
extern s32 func_001F1C10(void*, s32, s32, s32, s32, s32, s32);
extern s32 func_001FD8F0(void*, s32, s32, s32);
extern s32 func_001FDAD0(void*, s32);
extern s32 func_001FAE18(void*, s32, s32, s32);
static inline u8 FrontendPayloadKind(u8* ptr) {
    if (ptr) return *ptr;
    return 0xFF;
}
s32 func_001FD298(void* self, s8 index, s32 first, s32 second) {
    s32 categoryValue;
    s8 category;
    s8 current;
    u8* definition;
    u32 previous;
    u8 kind;
    void* firstState;
    void* secondState;

    M2C_FIELD(self, s8*, 0x2D8) = (s8)index;
    M2C_FIELD(self, s32*, 0x2E0) =
        (s32)M2C_FIELD(M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x2D4), void**, 0xF4), s8*, 0x20);
    definition = M2C_FIELD(((void*)(((s8)index * 0x8C0) + ((s8*)D_0040F4D0))), u8**, 0x2D4);
    kind = FrontendPayloadKind(definition);
    M2C_FIELD(self, s8*, 0x2D9) = 0;
    M2C_FIELD(self, s8*, 0x2DA) = 0;
    M2C_FIELD(self, s8*, 0x2DB) = 0;
    M2C_FIELD(self, s8*, 0x2DC) = 0;
    M2C_FIELD(self, u8*, 0x2DD) = kind;
    func_001F1C10(self, 2, 3, 0, (s32)(s8)index, first, second);
    firstState = (void*)(((s8*)self) + 0x30);
    func_001FD8F0(firstState, (s32)(s8)index, first, second);
    category = (s8)M2C_FIELD(self, u8*, 0x2DD);
    if (category == -1) {
        categoryValue = 0;
    } else {
        categoryValue = D_00414D54[category];
    }
    func_001FDAD0(firstState, categoryValue);
    secondState = (void*)(((s8*)self) + 0xE0);
    M2C_FIELD(self, u64*, 0x2D0) = (u64)*M2C_FIELD(self, u64**, 0x30);
    func_001FAE18(secondState, (s32)(s8)index, first, second);
    previous = M2C_FIELD(secondState, u8*, 0x195);
    current = (s8)M2C_FIELD(self, u8*, 0x2DD);
    M2C_FIELD(secondState, u8*, 0x196) = previous;
    M2C_FIELD(secondState, u8*, 0x195) = (u8)current;
    if ((s8)previous == 0) { M2C_FIELD(secondState, u8*, 0x196) = (u8)current; }
    return 1;
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90", func_001FD298);
#endif

void func_001FD3E8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2DB) == 0) {
        func_001FD440();
    }
    if (M2C_FIELD(arg0, u8 *, 0x2D9) == 0) {
        func_001FD648(arg0);
    }
    func_001FBA78(arg0 + 0xE0);
}

s32 func_001FD438(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90", func_001FD440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90", func_001FD648);

void func_001FD8A0(void *arg0)
{
  void *new_var3;
  void *new_var;
  void *new_var2;
  s32 *temp_3;
  u32 var_4;
  func_001F1C08(arg0);
  var_4 = 0;
  do
  {
    new_var3 = (new_var = arg0 + 0x70);
    new_var2 = new_var3 + (var_4 * 4);
    temp_3 = new_var2;
    var_4 = (var_4 + 1) & 0xFF;
    *temp_3 = 0;
  }
  while (var_4 < 2U);
  M2C_FIELD(arg0, s32 *, 0x78) = 0;
}

extern s32 func_001F1EE0(void*, s32, s32, s32, s32, s32, s32);
extern void Text_CopyUtf8ToUtf16(const char*, u16*, s32);
extern char D_0040DDA8[];
extern s32 func_001F1D48(void*, const void*, const void*);

s32 func_001FD8F0(void* self, s32 arg1, s32 arg2, s32 arg3) {
    u16* text;

    text = (u16*)((u8*)self + 0x7C);
    M2C_FIELD(self, s8*, 0xA4) = 1;
    M2C_FIELD(self, s8*, 0xA5) = 0;
    M2C_FIELD(self, s32*, 0xA8) = 0;
    func_001F1EE0(self, 3, 2, 0, (s32)(s8)arg1, arg2, arg3);
    Text_CopyUtf8ToUtf16(D_0040DDA8, text, 0x14);
    func_001F1D48(self, &D_003F9DD8, text);
    return 1;
}

void func_001FD978(void) {
    func_001F1F08();
}

s32 func_001FD998(s32 arg0) {
    func_001F1E20(arg0, (s32) &D_003F9DD8);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90", func_001FD9C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90", func_001FDAD0);
