#include "auto/prelude.h"

extern s32 func_0013D4B8();
extern void func_0013D5F8();
extern s32 func_0018C260();
extern s32 func_0018C3C0();
extern s32 func_00181418();
extern s32 func_0017CAF8();
extern s32 func_0016AC08();
extern void func_0013D588();

void func_0013D228(void *arg0) {
    void *temp_16;

    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0x7C), s32 *, 0x38C) ^ 2) != 0) {
        temp_16 = arg0 + 0x1DA0;
        func_0013D4B8();
        func_0013D5F8(arg0);
        func_0018C260(temp_16);
        if (func_0018C3C0(temp_16) != 0) {
            func_00181418(arg0 + 0xEC0);
            func_0017CAF8(arg0 + 0x650);
        }
        func_0016AC08(arg0 + 0x1F90);
        func_0013D588(arg0);
    }
}
