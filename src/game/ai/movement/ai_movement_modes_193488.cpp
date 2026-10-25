#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace Game {
// /SLUS_213.76 0x193488

bool DirectMode::Reset() { return ResetBase(); }

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001934A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193568);
