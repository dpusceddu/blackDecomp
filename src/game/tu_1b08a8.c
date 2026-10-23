#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s64 func_0027B148(void *, u32, u32, u32);
extern void * func_002A9240(void *, f32);
extern void * func_002A9310(void *, f32);

void * func_001B08A8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    func_0027B148(arg0, (u32) arg1, (u32) arg2, (u32) arg3);
    M2C_FIELD(arg0, f32 *, 0x84) = 0.08f;
    func_002A9240(M2C_FIELD(arg0, void **, 0x58), 0.08f);
    M2C_FIELD(arg0, f32 *, 0x88) = 5000.0f;
    temp_v0 = func_002A9310(M2C_FIELD(arg0, void **, 0x58), 5000.0f);
    M2C_FIELD(arg0, f32 *, 0x90) = 1.0f;
    return temp_v0;
}
