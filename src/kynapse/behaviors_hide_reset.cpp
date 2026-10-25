#include "include_asm.h"

#include "kynapse/behaviors/hide.hpp"
extern const float kNearestLimit;
namespace HideRecovery {

void HideAgent::Reset() {
    farLimit=0;
    nearLimit=kNearestLimit;
}
}
const float kNearestLimit=3.4028234663852886e+38F;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E16B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E4E28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E52C8);
