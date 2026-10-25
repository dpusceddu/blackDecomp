#include "include_asm.h"

#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "rw_core/stream.h"
#include "ps2/recovered_types.h"
#include "rw_core/error.h"
#endif

f32 func_002A76C0(const f32 *vector) {f32 squared=vector[0]*vector[0]+vector[1]*vector[1],length;__asm__("sqrt.s %0, %1" : "=f"(length):"f"(squared));return length;}

#ifdef NON_MATCHING
extern s32 func_002A5548(s32,...);extern RwErrorRecordPS2 *func_002A55D8(RwErrorRecordPS2 *);
// Unmatched: constant-address folding or FP scheduling remains different.
f32 func_002A76E0(f32 *destination,const f32 *source) {
 f32 squared=source[0]*source[0]+source[1]*source[1],length,factor;
 __asm__("sqrt.s %0, %1":"=f"(length):"f"(squared));
 factor=length;if(length>0.0f)factor=1.0f/length;
 destination[0]=source[0]*factor;destination[1]=source[1]*factor;
 if(length<=0.0f) {RwErrorRecordPS2 error;error.plugin_id=1;error.error_code=func_002A5548(25);func_002A55D8(&error);}
 return length;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A76E0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A7790);
