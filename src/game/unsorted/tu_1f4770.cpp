#include "include_asm.h"
#ifdef NON_MATCHING
#include "game/classes/other/UnknownVtable_003E0A40.hpp"
#include "game/classes/other/UnknownVtable_003E0AC0.hpp"
#endif

#ifdef NON_MATCHING
// Partial PS2 views retained for subsequent reconstruction. Enable one candidate
// only after re-scoring its complete class context. No full object sizes are known.



struct Sprite;
extern "C" {void func_00278F00(void*,int,Sprite*);extern char* D_0040F518;}
template<class T> inline T& At(void* p,int offset){return *(T*)((char*)p+offset);}
inline void ReleaseSprite(void* self,int group,int offset){func_00278F00(D_0040F518+At<signed char>(self,0x12)*0xa8+0x40,At<short>(self,0x10)+group,At<Sprite*>(self,offset));}
// Unmatched: renderer pointer and player-index load scheduling; 6 differences.
int Unnamed::UnknownVtable_003E0A40::Function_001F4CB0(){
 ReleaseSprite(this,0,0x1c);ReleaseSprite(this,0,0x18);return 1;
}

// Unmatched: teardown loop shape and register scheduling; 45 differences.
int Unnamed::UnknownVtable_003E0AC0::Function_001FBB48(){
 ReleaseSprite(this,0,0x50);ReleaseSprite(this,0,0x58);ReleaseSprite(this,2,0x18);ReleaseSprite(this,2,0x20);
 for(int i=0;i<3;++i)ReleaseSprite(this,1,0x28+i*4);
 ReleaseSprite(this,2,0x40);ReleaseSprite(this,1,0x48);ReleaseSprite(this,2,0x60);ReleaseSprite(this,2,0x68);
 for(int i=0;i<15;++i)ReleaseSprite(this,2,0x70+i*4);
 for(int i=0;i<8;++i)ReleaseSprite(this,2,0xe8+i*4);
 return 1;
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F4770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F4CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001FBB48);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8318);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F84E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8528);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8FB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001FAC78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001FAE18);
