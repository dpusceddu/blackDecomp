#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/partial/Recovered_BkEffectLightsPS2.h"
#include "ps2/recovered_types.h"
extern s32 func_001B86F8(s32);
extern void func_001C1930(Recovered_BkEffectLightsPS2 *);
extern s32 func_001BE108(void *);
extern void * D_0040F4C0;
extern s32 func_001C6668(void *);
extern s32 func_001C1A98(void *, void *);
extern s32 func_001C05D8(s32, s32);
extern s32 func_001C67C0(s32, s32);
extern s32 func_001C6860(void *, s32);
extern s32 func_001BCF50(void *);

s32 func_001B1E00(s32 arg0) {
    void *temp_16;

    func_001B86F8(arg0 + 0x54AB0);
    func_001C1930(arg0 + 0x2DC30);
    func_001BE108(arg0 + 0x4EED0);
    temp_16 = (void *) (((s8 *) D_0040F4C0) + 0xD170);
    func_001C6668(temp_16);
    func_001C1A98(arg0 + 0x66280, temp_16);
    func_001C05D8(arg0, 0);
    func_001C67C0((s32) temp_16, 0);
    func_001C6860(temp_16, 0);
    return func_001BCF50(arg0 + 0x4EE00);
}
