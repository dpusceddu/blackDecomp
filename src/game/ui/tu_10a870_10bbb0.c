#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_FrontendResourceCache: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_FrontendResourceCache {
    u8 unk_0[3388];
    s32 unk_D3C;
    s32 unk_D40;
    s16 unk_D44;
    u16 unk_D46;
    s32 unk_D48;
    s32 unk_D4C;
    s16 unk_D50;
    u16 unk_D52;
    s32 unk_D54;
    s32 unk_D58;
    s16 unk_D5C;
    u16 unk_D5E;
    s32 unk_D60;
    s32 unk_D64;
    s16 unk_D68;
    u16 unk_D6A;
    s32 unk_D6C;
    s32 unk_D70;
    s16 unk_D74;
    u16 unk_D76;
    s32 unk_D78;
    s32 unk_D7C;
    s16 unk_D80;
    u16 unk_D82;
    s32 unk_D84;
    s32 unk_D88;
    s16 unk_D8C;
    u16 unk_D8E;
    s32 unk_D90;
    s32 unk_D94;
    s16 unk_D98;
    u16 unk_D9A;
} Recovered_FrontendResourceCache;

#include "ps2/recovered_types.h"
extern s32 func_0010BAE0(void *, s32 *, s32);
extern void func_001084A8(Recovered_FrontendResourceCache *, s32, s16);
extern Recovered_FrontendResourceCache * D_0040F4C4;

void func_0010BBB0(void *arg0) {
    func_0010BAE0(arg0, NULL, 0);
    func_001084A8(D_0040F4C4, 0xD, 0);
}
