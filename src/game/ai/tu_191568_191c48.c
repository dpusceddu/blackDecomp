#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00179BD0(void *, s32);
extern void func_00191578(void *);
extern s32 func_0013D3F0(void *);
extern void *func_002E1C58(s32, void *);
extern void *func_0016DD68(void *, s32);
extern void func_00192380(void *, s32);
extern void func_00179C60(void *);
extern void func_00191F28(void *);
extern void *D_0040F4D4;
extern s32 D_004548B8;

void func_00191C48(void *arg0) {
    func_00179BD0(arg0 + 0xA0, M2C_FIELD(arg0, s32 *, 0x34));
    func_00179BD0(arg0 + 0x110, M2C_FIELD(arg0, s32 *, 0x34));
}

// Unmatched: 00191C80: virtual-call registers and route field-store scheduling.
#ifdef NON_MATCHING
u8 func_00191C80(void *mode) {
    void *route;
    void *vtable;
    void *selection;
    func_00191578(mode);
    M2C_FIELD(mode, void **, 0x90) = func_002E1C58(
        func_0013D3F0(M2C_FIELD(mode, void **, 0x34)), &D_004548B8);
    selection = func_0016DD68(D_0040F4D4, 1);
    route = M2C_FIELD(mode, void **, 0x90);
    vtable = M2C_FIELD(route, void **, 0);
    {
        s16 adjustment = M2C_FIELD(vtable, s16 *, 0x70);
        void (*setSelection)(void *, void *) = M2C_FIELD(vtable, void (**)(void *, void *), 0x74);
        setSelection((s8 *) route + adjustment, selection);
    }
    M2C_FIELD(M2C_FIELD(mode, void **, 0x90), s32 *, 0x70) = 0;
    M2C_FIELD(M2C_FIELD(mode, void **, 0x90), s32 *, 0x74) = 0;
    M2C_FIELD(mode, s32 *, 0x188) = 3;
    func_00192380(mode, 1);
    func_00179C60((s8 *) mode + 0xA0);
    func_00179C60((s8 *) mode + 0x110);
    M2C_FIELD(mode, s32 *, 0x180) = 0;
    M2C_FIELD(mode, s32 *, 0x184) = 0;
    M2C_FIELD(mode, s32 *, 0x98) = -1;
    func_00191F28(mode);
    return 1;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_191568_191c48", func_00191C80);
