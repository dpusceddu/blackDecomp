#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193980();
extern s32 func_00187FE0(s32, M2C_UNK);
extern s32 func_001825B0(void *);
extern void func_00193988(void);
extern void func_001880D8(void *);
extern void func_00173690(f32 *);
extern void func_00173640(f32 *, f32);

typedef struct {
    void *owner;
    u8 unk_04[4];
    s32 unk_08;
    f32 unk_0c;
    f32 unk_10;
    f32 unk_14;
} ActionState;

void func_001941A8(void **arg0) {
    func_00193980();
    func_00187FE0(*arg0 + 0x290, 0);
    M2C_FIELD(M2C_FIELD(*arg0, void **, 0x694), s8 *, 0x30) = 1;
    func_001825B0(*arg0 + 0x810);
}

void func_001941F8(void **state) {
    void *owner;
    u8 *movement;
    func_00193988();
    M2C_FIELD(M2C_FIELD(*state, void **, 0x694), s8 *, 0x30) = 0;
    owner = *state;
    movement = (u8 *) owner + 0x290;
    if (*movement != 0) {
        func_001880D8(movement);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_193978_1941a8", func_00194240);
// Unmatched: 00194420: owner pointer register allocation.
#ifdef NON_MATCHING
void func_00194420(void **state) {
    func_00193980();
    func_00173690((f32 *) ((s8 *) state + 0x10));
    func_00173640((f32 *) ((s8 *) state + 0x0c), 0.0f);
    M2C_FIELD(state, s32 *, 8) = 0;
    func_00173690((f32 *) ((s8 *) state + 0x14));
    func_00187FE0(*state + 0x290, 0);
    M2C_FIELD(M2C_FIELD(*state, void **, 0x694), s8 *, 0x30) = 0;
    func_001825B0(*state + 0x810);
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_193978_1941a8", func_00194420);
void func_00194490(ActionState *state) {
    void *owner;
    u8 *movement;
    func_00193988();
    M2C_FIELD(state->owner, s8 *, 0x38) = 0;
    owner = state->owner;
    movement = (u8 *) owner + 0x290;
    if (*movement != 0) {
        func_001880D8(movement);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_193978_1941a8", func_001944D8);
