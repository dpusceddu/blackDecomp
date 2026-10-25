#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

int IsWeaponReadyWithoutAction(void* object) {
    void* actor=Field<void*>(Field<void*>(object,0x44),0x7c);
    if(!WeaponReady(Field<void*>(actor,0x2a4)))return 0;
    actor=Field<void*>(Field<void*>(object,0x44),0x7c);
    return PendingWeaponAction(Field<void*>(actor,0x2a4))==0;
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017EA70);
#endif
