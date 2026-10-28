#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0020DF68(void *, s32, s32);
extern M2C_UNK D_003FB608;
extern void func_00212940(const char*);
extern s32 func_0020DCB0(s32 *);
extern s32 D_00492220;
extern s32 D_00492230;
extern s32 D_00492240;
extern s32 D_00492250;
extern s32 D_00492260;
extern s32 D_00492270;
extern s32 D_00492280;
extern s32 D_00492290;
extern s32 D_004922A0;
extern s32 D_004922B0;
extern s32 D_004922C0;
extern s32 D_004922D0;
extern s32 D_004922E0;
extern s32 D_004922F0;
extern s32 func_0020DCF8(void *, void *);
extern M2C_UNK D_003FAFD8;
extern M2C_UNK D_003FAFE8;
extern M2C_UNK D_003FAD90;
extern M2C_UNK D_003FB030;
extern s32 func_0020DF90(s32, s32);
extern s32 func_0020DD48(void *);
extern s32 func_0020DF30(s32 *);

s32 func_00212528(void *arg0) {
    func_0020DF68(arg0, (s32) &D_003FB608, (s32) func_00212940);
    func_0020DCB0(&D_00492220);
    func_0020DCB0(&D_00492230);
    func_0020DCB0(&D_00492240);
    func_0020DCB0(&D_00492250);
    func_0020DCB0(&D_00492260);
    func_0020DCB0(&D_00492270);
    func_0020DCB0(&D_00492280);
    func_0020DCB0(&D_00492290);
    func_0020DCB0(&D_004922A0);
    func_0020DCB0(&D_004922B0);
    func_0020DCB0(&D_004922C0);
    func_0020DCB0(&D_004922D0);
    func_0020DCB0(&D_004922E0);
    func_0020DCB0(&D_004922F0);
    func_0020DCF8(&D_00492220, "FE_RESULTSLEVELNAME");
    func_0020DCF8(&D_00492230, "FE_MISSIONSTATUS");
    func_0020DCF8(&D_00492240, "FE_PRIMARYSCORE");
    func_0020DCF8(&D_00492250, "FE_SECONDARYSCORE");
    func_0020DCF8(&D_00492260, "FE_BLACKMAILSCORE");
    func_0020DCF8(&D_00492270, "FE_INTELSCORE");
    func_0020DCF8(&D_00492280, &D_003FAFD8);
    func_0020DCF8(&D_00492290, &D_003FAFE8);
    func_0020DCF8(&D_004922A0, "FE_OVERALLRATING");
    func_0020DCF8(&D_004922B0, "FE_BODYCOUNT");
    func_0020DCF8(&D_004922C0, "FE_MISSIONTIME");
    func_0020DCF8(&D_004922D0, &D_003FAD90);
    func_0020DCF8(&D_004922E0, "FE_OBJECTIVESTOTAL");
    func_0020DCF8(&D_004922F0, &D_003FB030);
    return 1;
}

s32 func_00212770(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FB608);
    func_0020DD48(&D_00492220);
    func_0020DD48(&D_00492230);
    func_0020DD48(&D_00492240);
    func_0020DD48(&D_00492250);
    func_0020DD48(&D_00492260);
    func_0020DD48(&D_00492270);
    func_0020DD48(&D_00492280);
    func_0020DD48(&D_00492290);
    func_0020DD48(&D_004922A0);
    func_0020DD48(&D_004922B0);
    func_0020DD48(&D_004922C0);
    func_0020DD48(&D_004922D0);
    func_0020DD48(&D_004922E0);
    func_0020DD48(&D_004922F0);
    func_0020DF30(&D_00492220);
    func_0020DF30(&D_00492230);
    func_0020DF30(&D_00492240);
    func_0020DF30(&D_00492250);
    func_0020DF30(&D_00492260);
    func_0020DF30(&D_00492270);
    func_0020DF30(&D_00492280);
    func_0020DF30(&D_00492290);
    func_0020DF30(&D_004922A0);
    func_0020DF30(&D_004922B0);
    func_0020DF30(&D_004922C0);
    func_0020DF30(&D_004922D0);
    func_0020DF30(&D_004922E0);
    func_0020DF30(&D_004922F0);
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: scalar spill slots, signed min/max selection and scheduling differ.

