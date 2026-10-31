#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai/action_views.h"
#include "game/ai_manager.h"

extern s32 func_00177C90(s32, s32);
extern s32 func_0017B358(s32);
extern s32 func_00193980();
extern s32 func_00187FE0(s32, M2C_UNK);
extern s32 func_00181A90(s32, M2C_UNK);
extern s32 func_00193990();
extern s32 func_00199F70();
extern s32 func_00193988();



extern Recovered_AIManager* D_0040F4D4;
extern void func_00173640(f32*, f32);
extern void func_00173690(f32*);
extern s32 func_00173610(f32*);
extern s32 func_00188F10(void*);
extern void func_0017E428(void*, s128);
extern f32 func_00189310(void*);
extern s32 func_0017E860(void*);
extern u8 func_00188350(void*);
extern u8 func_0018D608(void*);
extern f32 func_001891A8(void*);
extern s32 func_001880D8(void*);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_199988", func_00199988);
#ifdef NON_MATCHING
// Unmatched: prologue scheduling and timer-address lifetime differ.
void func_00199C40(Recovered_ActionTimers* self) {
    u8* actor;
    func_00193980();
    M2C_FIELD(M2C_FIELD(self->owner, void**, 0x694), u8*, 0x30) = 1;
    M2C_FIELD(M2C_FIELD(self->owner, void**, 0x694), u8*, 0x39) = 1;
    self->unk_38 = NULL;
    func_00173640(&self->unk_24, AIManager_RandomRange(D_0040F4D4, 1.0f, 1.5f));
    func_00173640(&self->unk_28, 0.0f);
    func_00173640(&self->unk_30, 0.0f);
    func_00173640(&self->unk_34, 0.0f);
    func_00173690(&self->unk_2C);
    M2C_FIELD(M2C_FIELD(self->owner, void**, 0x7C), u8*, 0x3AF) = 1;
    func_00173690(&self->unk_20);
    actor = self->owner;
    self->unk_10 = M2C_FIELD(M2C_FIELD(actor, void**, 0x7C), s128*, 0x90);
    self->unk_3C = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_199988", func_00199C40);
#endif
#ifdef NON_MATCHING
// Unmatched: pointer register allocation differs.
void func_00199D20(Recovered_ActionTimers* self) {
    func_00193988();
    {
        u8* owner = self->owner;
        u8* state = M2C_FIELD(owner, u8**, 0x694);
        state[0x30] = 0;
    }
    {
        u8* owner = self->owner;
        u8* state = M2C_FIELD(owner, u8**, 0x694);
        state[0x39] = 0;
    }
    if (self->unk_38) {
        M2C_FIELD(self->owner, u8*, 0x1F50) = 0;
        func_00177C90((s32)self->unk_38, (s32)(self->owner + 0x1F00));
        self->unk_38 = NULL;
    }
    {
        u8* owner = self->owner;
        M2C_FIELD(M2C_FIELD(owner, void**, 0x7C), u8*, 0x3AF) = 0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_199988", func_00199D20);
#endif
extern s32 func_0017EA70(void*);
extern void func_0017DB18(void*);

void func_00199D90(Recovered_ActionTimers* self, s32 event, s32 value) {
    f32* timer;
    u8 enabled;

    switch (event) { /* irregular */
        case 0x3A:
            timer = &self->unk_34;
            func_00173640(timer, AIManager_RandomRange(D_0040F4D4, 2.0f, 4.0f));
            func_00173640((f32*)&self->unk_28, 0.0f);
            if (value != 0) {
                enabled = self->unk_3C ^ 1;
                self->unk_3C = enabled;
                if (enabled != 0) { func_00173640(timer, 1.0f); }
            } else {
                func_00173640((f32*)&self->unk_24, 0.0f);
            }
            return;
        case 0x39:
            func_00173640((f32*)&self->unk_28, AIManager_RandomRange(D_0040F4D4, 2.0f, 3.0f));
            func_00173640((f32*)&self->unk_24, 0.0f);
            break;
        case 0x38:
            func_00173640((f32*)&self->unk_24, AIManager_RandomRange(D_0040F4D4, 1.0f, 1.5f));
            if (value || func_0017EA70((u8*)self->owner + 0x650)) { func_0017DB18((u8*)self->owner + 0x650); }
            break;
    }
}


void func_00199F08(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x38);
    if (temp_4 != 0) {
        func_00177C90(temp_4, M2C_FIELD(arg0, s32 *, 0) + 0x1F00);
        M2C_FIELD(arg0, s32 *, 0x38) = 0;
    }
}

void func_00199F48(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    func_0017B358(M2C_FIELD(arg0, s32 *, 0) + 0x1F60);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_199988", func_00199F70);
s32 func_0019A350(Recovered_ActionTimers* self, void* event) {
    if (M2C_FIELD(event, s32*, 0) == 0x13 && func_00173610(&self->unk_30)) {
        if (!func_00188F10(self->owner + 0x150)) {
            void* actor = M2C_FIELD(event, void**, 8);
            func_0017E428(self->owner + 0x650, M2C_FIELD(actor, s128*, 0xA0));
            func_00173640(&self->unk_30, 3.0f);
            return 1;
        }
    }
    return 0;
}
void func_0019A3E8(Recovered_ActionPeer* self) {
    u8* owner;
    if (!func_00188F10(self->owner + 0x150)) goto failed;
    if (func_00189310(self->owner + 0x150) > 3.0f) goto failed;
    if (!func_0017E860(self->owner + 0x650)) goto failed;
    if (func_00188350(self->owner + 0x290)) goto failed;
    owner = self->owner;
    if (M2C_FIELD(owner, u8*, 0x291)) goto success;
    if (func_0018D608(owner + 0xD10)) goto proceed;
failed:
    func_00193990(self, 0);
    return;
proceed:
    if (func_00199F70(self->unk_08)) goto check;
success:
    func_00193990(self, 1);
    return;
check:
    if (func_001891A8(self->owner + 0x150) < 3.3f) func_00193990(self, 1);
}

void func_0019A4F0(void *arg0) {
    func_00193980();
    func_00187FE0(M2C_FIELD(arg0, s32 *, 0) + 0x290, 0);
    M2C_FIELD(arg0, s32 *, 8) = func_00181A90(M2C_FIELD(arg0, s32 *, 0) + 0xEC0, 0x37);
}

void func_0019A538(Recovered_ActionPeer* self) {
    u8* owner;
    u8* state;
    func_00193988();
    owner = self->owner;
    state = owner + 0x290;
    if (*state) func_001880D8(state);
    self->unk_08 = NULL;
}

void func_0019A578(void **arg0) {
    if ((M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x694), u8 *, 0x3B) ^ 1) != 0) {
        func_00193990(arg0, 1);
        return;
    }
    if (func_00199F70(M2C_FIELD(arg0, s32 *, 8)) == 0) {
        func_00193990(arg0, 0);
    }
}


void func_0019A648(void *arg0) {
    func_00193988();
    M2C_FIELD(arg0, s32 *, 8) = 0;
}
