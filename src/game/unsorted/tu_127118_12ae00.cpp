#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

int VisitWorldActor(void* node,int,void* hit) {
    void* actor=Field<void*>(node,0x34);
    if(actor && Field<int>(actor,0xc4)==0) {
        void* owner=Field<void*>(hit,0x24);
        ActorVisited(actor,hit,owner?Field<void*>(owner,0x2a4):0);
    }
    return 1;
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012AE00);
#endif
