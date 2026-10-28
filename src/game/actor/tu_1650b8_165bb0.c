#include "include_asm.h"
#include "ps2/prelude.h"

void func_00165BB0(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xE) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s8 *, 0xD) = 0;
    M2C_FIELD(arg0, s64 *, 0) = 0;
}

extern void *func_00107D20(u32);

#ifdef NON_MATCHING
// Unmatched: allocation loop and return scheduling differ.
void *func_00165BC8(void *arg0, u8 arg1) {
    s32 i;
    void *result;
    M2C_FIELD(arg0, u8 *, 0xC) = arg1;
    if (arg1 == 0) {
        M2C_FIELD(arg0, void **, 8) = 0;
        return 0;
    }
    result = func_00107D20(M2C_FIELD(arg0, u8 *, 0xC) * 4);
    M2C_FIELD(arg0, void **, 8) = result;
    for (i = 0; i < arg1; i++) {
        result = M2C_FIELD(arg0, void **, 8);
        M2C_FIELD((char *) result + i * 4, s32 *, 0) = 0;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00165BC8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00165DF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00165F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00166808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00167000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00167208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00167A10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00167AA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00168618);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169898);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169920);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001699A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169A98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169AA0);
#ifdef NON_MATCHING
// Unmatched: loop control and scheduling differ.
s32 func_00169B88(void *arg0) {
    s32 i = 0;
    u16 result = M2C_FIELD(arg0, u16 *, 0x44);
    if (result != 0) {
        do {
            void *entry = M2C_FIELD(M2C_FIELD(arg0, s32 *, 0xD0) + i * 4, void **, 0);
            i++;
            M2C_FIELD(entry, s8 *, 0x11C) = 0;
            result = i < M2C_FIELD(arg0, u16 *, 0x44);
        } while (result != 0);
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169B88);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016D7F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016D958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016DB58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016DC80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E6B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E7A8);
extern s128 D_004432A0;

#ifdef NON_MATCHING
// Unmatched: instruction scheduling differs under the file recipe.
void func_0016E7F8(void *arg0) {
    void *base = (char *) arg0 + 0x20000;
    s128 value;
    M2C_FIELD(base, s32 *, 0x2BCC) = 0;
    value = D_004432A0;
    M2C_FIELD(base, s32 *, 0x2BD0) = 0;
    M2C_FIELD(base, s128 *, 0x2BE0) = value;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E7F8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E820);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E928);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016EA10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016EAD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016EB28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00171ED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001721E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001722A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00174040);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001740A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00174858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00174930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176310);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176FB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176FE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177030);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001770E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177A70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177AA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177B48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177C90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001793C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00179B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00179BD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017A9F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AB40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AED8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AF20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AFD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A7F88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A80F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A8168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A8300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A8350);
