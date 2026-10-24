#include "ps2/prelude.h"

#include "types_ghidra.h"
extern void * func_00280680();
extern void * D_0040F510;
extern s32 func_00103870();
extern void * D_0040F0E0;
extern s32 func_001E3B48();
extern s32 func_001E5900();
extern s32 func_001D6C48();
extern s32 func_001DBA00(s32, f32);
extern void * D_0040F4D0;
extern void func_001EA7C8();
extern s32 func_001EB4C0();
extern s32 func_001E27D8();
extern s32 func_001E0440();
extern s32 func_001EA200();
extern s32 func_001ED648();
extern s32 func_001EEB00();
extern s32 func_001EF6F0();
extern s32 func_001D8728();

void func_001E9150(void *arg0) {
    s32 temp_16;
    s128 temp_17;
    s128 temp_19;

    temp_19 = M2C_FIELD(func_00280680(D_0040F510 + 0xCB7C, 0), s128 *, 0x30);
    temp_17 = M2C_FIELD(func_00280680(D_0040F510 + 0xCB7C, 0), s128 *, 0x20);
    temp_16 = func_00103870(D_0040F0E0);
    func_001E3B48(M2C_FIELD(arg0, s32 *, 0x188));
    if (temp_16 == 0) {
        func_001E5900(M2C_FIELD(arg0, s32 *, 0x170));
    }
    func_001D6C48(M2C_FIELD(arg0, s32 *, 0x178));
    func_001DBA00(M2C_FIELD(arg0, s32 *, 0x18C), M2C_FIELD(D_0040F4D0, f32 *, 0x1C));
    func_001EA7C8(M2C_FIELD(arg0, void **, 0x194));
    func_001EB4C0(M2C_FIELD(arg0, s32 *, 0x190));
    func_001E27D8(M2C_FIELD(arg0, s32 *, 0x180), temp_19, temp_17);
    func_001E0440(M2C_FIELD(arg0, s32 *, 0x17C));
    func_001EA200(M2C_FIELD(arg0, s32 *, 0x174));
    func_001ED648(M2C_FIELD(arg0, s32 *, 0x198));
    func_001EEB00(M2C_FIELD(arg0, s32 *, 0x19C));
    func_001EF6F0(M2C_FIELD(arg0, s32 *, 0x1A0));
    func_001D8728(M2C_FIELD(arg0, s32 *, 0x1A8));
}
