#include "include_asm.h"

#include "game/effects/mod_muzzle.hpp"

int ModEffects::MuzzleMethods::Reset() {resource=0;phase=3;return 1;}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BCDF0);
