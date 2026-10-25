#include "include_asm.h"

#include "ps2/prelude.h"
#include "rw_core/stream.h"
#include "ps2/recovered_types.h"
#ifdef NON_MATCHING
#include "rw_core/error.h"
#endif

s32 func_002A50F8(RwChunkHeaderPS2 *header) {
    s32 temp_2;

    temp_2 = header->type;
    switch (temp_2) {
    case 1:
    case 2:
    case 3:
    case 13:
    case 19:
        return 0;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 14:
    case 15:
    case 16:
    case 18:
    case 20:
    case 26:
        return 1;
    default:
        return 0;
    }
}

/* Typed PS2 stream, matrix and bitmap free-list hypotheses. */















#ifdef NON_MATCHING
extern s32 func_002A5548(s32,...);extern RwErrorRecordPS2 *func_002A55D8(RwErrorRecordPS2 *);extern u32 func_002A7050(RwStreamPS2 *,void *,u32);extern RwStreamPS2 *func_002A73D8(RwStreamPS2 *,u32);extern s32 func_002A50F8(RwChunkHeaderPS2 *);
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
s32 func_002A5140(RwStreamPS2 *stream,u32 type,u32 *length,u32 *version) {
 RwChunkHeaderPS2 header;struct {u32 type,length,stamp;} disk;
 for(;;) {
  if(func_002A7050(stream,&disk,12)!=12) {RwErrorRecordPS2 error;error.plugin_id=1;error.error_code=func_002A5548(0x8000001a);func_002A55D8(&error);return 0;}
  header.type=disk.type;header.length=disk.length;
  if(!(disk.stamp&0xffff0000)) {header.version=disk.stamp<<8;header.build=0;}
  else {header.build=disk.stamp&65535;header.version=(((disk.stamp>>14)&0x3ff00)+0x30000)|((disk.stamp>>16)&63);}
  header.is_complex=func_002A50F8(&header);
  if(header.type==type)break;
  if(!func_002A73D8(stream,header.length))return 0;
 }
 if(header.version<0x35000 || header.version>=0x37003) {RwErrorRecordPS2 error;error.plugin_id=1;error.error_code=func_002A5548(0x80000004);func_002A55D8(&error);return 0;}
 if(length)*length=header.length;if(version)*version=header.version;return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5140);
#endif
