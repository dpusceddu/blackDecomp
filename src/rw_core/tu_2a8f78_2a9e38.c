#include "include_asm.h"

#include "ps2/prelude.h"
extern u8 D_00449438[];extern s32 D_0040DF14;extern void func_002CF990(void),func_002A6AB8(void);

s32 func_002A9E38(void) {s32 success=D_0040DF14==0;if(success){func_002CF990();func_002A6AB8();M2C_FIELD(D_00449438,s32 *,0x124)=0;}return success;}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9E80);
