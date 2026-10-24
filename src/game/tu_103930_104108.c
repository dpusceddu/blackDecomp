#include "ps2/prelude.h"

extern void func_00108668();
extern void ** D_0040F4C4;
extern s32 func_00107B18();
extern M2C_UNK D_0040F0F0;
extern s32 func_00107AB8();
extern void * func_00107CF8();
extern s32 func_00102000();
extern void func_00108540();
extern s32 func_00107B08();

void func_00104108(void) {
    void *temp_2;

    func_00108668(D_0040F4C4, 2);
    func_00107B18(&D_0040F0F0, 2, 0);
    func_00107AB8(&D_0040F0F0, 2, 0);
    temp_2 = func_00107CF8(0x4EB148);
    func_00102000(temp_2);
    func_00108540(D_0040F4C4, 5, temp_2, 0);
    func_00107B08(&D_0040F0F0, 2, 0);
}
