#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace Game {
// /SLUS_213.76 0x18b168
// PS2 0x18b168; the Xbox build expands it (ai_movement.hpp) inside UpdateStallRecovery.

bool StallGrace::Pending() const { return !timer.Expired(); }

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/ai_movement_modes_18b168", func_0018B190);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/ai_movement_modes_18b168", func_0018B400);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/ai_movement_modes_18b168", func_0018B458);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/ai_movement_modes_18b168", func_0018B490);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/ai_movement_modes_18b168", func_0018B4C0);
