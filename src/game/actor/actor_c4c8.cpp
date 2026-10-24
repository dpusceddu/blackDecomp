#include "include_asm.h"

#include "game/actor/region_state.hpp"
namespace CampaignActor {
extern "C" {
void func_00125CD8(void *);
void func_0026AA68(int);void func_0026A840(int);
void func_001AE5E8(void *, const Matrix4 *, PositionArg, PositionArg, PositionArg);
extern char *D_0040F4C0;
extern Position4 D_00414D20, D_00414D30;
}

int RegionState::Initialize(unsigned long id,RegionConfig*data){
 func_00125CD8(this);*(unsigned long*)this=id;config=data;source=data;if(data->enabled)enabled=1;else enabled=0;
 switch(data->mode){case 0:mode=0;break;case 1:mode=1;break;case 2:mode=2;break;case 3:mode=3;break;case 4:mode=4;break;}
 switch(data->policy){case 0:policy=0;break;case 1:policy=1;break;case 2:policy=2;break;}
 if(config->enabled)enabled=1;else enabled=0;triggered=0;return 1;
}
void RegionState::RenderBox(){
 func_0026AA68(0);func_0026A840(0);PositionArg color=Load(D_00414D30);if(enabled)color=Load(D_00414D20);
 func_001AE5E8(D_0040F4C0,&world,Load(this->color),Load(halfExtent),color);
}
}

// Unmatched: 0x16C728 yaw polynomial and rigid-inverse temporary copies.
// Unmatched: 0x16C9E8 trigger predicate and callback control-flow lifetimes.

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169D20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169D48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169D88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169EB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169EB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169ED8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169EE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169EF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169EF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00169F38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A2F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A5E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A720);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A7A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A7C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AA78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AB18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AB38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AB40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AB58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016ABA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016ABA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AC08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AC98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016ACB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AD18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AD38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AD40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016ADE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AE08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AFB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B4F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B5E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B630);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B690);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B710);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B730);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B788);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B7A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BA18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BBF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BE08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BE10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BE60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BEA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BEE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016C220);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016C250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016C2A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016C380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016C3B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016C700);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016C708);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016C728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016C9E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016CB50);
