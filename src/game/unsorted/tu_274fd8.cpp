#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

int ContainsAddress(void* object,void* address) {
    unsigned value=reinterpret_cast<unsigned>(address);
    return value>=Field<unsigned>(object,8) && value<Field<unsigned>(object,0xc);
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_274fd8", func_00274FD8);
#endif
