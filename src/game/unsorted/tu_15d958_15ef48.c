#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

#ifdef NON_MATCHING
// Unmatched: counter spills, mode gating and virtual-call scheduling differ.
/* UNVERIFIED offset views and call interfaces; original type names are unknown. */

typedef struct Recovered_ActionInitView {
    s64 unk_0;
    u8 unk_8[24];
    void* unk_20;
} Recovered_ActionInitView;

typedef struct Recovered_ActionMirrorInitView {
    u64 unk_0;
    u8 unk_8[16];
    u32 unk_18;
    u8 unk_1C[4];
    u32 unk_20;
} Recovered_ActionMirrorInitView;

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

typedef struct Recovered_ActorBinding {
    u64 unk_0;
    u8 unk_8[8];
    void* unk_10;
    u8 unk_14[4];
    u32 unk_18;
    u8 unk_1C;
    u8 unk_1D[3];
    void* unk_20;
    s32 unk_24;
    s16 unk_28;
    u8 unk_2A[2];
    s32 unk_2C;
    u32 unk_30;
    u8 unk_34[12];
    u128 unk_40;
    void* unk_50;
} Recovered_ActorBinding;

typedef struct Recovered_ActorBindingDescriptor {
    u8 unk_0[46];
    u8 unk_2E;
} Recovered_ActorBindingDescriptor;

typedef struct Recovered_AiEntryTable {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
    u8 unk_C[4];
    u64 unk_10;
    void* unk_18;
} Recovered_AiEntryTable;

typedef struct Recovered_AiVectorDefinition {
    u8 unk_0[16];
    s128 unk_10;
    f32 unk_20;
} Recovered_AiVectorDefinition;

typedef struct Recovered_AiVectorEntry {
    u8 unk_0[24];
    u32 unk_18;
    u8 unk_1C[4];
    u128 unk_20;
    f32 unk_30;
    u8 unk_34[4];
    s64 unk_38;
    u32 unk_40;
} Recovered_AiVectorEntry;

typedef struct Recovered_BindingAction {
    u64 unk_0;
    u8 unk_8[136];
    s32 unk_90;
    void* unk_94;
} Recovered_BindingAction;

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

typedef struct Recovered_CountdownDefinition {
    u8 unk_0[8];
    f32 unk_8;
} Recovered_CountdownDefinition;

typedef struct Recovered_CounterAction {
    u64 unk_0;
    u8 unk_8[8];
    void* unk_10;
    u8 unk_14[4];
    s32 unk_18;
    void* unk_1C;
} Recovered_CounterAction;

typedef struct Recovered_GroupView {
    u64 unk_0;
    u8 unk_8[16];
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u32 unk_40;
    u32 unk_44;
    u32 unk_48;
    u32 unk_4C;
    u32 unk_50;
    u32 unk_54;
    u32 unk_58;
    u8 unk_5C[8];
    u32 unk_64;
    u8 unk_68[1];
    u8 unk_69;
} Recovered_GroupView;

typedef struct Recovered_PS2CollisionQueue {
    void* unk_0;
    void* unk_4;
    void* unk_8;
    void* unk_C;
    void* unk_10;
    void* unk_14;
    void* unk_18;
    void* unk_1C;
    s32 unk_20;
    u8 unk_24[32];
    s32 unk_44;
    u8 unk_48[8];
    s32 unk_50;
    u8 unk_54[8];
    s32 unk_5C;
    u8 unk_60[8];
    s32 unk_68;
    u8 unk_6C[8];
    s32 unk_74;
    u8 unk_78[8];
    s32 unk_80;
    u8 unk_84[8];
    s32 unk_8C;
    u8 unk_90[8];
    s32 unk_98;
} Recovered_PS2CollisionQueue;

typedef struct Recovered_ParameterAction {
    u64 unk_0;
    u8 unk_8[16];
    u32 unk_18;
    u8 unk_1C[4];
    u32 unk_20;
} Recovered_ParameterAction;

typedef struct Recovered_ParameterDefinition {
    u8 unk_0[16];
    s128 unk_10;
    u8 unk_20;
} Recovered_ParameterDefinition;

typedef struct Recovered_SequenceState {
    u8 unk_0[144];
    s32 unk_90;
    void* unk_94;
    s32 unk_98;
    s32 unk_9C;
} Recovered_SequenceState;

