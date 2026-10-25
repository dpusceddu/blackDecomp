#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern void func_00291FA8();
extern s32 func_00291130();
extern u64 func_00291000();
extern void * func_002911D0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_002902F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_002903F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_00290488);

void func_002904E8(void) {
    func_00291FA8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_002904F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_00290AC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_00291000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_00291130);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_002911D0);

void func_00291410(u64 arg0, u64 arg1) {
    u8 sp[104] __attribute__((aligned(16)));

    *(u64 *)(sp + 96) = arg0;
    *(u64 *)(sp + 104) = arg1;
    func_00291130((sp + 96), sp);
    func_00291130((sp + 104), (sp + 32));
    func_00291000(func_002911D0(sp, (sp + 32), (sp + 64)));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_00291468);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_002914D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_00291778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_002918E0);

#include "ps2/recovered_types.h"
extern s32 func_00291130(void *, void *);
extern s32 func_002918E0(void *, void *);

s32 func_002919F8(s32 arg0, s32 arg1) {
    u8 sp[72] __attribute__((aligned(16)));

    *(s64 *)(sp + 64) = (s64) arg0;
    *(s64 *)(sp + 72) = (s64) arg1;
    func_00291130((sp + 64), sp);
    func_00291130((sp + 72), (sp + 32));
    return func_002918E0(sp, (sp + 32));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_00291A48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_00291B00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_2902f8", func_00291B98);
