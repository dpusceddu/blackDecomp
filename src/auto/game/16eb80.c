#include "auto/prelude.h"

extern s32 func_00274E40();
extern s32 func_0016EA10();
extern void func_0016EC78();
extern void func_0016ED80();
extern s32 func_00107B08();
extern M2C_UNK D_0040F0F0;
extern s32 func_00107AB8();
extern void * func_00107D20();
extern s32 func_00274E68();
extern s32 func_0016EF00();
extern s32 func_0016F3D0();

void func_0016EB80(void *arg0) {
    s32 temp_18;
    void *temp_19;

    temp_18 = arg0 + 0x50;
    M2C_FIELD(arg0, s32 *, 0x6C) = 0;
    M2C_FIELD(arg0, s8 *, 0x4C) = 0;
    M2C_FIELD(arg0, s8 *, 0x4D) = 0;
    func_00274E40(temp_18);
    func_0016EA10(arg0 + 0x7C, 0x10);
    func_0016EA10(arg0 + 0x88, 1);
    M2C_FIELD(arg0, s32 *, 0x78) = 0;
    func_0016EC78(arg0);
    func_0016ED80(arg0);
    func_00107B08(&D_0040F0F0, 0, 0);
    func_00107AB8(&D_0040F0F0, 2, 0);
    temp_19 = func_00107D20(0x40000);
    func_00107B08(&D_0040F0F0, 2, 0);
    func_00107AB8(&D_0040F0F0, 0, 0);
    func_00274E40(temp_18);
    func_00274E68(temp_18, temp_19, 0x40000);
    func_0016EF00(arg0);
    func_0016F3D0(arg0);
}
