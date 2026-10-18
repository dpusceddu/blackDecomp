#include "auto/prelude.h"

extern s32 func_0032D248();
extern s32 func_0032D358();
extern s32 func_0032D590();
extern s32 func_0032D7C0();
extern s32 func_0032D990();
extern s32 func_0032DCE8();
extern s32 func_0032FAF8();
extern s32 func_0037C4E0();
extern s32 func_0032DF00(M2C_UNK, M2C_UNK);

s32 func_0032E320(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x18);
}

void func_0032E328(void *arg0) {
    func_0032D248();
    func_0032D358(arg0);
    func_0032D590(arg0);
    func_0032D7C0(arg0);
    func_0032D990(arg0, M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0x20));
    func_0032DCE8(arg0);
    func_0032FAF8(M2C_FIELD(arg0, void **, 0x1C));
    func_0037C4E0(M2C_FIELD(arg0, s32 *, 0x18));
}

void func_0032E390(void) {
    func_0032DF00(1, 0xFFFF);
}

void func_0032E3B0(void) {
    func_0032DF00(0, 0xFFFF);
}
