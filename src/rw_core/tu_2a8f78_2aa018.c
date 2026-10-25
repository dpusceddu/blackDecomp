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


#ifdef NON_MATCHING
#include "ps2/prelude.h"
extern void *func_002AAF48(const char *,s32,void *,void *);extern void func_002AC128(void);
// Unmatched: exact 48-byte body has a 16-byte original zero tail that natural alignment does not explain.
s32 func_002AC090(const char *name) {s32 found=0;func_002AAF48(name,20,func_002AC128,&found);return found;}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa018", func_002AC090);
#endif


s32 func_002AC6E8(s32 arg0, s32 arg1, s32 arg2) {
    s32 (*temp_18)(s32, s32, s32);

    temp_18 = D_004494D0;
    func_002CF888();
    return (temp_18(arg0, arg1, arg2) == 0) ? 0 : arg0;
}


s32 func_002AC790(s32 arg0) {
    D_004494C0(0, arg0, 0);
    return arg0;
}


void * func_002AC808(void *arg0) {
    D_004494E0(0, arg0, 0);
    M2C_FIELD(arg0, u8 *, 0x22) = (u8) (M2C_FIELD(arg0, u8 *, 0x22) & 0xE7);
    return arg0;
}
