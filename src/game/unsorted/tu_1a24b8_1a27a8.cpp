#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

int IsMovementReady(void* object) {
    if(!MovementReady(Field<char*>(object,0x38)+0x650))return 0;
    return MovementEnabled(Field<char*>(object,0x38)+0x650)!=0;
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A27A8);
#endif
