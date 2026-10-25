#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "rw_core/stream.h"
#include "ps2/recovered_types.h"
#endif

extern void * func_0035E7D8();
extern s32 func_0035F660();
extern s32 func_0035E778();

void func_002A6FF0(void) {
    func_0035E7D8();
}

void func_002A7010(void) {
    func_0035F660();
}

void func_002A7030(void) {
    func_0035E778();
}

#ifdef NON_MATCHING
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern void *func_0035C544(void *,const void *,u32);extern u32 func_0032A750(void *,u32,u32,void *);extern s32 func_0032A8C8(void *);
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
u32 func_002A7050(RwStreamPS2 *stream,void *destination,u32 size) {
 if(stream->type==3) {
  if(stream->data.memory.size-stream->data.memory.position<size) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(5);func_002A55D8(&error);size=stream->data.memory.size-stream->data.memory.position;}
  func_0035C544(destination,stream->data.memory.buffer+stream->data.memory.position,size);stream->data.memory.position+=size;return size;
 }
 if(stream->type==1 || stream->type==2) {
  void *file=stream->data.file;u32 amount=func_0032A750(destination,1,size,file);if(amount==size)return amount;
  if(func_0032A8C8(file)) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(5);func_002A55D8(&error);}else {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x8000001a);func_002A55D8(&error);}return amount;
 }
 if(stream->type==4)return stream->data.custom.read(stream->data.custom.context,destination,size);
 {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(14);func_002A55D8(&error);return 0;}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a6ff0", func_002A7050);
#endif
#ifdef NON_MATCHING
extern u8 D_00449438[];extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern void *func_0035C544(void *,const void *,u32);extern u32 func_0032A7A0(const void *,u32,u32,void *);
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
RwStreamPS2 *func_002A71E0(RwStreamPS2 *stream,const void *source,u32 size) {
 if(stream->type==3) {
  if(!stream->data.memory.buffer) {
   stream->data.memory.buffer=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(512,0x30404);
   if(!stream->data.memory.buffer) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,512);func_002A55D8(&error);return 0;}stream->data.memory.size=512;
  }
  if(stream->data.memory.size-stream->data.memory.position<size) {
   u32 capacity=stream->data.memory.size+(size<512?512:size);u8 *memory=M2C_FIELD(D_00449438,void *(**)(void *,u32,u32),0x110)(stream->data.memory.buffer,capacity,0x1030404);
   if(!memory) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,capacity-stream->data.memory.size);func_002A55D8(&error);return 0;}
   stream->data.memory.buffer=memory;stream->data.memory.size=capacity;
  }
  func_0035C544(stream->data.memory.buffer+stream->data.memory.position,source,size);stream->data.memory.position+=size;return stream;
 }
 if(stream->type==1 || stream->type==2) {if(func_0032A7A0(source,1,size,stream->data.file)==size)return stream;{RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x8000001c);func_002A55D8(&error);return 0;}}
 if(stream->type==4)return stream->data.custom.write(stream->data.custom.context,source,size)?stream:0;
 {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(14);func_002A55D8(&error);return 0;}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a6ff0", func_002A71E0);
#endif
#ifdef NON_MATCHING
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern s32 func_0032A7F0(void *,u32,s32),func_0032A8C8(void *);
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
RwStreamPS2 *func_002A73D8(RwStreamPS2 *stream,u32 size) {
 if(!size)return stream;
 if(stream->type==3) {
  u32 position=stream->data.memory.position+size;if(position<=stream->data.memory.size){stream->data.memory.position=position;return stream;}
  stream->data.memory.position=stream->data.memory.size;{RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(5);func_002A55D8(&error);return 0;}
 }
 if(stream->type==1 || stream->type==2) {void *file=stream->data.file;if(!func_0032A7F0(file,size,1))return stream;
  if(func_0032A8C8(file)){RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(5);func_002A55D8(&error);}return 0;}
 if(stream->type==4)return stream->data.custom.skip(stream->data.custom.context,size)?stream:0;
 {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(14);func_002A55D8(&error);return 0;}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a6ff0", func_002A73D8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a6ff0", func_002A7510);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a6ff0", func_002A7520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a6ff0", func_002A7598);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a6ff0", func_002A75F0);
