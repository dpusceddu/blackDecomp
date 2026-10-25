#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

void AdvanceRing(void* object) {
    int count=Field<int>(object,0);
    if(count>0) {
        int next=static_cast<int>(static_cast<unsigned>(Field<int>(object,4))+1);
        Field<int>(object,4)=next%count;
    }
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176f38", func_00176F38);
#endif
