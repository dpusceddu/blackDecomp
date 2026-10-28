#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

#ifdef NON_MATCHING
// Unmatched: the second external-loop counter uses a different load/copy sequence.
/* Working by-value key layout; the original type name is unknown. */
typedef struct ActionKey {
    unsigned long value;
} ActionKey;

/* Provisional offset views; original class and field names are unknown. */
typedef struct Recovered_ActionView {
    u64 unk_0;
    u8 unk_8[16];
    u32 unk_18;
    u8 unk_1C;
    u8 unk_1D[3];
    u32 unk_20;
    u32 unk_24;
    u8 unk_28[4];
    u32 unk_2C;
} Recovered_ActionView;

typedef struct Recovered_CountdownAction {
    u64 unk_0;
    u8 unk_8[8];
    void* unk_10;
    u8 unk_14[4];
    u8 unk_18;
    u8 unk_19[3];
    f32 unk_1C;
    u32 unk_20;
} Recovered_CountdownAction;

typedef struct Recovered_FrontendResourceTable {
    u8 unk_0[940];
    void* unk_3AC;
    u8 unk_3B0[4];
    u32 unk_3B4;
    u8 unk_3B8;
} Recovered_FrontendResourceTable;

typedef struct Recovered_PairedBank {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
    u8 unk_C[4];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
} Recovered_PairedBank;

extern u32 func_00107CE8(Recovered_FrontendResourceTable*);
extern Recovered_FrontendResourceTable D_0040F0F0;
extern void* func_00107D20(u32);
extern void func_00107B78(Recovered_FrontendResourceTable*, s32, u32, s32);
extern void func_0012F060(Recovered_PairedBank*, s8);
extern Recovered_PairedBank* D_0040F538;
extern void* func_00107CF8(u32);
extern M2C_UNK D_003DD168;
extern void func_001743F0(s32, s32);
extern M2C_UNK D_003DC010;
extern void func_00169EF8(s32, s32);
extern M2C_UNK D_003DBF48;
extern void func_0016A7A0(void*, s32);
extern M2C_UNK D_003DC4C8;
extern void func_0016C708(void*);
extern M2C_UNK D_003DB828;
extern void func_00163CC8(void*, s32);
extern M2C_UNK D_003DC6B8;
extern M2C_UNK D_003DC6E8;
extern void func_00153758(void*, ActionKey, void*);
extern M2C_UNK D_003DC0D0;
extern void func_001650B8(void*, s32);
extern M2C_UNK D_003DC130;
extern void func_001651D0(Recovered_CountdownAction*, s32);
extern M2C_UNK D_003DC100;
extern void func_001652F0(Recovered_ActionView*, s32);
extern M2C_UNK D_003DBF10;
extern void func_00161ED0(void*);
extern M2C_UNK D_003DBC38;
extern void func_00162738(void*);
extern M2C_UNK D_003DBC00;
extern void func_001628C8(void*);
extern M2C_UNK D_003DBED8;
extern void func_00163230(void*);
extern M2C_UNK D_003DC200;
extern void func_00162160(Recovered_ActionView*, s32);
extern M2C_UNK D_003DBEA0;
extern M2C_UNK D_003DFFC8;
extern void func_001625E0(void*);
extern M2C_UNK D_003DBE68;
extern void func_00160F20(void*, s32);
extern M2C_UNK D_003DB7A8;
extern M2C_UNK D_003E26B0;
extern M2C_UNK D_003DB758;
extern M2C_UNK D_003DB708;
extern M2C_UNK D_003DBE30;
extern void func_00160E70(void*);
extern M2C_UNK D_003DBDC0;
extern M2C_UNK D_003DC588;
extern M2C_UNK D_003DBDF8;
extern M2C_UNK D_003DBCE0;
extern M2C_UNK D_003DBCA8;
extern M2C_UNK D_003DBC70;
extern M2C_UNK D_003DBD88;
extern void func_00161920(void*);
extern M2C_UNK D_003DBD50;
extern void func_00161AA8(s32*, s32);
extern M2C_UNK D_003DBD18;
extern void func_00161D58(void*);
extern M2C_UNK D_003DC5C0;
extern void func_00183578(s32, s32);
extern M2C_UNK D_003DBBC8;
extern void func_00162A40(void*);
extern M2C_UNK D_003DBB90;
extern void func_00162F08(void*);
extern M2C_UNK D_003DBB58;
extern void func_00162CF0(void*);
extern M2C_UNK D_003DB6D0;
extern void func_0016AC98(void*);
extern void func_0014C548(void*, s32);
extern void func_0014C550(s32);
extern M2C_UNK D_003DBAA0;
extern void func_00164E40(void*);
extern void func_0014EC08(void*);
extern void* func_00383B08(void*);
extern void func_001653F0(void*, s32);
extern M2C_UNK D_003DB920;
extern void func_00164248(void*);
extern M2C_UNK D_003DB860;
extern void func_001648E0(void*);
extern M2C_UNK D_003DCF18;
extern void func_00174CD8(void*, void*, void*);
extern M2C_UNK D_003DD0E8;
extern void func_00174DD0(void*);
extern M2C_UNK D_003DCED0;
extern void func_00175090(void*, ActionKey, void*, void*);
extern M2C_UNK D_003DCE88;
extern void func_001751E0(void*, void*, void*);
extern M2C_UNK D_003DCE40;
extern void func_001752D8(void*);
extern M2C_UNK D_003DCDF8;
extern void func_00175348(void*, void*, void*);
extern M2C_UNK D_003DCDB0;
extern void func_00175440(void*);
extern M2C_UNK D_003DCD68;
extern void func_001754B0(void*, void*, void*);
extern M2C_UNK D_003DCD20;
extern void func_001755A8(void*);
extern M2C_UNK D_003DCCD8;
extern void func_00175648(void*);
extern void func_0012F208(Recovered_PairedBank*, u64, s128);
extern M2C_UNK D_003DB7F8;
extern void func_00163DE8(void*);

