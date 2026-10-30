#include "ps2/prelude.h"
#include "ps2/vu0.hpp"
extern "C" void* func_0011D090(void*, void*);
extern "C" void func_0011D3C8(void*, s32);
extern "C" void func_001412E8(void*, s32);
extern "C" s32 func_00141308(void*);
extern "C" s32 func_001412C0(void*);
extern "C" void func_00135B80(void*, s32);
extern "C" s32 func_00139060(s32, s32);
extern "C" s32 D_0040F514;

/* Partial controller/child views; original class identities remain UNVERIFIED. */
static inline void ActivateSelectedChild(void* controller) {
    void* child = (void*)func_001412C0(controller);
    void* table = M2C_FIELD(child, void**, 0x4C);
    void (*activate)(void*) = M2C_FIELD(table, void (**)(void*), 0x44);
    activate((u8*)child + M2C_FIELD(table, s16*, 0x40));
}

extern "C" void func_0011CE98(void* pool, void* actor, void* unused, Game::Vec position, Game::Vec target, f32 time,
                              f32 distance) {
    void* controller = func_0011D090(pool, actor);
    if (controller == NULL) {
        func_00135B80(actor, 2);
        func_00139060(D_0040F514, (s32)actor);
    } else {
        func_0011D3C8((u8*)controller + 0xA0, 2);
        M2C_FIELD(controller, Game::Vec*, 0xB0) = position;
        M2C_FIELD(controller, f32*, 0xC0) = time;
        M2C_FIELD(controller, Game::Vec*, 0xA0) = target;
        M2C_FIELD(controller, f32*, 0xC4) = distance;
        if (Ps2Math::VU0::Length3Word(Game::Sub3(M2C_FIELD(actor, Game::Vec*, 0xA0), target)) < distance * 0.75f)
            func_001412E8(controller, 2);
        func_001412E8(controller, 0);
        func_00141308(controller);
        ActivateSelectedChild(controller);
    }
}
