#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/effects/random_state.h"

void func_00382340(void) {

}

void func_00382348(void *arg0, s32 arg1) {
    BkEffectRandomSeedPS2((BkEffectRandomStatePS2*)arg0,(EeU32)arg1);
}
