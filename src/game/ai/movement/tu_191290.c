#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#include "game/ai/movement_views.h"

extern s32 func_0018E458();
extern void func_00191360();
extern void func_0018E338(void *);
extern s32 func_00180BC0(void *);
extern void func_0016ABA8(void *, s32, u8, void *);
extern void *func_00191450(void *);
extern s32 func_00188F10(void *);
extern s32 func_00189208(void *);
extern s128 *func_001893A0(void *);
extern s128 func_00180A00(void *);
extern void func_00180AA0(void *, s128, s32, f32);
extern void func_00180B38(void *, f32);
extern void *D_0040F514;
extern void *func_00135550(void *);

void func_00191290(Recovered_MovementControl *self) {
    void *config;
    s32 finished;
    func_0018E338(self);
    config = M2C_FIELD(self->unk_00, void **, 0x28);
    if (self->unk_14 == 0) {
        finished = func_00180BC0((u8 *) self->unk_04 + 0xB30);
        self->unk_14 = finished;
        if (finished & 0xFF) {
            if (M2C_FIELD(config, u8 *, 0x2C) != 0) {
                u8 *owner = self->unk_04;
                func_0016ABA8(owner + 0x1F90, M2C_FIELD(config, s32 *, 0x20), M2C_FIELD(config, u8 *, 0x2C),
                               M2C_FIELD(owner, void **, 0x7C));
            }
        } else if (func_001829A8((RecoveredAIController *) ((u8 *) self->unk_04 + 0x810)) == 0) {
            func_00191360(self);
        }
    }
}

void func_00191328(void *arg0) {
    func_0018E458();
    M2C_FIELD(arg0, s8 *, 0x15) = 0;
    func_00191360(arg0);
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s8 *, 0xD24) = 0;
}

void func_00191360(Recovered_MovementControl *self) {
    void *config = M2C_FIELD(self->unk_00, void **, 0x28);
    u8 *target = func_00191450(self);
    if (target != NULL && func_00188F10(target + 0x150) != 0) {
        u8 *records = target + 0x150;
        s128 position;
        if (func_00189208(records) != 0) position = *func_001893A0(records);
        else position = func_00180A00(target + 0xB30);
        func_00180AA0((u8 *) self->unk_04 + 0xB30, position, 2, 0.0f);
        func_00180B38((u8 *) self->unk_04 + 0xB30, 10.0f);
        self->unk_14 = 0;
    } else if (self->unk_15 == 0) {
        if (M2C_FIELD(config, u8 *, 0x2D) != 0) {
            u8 *owner = self->unk_04;
            func_0016ABA8(owner + 0x1F90, M2C_FIELD(config, s32 *, 0x24), M2C_FIELD(config, u8 *, 0x2D),
                           M2C_FIELD(owner, void **, 0x7C));
            self->unk_15 = 1;
        }
    }
}
// Unmatched: 00191450: nested iterator and saved-register allocation.
#ifdef NON_MATCHING
void *func_00191450(void *self) {
    void *config = M2C_FIELD(M2C_FIELD(self, void **, 0), void **, 0x28);
    s32 slot;
    s32 index = 0;
    if (M2C_FIELD(config, u8 *, 0x2E) != 0) {
        do {
            s64 id;
            slot = 0;
            id = ((s64 *) M2C_FIELD(config, s32 *, 0x28))[index];
            if (M2C_FIELD(D_0040F514, s32 *, 0x79A4) > 0) {
                do {
                    s64 *entry = ((s64 **) M2C_FIELD(D_0040F514, s32 *, 0x79AC))[slot];
                    if (entry != NULL && *entry == id && func_00135550(entry) != NULL &&
                        M2C_FIELD(func_00135550(entry), s32 *, 0x80) == 1) {
                        return func_00135550(entry);
                    }
                    slot++;
                    if (slot >= M2C_FIELD(D_0040F514, s32 *, 0x79A4)) break;
                } while (1);
            }
            index++;
        } while (index < M2C_FIELD(config, u8 *, 0x2E));
    }
    return NULL;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_191290", func_00191450);
