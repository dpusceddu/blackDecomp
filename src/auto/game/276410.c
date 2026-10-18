#include "auto/prelude.h"

extern void func_002763B0(void *arg0);
extern s32 func_002761A0();
extern s32 func_00274040(void *);

void func_00276410(void *arg0) {
    func_002763B0(M2C_FIELD(arg0, void **, 0x14));
    func_002761A0(M2C_FIELD(arg0, void **, 0x14));
    func_002761A0(M2C_FIELD(arg0, void **, 0x14) + 0x20);
    func_00274040(arg0);
}
