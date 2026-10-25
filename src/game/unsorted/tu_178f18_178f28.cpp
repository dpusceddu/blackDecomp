#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

int IsUnblockedPlayer(void* object) {
    return Field<int>(object,4)==0 && Field<int>(Field<void*>(object,8),0xc4)==2;
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00178F28);
#endif