extern char D_003FB6E8[];
extern s32 D_0040EAE4;
extern void func_002756A8(s32, s32);
extern s32 func_00122900(s32, s32);
extern s32 D_0040F4E8;
extern void* D_0040F0E0;
extern void* func_00123C90(void*, void*, void*);
extern M2C_UNK D_0048EFA8;
extern s32 func_0035CA74(const char*, const char*);
extern s32 func_00122A00(s32, s32);
extern void func_001227A8(s32*);
extern s32 func_00217818(s32);
extern M2C_UNK D_0048F4E0;
extern s32 func_001227C0(s32*);
extern s32 func_0035D728(void*, s8*, ...);
extern s8 D_003FAE50;
extern s32 func_0020DE28(s32*, s8*);
extern s8* func_001087C8(void*, s8*);
extern void* D_0040F4C4;
extern void func_0020DEC8(void*, const char*, ...);
extern s8 D_003FB0F8;
extern s8 D_003FB0D8;
extern void func_0020DD88(void*);
extern M2C_UNK D_004922A0;
extern void* func_00275560(void*, s32, s32, s32);
extern s32 func_00275260(s8*, void*, s32);
extern s32 func_00384DA8(s32, void*, void*, void*, void*);
extern void func_0020DE78(s32*, void*);
extern s8 D_003FB718;
extern s8* func_00108CE0(void*);
extern s32 D_0040F544;
extern s8 D_003FB118;
extern void* func_0024F7D0(s32);
extern void func_0021A7E0(const char*, void*, void*, s32, ...);
extern M2C_UNK D_003FB738;
extern s8 D_003FA968;
extern s32 func_0012F880(void*, s32, s32, s32*);
extern s32 D_0040F4D0;
extern s8 D_003FB750;
extern s8 D_003FB768;

