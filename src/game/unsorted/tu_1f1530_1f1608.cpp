#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

void UpdateLinkedItems(void* object,float delta) {
    void* item=Field<void*>(object,0xa0);
    while(item) {
        char* table=Field<char*>(item,0x14);
        typedef void (*Update)(void*,float);
        Update update=Field<Update>(table,0x14);
        update(static_cast<char*>(item)+Field<short>(table,0x10),delta);
        item=Field<void*>(item,4);
    }
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F1608);
#endif
