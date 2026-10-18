/* Translation unit renderware_core/tu_2a8f78 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 (*D_00449540)();
extern void * D_004494F4;
extern s32 D_004494D0;
extern void func_002CF888();
extern s32 (*D_004494C0)();
extern s32 (*D_004494E0)();

void func_002AA018(s32 *arg0) {
    D_00449540(*arg0);
}

/* Assembly between the functions: func_002AA040 (56 bytes), func_002AA078 (8 bytes), func_002AA080 (232 bytes), func_002AA168 (32 bytes), func_002AA188 (240 bytes), func_002AA278 (16 bytes) */

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

/* Assembly between the functions: func_002AA2E0 (8 bytes), func_002AA2E8 (88 bytes), func_002AA340 (184 bytes), func_002AA3F8 (40 bytes), func_002AA420 (104 bytes), func_002AA488 (136 bytes), func_002AA510 (88 bytes), func_002AA568 (8 bytes), func_002AA570 (416 bytes), func_002AA710 (304 bytes), func_002AA840 (552 bytes), func_002AAA68 (1248 bytes) ... */

s32 func_002AC6E8(s32 arg0, s32 arg1, s32 arg2) {
    s32 (*temp_18)(s32, s32, s32);

    temp_18 = D_004494D0;
    func_002CF888();
    return (temp_18(arg0, arg1, arg2) == 0) ? 0 : arg0;
}

/* Assembly between the functions: func_002AC750 (64 bytes) */

s32 func_002AC790(s32 arg0) {
    D_004494C0(0, arg0, 0);
    return arg0;
}

/* Assembly between the functions: func_002AC7D0 (56 bytes) */

void * func_002AC808(void *arg0) {
    D_004494E0(0, arg0, 0);
    M2C_FIELD(arg0, u8 *, 0x22) = (u8) (M2C_FIELD(arg0, u8 *, 0x22) & 0xE7);
    return arg0;
}
