#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00368E20(s32);

void func_00368F08(s32 arg0) {
    if (arg0 == 0xA) {
        func_00368E20(0xD);
        func_00368E20(0xA);
        return;
    }
    func_00368E20(arg0);
}
