#include "include_asm.h"

#include "game/effects/muzzle.hpp"

int Effects::MuzzleMethods::Reset() {resource=0;phase=3;return 1;}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/muzzle_1bcdd8", func_001BCDF0);
