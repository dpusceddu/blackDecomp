#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

void* SelectedRecord(void* object) {
    if(Field<int>(object,0x120)!=0x1c)return 0;
    int index=Field<signed char>(object,0x11d);
    return index<0?0:static_cast<char*>(object)+index*0x18;
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002722D0);
#endif
