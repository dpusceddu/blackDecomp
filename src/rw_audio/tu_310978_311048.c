#include "include_asm.h"

/* Provisional object-allocation TU from call and shared-data joins. */

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311048", func_00310978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311048", func_00310C88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311048", func_00310DE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311048", func_00310DE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311048", func_00310F68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311048", func_00311008);





#include "rw_audio/object.h"
extern s32 func_0031E1F8(RwaClass *,s32,s32);
extern RwaObject *func_0031E2C0(RwaClass *,s32);
RwaObject *func_00311048(RwaClass *type,u32 *flags,void *defaults,s32 size){
    s32 allocation_flags=*flags;
    if(!type->field48){
        if(!func_0031E1F8(type,size,(allocation_flags>>2)&1))return 0;
    }
    return func_0031E2C0(type,size);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311048", func_003110B0);
#ifdef NON_MATCHING
// Unmatched: typed object/class and property-link hypothesis differs in allocation and scheduling.
u32 func_003111A8(RwaClass *type,u32 flags,u32 *offset){
    u32 local,size=0x28,alignment,value=type->extent_alignment;
    if(!offset)offset=&local;
    if(value&0x0fffffff){
        alignment=1<<(value>>28);
        *offset=(alignment+0x27)&-alignment;
        size=*offset+(type->extent_alignment&0x0fffffff);
    }else *offset=0;
    if(flags&2)size+=4;
    if(flags&1)size+=8+type->properties->input*12+type->properties->output*8;
    return size;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311048", func_003111A8);
#endif
