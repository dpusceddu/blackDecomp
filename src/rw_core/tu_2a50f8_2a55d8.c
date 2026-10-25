#include "include_asm.h"

#include "rw_core/error.h"
#ifdef NON_MATCHING
#include "ps2/prelude.h"
#include "rw_core/stream.h"
#include "ps2/recovered_types.h"
#include "rw_core/math.h"
#endif
extern u8 D_00449438[];extern s32 D_0040E5A0;

RwErrorRecordPS2 *func_002A55D8(RwErrorRecordPS2 *error) {
 RwErrorRecordPS2 *current=(RwErrorRecordPS2 *)(D_00449438+D_0040E5A0);
 if(!current->plugin_id && current->error_code==(s32)0x80000000) {
  if(error->error_code<0)current->plugin_id=0;else current->plugin_id=error->plugin_id;
  ((RwErrorRecordPS2 *)(D_00449438+D_0040E5A0))->error_code=error->error_code;
 }
 return error;
}

#ifdef NON_MATCHING
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
void func_002A5640(RwMatrixPS2 *result,const RwMatrixPS2 *left,const RwMatrixPS2 *right) {
 f32 b00=right->components.right.x,a00=left->components.right.x,b02=right->components.right.z,b10=right->components.up.x;
 f32 a01=left->components.right.y,a10=left->components.up.x,a11=left->components.up.y,b12=right->components.up.z;
 f32 a20=left->components.at.x,a21=left->components.at.y,b01=right->components.right.y,b11=right->components.up.y;
 f32 b22=right->components.at.z,b20=right->components.at.x,a02=left->components.right.z,a12=left->components.up.z;
 f32 a22=left->components.at.z,b21=right->components.at.y,a30=left->components.position.x,a31=left->components.position.y,a32=left->components.position.z;
 result->components.right.x=a00*b00+a01*b10+a02*b20;
 result->components.right.y=a00*b01+a01*b11+a02*b21;
 result->components.up.z=a10*b02+a11*b12+a12*b22;
 result->components.at.z=a20*b02+a21*b12+a22*b22;
 result->components.right.z=a00*b02+a01*b12+a02*b22;
 result->components.up.x=a10*b00+a11*b10+a12*b20;
 result->components.up.y=a10*b01+a11*b11+a12*b21;
 result->components.at.x=a20*b00+a21*b10+a22*b20;
 result->components.at.y=a20*b01+a21*b11+a22*b21;
 result->components.position.x=a30*b00+a31*b10+a32*b20+right->components.position.x;
 result->components.position.y=a30*b01+a31*b11+a32*b21+right->components.position.y;
 result->components.position.z=a30*b02+a31*right->components.up.z+a32*b22+right->components.position.z;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a55d8", func_002A5640);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a55d8", func_002A5840);
#ifdef NON_MATCHING
extern u8 D_00449444[];extern s32 D_0040E5A8;
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
RwMatrixPS2 *func_002A5850(RwMatrixPS2 *matrix,const RwMatrixTolerancePS2 *tolerance) {
 f32 rx=matrix->components.right.x,ry=matrix->components.right.y,rz=matrix->components.right.z;
 f32 ux=matrix->components.up.x,uy=matrix->components.up.y,uz=matrix->components.up.z;
 f32 ax=matrix->components.at.x,ay=matrix->components.at.y,az=matrix->components.at.z;
 f32 rn=rx*rx+ry*ry+rz*rz-1.0f,un=ux*ux+uy*uy+uz*uz-1.0f,an=ax*ax+ay*ay+az*az-1.0f;
 f32 ra=ax*rx+ay*ry+az*rz,ua=ux*ax+uy*ay+uz*az,ru=rx*ux+ry*uy+rz*uz;
 s32 normal,orthogonal,identity=0;u32 flags=matrix->components.flags;
 if(!tolerance)tolerance=(const RwMatrixTolerancePS2 *)(D_00449444+D_0040E5A8);
 normal=tolerance->normal<rn*rn+un*un+an*an;orthogonal=tolerance->orthogonal<ua*ua+ra*ra+ru*ru;
 if(!normal && !orthogonal) {f32 x=matrix->components.position.x,y=matrix->components.position.y,z=matrix->components.position.z;
  identity=(rx-1.0f)*(rx-1.0f)+ry*ry+rz*rz+ux*ux+(uy-1.0f)*(uy-1.0f)+uz*uz+ax*ax+ay*ay+(az-1.0f)*(az-1.0f)+x*x+y*y+z*z<=tolerance->identity;}
 if(normal)flags&=~1;else flags|=1;if(orthogonal)flags&=~2;else flags|=2;if(identity)flags|=0x20000;else flags&=~0x20000;matrix->components.flags=flags;return matrix;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a55d8", func_002A5850);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a55d8", func_002A5A78);
