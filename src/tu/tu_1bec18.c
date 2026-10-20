/* Translation unit tu_1bec18 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "mod/effects/attachments.h"
#include "mod/effects/emitter.h"

extern s32 func_001B0FF8();
extern s32 func_001B1080();
extern s32 func_001D0010(s32);

s32 func_001BEC68(BkModAttachedEffectsPS2 *arg0) {
    s32 *temp_3;
    u32 var_3;
    u32 var_4;
    BkModAttachedEffectPS2 *temp_2;
    BkModEffectChildrenPS2 *temp_5;

    var_3 = 0;
    do {
        temp_2 = &arg0->records[var_3];
        temp_2->active = 0;
        var_4 = 0;
        temp_5 = &temp_2->children;
loop_2:
        temp_3 = (s32 *)&temp_5->items[var_4];
        var_4 = (var_4 + 1) & 0xFFFF;
        *temp_3 = 0;
        if (var_4 < 8U) {
            goto loop_2;
        }
        var_3 = (var_3 + 1) & 0xFFFF;
        temp_5->resource = 0;
    } while (var_3 < 0x2CU);
    return 1;
}

s32 func_001BECC8(void) {
    return 1;
}

/* Assembly between the functions: func_001BECD0 (668 code bytes; 672-byte span), func_001BEF70 (1964 code bytes; 1968-byte span) */

s32 func_001BF720(BkEffectEmitterRecordPS2 *arg0) {
    arg0->owner = 0;
    return func_001B0FF8(arg0);
}

/* Assembly between the functions: func_001BF740 (472 bytes), func_001BF918 (1416 bytes) */

s32 func_001BFEA0(BkEffectEmitterRecordPS2 *arg0) {
    arg0->owner = 0;
    func_001B1080(arg0);
    return 1;
}

/* Assembly between the functions: func_001BFEC8 (4 code bytes; 8-byte span), func_001BFED0 (272 bytes), func_001BFFE0 (508 code bytes; 512-byte span), func_001C01E0 (192 bytes), func_001C02A0 (632 bytes), func_001C0518 (192 bytes) */

void func_001C05D8(s32 arg0, s32 arg1) {
    func_001D0010(arg1);
}

void func_001C05F8(void) {

}
