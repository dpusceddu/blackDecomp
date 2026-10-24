#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00286558(void *arg0);
extern void func_00286720(void *arg0);
extern s32 func_00286598(s32);
extern void func_00286770(void *arg0);

void func_00285C20(s32 arg0) {
    func_00286558(arg0 + 0x1C0);
}

void func_00285C40(s32 arg0) {
    func_00286720(arg0 + 0x1C0);
}

void func_00285C60(s32 arg0) {
    func_00286598(arg0 + 0x1C0);
}

void func_00285C80(s32 arg0) {
    func_00286770(arg0 + 0x1C0);
}
