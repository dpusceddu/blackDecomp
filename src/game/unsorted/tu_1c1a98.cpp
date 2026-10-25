#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/draft_views.hpp"
namespace Game { namespace DraftViews {

int RefreshAtCoordinates(void* object,const int* coordinates) {
    PrepareCoordinates(object,coordinates);
    void* context=Field<void*>(Field<void*>(effects,0xd540),0x58);
    void* position=Field<void*>(context,0x60);
    int previousX=Field<int>(position,0xc);
    Field<int>(position,0xc)=coordinates[0];
    int previousY=Field<int>(position,0x10);
    Field<int>(Field<void*>(context,0x60),0x10)=coordinates[1];
    PublishCoordinates(effects+0xcfd0,context);
    SetEffectMode(effects+0x14,3);
    Field<int>(Field<void*>(context,0x60),0xc)=previousX;
    Field<int>(Field<void*>(context,0x60),0x10)=previousY;
    PublishCoordinates(effects+0xcfd0,context);
    return FinishCoordinates(object);
}
} }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C1A98);
#endif
