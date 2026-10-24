#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/weapons/shot.h"

void func_001632E0(BkModDelayedShotPS2 *shot) {
    shot->active=0;
    shot->weapon=0;
    shot->remaining=0;
    shot->distance=0;
}
