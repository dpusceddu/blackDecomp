#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0011D490();
extern s32 func_0011D430();

void func_0011EBF0(void) { func_0011D490(); }

s32 func_0011EC10(s32 arg0) { return func_0011D430(arg0, 5); }

#include "game/animation_action.h"
extern void* func_0011D498(void*);
extern u8 func_00141490(void*);
extern void func_001412E8(void*, s32);
extern u8 func_00135CC8(void*);
extern void func_001A6330(void*, const Recovered_AnimationAction*);

void func_0011EC30(void* self) {
    Recovered_AnimationAction action;
    void* actor = func_0011D498(self);
    if (func_00141490(M2C_FIELD(self, void**, 0))) {
        func_001412E8(M2C_FIELD(self, void**, 0), 8);
        action.key = 4;
        action.value = 1.0f;
        action.mode = 0xB;
        action.kind = 1;
        action.flag = func_00135CC8(actor);
        func_001A6330(M2C_FIELD(actor, void**, 0x330), &action);
        M2C_FIELD(self, u8*, 0x48) = 1;
        return;
    }
    action.kind = 3;
    action.key = 0x1C;
    action.mode = 0xB;
    action.value = 1.0f;
    action.flag = func_00135CC8(actor);
    func_001A6330(M2C_FIELD(actor, void**, 0x330), &action);
}
