#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 (*D_00449540)();
extern void * D_004494F4;
extern s32 D_004494D0;
extern void func_002CF888();
extern s32 (*D_004494C0)();
extern s32 (*D_004494E0)();

s32 func_002AA018(s32 *size) {
    return D_00449540(*size);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA040);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA278);

void * func_002AA288(void *arg0) {
    u8 temp_8;
    void *temp_4;
    void *temp_5;
    void *temp_6;

    temp_6 = M2C_FIELD(arg0, void **, 0xA0);
    temp_8 = M2C_FIELD(temp_6, u8 *, 3);
    if (!(temp_8 & 3)) {
        temp_4 = temp_6 + 8;
        temp_5 = D_004494F4;
        M2C_FIELD(temp_6, void ***, 0xC) = &D_004494F4;
        M2C_FIELD(temp_5, void **, 4) = temp_4;
        D_004494F4 = temp_4;
        M2C_FIELD(temp_6, void **, 8) = temp_5;
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xA0), u8 *, 3) = (u8) (temp_8 | 3);
    M2C_FIELD(arg0, u8 *, 3) = (u8) (M2C_FIELD(arg0, u8 *, 3) | 0xC);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA2E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA2E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA340);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA3F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA420);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA510);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA570);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA710);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AA840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AAA68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AAF48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AB250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AB378);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AB538);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AB8E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ABAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ABAF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ABB98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ABC08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ABD18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ABD68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ABE80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ABE90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC080);

#ifdef NON_MATCHING
#include "ps2/prelude.h"
extern void *func_002AAF48(const char *,s32,void *,void *);extern void func_002AC128(void);
// Unmatched: exact 48-byte body has a 16-byte original zero tail that natural alignment does not explain.
s32 func_002AC090(const char *name) {s32 found=0;func_002AAF48(name,20,func_002AC128,&found);return found;}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC090);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC0D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC128);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC2E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC388);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC460);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC468);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC5D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC628);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC6C8);

s32 func_002AC6E8(s32 arg0, s32 arg1, s32 arg2) {
    s32 (*temp_18)(s32, s32, s32);

    temp_18 = D_004494D0;
    func_002CF888();
    return (temp_18(arg0, arg1, arg2) == 0) ? 0 : arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC750);

s32 func_002AC790(s32 arg0) {
    D_004494C0(0, arg0, 0);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC7D0);

void * func_002AC808(void *arg0) {
    D_004494E0(0, arg0, 0);
    M2C_FIELD(arg0, u8 *, 0x22) = (u8) (M2C_FIELD(arg0, u8 *, 0x22) & 0xE7);
    return arg0;
}
