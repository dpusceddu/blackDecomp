#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

unsigned CurrentBuffer(void* object) {
    return static_cast<unsigned*>(object)[Field<int>(object,8)];
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2A98);
#endif
