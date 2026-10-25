#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

unsigned CurrentBuffer(void* object) {
    return static_cast<unsigned*>(object)[Field<int>(object,8)];
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a98", func_001C2A98);
#endif
