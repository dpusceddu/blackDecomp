/* Translation unit sony_unidentified/tu_2902f8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern void func_00291FA8();
extern s32 func_00291130();
extern u64 func_00291000();
extern void * func_002911D0();

void func_002904E8(void) {
    func_00291FA8();
}

/* Assembly between the functions: func_002904F0 (1488 bytes), func_00290AC0 (1344 bytes), func_00291000 (304 bytes), func_00291130 (160 bytes), func_002911D0 (576 bytes) */

void func_00291410(u64 arg0, u64 arg1) {
    u8 sp[104] __attribute__((aligned(16)));

    *(u64 *)(sp + 96) = arg0;
    *(u64 *)(sp + 104) = arg1;
    func_00291130((sp + 96), sp);
    func_00291130((sp + 104), (sp + 32));
    func_00291000(func_002911D0(sp, (sp + 32), (sp + 64)));
}
