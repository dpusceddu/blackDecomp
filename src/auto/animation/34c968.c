#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_AnimationGraphNode.h"
#include "recovered/Recovered_AnimationParameters.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern f32 * func_0034BC30(s32 *, Recovered_AnimationGraphNode *, Recovered_AnimationParameters *, u32, void *, s32, f32, f32, f32, f32, f32);
extern s32 func_0034C8C8(void *, Recovered_AnimationGraphNode *, Recovered_AnimationParameters *);

f32 * func_0034C968(s32 *arg0, void *arg1, s32 arg2, s32 arg3, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg1, void **, 8);
    return func_0034BC30(arg0, (Recovered_AnimationGraphNode *) arg1, arg2, arg3, func_0034C8C8, M2C_FIELD(temp_2, s32 *, 8), fparg0, fparg1, fparg2, M2C_FIELD(temp_2, f32 *, 0xC), fparg3);
}
