#include "ps2/prelude.h"

extern s32 func_00193988();
extern s32 func_00188F10(s32);
extern s32 func_001894C8(s32);
extern s32 func_00193990(void **, M2C_UNK);

void func_00195D20(void) {
    func_00193988();
}

void func_00195D40(void) {

}

void func_00195D48(void **arg0) {
    if (func_00188F10(*arg0 + 0x150) != 0) {
        func_001894C8(*arg0 + 0x150);
    }
    func_00193990(arg0, 0);
}
