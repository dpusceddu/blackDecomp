#include "include_asm.h"

#include "game/effects/emitter_methods.hpp"
extern "C" int func_001B1080(void *);

int Effects::EmitterRecord::Reset() {
    owner = 0;
    func_001B1080(this);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/emitter_1bfea0", func_001BFEC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/emitter_1bfea0", func_001BFED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/emitter_1bfea0", func_001C01E0);

#ifdef NON_MATCHING
#include "game/effects/emitter.h"
#include "game/effects/emitter_list.h"
extern "C" {extern char *D_0040F4D0;extern s128 D_004432A0;void func_001CFF90(s128,f32);void func_001CFFB8(BkEmitterListPS2 *,u8);}
struct BkEmitterTailPS2 {u8 prefix[0x5c10];BkEmitterListPS2 *lists;u8 unknown[0xc];u16 count;};
// Unmatched: inline byte bool branch and large-offset register aliases.
extern "C" void func_001C0518(BkEffectEmittersPS2 *pool) {
 u16 i=0;func_001CFF90(D_004432A0,*(f32 *)(D_0040F4D0+0x20));
 BkEmitterTailPS2 *tail=(BkEmitterTailPS2 *)((char *)pool+0x28000);
 if(tail->count)do {BkEmitterListPS2 *list=tail->lists+i;if(list->HasEmitters())func_001CFFB8(list,*(u8 *)(list->definition+0xe6));i++;}while(i<tail->count);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/emitter_1bfea0", func_001C0518);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/emitter_1bfea0", func_001C0600);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/emitter_1bfea0", func_001C0728);