void func_00212940(const char* resultKind) {
    u16 output[40];
    char languageKey[48];
    u16 format[32];
    u16 currentText[16];
    u16 maximumText[16];
    s32 local_100;
    s32 local_104;
    s32 local_108;
    s32 local_10C;
    s32 local_110;
    s32 local_114;
    s32 local_118;
    s32 local_11C;
    s32 local_120;
    s32 local_124;
    s32 local_128;
    s32 local_12C;
    s32 local_130;
    s32 local_134;
    s32 local_138;
    f32 var_f20;
    s32 temp_19;
    s32 temp_17_4;
    s32 temp_23;
    s32 temp_23_2;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_f0;
    s32 temp_lo;
    s32 var_18;
    s32 var_19;
    s32 var_21;
    s32 var_23;
    s32 var_23_2;
    s32 var_4;
    s8* temp_16;
    s8* temp_16_10;
    s8* temp_16_2;
    s8* temp_16_4;
    s8* temp_16_5;
    s8* temp_16_6;
    s8* temp_16_7;
    s8* temp_16_8;
    s8* temp_16_9;
    s8* temp_4;
    s32 var_20;
    s32 var_22;
    void* temp_16_3;
    void* temp_17;
    void* temp_17_10;
    void* temp_17_11;
    void* temp_17_2;
    void* temp_17_3;
    void* temp_17_5;
    void* temp_17_6;
    void* temp_17_7;
    void* temp_17_8;
    void* temp_17_9;

    switch (D_0040EAE4) {
        case 4: func_002756A8(0xA0, 0x2C); break;
        case 3:
        case 5:
        case 6: func_002756A8(0x2E, 0x2C); break;
        default: func_002756A8(0x2C, 0x2E); break;
    }
    local_108 = func_00122900(D_0040F4E8, (s32)M2C_FIELD(D_0040F0E0, u8*, 0x2020C));
    temp_17_3 = func_00123C90(&D_0048EFA8, (void*)local_108, M2C_FIELD(D_0040F0E0, void**, 0x2014C));
    if (func_0035CA74(resultKind, D_003FB6E8) == 0) {
        func_001227A8((s32*)D_0040F4E8);
        func_00217818((s32)&D_0048F4E0);
        local_11C = (s32)M2C_FIELD(temp_17_3, s8*, 0x16);
        temp_16_3 = M2C_FIELD(D_0040F4E8, u32*, 0);
        local_10C = (s32)M2C_FIELD(temp_17_3, s8*, 0x10);
        local_130 = M2C_FIELD(temp_16_3, s8*, 0x19) > 0;
        var_20 = M2C_FIELD(temp_16_3, s8*, 0x15);
        local_134 = M2C_FIELD(temp_16_3, s8*, 0x1A) > 0;
        local_110 = (s32)M2C_FIELD(temp_17_3, s8*, 0x12);
        local_114 = (s32)M2C_FIELD(temp_16_3, s8*, 0x16);
        var_22 = M2C_FIELD(temp_17_3, s8*, 0x14);
        local_118 = (s32)M2C_FIELD(temp_16_3, s8*, 0x17);
        local_120 = (s32)M2C_FIELD(temp_16_3, s8*, 0x18);
        var_18 = func_001227C0((s32*)D_0040F4E8);
        var_19 = (s32)(s16)(M2C_FIELD(temp_16_3, u16*, 0x1C) + M2C_FIELD(temp_16_3, u16*, 0x1E));
        temp_2 = func_00122A00(D_0040F4E8, (s32)(s8)local_108);
        var_f20 = M2C_FIELD(temp_16_3, f32*, 4);
        var_23 = (temp_2 >= var_19) ? temp_2 : var_19;
    } else {
        temp_19 = M2C_FIELD(temp_17_3, s16*, 4);
        local_10C = (s32)M2C_FIELD(temp_17_3, s8*, 0x10);
        var_20 = M2C_FIELD(temp_17_3, s8*, 0x11);
        local_110 = (s32)M2C_FIELD(temp_17_3, s8*, 0x12);
        local_114 = (s32)M2C_FIELD(temp_17_3, s8*, 0x13);
        var_22 = M2C_FIELD(temp_17_3, s8*, 0x14);
        local_118 = (s32)M2C_FIELD(temp_17_3, s8*, 0x15);
        local_11C = (s32)M2C_FIELD(temp_17_3, s8*, 0x16);
        local_120 = (s32)M2C_FIELD(temp_17_3, s8*, 0x17);
        local_130 = (s32)M2C_FIELD(temp_17_3, u8*, 0x18);
        local_134 = (s32)M2C_FIELD(temp_17_3, u8*, 0x19);
        var_18 = M2C_FIELD(temp_17_3, s32*, 0);
        var_23 = func_00122A00(D_0040F4E8, (s32)(s8)local_108);
        var_f20 = M2C_FIELD(temp_17_3, f32*, 0xC);
        var_19 = (var_23 < temp_19) ? var_23 : (s32)temp_19;
    }
    var_21 = 1;
    if (var_18 >= 0) {
        local_124 = 1;
        local_128 = 1;
        local_12C = 1;
    } else {
        local_124 = 0;
        var_21 = 0;
        local_128 = 0;
        local_12C = 0;
    }
    func_0035D728(languageKey, &D_003FAE50, M2C_FIELD(D_0040F0E0, u8*, 0x2020C));
    func_0020DE28(&D_00492220, func_001087C8(D_0040F4C4, languageKey));
    if (var_21 != 0) {
        func_0020DEC8(&D_00492240, func_001087C8(D_0040F4C4, &D_003FB0F8), (s32)var_20, local_10C);
    } else {
        func_0020DEC8(&D_00492240, func_001087C8(D_0040F4C4, &D_003FB0D8), (s32)var_20);
    }
    if (local_124 != 0) {
        func_0020DEC8(&D_00492250, func_001087C8(D_0040F4C4, &D_003FB0F8), local_114, local_110);
    } else {
        func_0020DEC8(&D_00492250, func_001087C8(D_0040F4C4, &D_003FB0D8), local_114);
    }
    if (local_128 != 0) {
        func_0020DEC8(&D_00492260, func_001087C8(D_0040F4C4, &D_003FB0F8), local_118, (s32)var_22);
    } else {
        func_0020DEC8(&D_00492260, func_001087C8(D_0040F4C4, &D_003FB0D8), (s32)var_22);
    }
    if (local_12C != 0) {
        func_0020DEC8(&D_00492270, func_001087C8(D_0040F4C4, &D_003FB0F8), local_120, local_11C);
    } else {
        func_0020DEC8(&D_00492270, func_001087C8(D_0040F4C4, &D_003FB0D8), local_11C);
    }
    func_0020DD88(&D_004922A0);
    func_00275560(currentText, var_19, 1, 0);
    func_00275560(maximumText, var_23, 1, 0);
    temp_23 = local_118 + local_120;
    temp_4 = func_001087C8(D_0040F4C4, "FE_FORMAT_STRINGCOUNT_OF_STRINGCOUNT");
    local_138 = var_22 + local_11C;
    func_00275260(temp_4, format, 0x20);
    local_138 += 2;
    func_00384DA8(0x28, output, format, currentText, maximumText);
    func_0020DE78(&D_004922B0, output);
    temp_f0 = (s32)var_f20;
    temp_lo = temp_f0 / 3600;
    temp_17_4 = (temp_f0 / 60) - (temp_lo * 0x3C);
    func_0020DEC8(&D_004922C0, func_001087C8(D_0040F4C4, &D_003FB718), temp_lo, temp_17_4,
                  ((s32)var_f20 % 3600) - (temp_17_4 * 0x3C));
    func_0020DEC8(&D_00492280, func_001087C8(D_0040F4C4, &D_003FB0F8), (local_130 == 0) ? 0 : 1, 1);
    func_0020DEC8(&D_00492290, func_001087C8(D_0040F4C4, &D_003FB0F8), (local_134 == 0) ? 0 : 1, 1);
    func_0020DE28(&D_004922D0, func_00108CE0((void*)(((s8*)D_0040F0E0) + 0x2014C)));
    temp_23_2 = (local_130 != 0) ? (temp_23 + 1) : temp_23;
    var_23_2 = (local_134 != 0) ? (temp_23_2 + 1) : temp_23_2;
    if (M2C_FIELD(D_0040F0E0, void**, 0x2014C) == (void*)3) {
        var_23_2 += local_114;
        local_138 += local_110;
        goto block_37;
    }
    func_0020DE28(&D_00492250, func_001087C8(D_0040F4C4, &D_003FB118));
    temp_16_4 = D_0040F544 + 0x38E7;
    temp_17_5 = func_0024F7D0(0);
    func_0021A7E0((s32)&D_003FB738, NULL, temp_16_4, 2, temp_17_5, func_0024F7D0(0));
    if (M2C_FIELD(D_0040F0E0, void**, 0x2014C) != NULL) { goto block_41; }
    func_0020DE28(&D_00492290, func_001087C8(D_0040F4C4, &D_003FB118));
    temp_16_5 = D_0040F544 + 0x38E7;
    temp_17_6 = func_0024F7D0(4);
    func_0021A7E0((s32)&D_003FB738, NULL, temp_16_5, 2, temp_17_6, func_0024F7D0(0));
    func_0020DE28(&D_00492280, func_001087C8(D_0040F4C4, &D_003FB118));
    temp_16_6 = D_0040F544 + 0x38E7;
    temp_17_7 = func_0024F7D0(3);
    func_0021A7E0((s32)&D_003FB738, NULL, temp_16_6, 2, temp_17_7, func_0024F7D0(0));
    func_0020DE28(&D_00492270, func_001087C8(D_0040F4C4, &D_003FB118));
    temp_16_7 = D_0040F544 + 0x38E7;
    temp_17_8 = func_0024F7D0(2);
    func_0021A7E0((s32)&D_003FB738, NULL, temp_16_7, 2, temp_17_8, func_0024F7D0(0));
    func_0020DE28(&D_00492260, func_001087C8(D_0040F4C4, &D_003FB118));
    temp_16_8 = D_0040F544 + 0x38E7;
    temp_17_9 = func_0024F7D0(1);
    func_0021A7E0((s32)&D_003FB738, NULL, temp_16_8, 2, temp_17_9, func_0024F7D0(0));
block_37:
    if (M2C_FIELD(D_0040F0E0, void**, 0x2014C) != NULL) {
    block_41:
        func_0020DEC8(&D_004922E0, &D_003FA968, var_23_2);
        func_0012F880(D_0040F4D0 + 0x910, local_108, (s32)M2C_FIELD(D_0040F0E0, void**, 0x2014C), &local_100);
        func_0020DEC8(&D_004922F0, &D_003FA968, local_100);
    } else {
        func_0020DE28(&D_004922E0, func_001087C8(D_0040F4C4, &D_003FB118));
        func_0020DE28(&D_004922F0, func_001087C8(D_0040F4C4, &D_003FB118));
    }
    temp_2_2 = func_0012F880(D_0040F4D0 + 0x910, local_108, (s32)M2C_FIELD(D_0040F0E0, void**, 0x2014C), &local_104);
    if (temp_2_2 == 1 || (temp_2_2 == 2 && var_23_2 >= local_104) || (temp_2_2 == 0 && var_23_2 >= local_138)) {
        func_0020DE28(&D_00492230, func_001087C8(D_0040F4C4, &D_003FB750));
        temp_16_10 = D_0040F544 + 0x38E7;
        temp_17_11 = func_0024F7D0(8);
        func_0021A7E0((s32)&D_003FB738, NULL, temp_16_10, 2, temp_17_11, func_0024F7D0(1));
        temp_16 = D_0040F544 + 0x38E7;
        temp_17 = func_0024F7D0(7);
        func_0021A7E0((s32)&D_003FB738, NULL, temp_16, 2, temp_17, func_0024F7D0(1));
        return;
    } else {
        func_0020DE28(&D_00492230, func_001087C8(D_0040F4C4, &D_003FB768));
        temp_16_9 = D_0040F544 + 0x38E7;
        temp_17_10 = func_0024F7D0(7);
        func_0021A7E0((s32)&D_003FB738, NULL, temp_16_9, 2, temp_17_10, func_0024F7D0(2));
        temp_16_2 = D_0040F544 + 0x38E7;
        temp_17_2 = func_0024F7D0(8);
        func_0021A7E0((s32)&D_003FB738, NULL, temp_16_2, 2, temp_17_2, func_0024F7D0(2));
        return;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_212528", func_00212940);
#endif
