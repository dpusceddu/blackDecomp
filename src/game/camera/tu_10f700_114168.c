#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/effects/random_state.h"

// Partial Game view; only the random-state placement is recovered here.
typedef struct Recovered_GameRandomView {
    u8 unk_0[0x5AD8];
    BkEffectRandomStatePS2 random;
} Recovered_GameRandomView;

typedef char GameRandomOffset[(u32) & ((Recovered_GameRandomView*)0)->random == 0x5AD8 ? 1 : -1];
typedef char GameRandomStateSize[sizeof(BkEffectRandomStatePS2) == 8 ? 1 : -1];

typedef struct Recovered_PairedBank {
    void* unk_0[2];
    s8 unk_8[2];
    u8 unk_A[2];
    s8 unk_C;
} Recovered_PairedBank;

// Partial transition layouts; field meanings remain UNVERIFIED.
typedef struct Recovered_SlotOwnerView {
    u8 unk_0[0x6F0];
    u64 unk_6F0;
} Recovered_SlotOwnerView;
typedef struct Recovered_SlotTransition {
    u8 unk_0[0xC0];
    Recovered_SlotOwnerView* unk_C0;
    s32 unk_C4;
    s32 unk_C8;
} Recovered_SlotTransition;
extern void func_0027ACC8(void*);
extern void func_00118188(void*, s32, s32, f32);
extern void func_00110860(Recovered_SlotOwnerView*, s32);

typedef struct Recovered_TransitionQuery {
    u8 unk_0[0x1C];
    void* unk_1C;
    u8 unk_20;
    u8 unk_21[3];
    f32 unk_24;
} Recovered_TransitionQuery;
extern f32 func_00118158(void*, f32);
extern void func_00110C90(void*, f32, void*, s32);

extern s32 func_001B6CF8(s32, s32, M2C_UNK);
extern s32 D_0040F4D8;
extern s32 func_00149AC8(s32);

void func_00114168(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00114170);

void func_00114228(void) {

}

void func_00114230(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00114238);

void func_001145D0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001145D8);

void func_00114968(void) {

}

void func_00114970(void) {

}

s32 func_00114978(void) {
    return 1;
}

void func_00114980(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00114988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00115D38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00115D70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00115DA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00115DC8);
void func_001168E0(Recovered_SlotTransition* self, Recovered_SlotOwnerView* owner) {
    func_0027ACC8(self);
    self->unk_C0 = owner;
}
void func_00116918(Recovered_SlotTransition* self, s32 slot, s32 target, s32 arg3, s32 arg4, f32 duration) {
    func_00118188(self, arg3, arg4, duration);
    self->unk_C8 = target;
    self->unk_C4 = slot;
    self->unk_C0->unk_6F0 &= ~(1UL << slot);
    func_00110860(self->unk_C0, 2);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00116990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00116A78);
void func_00116E80(Recovered_TransitionQuery* self, void* value) {
    if (self->unk_20) {
        if (self->unk_24 == -1.0f) {
            func_00110C90(self->unk_1C, func_00118158(self, self->unk_24), value, 1);
        } else {
            func_00110C90(self->unk_1C, self->unk_24, value, 1);
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0011C930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0011C9C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0011CA20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0011CA28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125970);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125B10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125C60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125D18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125E98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125F88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126058);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126200);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126290);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001264C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126710);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126980);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126D78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126E48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126E50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126F08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126F10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126F80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00127060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012C650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012C790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012CBA0);
static inline u32 GameRandomStep(BkEffectRandomStatePS2* random) {
    random->state = (random->state << 16) + ((s32)random->state >> 16);
    random->state += random->accumulator;
    random->accumulator += random->state;
    return random->state;
}

static inline f32 GameRandomRange(Recovered_GameRandomView* self, f32 minimum, f32 maximum) {
    f32 fraction = (f32)GameRandomStep(&self->random) * 2.3283064365386963e-10f;
    return minimum + (maximum - minimum) * fraction;
}

f32 func_0012D058(Recovered_GameRandomView* self) {
    return (f32)GameRandomStep(&self->random) * 2.3283064365386963e-10f;
}
f32 func_0012D0D0(Recovered_GameRandomView* self, f32 minimum, f32 maximum) {
    return GameRandomRange(self, minimum, maximum);
}
s32 func_0012D158(Recovered_GameRandomView* self, s32 minimum, s32 maximum) {
    return (s32)GameRandomRange(self, (f32)minimum, (f32)maximum + 1.0f - 0.0000152587890625f);
}
s32 func_0012D218(Recovered_GameRandomView* self, f32 probability) {
    if (probability == 0.0f) return 0;
    return func_0012D058(self) <= probability;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012D270);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012D310);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012D3D0);
void func_0012EEE8(Recovered_PairedBank* self) {
    s8 i;
    for (i = 0; i < 2; i++) {
        self->unk_0[i] = NULL;
        self->unk_8[i] = 0;
    }
}
s32 func_0012EF28(Recovered_PairedBank* self) {
    s8 i;
    for (i = 0; i < 2; i++) {
        self->unk_0[i] = NULL;
        self->unk_8[i] = 0;
    }
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012EF68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F060);
void func_0012F1B8(Recovered_PairedBank* self) {
    s8 next = (self->unk_C + 1) % 2;
    if (self->unk_A[next]) {
        self->unk_0[next] = NULL;
        self->unk_8[next] = 0;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F2D8);
void func_0012F388(Recovered_PairedBank* self) {
    s8 i;
    for (i = 0; i < 2; i++) {
        self->unk_0[i] = NULL;
        self->unk_8[i] = 0;
    }
}
s32 func_0012F3C8(Recovered_PairedBank* self) {
    s8 i;
    for (i = 0; i < 2; i++) {
        self->unk_0[i] = NULL;
        self->unk_8[i] = 0;
    }
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F408);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F4F0);
void func_0012F610(Recovered_PairedBank* self) {
    s8 next = (self->unk_C + 1) % 2;
    if (self->unk_A[next]) {
        self->unk_0[next] = NULL;
        self->unk_8[next] = 0;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F660);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F6A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F740);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F780);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F7C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F800);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F880);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F8C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012FB48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012FC10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00130640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00130678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001306D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00131EF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00132188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00132610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001327F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001334E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00133BA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00133E60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135580);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135940);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135A38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135AC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001368F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00136BD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00136D60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00136DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00136E88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001386C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001387C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00139B68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00139BA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013C868);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013CE08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013CED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013CF38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013D048);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013D7A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013D8D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013D9A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00140AD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00140BB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001415A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00142AB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00142B90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00142E30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00143590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001444A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001448C8);

s32 func_00144E00(s32 arg0) {
    func_001B6CF8(D_0040F4D8 + 0x66290, arg0, 0);
    func_00149AC8(arg0);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00144E50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00144E58);
