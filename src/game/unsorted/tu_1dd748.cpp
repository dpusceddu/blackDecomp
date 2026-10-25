#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

float PlaybackInterval(void* object) {
    int divisor=(Field<unsigned short>(object,0x62)<<11)/Field<int>(object,0x48);
    int scaled=static_cast<int>(static_cast<unsigned>(divisor)*PlaybackScale(Field<void*>(object,0x30)));
    return static_cast<float>(PlaybackLength(Field<void*>(object,0x30)))/static_cast<float>(scaled);
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd748", func_001DD748);
#endif
