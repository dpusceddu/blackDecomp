#include "include_asm.h"
#include "ps2/prelude.h"

extern void* func_0027D118(void*, u64);
static inline void ChangeControllerState(void* controller, u64 key, s32 context) {
    void *nextState = func_0027D118(controller, key), *beforeTable, *previousState, *clock, *afterTable;
    if (M2C_FIELD(controller, void**, 0) != nextState) {
        beforeTable = M2C_FIELD(controller, void**, 0x14);
        M2C_FIELD(beforeTable, void (**)(void*, void*, s32),
                  0x2C)((void*)(((s8*)controller) + M2C_FIELD(beforeTable, s16*, 0x28)), nextState, context);
        previousState = M2C_FIELD(controller, void**, 0);
        clock = M2C_FIELD(controller, void**, 0xC);
        M2C_FIELD(controller, void**, 0) = nextState;
        if (clock != NULL) {
            M2C_FIELD(controller, f32*, 0x10) = (f32)M2C_FIELD(clock, f32*, 0x20);
            if (nextState != NULL) { M2C_FIELD(nextState, f32*, 8) = (f32)M2C_FIELD(clock, f32*, 0x20); }
        }
        afterTable = M2C_FIELD(controller, void**, 0x14);
        M2C_FIELD(afterTable, void (**)(void*, void*, s32),
                  0x34)((void*)(((s8*)controller) + M2C_FIELD(afterTable, s16*, 0x30)), previousState, context);
    }
}

extern s32 func_001183B8(void*, s32, s32, void*, f32);
extern void func_00116918(void*, s32, s32, s32, s32, f32);
extern s32 func_00118098(void*);
extern void func_00116E00(void*, s32, s32, s32);
extern void func_00110940(void*, s32);

extern s32 func_00118090();

void func_001188E0(void) {
    func_00118090();
}

void func_00118900(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_116f60_1188e0", func_00118908);
void func_00118D48(s32 unused, s32 event, void* controller, s32 command, s32 context) {

    switch (event) {
        case 0:
        case 1:
        case 2:
        case 4: return;
        case 3: func_00110940(controller, 0); return;
        case 5:
            switch (command) {
                case 3: ChangeControllerState(controller, 0x594c3aee53b27048UL, context); return;
                case 4: ChangeControllerState(controller, 0x594c3d53ef90903fUL, context); return;
                case 5: ChangeControllerState(controller, 0x594c3bfd6d9ff5e1UL, context); return;
                case 7: ChangeControllerState(controller, 0x594c3cc765b41051UL, context); return;
                default: return;
            }

            return;
    }
}
void func_00118F58(void* self, s32 event, void* controller, void* argument) {
    switch (event) {
        case 3:
            if (!argument)
                M2C_FIELD(self, u64*, 0x10) = 0x594c3bb5a28a38a1UL;
            else
                M2C_FIELD(self, u64*, 0x10) = *(u64*)argument;
            break;
        case 5:
            switch ((s32)argument) {
                case 0: M2C_FIELD(self, u64*, 0x10) = 0x594C3B3ED729E1C6UL; break;
                case 1: break;
                case 2: ChangeControllerState(controller, M2C_FIELD(self, u64*, 0x10), 0); break;
            }
            break;
    }
}
void func_00119090(void* self, s32 event, void* controller, s32 command, s32 context) {
    switch (event) {
        case 3:
            func_00116E00((u8*)controller + 0x4E0, 1, 0, context);
            func_00110940(controller, 8);
            M2C_FIELD(self, s32*, 0x10) = 0;
            return;
        case 4:
            switch (M2C_FIELD(self, s32*, 0x10)) {
                case 0:
                    if (func_00118098((u8*)controller + 0x4E0)) M2C_FIELD(self, s32*, 0x10) = 1;
                    return;
                case 1: ChangeControllerState(controller, 0x594C3B3ED729E1C6UL, 0); return;
            }
            break;
        case 5:
            switch (command) {
                case 13: M2C_FIELD(self, s32*, 0x10) = 2; return;
                case 14: ChangeControllerState(controller, 0x594C3B3ED729E1C6UL, 0); break;
            }
            break;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_116f60_1188e0", func_00119288);
void func_001198A8(s32 unused, s32 event, void* controller, s32 unused3, void* context) {
    switch (event) {
        case 0:
        case 1:
        case 2: return;
        case 3:
            func_001183B8((u8*)controller + 0x350, 1, 1, context, 5.0f);
            func_00116918((u8*)controller + 0x260, 0, 4, 1, 1, 3.0f);
            return;
        case 4:
            if (func_00118098((u8*)controller + 0x350)) ChangeControllerState(controller, 0x594C3B3ED729E1C6UL, 0);
            return;
    }
}
