#include "include_asm.h"
#include "ps2/prelude.h"

/* Partial view of this movement controller; class identity and extent are unknown. */
typedef struct Recovered_MovementControl {
    void* unk_00;
    void* unk_04;
    u8 unk_08[12];
    u8 unk_14;
    u8 unk_15;
    u8 unk_16[10];
    s128 unk_20;
} Recovered_MovementControl;

typedef union Recovered_MovementVector {
    s128 native;
    f32 lane[4];
} Recovered_MovementVector;

extern s32 func_0018E458();
extern s32 func_00188F10(void*);
extern s32 func_00189208(void*);
extern const s128* func_001893A0(void*);
extern void func_00180AA0(void*, s128, s32, f32);
extern void func_00180B38(void*, f32);
extern s32 func_00191270(Recovered_MovementControl*);
extern s32 func_0018E590(Recovered_MovementControl*);
extern s32 func_0018E5B8(Recovered_MovementControl*, s32);
extern void func_0018D610(void*);
extern void func_00181AD0(void*, s32);
extern void func_00181F48(void*, s32, s32, f32, f32);
extern void func_0018A890(void*);
extern void func_001911A8();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_190ea0", func_00190EA0);

void func_00191010(void *arg0) {
    void *temp_3;
    void *temp_4;

    func_0018E458();
    temp_3 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, s8 *, 0x15) = 0;
    if ((M2C_FIELD(temp_3, u8 *, 0x28) == 0) && (M2C_FIELD(temp_3, s8 *, 0x29) < 0)) {
        func_001911A8(arg0);
    }
    temp_4 = M2C_FIELD(arg0, void **, 4);
    M2C_FIELD(arg0, s128 *, 0x20) = (s128) M2C_FIELD(M2C_FIELD(temp_4, void **, 0x7C), s128 *, 0xA0);
    M2C_FIELD(temp_4, s8 *, 0xD24) = 0;
}

void func_00191070(Recovered_MovementControl* self) {
    if (func_00188F10((u8*)self->unk_04 + 0x150) && func_00189208((u8*)self->unk_04 + 0x150)) {
        u8* context = self->unk_04;
        func_00180AA0(context + 0xB30, *func_001893A0(context + 0x150), 2, 0.0f);
    } else {
        func_00180AA0((u8*)self->unk_04 + 0xB30, self->unk_20, 2, 0.0f);
    }
    func_00180B38((u8*)self->unk_04 + 0xB30, 10.0f);
}

u8 func_00191110(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x14);
}

s32 func_00191118(Recovered_MovementControl* self) {
    if (func_00191270(self)) return 0x17;
    return func_0018E590(self);
}
s32 func_00191158(Recovered_MovementControl* self, s32 value) {
    if (func_00191270(self)) return 0x4A;
    return func_0018E5B8(self, value);
}
#ifdef NON_MATCHING
// Unmatched: parameter-pointer allocation and scalar spill scheduling differ.
void func_001911A8(Recovered_MovementControl* self) {
    u8* target;
    u8* params;
    u8* context;
    s128 position;
    Recovered_MovementVector capture;
    params = self->unk_00;
    context = self->unk_04;
    target = M2C_FIELD(params, u8**, 0x2C);
    position = M2C_FIELD(target, s128*, 0x10);
    capture.native = position;
    M2C_FIELD(params, u8*, 0x29) = M2C_FIELD(context, u8*, 0x1EF4);
    func_00180AA0((u8*)self->unk_04 + 0xB30, position, 2, capture.lane[3]);
    func_00180B38((u8*)self->unk_04 + 0xB30, M2C_FIELD(target, f32*, 0x2C));
    func_0018D610((u8*)self->unk_04 + 0xD10);
    func_00181AD0((u8*)self->unk_04 + 0xEC0, 0xD);
    self->unk_14 = 0;
    func_00181F48((u8*)self->unk_04 + 0xC80, 0, 0x25, 0.0f, 2.0f);
    if (!func_00188F10((u8*)self->unk_04 + 0x150)) func_0018A890((u8*)self->unk_04 + 0x150);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_190ea0", func_001911A8);
#endif

s32 func_00191270(Recovered_MovementControl *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0), s8 *, 0x29) == M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x1EF4);
}
