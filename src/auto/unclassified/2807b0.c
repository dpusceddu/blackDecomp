#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00281620(void *, f32, f32, f32, f32, f32);
extern s32 func_002805A0(void *, f32);

void func_002807B0(s32 arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    func_00281620(arg0 + 0xB308, fparg0, fparg1, fparg2, fparg3, fparg4);
    func_002805A0(arg0 + 0xCB7C, fparg2);
}
