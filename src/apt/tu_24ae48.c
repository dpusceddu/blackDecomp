#include "ps2/prelude.h"

extern void * D_003BFB10;
extern s32 func_00253128(void **arg0, u32 arg1, void *);
extern s32 func_003874A8(void **);

void func_0024AE48(void *arg0) {
    void **temp_16;
    void *temp_6;

    temp_6 = D_003BFB10;
    temp_16 = arg0 + 8;
    M2C_FIELD(arg0, void **, 0xC) = temp_6;
    D_003BFB10 = arg0;
    if (func_00253128(temp_16, 0x21U, temp_6) != 0) {
        func_003874A8(temp_16);
    }
}

void func_0024AE98(void *arg0) {
    void **temp_16;
    void *temp_6;

    temp_6 = D_003BFB10;
    temp_16 = arg0 + 8;
    M2C_FIELD(arg0, void **, 0xC) = temp_6;
    D_003BFB10 = arg0;
    if (func_00253128(temp_16, 0x21U, temp_6) != 0) {
        func_003874A8(temp_16);
    }
}
