#include "include_asm.h"
#include "ps2/prelude.h"

extern void* func_0011D090(void*, void*);
extern void func_0011D3C8(void*, s32);
extern void func_001412E8(void*, s32);
extern s32 func_00141308(void*);
extern s32 func_001412C0(void*);
extern void func_00135B80(void*, s32);
extern s32 func_00139060(s32, s32);
extern s32 D_0040F514;

/* Partial controller/child views; original class identities remain UNVERIFIED. */
static inline void ActivateSelectedChild(void* controller) {
    void* child = (void*)func_001412C0(controller);
    void* table = M2C_FIELD(child, void**, 0x4C);
    void (*activate)(void*) = M2C_FIELD(table, void (**)(void*), 0x44);
    activate((u8*)child + M2C_FIELD(table, s16*, 0x40));
}

void func_0011CD00(void* pool, void* actor, f32 time) {
    void* controller = func_0011D090(pool, actor);
    if (controller == NULL) {
        func_00135B80(actor, 2);
        func_00139060(D_0040F514, (s32)actor);
    } else {
        func_0011D3C8((u8*)controller + 0xA0, 3);
        M2C_FIELD(controller, f32*, 0xC4) = time;
        func_001412E8(controller, 5);
        func_00141308(controller);
        ActivateSelectedChild(controller);
    }
}
void func_0011CDA8(void* pool, void* actor, void* target, s32 kind, s128 position, f32 time) {
    void* controller = func_0011D090(pool, actor);
    if (controller == NULL) {
        func_00135B80(actor, 2);
        func_00139060(D_0040F514, (s32)actor);
    } else {
        func_0011D3C8((u8*)controller + 0xA0, 1);
        M2C_FIELD(controller, void**, 0xD4) = target;
        M2C_FIELD(controller, s32*, 0xC8) = kind;
        M2C_FIELD(controller, s128*, 0xB0) = position;
        M2C_FIELD(controller, f32*, 0xC0) = time;
        func_001412E8(controller, 6);
        func_001412E8(controller, 3);
        func_001412E8(controller, 0);
        func_00141308(controller);
        ActivateSelectedChild(controller);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11cd00", func_0011CE98);
void func_0011CFD8(void* pool, void* actor) {
    void* controller = func_0011D090(pool, actor);
    if (controller == NULL) {
        func_00135B80(actor, 2);
        func_00139060(D_0040F514, (s32)actor);
    } else {
        func_0011D3C8((u8*)controller + 0xA0, 4);
        M2C_FIELD(controller, s8*, 0xD0) = -1;
        M2C_FIELD(controller, s32*, 0xC8) = 2;
        {
            s128 position = M2C_FIELD(actor, s128*, 0x90);
            M2C_FIELD(controller, s32*, 0xC0) = 0;
            M2C_FIELD(controller, s32*, 0xD8) = 0;
            M2C_FIELD(controller, s128*, 0xB0) = position;
        }
        func_001412E8(controller, 0);
        func_00141308(controller);
        ActivateSelectedChild(controller);
    }
}
extern void* func_0011D1D0(void*);
extern s32 func_0011D200(void*, void*);
extern s32 func_00136F10(void*, s32);
extern s32 func_00140BB8(void*, void*);
extern void func_001354E0(void*, void*);
extern s32 func_00138F08(void*, void*);
extern s32 func_001A6E58(void*);
extern s32 func_00141418(void*);
void* func_0011D090(void* arg0, void* arg1) {
    void* temp_2;
    s32 temp_2_2;

    temp_2 = func_0011D1D0(arg0);
    if (temp_2 == NULL) { return NULL; }
    temp_2_2 = func_0011D200(arg0, arg1);
    if (temp_2_2 != 0) { M2C_FIELD(arg0, void**, 4) = arg1; }
    func_00136F10(arg1, 1);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg1, void**, 0xB4), void**, 0x34), s32*, 0x18) = 7;
    func_00140BB8(temp_2, arg1);
    func_001354E0(arg1, temp_2);
    func_00138F08(D_0040F514, arg1);
    func_001A6E58(M2C_FIELD(arg1, void**, 0x330));
    if (temp_2_2 != 0) { func_00141418(temp_2); }
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11cd00", func_0011D158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11cd00", func_0011D1C8);

void * func_0011D1D0(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x18);
    if (temp_3 != NULL) {
        M2C_FIELD(arg0, void **, 0x18) = (void *) M2C_FIELD(temp_3, void **, 0x90);
    }
    return temp_3;
}

void func_0011D1F0(void *arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x90) = (void *) M2C_FIELD(arg0, void **, 0x18);
    M2C_FIELD(arg0, void **, 0x18) = arg1;
}
