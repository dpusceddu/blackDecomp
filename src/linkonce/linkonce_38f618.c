#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00407178[];
const char rodata_00407178[152] __asm__("D_00407178") __attribute__((aligned(8))) = "Q266_GLOBAL_$N$D__BuildMachine_sdk_rwaisdk_src_graph_kyastar.cppvHaaaa28CNodePushSuccessorsTraversal" "\000\000\000\000" "Q24Kaim16CVertexTraversal" "\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BB00;
extern s32 func_00389400();
extern s32 func_00370168();
extern M2C_UNK D_0049A938;

s32 * func_0038F618(void) {
    if (D_0049BB00 == 0) {
        func_00389400();
        func_00370168(&D_0049BB00, D_00407178, &D_0049A938);
    }
    return &D_0049BB00;
}
