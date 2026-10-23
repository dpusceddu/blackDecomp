#include "auto/prelude.h"

extern char D_00405C98[];
const char rodata_00405C98[152] __asm__("D_00405C98") __attribute__((aligned(8))) = "Q24Kaim14CScriptManager" "\000" "Q24Kaim13CWorldService" "\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim13CWorldServiceZPFv_PQ24Kaim13CWorldService" "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049ABC8;
extern s32 * func_0038AFB8();
extern s32 func_00370168();
extern s32 D_0049AB88;

s32 * func_0038B268(void) {
    if (D_0049ABC8 == 0) {
        func_0038AFB8();
        func_00370168(&D_0049ABC8, D_00405C98, &D_0049AB88);
    }
    return &D_0049ABC8;
}