extern void* memset(void*, int, unsigned int);
extern void* D_0040F4E4;
extern s32 func_00174430(void*, u64, void*, u32, u32, u32);
extern void* func_00138DF8(s32, s32, s128, s64, u64, s32);
extern void* D_0040F514;
extern void* func_00138C40(void*, void*);
extern s32 func_00153B60(void*, u64, void*);
extern s32 func_001650F8(Recovered_CounterAction*, u64, void*);
extern s32 func_00165210(Recovered_CountdownAction*, u64, Recovered_CountdownDefinition*);
extern s32 func_00165330(Recovered_ActionView*, u64, void*);
extern s32 func_00161EF0(void*, s64, s32, s32);
extern s32 func_00162758(Recovered_ActionView*, u64, void*);
extern s32 func_001628E8(Recovered_ActionView*, u64, void*);
extern s32 func_00163250(Recovered_ParameterAction*, u64, Recovered_ParameterDefinition*);
extern s32 func_001621A8(Recovered_ActorBinding*, u64, Recovered_ActorBindingDescriptor*);
extern s32 func_00162600(Recovered_BindingAction*, u64, void*);
extern s32 func_00160F60(void*, u64, void*);
extern s32 func_001615A8(Recovered_ActionInitView*, u64, void*);
extern s32 func_001631B0(Recovered_ActionView*, u64, void*);
extern s32 func_00161730(Recovered_ActionInitView*, u64, void*);
extern s32 func_00161660(Recovered_ActionInitView*, u64, void*);
extern s32 func_00161418(Recovered_ActionInitView*, u64, void*);
extern s32 func_001614E8(Recovered_ActionInitView*, u64, void*);
extern s32 func_001630E8(Recovered_ActionView*, u64, void*);
extern s32 func_001835B8(Recovered_AiVectorEntry*, s64, Recovered_AiVectorDefinition*);
extern s32 func_001836A8(Recovered_AiEntryTable*, Recovered_AiVectorEntry*);
extern s32 func_00162A60(Recovered_ActionView*, u64, void*, void*);
extern s32 func_00162F28(Recovered_ActionView*, u64, void*, void*);
extern s32 func_00162D10(Recovered_ActionView*, u64, void*, void*);
extern s32 func_00161940(Recovered_ActionMirrorInitView*, u64, void*);
extern s32 func_0016ACB8(void*, s64, s32, s32);
extern s32 func_00161AF0(void*, u64, void*, s32);
extern s32 func_00161D78(void*, u64, u32);
extern void func_00175980(Recovered_PS2CollisionQueue*, u64, s32);
extern s32 D_0040F4D4;
extern s32 func_00164E50(void*, s64, s32);
extern void func_001DC690(void*, void*);
extern void* D_0040F510;
extern s32 func_0014EC10(void*, s128, f32);
extern void* D_0040F0E0;
extern s32 func_00126710(void*, u64, void*);
extern s32 func_00174D48(s32, s64, s32, s32);
extern s32 func_00174DF0(Recovered_SequenceState*, s64, void*, s32);
extern s32 func_001750E8(s32, s64, s32, s32);
extern s32 func_00175250(s32, s64, s32, s32);
extern s32 func_001752F8(s32, s64, s32, s32);
extern s32 func_001753B8(s32, s64, s32, s32);
extern s32 func_00175460(s32, s64, s32, s32);
extern s32 func_00175520(s32, s64, s32, s32);
extern s32 func_001755C8(s32, s64, s32, s32);
extern s32 func_00175668(s32, s64, s32, s32);
extern s32 func_00163E08(Recovered_GroupView*, u64, s8*);
extern void* func_00107CF8(u32);
extern s32 func_00174858(void*, void*, s32, s32);
extern void func_0017BDC0(s32, s32, s32);
extern void func_00166D50(s32, s32, s32);
extern s32 D_0040F4F4;
extern void func_00166C30(s32, s32, s32);
extern void func_00166C60(s32, s32, s32);
extern void func_00166C90(s32, s32, s32);
extern void func_00166CC0(s32, s32, s32);
extern void func_00166CF0(s32, s32, s32);
extern void func_00166D20(s32, s32, s32);
extern void func_00166D80(s32, s32, s32);
extern void func_00166DB0(s32, s32, s32);
extern void func_00166DE0(s32, s32, s32);
extern void func_00166E10(s32, s32, s32);
extern void func_00166C00(s32, s32, s32);
extern void func_00166E40(s32, s32, s32);
extern void func_00166E70(s32, s32, s32);
extern void func_00166EA0(s32, s32, s32);
extern void func_00166ED0(s32, s32, s32);
extern void func_00166F00(s32, s32, s32);
extern void func_00166F30(s32, s32, s32);
extern void func_00176FB0(void*, s32, s32);
extern void func_00167208(void*);
extern void func_001604A0(void*, void*, s32);

