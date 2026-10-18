#include "auto/prelude.h"

extern s32 func_001F1C08();
extern void func_00200A68(void *arg0);
extern s32 func_001F9028(void *);
extern s32 func_001FA468(void *);

void func_001F9EB0(void *arg0) {
    func_001F1C08();
    M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    M2C_FIELD(arg0, s32 *, 0xA4) = 0;
    func_00200A68(arg0 + 0x20);
    func_001F9028(arg0 + 0xC0);
    func_001FA468(arg0 + 0xC80);
    M2C_FIELD(arg0, s32 *, 0xEA8) = 0;
}
