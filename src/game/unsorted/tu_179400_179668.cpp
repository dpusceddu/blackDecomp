#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

unsigned TableWord(void* object,int index) {
    return Field<unsigned*>(object,0x70)[index];
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_179400_179668", func_00179668);
#endif
