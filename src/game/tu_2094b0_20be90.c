#include "ps2/prelude.h"

extern void func_0020D188(void *, s32);
extern void * D_0040F544;
extern void func_0020D1A8(void *, s32);

void func_0020BE90(s32 arg0) {
    func_0020D188(D_0040F544 + 0xE90, arg0);
}

void func_0020BEB8(s32 arg0) {
    if (arg0 != 0) {
        func_0020D1A8(D_0040F544 + 0xE90, arg0);
    }
}

void func_0020BEE8(s32 arg0) {
    if (arg0 != 0) {
        func_0020D1A8(D_0040F544 + 0xE90, arg0);
    }
}

void func_0020BF18(void) {

}
