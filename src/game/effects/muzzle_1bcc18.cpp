#include "include_asm.h"

#include "game/effects/muzzle.hpp"

void Effects::MuzzleMethods::InitializeFields() {rotation=0.0f;resource=0;phase=3;}

#ifdef NON_MATCHING
#include "game/effects/vector.h"
struct BkEffectVertexPS2 { BkEffectPointPS2 position;f32 u,v;u32 color,unknown; };
static inline u32 PackColor(BkEffectPointPS2 color) {
 s128 v=*(s128 *)&color,packed,limit=(s128)0x8000ff00ff00ffULL;
 __asm__("vmulw.xyzw outv, cv, vf0w\n\tvftoi0.xyzw outv, outv":"=j outv"(v):"j cv"(v));
 __asm__("pextlh lv, zv, lv":"+r lv"(limit):"r zv"(0));
 __asm__("pminw pv, vv, lv\n\tppach pv, zv, pv\n\tppacb pv, zv, pv":"=r pv"(packed):"r vv"(v),"r lv"(limit),"r zv"(0));
 return (u32)packed;
}
// Unmatched: vector construction and packed color code generation.
extern "C" int func_001BCC30(BkEffectVertexPS2 *vertices) {
 const f32 coordinates[6][3]={{-1,-1,0},{1,-1,0},{-1,1,0},{-1,1,0},{1,-1,0},{1,1,0}};
 BkEffectPointPS2 white={128,128,128,128};u32 color=PackColor(white);
 for(int i=0;i<6;i++) {
  vertices[i].position.x=coordinates[i][0];vertices[i].position.y=coordinates[i][1];vertices[i].position.z=coordinates[i][2];vertices[i].position.w=1;
  vertices[i].color=color;
 }
 vertices[0].u=0;vertices[0].v=0;vertices[1].u=1;vertices[1].v=0;vertices[2].u=0;vertices[2].v=1;
 vertices[3].u=0;vertices[3].v=1;vertices[4].u=1;vertices[4].v=0;vertices[5].u=1;vertices[5].v=1;return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BCC30);
#endif