/* Call-site interfaces are provisional; some callees ignore native argument registers. */
void func_0015D958(void* self, void* definitions, s32 firstEntries, s32 firstCount, s32 secondEntries, s32 secondCount,
                   s32 unused) {
    s32 firstEntriesCopy;
    s32 secondEntriesCopy;
    s32 secondCountCopy;
    u32 savedAlignment;
    M2C_UNK* temp_3_2;
    M2C_UNK* temp_5;
    M2C_UNK* temp_5_2;
    Recovered_ActionView* temp_2_27;
    Recovered_ActionView* temp_2_32;
    Recovered_CountdownAction* temp_2_26;
    Recovered_FrontendResourceTable* temp_4_10;
    Recovered_FrontendResourceTable* temp_4_11;
    Recovered_FrontendResourceTable* temp_4_12;
    Recovered_FrontendResourceTable* temp_4_13;
    Recovered_FrontendResourceTable* temp_4_14;
    Recovered_FrontendResourceTable* temp_4_15;
    Recovered_FrontendResourceTable* temp_4_16;
    Recovered_FrontendResourceTable* temp_4_17;
    Recovered_FrontendResourceTable* temp_4_18;
    Recovered_FrontendResourceTable* temp_4_19;
    Recovered_FrontendResourceTable* temp_4_20;
    Recovered_FrontendResourceTable* temp_4_21;
    Recovered_FrontendResourceTable* temp_4_22;
    Recovered_FrontendResourceTable* temp_4_23;
    Recovered_FrontendResourceTable* temp_4_24;
    Recovered_FrontendResourceTable* temp_4_25;
    Recovered_FrontendResourceTable* temp_4_26;
    Recovered_FrontendResourceTable* temp_4_27;
    Recovered_FrontendResourceTable* temp_4_28;
    Recovered_FrontendResourceTable* temp_4_29;
    Recovered_FrontendResourceTable* temp_4_2;
    Recovered_FrontendResourceTable* temp_4_30;
    Recovered_FrontendResourceTable* temp_4_31;
    Recovered_FrontendResourceTable* temp_4_32;
    Recovered_FrontendResourceTable* temp_4_33;
    Recovered_FrontendResourceTable* temp_4_34;
    Recovered_FrontendResourceTable* temp_4_35;
    Recovered_FrontendResourceTable* temp_4_36;
    Recovered_FrontendResourceTable* temp_4_37;
    Recovered_FrontendResourceTable* temp_4_38;
    Recovered_FrontendResourceTable* temp_4_39;
    Recovered_FrontendResourceTable* temp_4_3;
    Recovered_FrontendResourceTable* temp_4_40;
    Recovered_FrontendResourceTable* temp_4_41;
    Recovered_FrontendResourceTable* temp_4_42;
    Recovered_FrontendResourceTable* temp_4_43;
    Recovered_FrontendResourceTable* temp_4_44;
    Recovered_FrontendResourceTable* temp_4_45;
    Recovered_FrontendResourceTable* temp_4_46;
    Recovered_FrontendResourceTable* temp_4_47;
    Recovered_FrontendResourceTable* temp_4_48;
    Recovered_FrontendResourceTable* temp_4_49;
    Recovered_FrontendResourceTable* temp_4_4;
    Recovered_FrontendResourceTable* temp_4_5;
    Recovered_FrontendResourceTable* temp_4_6;
    Recovered_FrontendResourceTable* temp_4_7;
    Recovered_FrontendResourceTable* temp_4_8;
    Recovered_FrontendResourceTable* temp_4_9;
    s32* temp_2_46;
    s32 temp_4;
    s32 definitionIndex;
    s32 firstCursor;
    s32 secondCursor;
    s32 firstRemaining;
    s32 secondRemaining;
    u32 temp_3;
    void* temp_17;
    void* definition;
    void* temp_21;
    void* temp_2_19;
    void* temp_2_20;
    void* temp_2_21;
    void* temp_2_22;
    void* temp_2_23;
    void* temp_2_24;
    void* temp_2_25;
    void* temp_2_28;
    void* temp_2_29;
    void* temp_2_30;
    void* temp_2_31;
    void* temp_2_33;
    void* temp_2_34;
    void* temp_2_35;
    void* temp_2_36;
    void* temp_2_37;
    void* temp_2_38;
    void* temp_2_39;
    void* temp_2_40;
    void* temp_2_41;
    void* temp_2_42;
    void* temp_2_43;
    void* temp_2_44;
    void* temp_2_45;
    void* temp_2_47;
    void* temp_2_48;
    void* temp_2_49;
    void* temp_2_50;
    void* temp_2_51;
    void* temp_2_52;
    void* temp_2_53;
    void* temp_2_54;
    void* temp_2_55;
    void* temp_2_56;
    void* temp_2_57;
    void* temp_2_58;
    void* temp_2_59;
    void* temp_2_60;
    void* temp_2_61;
    void* temp_2_62;
    void* temp_2_63;
    void* temp_2_64;
    void* temp_2_65;
    void* temp_2_66;
    void* temp_2_67;
    void* temp_6;
    s32 capacity;
    M2C_UNK** bankSlot;
    s32 thisAdjustment;

    capacity = (M2C_FIELD(definitions, u32*, 0x60) & 0xFFFFU);
    M2C_FIELD(self, s32*, 0x9C) = 0;
    M2C_FIELD(self, s32*, 0x98) = capacity;
    M2C_FIELD(self, void**, 0x94) = NULL;
    firstEntriesCopy = firstEntries;
    M2C_FIELD(self, void**, 8) = NULL;
    M2C_FIELD(self, void**, 0x10) = NULL;
    secondEntriesCopy = secondEntries;
    M2C_FIELD(self, void**, 0x14) = NULL;
    secondCountCopy = secondCount;
    M2C_FIELD(self, void**, 0x18) = NULL;
    M2C_FIELD(self, void**, 0x1C) = NULL;
    M2C_FIELD(self, void**, 0x20) = NULL;
    M2C_FIELD(self, void**, 0x24) = NULL;
    M2C_FIELD(self, void**, 0x2C) = NULL;
    M2C_FIELD(self, void**, 0x30) = NULL;
    M2C_FIELD(self, void**, 0x34) = NULL;
    M2C_FIELD(self, void**, 0x38) = NULL;
    M2C_FIELD(self, void**, 0x3C) = NULL;
    M2C_FIELD(self, void**, 0x40) = NULL;
    M2C_FIELD(self, void**, 0) = NULL;
    M2C_FIELD(self, void**, 0x44) = NULL;
    M2C_FIELD(self, void**, 0x48) = NULL;
    M2C_FIELD(self, void**, 0x4C) = NULL;
    M2C_FIELD(self, s32*, 0xC) = 0;
    M2C_FIELD(self, s32*, 0x50) = 0;
    M2C_FIELD(self, s32*, 0x58) = 0;
    M2C_FIELD(self, s32*, 0x54) = 0;
    M2C_FIELD(self, s32*, 0x5C) = 0;
    M2C_FIELD(self, s32*, 0x60) = 0;
    M2C_FIELD(self, s32*, 0x78) = 0;
    M2C_FIELD(self, s32*, 0x64) = 0;
    M2C_FIELD(self, s32*, 0x68) = 0;
    M2C_FIELD(self, s32*, 0x6C) = 0;
    M2C_FIELD(self, s32*, 0xA0) = 0;
    M2C_FIELD(self, s32*, 0x70) = 0;
    M2C_FIELD(self, s32*, 0x74) = 0;
    M2C_FIELD(self, s32*, 0x7C) = 0;
    M2C_FIELD(self, s32*, 0x80) = 0;
    M2C_FIELD(self, s32*, 0x84) = 0;
    M2C_FIELD(self, s32*, 4) = 0;
    M2C_FIELD(self, s32*, 0x88) = 0;
    M2C_FIELD(self, s32*, 0x8C) = 0;
    M2C_FIELD(self, s32*, 0x90) = 0;
    savedAlignment = func_00107CE8(&D_0040F0F0);
    temp_4 = M2C_FIELD(self, s32*, 0x98);
    if (temp_4 > 0) { M2C_FIELD(self, void**, 0x94) = func_00107D20(temp_4 * 4); }
    func_00107B78(&D_0040F0F0, (s32)D_0040F0F0.unk_3B4, 0x10U, 0);
    if (M2C_FIELD(definitions, u16*, 0x62) != 0) {
        M2C_FIELD(self, void**, 8) = func_00107D20(M2C_FIELD(definitions, u16*, 0x62) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x68) != 0) {
        M2C_FIELD(self, void**, 0x10) = func_00107D20(M2C_FIELD(definitions, u16*, 0x68) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x6C) != 0) {
        M2C_FIELD(self, void**, 0x14) = func_00107D20(M2C_FIELD(definitions, u16*, 0x6C) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x6A) != 0) {
        M2C_FIELD(self, void**, 0x18) = func_00107D20(M2C_FIELD(definitions, u16*, 0x6A) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x64) != 0) {
        M2C_FIELD(self, void**, 0x1C) = func_00107D20(M2C_FIELD(definitions, u16*, 0x64) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x66) != 0) {
        M2C_FIELD(self, void**, 0x20) = func_00107D20(M2C_FIELD(definitions, u16*, 0x66) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x72) != 0) {
        M2C_FIELD(self, void**, 0x24) = func_00107D20(M2C_FIELD(definitions, u16*, 0x72) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x7E) != 0) {
        M2C_FIELD(self, void**, 0x3C) = func_00107D20(M2C_FIELD(definitions, u16*, 0x7E) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x6E) != 0) {
        M2C_FIELD(self, void**, 0x2C) = func_00107D20(M2C_FIELD(definitions, u16*, 0x6E) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x76) != 0) {
        M2C_FIELD(self, void**, 0x30) = func_00107D20(M2C_FIELD(definitions, u16*, 0x76) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x78) != 0) {
        M2C_FIELD(self, void**, 0x34) = func_00107D20(M2C_FIELD(definitions, u16*, 0x78) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x7A) != 0) {
        M2C_FIELD(self, void**, 0x38) = func_00107D20(M2C_FIELD(definitions, u16*, 0x7A) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x7C) != 0) {
        M2C_FIELD(self, void**, 0x28) = func_00107D20(M2C_FIELD(definitions, u16*, 0x7C) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x80) != 0) {
        M2C_FIELD(self, void**, 0x40) = func_00107D20(M2C_FIELD(definitions, u16*, 0x80) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x84) != 0) {
        M2C_FIELD(self, void**, 0) = func_00107D20(M2C_FIELD(definitions, u16*, 0x84) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x86) != 0) {
        M2C_FIELD(self, void**, 0x44) = func_00107D20(M2C_FIELD(definitions, u16*, 0x86) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x88) != 0) {
        M2C_FIELD(self, void**, 0x48) = func_00107D20(M2C_FIELD(definitions, u16*, 0x88) * 4);
    }
    if (M2C_FIELD(definitions, u16*, 0x8A) != 0) {
        M2C_FIELD(self, void**, 0x4C) = func_00107D20(M2C_FIELD(definitions, u16*, 0x8A) * 4);
    }
    func_0012F060(D_0040F538, M2C_FIELD(definitions, s8*, 0x82));
    for (definitionIndex = 0; definitionIndex < M2C_FIELD(definitions, s32*, 0); definitionIndex++) {
        definition = M2C_FIELD(definitions, s32*, 4) + (definitionIndex * 0x10);
        temp_3 = M2C_FIELD(definition, u32*, 0);
        switch (temp_3) {
            case 0:
            case 1:
            case 2: break;
            case 0x3:
            case 0x4:
            case 0x5:
            case 0x6:
            case 0x7:
            case 0x8:
            case 0x9:
                func_00107B78(&D_0040F0F0, (s32)D_0040F0F0.unk_3B4, 0x10U, 0);
                temp_2_19 = func_00107CF8(0x48U);
                M2C_FIELD(temp_2_19, M2C_UNK**, 0x10) = &D_003DD168;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x64) * 4) + ((s8*)M2C_FIELD(self, void**, 0x24)))), u32*,
                          0) = temp_2_19;
                func_001743F0((s32)temp_2_19, (s32)M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x64) = (s32)(M2C_FIELD(self, s32*, 0x64) + 1);
                break;
            case 0xB:
                temp_4_2 = &D_0040F0F0;
                func_00107B78(temp_4_2, temp_4_2->unk_3B4, 0x10U, 0);
                temp_2_20 = func_00107CF8(0x160U);
                M2C_FIELD(temp_2_20, M2C_UNK**, 0x10) = &D_003DC010;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0xC) * 4) + ((s8*)M2C_FIELD(self, void**, 8)))), u32*, 0) =
                    temp_2_20;
                func_00169EF8((s32)temp_2_20, (s32)M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0xC) = (s32)(M2C_FIELD(self, s32*, 0xC) + 1);
                break;
            case 0xC:
                temp_4_3 = &D_0040F0F0;
                func_00107B78(temp_4_3, temp_4_3->unk_3B4, 0x10U, 0);
                temp_2_21 = func_00107CF8(0x170U);
                M2C_FIELD(temp_2_21, M2C_UNK**, 0x10) = &D_003DBF48;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0xC) * 4) + ((s8*)M2C_FIELD(self, void**, 8)))), u32*, 0) =
                    temp_2_21;
                func_0016A7A0(temp_2_21, M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0xC) = (s32)(M2C_FIELD(self, s32*, 0xC) + 1);
                break;
            case 0x43:
                temp_4_4 = &D_0040F0F0;
                func_00107B78(temp_4_4, temp_4_4->unk_3B4, 0x10U, 0);
                temp_2_22 = func_00107CF8(0x1C0U);
                M2C_FIELD(temp_2_22, M2C_UNK**, 0x10) = &D_003DC4C8;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x90) * 4) + ((s8*)M2C_FIELD(self, void**, 0x4C)))), u32*,
                          0) = temp_2_22;
                func_0016C708(temp_2_22);
                M2C_FIELD(self, s32*, 0x90) = (s32)(M2C_FIELD(self, s32*, 0x90) + 1);
                break;
            case 0x12:
                temp_4_5 = &D_0040F0F0;
                func_00107B78(temp_4_5, temp_4_5->unk_3B4, 0x10U, 0);
                temp_2_23 = func_00107CF8(0x90U);
                M2C_FIELD(temp_2_23, M2C_UNK**, 0x10) = &D_003DB828;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x84) * 4) + ((s8*)M2C_FIELD(self, void**, 0x40)))), u32*,
                          0) = temp_2_23;
                func_00163CC8(temp_2_23, (s32)M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x84) = (s32)(M2C_FIELD(self, s32*, 0x84) + 1);
                break;
            case 0x41:
                temp_4_6 = &D_0040F0F0;
                func_00107B78(temp_4_6, temp_4_6->unk_3B4, 0x10U, 0);
                temp_2_24 = func_00107CF8(0x150U);
                M2C_FIELD(temp_2_24, void**, 0x10) = &D_003DC6B8;
                M2C_FIELD(temp_2_24, void**, 0x80) = &D_003DC6E8;
                func_00153758(temp_2_24, M2C_FIELD(definition, ActionKey*, 8), M2C_FIELD(definition, void**, 4));
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 4) * 4) + ((s8*)M2C_FIELD(self, void**, 0)))), u32*, 0) =
                    temp_2_24;
                M2C_FIELD(self, s32*, 4) = (s32)(M2C_FIELD(self, s32*, 4) + 1);
                break;
            case 0xF:
                temp_4_7 = &D_0040F0F0;
                func_00107B78(temp_4_7, temp_4_7->unk_3B4, 0x10U, 0);
                temp_2_25 = func_00107CF8(0x20U);
                M2C_FIELD(temp_2_25, M2C_UNK**, 0x10) = &D_003DC0D0;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x54) * 4) + ((s8*)M2C_FIELD(self, void**, 0x14)))), u32*,
                          0) = temp_2_25;
                func_001650B8(temp_2_25, (s32)M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x54) = (s32)(M2C_FIELD(self, s32*, 0x54) + 1);
                break;
            case 0x10:
                temp_4_8 = &D_0040F0F0;
                func_00107B78(temp_4_8, temp_4_8->unk_3B4, 0x10U, 0);
                temp_2_26 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_26, M2C_UNK**, 0x10) = &D_003DC130;
                M2C_FIELD(((Recovered_CountdownAction**)((M2C_FIELD(self, s32*, 0x50) * 4) +
                                                         ((s8*)M2C_FIELD(self, void**, 0x10)))),
                          u32*, 0) = temp_2_26;
                func_001651D0(temp_2_26, (s32)M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x50) = (s32)(M2C_FIELD(self, s32*, 0x50) + 1);
                break;
            case 0x11:
                temp_4_9 = &D_0040F0F0;
                func_00107B78(temp_4_9, temp_4_9->unk_3B4, 0x10U, 0);
                temp_2_27 = func_00107CF8(0x20U);
                M2C_FIELD(temp_2_27, M2C_UNK**, 0x10) = &D_003DC100;
                M2C_FIELD(((Recovered_ActionView**)((M2C_FIELD(self, s32*, 0x58) * 4) +
                                                    ((s8*)M2C_FIELD(self, void**, 0x18)))),
                          u32*, 0) = temp_2_27;
                func_001652F0(temp_2_27, (s32)M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x58) = (s32)(M2C_FIELD(self, s32*, 0x58) + 1);
                break;
            case 0x1B:
                temp_4_10 = &D_0040F0F0;
                func_00107B78(temp_4_10, temp_4_10->unk_3B4, 0x10U, 0);
                temp_2_28 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_28, M2C_UNK**, 0x10) = &D_003DBF10;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_28;
                func_00161ED0(temp_2_28);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x25:
                temp_4_11 = &D_0040F0F0;
                func_00107B78(temp_4_11, temp_4_11->unk_3B4, 0x10U, 0);
                temp_2_29 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_29, M2C_UNK**, 0x10) = &D_003DBC38;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_29;
                func_00162738(temp_2_29);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x26:
                temp_4_12 = &D_0040F0F0;
                func_00107B78(temp_4_12, temp_4_12->unk_3B4, 0x10U, 0);
                temp_2_30 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_30, M2C_UNK**, 0x10) = &D_003DBC00;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_30;
                func_001628C8(temp_2_30);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x23:
                temp_4_13 = &D_0040F0F0;
                func_00107B78(temp_4_13, temp_4_13->unk_3B4, 0x10U, 0);
                temp_2_31 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_31, M2C_UNK**, 0x10) = &D_003DBED8;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_31;
                func_00163230(temp_2_31);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x13:
                temp_4_14 = &D_0040F0F0;
                func_00107B78(temp_4_14, temp_4_14->unk_3B4, 0x10U, 0);
                temp_2_32 = func_00107CF8(0x60U);
                M2C_FIELD(temp_2_32, M2C_UNK**, 0x10) = &D_003DC200;
                M2C_FIELD(((Recovered_ActionView**)((M2C_FIELD(self, s32*, 0x5C) * 4) +
                                                    ((s8*)M2C_FIELD(self, void**, 0x1C)))),
                          u32*, 0) = temp_2_32;
                func_00162160(temp_2_32, (s32)M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x14:
                temp_4_15 = &D_0040F0F0;
                func_00107B78(temp_4_15, temp_4_15->unk_3B4, 0x10U, 0);
                temp_2_33 = func_00107CF8(0xA0U);
                M2C_FIELD(temp_2_33, M2C_UNK**, 0x10) = &D_003DBEA0;
                M2C_FIELD(temp_2_33, M2C_UNK**, 0x50) = &D_003DFFC8;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x60) * 4) + ((s8*)M2C_FIELD(self, void**, 0x20)))),
                          M2C_UNK**, 0) = temp_2_33;
                func_001625E0(temp_2_33);
                M2C_FIELD(self, s32*, 0x60) = (s32)(M2C_FIELD(self, s32*, 0x60) + 1);
                break;
            case 0x15:
                temp_4_16 = &D_0040F0F0;
                func_00107B78(temp_4_16, temp_4_16->unk_3B4, 0x10U, 0);
                temp_2_34 = func_00107CF8(0x70U);
                M2C_FIELD(temp_2_34, M2C_UNK**, 0x10) = &D_003DBE68;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_34;
                func_00160F20(temp_2_34, (s32)M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x16:
                temp_4_17 = &D_0040F0F0;
                func_00107B78(temp_4_17, temp_4_17->unk_3B4, 0x10U, 0);
                temp_2_35 = func_00107CF8(0x40U);
                M2C_FIELD(temp_2_35, M2C_UNK**, 0x10) = &D_003DB7A8;
                M2C_FIELD(temp_2_35, M2C_UNK**, 0x20) = &D_003E26B0;
                bankSlot = (M2C_UNK**)(M2C_FIELD(self, s32*, 0x5C) * 4 + M2C_FIELD(self, u32*, 0x1C));
                M2C_FIELD(temp_2_35, s8*, 0x24) = 0;
                *bankSlot = temp_2_35;
                temp_3_2 = M2C_FIELD(temp_2_35, M2C_UNK**, 0x10);
                temp_6 = M2C_FIELD(definition, M2C_UNK**, 4);
                M2C_FIELD(temp_3_2, void (**)(void*, u8),
                          0x34)((void*)(((s8*)temp_2_35) + M2C_FIELD(temp_3_2, s16*, 0x30)), M2C_FIELD(temp_6, u8*, 4));
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x17:
                temp_4_18 = &D_0040F0F0;
                func_00107B78(temp_4_18, temp_4_18->unk_3B4, 0x10U, 0);
                temp_2_36 = func_00107CF8(0x30U);
                M2C_FIELD(temp_2_36, M2C_UNK**, 0x10) = &D_003DB758;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))),
                          M2C_UNK**, 0) = temp_2_36;
                temp_5 = M2C_FIELD(temp_2_36, M2C_UNK**, 0x10);
                M2C_FIELD(temp_5, void (**)(void*, u8), 0x34)((void*)(((s8*)temp_2_36) + M2C_FIELD(temp_5, s16*, 0x30)),
                                                              M2C_FIELD(M2C_FIELD(definition, M2C_UNK**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x18:
                temp_4_19 = &D_0040F0F0;
                func_00107B78(temp_4_19, temp_4_19->unk_3B4, 0x10U, 0);
                temp_2_37 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_37, M2C_UNK**, 0x10) = &D_003DB708;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))),
                          M2C_UNK**, 0) = temp_2_37;
                temp_5_2 = M2C_FIELD(temp_2_37, M2C_UNK**, 0x10);
                M2C_FIELD(temp_5_2, void (**)(void*, u8),
                          0x34)((void*)(((s8*)temp_2_37) + M2C_FIELD(temp_5_2, s16*, 0x30)),
                                M2C_FIELD(M2C_FIELD(definition, M2C_UNK**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x1C:
                temp_4_20 = &D_0040F0F0;
                func_00107B78(temp_4_20, temp_4_20->unk_3B4, 0x10U, 0);
                temp_2_38 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_38, M2C_UNK**, 0x10) = &D_003DBE30;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_38;
                func_00160E70(temp_2_38);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x1D:
                temp_4_21 = &D_0040F0F0;
                func_00107B78(temp_4_21, temp_4_21->unk_3B4, 0x10U, 0);
                temp_2_39 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_39, M2C_UNK**, 0x10) = &D_003DBDC0;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_39;
                func_00160E70(temp_2_39);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x1E:
                temp_4_22 = &D_0040F0F0;
                func_00107B78(temp_4_22, temp_4_22->unk_3B4, 0x10U, 0);
                temp_2_40 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_40, M2C_UNK**, 0x10) = &D_003DC588;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x8C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x48)))), u32*,
                          0) = temp_2_40;
                func_00160E70(temp_2_40);
                M2C_FIELD(self, s32*, 0x8C) = (s32)(M2C_FIELD(self, s32*, 0x8C) + 1);
                break;
            case 0x22:
                temp_4_23 = &D_0040F0F0;
                func_00107B78(temp_4_23, temp_4_23->unk_3B4, 0x10U, 0);
                temp_2_41 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_41, M2C_UNK**, 0x10) = &D_003DBDF8;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_41;
                func_00160E70(temp_2_41);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x1F:
                temp_4_24 = &D_0040F0F0;
                func_00107B78(temp_4_24, temp_4_24->unk_3B4, 0x10U, 0);
                temp_2_42 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_42, M2C_UNK**, 0x10) = &D_003DBCE0;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_42;
                func_00160E70(temp_2_42);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x20:
                temp_4_25 = &D_0040F0F0;
                func_00107B78(temp_4_25, temp_4_25->unk_3B4, 0x10U, 0);
                temp_2_43 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_43, M2C_UNK**, 0x10) = &D_003DBCA8;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_43;
                func_00160E70(temp_2_43);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x42:
                temp_4_26 = &D_0040F0F0;
                func_00107B78(temp_4_26, temp_4_26->unk_3B4, 0x10U, 0);
                temp_2_44 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_44, M2C_UNK**, 0x10) = &D_003DBC70;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_44;
                func_00160E70(temp_2_44);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x19:
                temp_4_27 = &D_0040F0F0;
                func_00107B78(temp_4_27, temp_4_27->unk_3B4, 0x10U, 0);
                temp_2_45 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_45, M2C_UNK**, 0x10) = &D_003DBD88;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_45;
                func_00161920(temp_2_45);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x1A:
                temp_4_28 = &D_0040F0F0;
                func_00107B78(temp_4_28, temp_4_28->unk_3B4, 0x10U, 0);
                temp_2_46 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_46, M2C_UNK**, 0x10) = &D_003DBD50;
                M2C_FIELD(((s32**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), s32**,
                          0) = temp_2_46;
                func_00161AA8(temp_2_46, (s32)M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x36:
                temp_4_29 = &D_0040F0F0;
                func_00107B78(temp_4_29, temp_4_29->unk_3B4, 0x10U, 0);
                temp_2_47 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_47, M2C_UNK**, 0x10) = &D_003DBD18;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_47;
                func_00161D58(temp_2_47);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x34:
                temp_4_30 = &D_0040F0F0;
                func_00107B78(temp_4_30, temp_4_30->unk_3B4, 0x10U, 0);
                temp_2_48 = func_00107CF8(0x50U);
                M2C_FIELD(temp_2_48, M2C_UNK**, 0x10) = &D_003DC5C0;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_48;
                func_00183578((s32)temp_2_48, (s32)M2C_FIELD(M2C_FIELD(definition, void**, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x27:
                temp_4_31 = &D_0040F0F0;
                func_00107B78(temp_4_31, temp_4_31->unk_3B4, 0x10U, 0);
                temp_2_49 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_49, M2C_UNK**, 0x10) = &D_003DBBC8;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_49;
                func_00162A40(temp_2_49);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x28:
                temp_4_32 = &D_0040F0F0;
                func_00107B78(temp_4_32, temp_4_32->unk_3B4, 0x10U, 0);
                temp_2_50 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_50, M2C_UNK**, 0x10) = &D_003DBB90;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_50;
                func_00162F08(temp_2_50);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x29:
                temp_4_33 = &D_0040F0F0;
                func_00107B78(temp_4_33, temp_4_33->unk_3B4, 0x10U, 0);
                temp_2_51 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_51, M2C_UNK**, 0x10) = &D_003DBB58;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_51;
                func_00162CF0(temp_2_51);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x2A:
                temp_4_34 = &D_0040F0F0;
                func_00107B78(temp_4_34, temp_4_34->unk_3B4, 0x10U, 0);
                temp_2_52 = func_00107CF8(0x28U);
                M2C_FIELD(temp_2_52, M2C_UNK**, 0x10) = &D_003DB6D0;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x5C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x1C)))), u32*,
                          0) = temp_2_52;
                func_0016AC98(temp_2_52);
                M2C_FIELD(self, s32*, 0x5C) = (s32)(M2C_FIELD(self, s32*, 0x5C) + 1);
                break;
            case 0x2D:
                temp_21 = M2C_FIELD(definition, void**, 4);
                if (firstCount > 0) {
                    firstCursor = firstEntriesCopy;
                    firstRemaining = firstCount;
                    do {
                        if (M2C_FIELD(firstCursor, s64*, 0) == M2C_FIELD(definition, s64*, 8)) {
                            func_0014C548((void*)firstCursor, (s32)temp_21);
                            func_0014C550(firstCursor);
                            M2C_FIELD(
                                ((s32*)((M2C_FIELD(self, s32*, 0x9C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x94)))),
                                s32*, 0) = firstCursor;
                            M2C_FIELD(self, s32*, 0x9C) = (s32)(M2C_FIELD(self, s32*, 0x9C) + 1);
                        }
                        firstRemaining -= 1;
                        firstCursor += 0x1D0;
                    } while (firstRemaining != 0);
                }
                secondCursor = secondEntriesCopy;
                secondRemaining = secondCountCopy;
                if (secondRemaining > 0) {
                    do {
                        if (M2C_FIELD(secondCursor, s64*, 0) == M2C_FIELD(definition, s64*, 8)) {
                            func_0014C548((void*)secondCursor, (s32)temp_21);
                            func_0014C550(secondCursor);
                            M2C_FIELD(
                                ((s32*)((M2C_FIELD(self, s32*, 0x9C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x94)))),
                                s32*, 0) = secondCursor;
                            M2C_FIELD(self, s32*, 0x9C) = (s32)(M2C_FIELD(self, s32*, 0x9C) + 1);
                        }
                        secondRemaining -= 1;
                        secondCursor += 0x200;
                    } while (secondRemaining != 0);
                }
                break;
            case 0x2E:
                temp_4_35 = &D_0040F0F0;
                func_00107B78(temp_4_35, temp_4_35->unk_3B4, 0x10U, 0);
                temp_2_53 = func_00107CF8(0x140U);
                M2C_FIELD(temp_2_53, M2C_UNK**, 0x10) = &D_003DBAA0;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x68) * 4) + ((s8*)M2C_FIELD(self, void**, 0x2C)))), u32*,
                          0) = temp_2_53;
                func_00164E40(temp_2_53);
                M2C_FIELD(self, s32*, 0x68) = (s32)(M2C_FIELD(self, s32*, 0x68) + 1);
                break;
            case 0x2B:
                func_0014EC08((char*)self + 0xB0 + M2C_FIELD(self, s32*, 0xA0) * 0x10);
                M2C_FIELD(self, s32*, 0xA0) = (s32)(M2C_FIELD(self, s32*, 0xA0) + 1);
                break;
            case 0x32:
                temp_4_36 = &D_0040F0F0;
                func_00107B78(temp_4_36, temp_4_36->unk_3B4, 0x10U, 0);
                temp_2_54 = func_00383B08(func_00107CF8(0x1A0U));
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x6C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x30)))), u32*,
                          0) = temp_2_54;
                func_001653F0(temp_2_54, (s32)M2C_FIELD((void*)M2C_FIELD(definition, u32*, 4), u8*, 4));
                M2C_FIELD(self, s32*, 0x6C) = (s32)(M2C_FIELD(self, s32*, 0x6C) + 1);
                break;
            case 0x30:
                temp_4_37 = &D_0040F0F0;
                func_00107B78(temp_4_37, temp_4_37->unk_3B4, 0x10U, 0);
                temp_2_55 = func_00107CF8(0x1A0U);
                M2C_FIELD(temp_2_55, M2C_UNK**, 0x10) = &D_003DB920;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x70) * 4) + ((s8*)M2C_FIELD(self, void**, 0x34)))), u32*,
                          0) = temp_2_55;
                func_00164248(temp_2_55);
                M2C_FIELD(self, s32*, 0x70) = (s32)(M2C_FIELD(self, s32*, 0x70) + 1);
                break;
            case 0x31:
                temp_4_38 = &D_0040F0F0;
                func_00107B78(temp_4_38, temp_4_38->unk_3B4, 0x10U, 0);
                temp_2_56 = func_00107CF8(0x1A0U);
                M2C_FIELD(temp_2_56, M2C_UNK**, 0x10) = &D_003DB860;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x74) * 4) + ((s8*)M2C_FIELD(self, void**, 0x38)))), u32*,
                          0) = temp_2_56;
                func_001648E0(temp_2_56);
                M2C_FIELD(self, s32*, 0x74) = (s32)(M2C_FIELD(self, s32*, 0x74) + 1);
                break;
            case 0x37:
                temp_4_39 = &D_0040F0F0;
                func_00107B78(temp_4_39, temp_4_39->unk_3B4, 0x10U, 0);
                temp_2_57 = func_00107CF8(0x38U);
                M2C_FIELD(temp_2_57, M2C_UNK**, 0x10) = &D_003DCF18;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x7C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x3C)))),
                          M2C_UNK**, 0) = temp_2_57;
                func_00174CD8(temp_2_57, definitions, M2C_FIELD(definition, M2C_UNK**, 4));
                M2C_FIELD(self, s32*, 0x7C) = (s32)(M2C_FIELD(self, s32*, 0x7C) + 1);
                break;
            case 0x38:
                temp_4_40 = &D_0040F0F0;
                func_00107B78(temp_4_40, temp_4_40->unk_3B4, 0x10U, 0);
                temp_2_58 = func_00107CF8(0xA0U);
                M2C_FIELD(temp_2_58, M2C_UNK**, 0x10) = &D_003DD0E8;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x7C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x3C)))), u32*,
                          0) = temp_2_58;
                func_00174DD0(temp_2_58);
                M2C_FIELD(self, s32*, 0x7C) = (s32)(M2C_FIELD(self, s32*, 0x7C) + 1);
                break;
            case 0x39:
                temp_4_41 = &D_0040F0F0;
                func_00107B78(temp_4_41, temp_4_41->unk_3B4, 0x80U, 0);
                temp_17 = M2C_FIELD(definition, void**, 4);
                temp_2_59 = func_00107CF8(0xB0U);
                M2C_FIELD(temp_2_59, M2C_UNK**, 0x10) = &D_003DCED0;
                func_00175090(temp_2_59, M2C_FIELD(definition, ActionKey*, 8), temp_17, definitions);
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x7C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x3C)))), u32*,
                          0) = temp_2_59;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x78) * 4) + ((s8*)(void*)M2C_FIELD(self, s32*, 0x28)))),
                          u32*, 0) = (void*)(((s8*)temp_2_59) + 0x28);
                M2C_FIELD(self, s32*, 0x78) = (s32)(M2C_FIELD(self, s32*, 0x78) + 1);
                M2C_FIELD(self, s32*, 0x7C) = (s32)(M2C_FIELD(self, s32*, 0x7C) + 1);
                break;
            case 0x3A:
                temp_4_42 = &D_0040F0F0;
                func_00107B78(temp_4_42, temp_4_42->unk_3B4, 0x10U, 0);
                temp_2_60 = func_00107CF8(0x38U);
                M2C_FIELD(temp_2_60, M2C_UNK**, 0x10) = &D_003DCE88;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x7C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x3C)))),
                          M2C_UNK**, 0) = temp_2_60;
                func_001751E0(temp_2_60, definitions, M2C_FIELD(definition, M2C_UNK**, 4));
                M2C_FIELD(self, s32*, 0x7C) = (s32)(M2C_FIELD(self, s32*, 0x7C) + 1);
                break;
            case 0x3B:
                temp_4_43 = &D_0040F0F0;
                func_00107B78(temp_4_43, temp_4_43->unk_3B4, 0x10U, 0);
                temp_2_61 = func_00107CF8(0x30U);
                M2C_FIELD(temp_2_61, M2C_UNK**, 0x10) = &D_003DCE40;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x7C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x3C)))), u32*,
                          0) = temp_2_61;
                func_001752D8(temp_2_61);
                M2C_FIELD(self, s32*, 0x7C) = (s32)(M2C_FIELD(self, s32*, 0x7C) + 1);
                break;
            case 0x3C:
                temp_4_44 = &D_0040F0F0;
                func_00107B78(temp_4_44, temp_4_44->unk_3B4, 0x10U, 0);
                temp_2_62 = func_00107CF8(0x38U);
                M2C_FIELD(temp_2_62, M2C_UNK**, 0x10) = &D_003DCDF8;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x7C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x3C)))),
                          M2C_UNK**, 0) = temp_2_62;
                func_00175348(temp_2_62, definitions, M2C_FIELD(definition, M2C_UNK**, 4));
                M2C_FIELD(self, s32*, 0x7C) = (s32)(M2C_FIELD(self, s32*, 0x7C) + 1);
                break;
            case 0x3D:
                temp_4_45 = &D_0040F0F0;
                func_00107B78(temp_4_45, temp_4_45->unk_3B4, 0x10U, 0);
                temp_2_63 = func_00107CF8(0x30U);
                M2C_FIELD(temp_2_63, M2C_UNK**, 0x10) = &D_003DCDB0;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x7C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x3C)))), u32*,
                          0) = temp_2_63;
                func_00175440(temp_2_63);
                M2C_FIELD(self, s32*, 0x7C) = (s32)(M2C_FIELD(self, s32*, 0x7C) + 1);
                break;
            case 0x3E:
                temp_4_46 = &D_0040F0F0;
                func_00107B78(temp_4_46, temp_4_46->unk_3B4, 0x10U, 0);
                temp_2_64 = func_00107CF8(0x38U);
                M2C_FIELD(temp_2_64, M2C_UNK**, 0x10) = &D_003DCD68;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x7C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x3C)))),
                          M2C_UNK**, 0) = temp_2_64;
                func_001754B0(temp_2_64, definitions, M2C_FIELD(definition, M2C_UNK**, 4));
                M2C_FIELD(self, s32*, 0x7C) = (s32)(M2C_FIELD(self, s32*, 0x7C) + 1);
                break;
            case 0x3F:
                temp_4_47 = &D_0040F0F0;
                func_00107B78(temp_4_47, temp_4_47->unk_3B4, 0x10U, 0);
                temp_2_65 = func_00107CF8(0x30U);
                M2C_FIELD(temp_2_65, M2C_UNK**, 0x10) = &D_003DCD20;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x7C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x3C)))), u32*,
                          0) = temp_2_65;
                func_001755A8(temp_2_65);
                M2C_FIELD(self, s32*, 0x7C) = (s32)(M2C_FIELD(self, s32*, 0x7C) + 1);
                break;
            case 0x40:
                temp_4_48 = &D_0040F0F0;
                func_00107B78(temp_4_48, temp_4_48->unk_3B4, 0x10U, 0);
                temp_2_66 = func_00107CF8(0x30U);
                M2C_FIELD(temp_2_66, M2C_UNK**, 0x10) = &D_003DCCD8;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x7C) * 4) + ((s8*)M2C_FIELD(self, void**, 0x3C)))), u32*,
                          0) = temp_2_66;
                func_00175648(temp_2_66);
                M2C_FIELD(self, s32*, 0x7C) = (s32)(M2C_FIELD(self, s32*, 0x7C) + 1);
                break;
            case 0x24:
                func_0012F208(D_0040F538, M2C_FIELD(definition, u64*, 8),
                              M2C_FIELD(M2C_FIELD(definition, void**, 4), s128*, 0));
                break;
            case 0x44:
                temp_4_49 = &D_0040F0F0;
                func_00107B78(temp_4_49, temp_4_49->unk_3B4, 0x10U, 0);
                temp_2_67 = func_00107CF8(0x70U);
                M2C_FIELD(temp_2_67, M2C_UNK**, 0x10) = &D_003DB7F8;
                M2C_FIELD(((void**)((M2C_FIELD(self, s32*, 0x88) * 4) + ((s8*)M2C_FIELD(self, void**, 0x44)))), u32*,
                          0) = temp_2_67;
                func_00163DE8(temp_2_67);
                M2C_FIELD(self, s32*, 0x88) = (s32)(M2C_FIELD(self, s32*, 0x88) + 1);
                break;
        }
    }
    func_00107B78(&D_0040F0F0, (s32)D_0040F0F0.unk_3B4, savedAlignment, 0);
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_2", func_0015D958);
#endif
