#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

unsigned SwapBuffer(void* object) {
    int next=static_cast<int>(static_cast<unsigned>(Field<int>(object,8))+1)%2;
    Field<int>(object,8)=next;
    return static_cast<unsigned*>(object)[next];
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a68", func_001C2A68);
#endif