/* Provisional call-site interfaces and offset views; original type names are unknown. */
s32 func_0015EF48(void* self, void* definitions, s32 arg2, s32 arg3) {
    s32 pending[100];
    s32 contextCopy;
    s32 selectorCopy;
    s32 bank08Index;
    s32 bank10Index;
    s32 bank18Index;
    s32 bank14Index;
    s32 bank20Index;
    s32 bank2CIndex;
    s32 bank30Index;
    s32 bankB0Index;
    s32 bank34Index;
    s32 bank38Index;
    s32 bank40Index;
    s32 bank00Index;
    s32 bank44Index;
    s32 bank48Index;
    s32 bank4CIndex;
    s32 pendingCount;
    Recovered_ActionInitView* temp_4_14;
    Recovered_ActionInitView* temp_4_15;
    Recovered_ActionInitView* temp_4_16;
    Recovered_ActionInitView* temp_4_17;
    Recovered_ActionMirrorInitView* temp_4_22;
    Recovered_ActionView* temp_4_13;
    Recovered_ActionView* temp_4_18;
    Recovered_ActionView* temp_4_19;
    Recovered_ActionView* temp_4_20;
    Recovered_ActionView* temp_4_21;
    Recovered_ActionView* temp_4_5;
    Recovered_ActionView* temp_4_7;
    Recovered_ActionView* temp_4_8;
    Recovered_ActorBinding* temp_4_10;
    Recovered_AiVectorEntry* temp_17_2;
    Recovered_BindingAction* temp_4_11;
    Recovered_CountdownAction* temp_4_4;
    Recovered_CounterAction* temp_4_3;
    Recovered_GroupView* temp_4_37;
    Recovered_ParameterAction* temp_4_9;
    Recovered_SequenceState* temp_4_28;
    s32* temp_5;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_3_8;
    s32 temp_4_27;
    s32 temp_4_29;
    s32 temp_4_30;
    s32 temp_4_31;
    s32 temp_4_32;
    s32 temp_4_33;
    s32 temp_4_34;
    s32 temp_4_35;
    s32 temp_4_36;
    s32 var_16;
    s32 definitionIndex;
    s32 bank1CIndex;
    s32 bank3CIndex;
    s32 bank24Index;
    s32 var_5;
    u32 temp_17_3;
    u32 temp_2_4;
    u32 temp_3;
    u32 temp_6;
    void** temp_2_3;
    void* definition;
    void* temp_2_5;
    void* temp_3_2;
    void* temp_3_3;
    void* temp_3_4;
    void* temp_3_5;
    void* temp_3_6;
    void* temp_3_7;
    void* temp_4;
    void* temp_4_12;
    void* temp_4_23;
    void* temp_4_24;
    void* temp_4_25;
    void* temp_4_26;
    void* temp_4_2;
    void* temp_4_6;
    void* var_7;

    contextCopy = arg2;
    bank1CIndex = 0;
    bank24Index = 0;
    bank3CIndex = 0;
    definitionIndex = 0;
    selectorCopy = (s32)arg3;
    bank08Index = 0;
    memset(pending, 0, 0x190);
    bank10Index = 0;
    bank18Index = 0;
    bank14Index = 0;
    bank20Index = 0;
    bank2CIndex = 0;
    bank30Index = 0;
    bankB0Index = 0;
    bank34Index = 0;
    bank38Index = 0;
    bank40Index = 0;
    bank00Index = 0;
    bank44Index = 0;
    bank48Index = 0;
    bank4CIndex = 0;
    pendingCount = 0;
    M2C_FIELD(D_0040F4E4, s8*, 0x5850) = (s8)((s32)(M2C_FIELD(D_0040F4E4, s8*, 0x5850) + 1) % 3);
    for (definitionIndex = 0; definitionIndex < M2C_FIELD(definitions, s32*, 0); ++definitionIndex) {
        definition = M2C_FIELD(definitions, s32*, 4) + (definitionIndex * 0x10);
        temp_3 = M2C_FIELD(definition, u32*, 0);
        switch (temp_3) {
            case 0:
            case 1:
            case 2: break;
            case 0x3:
                temp_4 = M2C_FIELD(((bank24Index * 4) + M2C_FIELD(self, s32*, 0x24)), u32*, 0);
                bank24Index += 1;
                func_00174430(temp_4, M2C_FIELD(definition, s64*, 8), definition, (u32)definitions,
                              M2C_FIELD(definition, u32*, 4), (u32)contextCopy);
                break;
            case 0x4:
                temp_4 = M2C_FIELD(((bank24Index * 4) + M2C_FIELD(self, s32*, 0x24)), u32*, 0);
                bank24Index += 1;
                func_00174430(temp_4, M2C_FIELD(definition, s64*, 8), definition, (u32)definitions,
                              M2C_FIELD(definition, u32*, 4), (u32)contextCopy);
                break;
            case 0x5:
                temp_4 = M2C_FIELD(((bank24Index * 4) + M2C_FIELD(self, s32*, 0x24)), u32*, 0);
                bank24Index += 1;
                func_00174430(temp_4, M2C_FIELD(definition, s64*, 8), definition, (u32)definitions,
                              M2C_FIELD(definition, u32*, 4), (u32)contextCopy);
                break;
            case 0x6:
                temp_4 = M2C_FIELD(((bank24Index * 4) + M2C_FIELD(self, s32*, 0x24)), u32*, 0);
                bank24Index += 1;
                func_00174430(temp_4, M2C_FIELD(definition, s64*, 8), definition, (u32)definitions,
                              M2C_FIELD(definition, u32*, 4), (u32)contextCopy);
                break;
            case 0x7:
                temp_4 = M2C_FIELD(((bank24Index * 4) + M2C_FIELD(self, s32*, 0x24)), u32*, 0);
                bank24Index += 1;
                func_00174430(temp_4, M2C_FIELD(definition, s64*, 8), definition, (u32)definitions,
                              M2C_FIELD(definition, u32*, 4), (u32)contextCopy);
                break;
            case 0x8:
                temp_4 = M2C_FIELD(((bank24Index * 4) + M2C_FIELD(self, s32*, 0x24)), u32*, 0);
                bank24Index += 1;
                func_00174430(temp_4, M2C_FIELD(definition, s64*, 8), definition, (u32)definitions,
                              M2C_FIELD(definition, u32*, 4), (u32)contextCopy);
                break;
            case 0x9:
                temp_4 = M2C_FIELD(((bank24Index * 4) + M2C_FIELD(self, s32*, 0x24)), u32*, 0);
                bank24Index += 1;
                func_00174430(temp_4, M2C_FIELD(definition, s64*, 8), definition, (u32)definitions,
                              M2C_FIELD(definition, u32*, 4), (u32)contextCopy);
                break;
            case 0xA:
                M2C_FIELD(func_00138DF8((s32)D_0040F514, func_00138C40(D_0040F514, (void*)0x23),
                                        M2C_FIELD(M2C_FIELD(definition, u32*, 4), s128*, 0x10),
                                        M2C_FIELD(definition, s64*, 8), 0x5446127297C60000UL, contextCopy),
                          s32*, 0x3A4) = 1;
                break;
            case 0xB:
                var_7 = M2C_FIELD(((bank08Index * 4) + M2C_FIELD(self, s32*, 8)), u32*, 0);
                bank08Index += 1;
                temp_3_2 = M2C_FIELD(var_7, void**, 0x10);
                M2C_FIELD(temp_3_2, M2C_UNK(**)(void*, s64, u32),
                          0xB4)((void*)(((s8*)var_7) + M2C_FIELD(temp_3_2, s16*, 0xB0)), M2C_FIELD(definition, s64*, 8),
                                M2C_FIELD(definition, u32*, 4));
                break;
            case 0xC:
                var_7 = M2C_FIELD(((bank08Index * 4) + M2C_FIELD(self, s32*, 8)), u32*, 0);
                bank08Index += 1;
                temp_3_3 = M2C_FIELD(var_7, void**, 0x10);
                M2C_FIELD(temp_3_3, M2C_UNK(**)(void*, s64, u32),
                          0xBC)((void*)(((s8*)var_7) + M2C_FIELD(temp_3_3, s16*, 0xB8)), M2C_FIELD(definition, s64*, 8),
                                M2C_FIELD(definition, u32*, 4));
                break;
            case 0x43:
                var_7 = M2C_FIELD(((bank4CIndex * 4) + M2C_FIELD(self, s32*, 0x4C)), u32*, 0);
                bank4CIndex += 1;
                temp_3_2 = M2C_FIELD(var_7, void**, 0x10);
                M2C_FIELD(temp_3_2, M2C_UNK(**)(void*, s64, u32),
                          0xB4)((void*)(((s8*)var_7) + M2C_FIELD(temp_3_2, s16*, 0xB0)), M2C_FIELD(definition, s64*, 8),
                                M2C_FIELD(definition, u32*, 4));
                break;
            case 0x12:
                var_7 = M2C_FIELD(((bank40Index * 4) + M2C_FIELD(self, s32*, 0x40)), u32*, 0);
                bank40Index += 1;
                temp_3_4 = M2C_FIELD(var_7, void**, 0x10);
                M2C_FIELD(temp_3_4, M2C_UNK(**)(void*, s64, u32),
                          0x2C)((void*)(((s8*)var_7) + M2C_FIELD(temp_3_4, s16*, 0x28)), M2C_FIELD(definition, s64*, 8),
                                M2C_FIELD(definition, u32*, 4));
                break;
            case 0x41:
                temp_4_2 = M2C_FIELD(((bank00Index * 4) + M2C_FIELD(self, s32*, 0)), u32*, 0);
                bank00Index += 1;
                func_00153B60(temp_4_2, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0xF:
                temp_4_3 = M2C_FIELD(((bank14Index * 4) + M2C_FIELD(self, s32*, 0x14)), u32*, 0);
                bank14Index += 1;
                func_001650F8(temp_4_3, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x10:
                temp_4_4 = M2C_FIELD(((bank10Index * 4) + M2C_FIELD(self, s32*, 0x10)), u32*, 0);
                bank10Index += 1;
                func_00165210(temp_4_4, M2C_FIELD(definition, s64*, 8),
                              (Recovered_CountdownDefinition*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x11:
                temp_4_5 = M2C_FIELD(((bank18Index * 4) + M2C_FIELD(self, s32*, 0x18)), u32*, 0);
                bank18Index += 1;
                func_00165330(temp_4_5, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x1B:
                temp_4_6 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00161EF0(temp_4_6, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4), (s32)self);
                break;
            case 0x25:
                temp_4_7 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00162758(temp_4_7, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x26:
                temp_4_8 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_001628E8(temp_4_8, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x23:
                temp_4_9 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00163250(temp_4_9, M2C_FIELD(definition, s64*, 8),
                              (Recovered_ParameterDefinition*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x13:
                temp_4_10 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_001621A8(temp_4_10, M2C_FIELD(definition, s64*, 8),
                              (Recovered_ActorBindingDescriptor*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x14:
                temp_4_11 = M2C_FIELD(((bank20Index * 4) + M2C_FIELD(self, s32*, 0x20)), u32*, 0);
                bank20Index += 1;
                func_00162600(temp_4_11, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x15:
                temp_4_12 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00160F60(temp_4_12, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x16:
                var_7 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                temp_3_5 = M2C_FIELD(var_7, void**, 0x10);
                M2C_FIELD(temp_3_5, M2C_UNK(**)(void*, s64, u32),
                          0x3C)((void*)(((s8*)var_7) + M2C_FIELD(temp_3_5, s16*, 0x38)), M2C_FIELD(definition, s64*, 8),
                                M2C_FIELD(definition, u32*, 4));
                break;
            case 0x17:
                var_7 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                temp_3_6 = M2C_FIELD(var_7, void**, 0x10);
                M2C_FIELD(temp_3_6, M2C_UNK(**)(void*, s64, u32),
                          0x3C)((void*)(((s8*)var_7) + M2C_FIELD(temp_3_6, s16*, 0x38)), M2C_FIELD(definition, s64*, 8),
                                M2C_FIELD(definition, u32*, 4));
                break;
            case 0x18:
                var_7 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                temp_3_7 = M2C_FIELD(var_7, void**, 0x10);
                M2C_FIELD(temp_3_7, M2C_UNK(**)(void*, s64, u32),
                          0x3C)((void*)(((s8*)var_7) + M2C_FIELD(temp_3_7, s16*, 0x38)), M2C_FIELD(definition, s64*, 8),
                                M2C_FIELD(definition, u32*, 4));
                break;
            case 0x1C:
                temp_2 = bank1CIndex * 4;
                bank1CIndex += 1;
                func_001615A8(M2C_FIELD((temp_2 + M2C_FIELD(self, s32*, 0x1C)), u32*, 0),
                              M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                temp_5 = &pending[pendingCount];
                pendingCount += 1;
                *temp_5 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), s32*, -4);
                break;
            case 0x1D:
                temp_4_13 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_001631B0(temp_4_13, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x1E:
                temp_4_14 = M2C_FIELD(((bank48Index * 4) + M2C_FIELD(self, s32*, 0x48)), u32*, 0);
                bank48Index += 1;
                func_00161730(temp_4_14, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x22:
                temp_4_15 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00161660(temp_4_15, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x1F:
                temp_4_16 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00161418(temp_4_16, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x20:
                temp_4_17 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_001614E8(temp_4_17, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x42:
                temp_4_18 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_001630E8(temp_4_18, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x34:
                temp_17_2 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                var_16 = 0;
                func_001835B8(temp_17_2, M2C_FIELD(definition, s64*, 8),
                              (Recovered_AiVectorDefinition*)M2C_FIELD(definition, u32*, 4));
                if (M2C_FIELD(self, s32*, 0x78) > 0) {
                    do {
                        temp_2_2 = var_16 * 4;
                        var_16 += 1;
                        func_001836A8(M2C_FIELD((temp_2_2 + M2C_FIELD(self, s32*, 0x28)), u32*, 0), temp_17_2);
                    } while (var_16 < M2C_FIELD(self, s32*, 0x78));
                }
                break;
            case 0x27:
                temp_4_19 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00162A60(temp_4_19, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4), self);
                break;
            case 0x28:
                temp_4_20 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00162F28(temp_4_20, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4), self);
                break;
            case 0x29:
                temp_4_21 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00162D10(temp_4_21, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4), self);
                break;
            case 0x19:
                temp_4_22 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00161940(temp_4_22, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x2A:
                temp_4_23 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_0016ACB8(temp_4_23, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4),
                              (s32)self);
                break;
            case 0x1A:
                temp_2_3 = (bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C);
                bank1CIndex += 1;
                func_00161AF0(*temp_2_3, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4),
                              contextCopy);
                break;
            case 0x36:
                temp_4_24 = M2C_FIELD(((bank1CIndex * 4) + M2C_FIELD(self, s32*, 0x1C)), u32*, 0);
                bank1CIndex += 1;
                func_00161D78(temp_4_24, M2C_FIELD(definition, s64*, 8), M2C_FIELD(definition, u32*, 4));
                break;
            case 0x2D:
                if (M2C_FIELD(M2C_FIELD(definition, u32*, 4), u8*, 0x1E) == 1) {
                    func_00175980(D_0040F4D4 + 0xA48, M2C_FIELD(definition, s64*, 8), 1);
                }
                break;
            case 0x2E:
                temp_4_25 = M2C_FIELD(((bank2CIndex * 4) + M2C_FIELD(self, s32*, 0x2C)), u32*, 0);
                bank2CIndex += 1;
                func_00164E50(temp_4_25, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x2F:
                func_001DC690(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x20),
                              (void*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x2B:
                temp_2_4 = M2C_FIELD(definition, u32*, 4);
                temp_4_26 = (void*)(((s8*)self) + ((bankB0Index * 0x10) + 0xB0));
                bankB0Index += 1;
                func_0014EC10(temp_4_26, M2C_FIELD(temp_2_4, s128*, 0), M2C_FIELD(temp_2_4, f32*, 0x10));
                break;
            case 0x2C:
                var_5 = 0;
                temp_3_8 = M2C_FIELD(D_0040F0E0, s32*, 0x2014C);
                temp_6 = M2C_FIELD(definition, u32*, 4);
                switch (temp_3_8) {
                    case 0: var_5 = (M2C_FIELD(temp_6, u8*, 0x57) & 1) ? 1 : 0; break;
                    case 1: var_5 = (M2C_FIELD(temp_6, u8*, 0x57) & 2) ? temp_3_8 : 0; break;
                    case 2:
                    case 3: var_5 = (M2C_FIELD(temp_6, u8*, 0x57) & 4) != 0; break;
                }
                if (var_5 != 0) func_00126710(D_0040F4E4, M2C_FIELD(definition, s64*, 8), (void*)temp_6);
                break;
            case 0x32:
                var_7 = M2C_FIELD(((bank30Index * 4) + M2C_FIELD(self, s32*, 0x30)), u32*, 0);
                bank30Index += 1;
                temp_3_2 = M2C_FIELD(var_7, void**, 0x10);
                M2C_FIELD(temp_3_2, M2C_UNK(**)(void*, s64, u32),
                          0xB4)((void*)(((s8*)var_7) + M2C_FIELD(temp_3_2, s16*, 0xB0)), M2C_FIELD(definition, s64*, 8),
                                M2C_FIELD(definition, u32*, 4));
                break;
            case 0x30:
                var_7 = M2C_FIELD(((bank34Index * 4) + M2C_FIELD(self, s32*, 0x34)), u32*, 0);
                bank34Index += 1;
                temp_3_2 = M2C_FIELD(var_7, void**, 0x10);
                M2C_FIELD(temp_3_2, M2C_UNK(**)(void*, s64, u32),
                          0xB4)((void*)(((s8*)var_7) + M2C_FIELD(temp_3_2, s16*, 0xB0)), M2C_FIELD(definition, s64*, 8),
                                M2C_FIELD(definition, u32*, 4));
                break;
            case 0x31:
                var_7 = M2C_FIELD(((bank38Index * 4) + M2C_FIELD(self, s32*, 0x38)), u32*, 0);
                bank38Index += 1;
                temp_3_2 = M2C_FIELD(var_7, void**, 0x10);
                M2C_FIELD(temp_3_2, M2C_UNK(**)(void*, s64, u32),
                          0xB4)((void*)(((s8*)var_7) + M2C_FIELD(temp_3_2, s16*, 0xB0)), M2C_FIELD(definition, s64*, 8),
                                M2C_FIELD(definition, u32*, 4));
                break;
            case 0x37:
                temp_4_27 = M2C_FIELD(((bank3CIndex * 4) + M2C_FIELD(self, s32*, 0x3C)), s32*, 0);
                bank3CIndex += 1;
                func_00174D48(temp_4_27, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4),
                              (s32)definitions);
                break;
            case 0x38:
                temp_4_28 = M2C_FIELD(((bank3CIndex * 4) + M2C_FIELD(self, s32*, 0x3C)), u32*, 0);
                bank3CIndex += 1;
                func_00174DF0(temp_4_28, M2C_FIELD(definition, s64*, 8), (void*)M2C_FIELD(definition, u32*, 4),
                              (s32)definitions);
                break;
            case 0x39:
                temp_4_29 = M2C_FIELD(((bank3CIndex * 4) + M2C_FIELD(self, s32*, 0x3C)), s32*, 0);
                bank3CIndex += 1;
                func_001750E8(temp_4_29, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4),
                              (s32)definitions);
                break;
            case 0x3A:
                temp_4_30 = M2C_FIELD(((bank3CIndex * 4) + M2C_FIELD(self, s32*, 0x3C)), s32*, 0);
                bank3CIndex += 1;
                func_00175250(temp_4_30, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4),
                              (s32)definitions);
                break;
            case 0x3B:
                temp_4_31 = M2C_FIELD(((bank3CIndex * 4) + M2C_FIELD(self, s32*, 0x3C)), s32*, 0);
                bank3CIndex += 1;
                func_001752F8(temp_4_31, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4),
                              (s32)definitions);
                break;
            case 0x3C:
                temp_4_32 = M2C_FIELD(((bank3CIndex * 4) + M2C_FIELD(self, s32*, 0x3C)), s32*, 0);
                bank3CIndex += 1;
                func_001753B8(temp_4_32, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4),
                              (s32)definitions);
                break;
            case 0x3D:
                temp_4_33 = M2C_FIELD(((bank3CIndex * 4) + M2C_FIELD(self, s32*, 0x3C)), s32*, 0);
                bank3CIndex += 1;
                func_00175460(temp_4_33, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4),
                              (s32)definitions);
                break;
            case 0x3E:
                temp_4_34 = M2C_FIELD(((bank3CIndex * 4) + M2C_FIELD(self, s32*, 0x3C)), s32*, 0);
                bank3CIndex += 1;
                func_00175520(temp_4_34, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4),
                              (s32)definitions);
                break;
            case 0x3F:
                temp_4_35 = M2C_FIELD(((bank3CIndex * 4) + M2C_FIELD(self, s32*, 0x3C)), s32*, 0);
                bank3CIndex += 1;
                func_001755C8(temp_4_35, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4),
                              (s32)definitions);
                break;
            case 0x40:
                temp_4_36 = M2C_FIELD(((bank3CIndex * 4) + M2C_FIELD(self, s32*, 0x3C)), s32*, 0);
                bank3CIndex += 1;
                func_00175668(temp_4_36, M2C_FIELD(definition, s64*, 8), (s32)M2C_FIELD(definition, u32*, 4),
                              (s32)definitions);
                break;
            case 0x44:
                temp_4_37 = M2C_FIELD(((bank44Index * 4) + M2C_FIELD(self, s32*, 0x44)), u32*, 0);
                bank44Index += 1;
                func_00163E08(temp_4_37, M2C_FIELD(definition, s64*, 8), (s8*)M2C_FIELD(definition, u32*, 4));
                break;
            case 0x35:
                temp_17_3 = M2C_FIELD(definition, u32*, 4);
                temp_2_5 = func_00107CF8(0xCU);
                func_00174858(temp_2_5, (void*)temp_17_3, M2C_FIELD(self, s32*, 0x94), M2C_FIELD(self, s32*, 0x9C));
                func_0017BDC0(D_0040F4D4 + 0xCD4, selectorCopy, (s32)temp_2_5);
                break;
        }
    }
    func_00166D50(D_0040F4F4, M2C_FIELD(self, s32*, 0x24), (s32)M2C_FIELD(definitions, u16*, 0x72));
    func_00166C30(D_0040F4F4, M2C_FIELD(self, s32*, 8), (s32)M2C_FIELD(definitions, u16*, 0x62));
    func_00166C60(D_0040F4F4, M2C_FIELD(self, s32*, 0x14), (s32)M2C_FIELD(definitions, u16*, 0x6C));
    func_00166C90(D_0040F4F4, M2C_FIELD(self, s32*, 0x10), (s32)M2C_FIELD(definitions, u16*, 0x68));
    func_00166CC0(D_0040F4F4, M2C_FIELD(self, s32*, 0x18), (s32)M2C_FIELD(definitions, u16*, 0x6A));
    func_00166CF0(D_0040F4F4, M2C_FIELD(self, s32*, 0x1C), (s32)M2C_FIELD(definitions, u16*, 0x64));
    func_00166D20(D_0040F4F4, M2C_FIELD(self, s32*, 0x20), (s32)M2C_FIELD(definitions, u16*, 0x66));
    func_00166D80(D_0040F4F4, M2C_FIELD(self, s32*, 0x2C), (s32)M2C_FIELD(definitions, u16*, 0x6E));
    func_00166DB0(D_0040F4F4, M2C_FIELD(self, s32*, 0x30), (s32)M2C_FIELD(definitions, u16*, 0x76));
    func_00166DE0(D_0040F4F4, M2C_FIELD(self, s32*, 0x34), (s32)M2C_FIELD(definitions, u16*, 0x78));
    func_00166E10(D_0040F4F4, M2C_FIELD(self, s32*, 0x38), (s32)M2C_FIELD(definitions, u16*, 0x7A));
    func_00166C00(D_0040F4F4, M2C_FIELD(self, s32*, 0x94), M2C_FIELD(self, s32*, 0x9C));
    func_00166E40(D_0040F4F4, M2C_FIELD(self, s32*, 0x40), (s32)M2C_FIELD(definitions, u16*, 0x80));
    func_00166E70(D_0040F4F4, M2C_FIELD(self, s32*, 0), (s32)M2C_FIELD(definitions, u16*, 0x84));
    func_00166EA0(D_0040F4F4, M2C_FIELD(self, s32*, 0x3C), (s32)M2C_FIELD(definitions, u16*, 0x7E));
    func_00166ED0(D_0040F4F4, M2C_FIELD(self, s32*, 0x44), (s32)M2C_FIELD(definitions, u16*, 0x86));
    func_00166F00(D_0040F4F4, M2C_FIELD(self, s32*, 0x48), (s32)M2C_FIELD(definitions, u16*, 0x88));
    func_00166F30(D_0040F4F4, M2C_FIELD(self, s32*, 0x4C), (s32)M2C_FIELD(definitions, u16*, 0x8A));
    func_00176FB0(D_0040F4D4 + 0x112C, M2C_FIELD(self, s32*, 0x28), (s32)M2C_FIELD(definitions, u16*, 0x7C));
    func_00167208((void*)D_0040F4F4);
    func_001604A0(self, pending, pendingCount);
    return 1;
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_15ef48", func_0015EF48);
#endif
