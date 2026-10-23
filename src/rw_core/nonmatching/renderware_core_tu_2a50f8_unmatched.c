/* Typed PS2 stream, matrix and bitmap free-list hypotheses. */

#ifdef NONMATCHING_2A5140
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/stream.h"
#include "rw_core/error.h"
extern s32 func_002A5548(s32,...);extern RwErrorRecordPS2 *func_002A55D8(RwErrorRecordPS2 *);extern u32 func_002A7050(RwStreamPS2 *,void *,u32);extern RwStreamPS2 *func_002A73D8(RwStreamPS2 *,u32);extern s32 func_002A50F8(RwChunkHeaderPS2 *);
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

#endif

#ifdef NONMATCHING_2A5640
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/math.h"
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

#endif

#ifdef NONMATCHING_2A5850
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/math.h"
extern u8 D_00449444[];extern s32 D_0040E5A8;
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

#endif

#ifdef NONMATCHING_2A5CE8
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/freelist.h"
extern u8 D_00449438[];extern s32 D_0040DEE4;extern void *D_0040DEEC;extern RwFreeLinkPS2 D_0040E5B0;
extern void func_002A6C08(RwFreeListPS2 *);extern void *func_0035C6EC(void *,s32,u32);
RwFreeListPS2 *func_002A5CE8(u32 entry_size,u32 entries,u32 alignment,u32 hint) {
 RwFreeListPS2 *storage=0;s32 preallocate=D_0040DEE4!=0;
 u32 storage_flags=3,bitmap_bytes,rounded_size,bytes;RwFreeListPS2 *list=storage;
 if(!alignment)alignment=16;
 if(!list) {
  if(D_0040DEEC)list=M2C_FIELD(D_00449438,void *(**)(void *,u32),0x118)(D_0040DEEC,hint&0xff0000);
  else list=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(36,hint&0xff0000);
  if(!list)return 0;storage_flags=2;
 }
 bitmap_bytes=(entries+7)>>3;rounded_size=(entry_size+alignment-1)&-alignment;
 list->flags=storage_flags;list->entry_size=rounded_size;list->entries_per_block=entries;list->alignment=alignment;list->bitmap_bytes=bitmap_bytes;list->blocks.next=&list->blocks;list->blocks.previous=&list->blocks;
 bytes=bitmap_bytes+entries*rounded_size+8+alignment-1;
 while(preallocate--) {
  RwFreeLinkPS2 *block=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(bytes,hint);
  if(!block){func_002A6C08(list);return 0;}
  block->previous=&list->blocks;block->next=list->blocks.next;block->next->previous=block;list->blocks.next=block;func_0035C6EC(block+1,0,bitmap_bytes);
 }
 list->global.previous=&D_0040E5B0;list->global.next=D_0040E5B0.next;D_0040E5B0.next->previous=&list->global;D_0040E5B0.next=&list->global;
 return list;
}

#endif

#ifdef NONMATCHING_2A6010
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/freelist.h"
extern u8 D_00449438[];extern s32 D_0040DEE4;extern void *D_0040DEEC;extern RwFreeLinkPS2 D_0040E5B0;
extern void func_002A6C08(RwFreeListPS2 *);extern void *func_0035C6EC(void *,s32,u32);
RwFreeListPS2 *func_002A6010(u32 entry_size,u32 entries,u32 alignment,s32 preallocate,RwFreeListPS2 *storage,u32 hint) {

 u32 storage_flags=3,bitmap_bytes,rounded_size,bytes;RwFreeListPS2 *list=storage;
 if(!D_0040DEE4)preallocate=0;
 if(!alignment)alignment=16;
 if(!list) {
  if(D_0040DEEC)list=M2C_FIELD(D_00449438,void *(**)(void *,u32),0x118)(D_0040DEEC,hint&0xff0000);
  else list=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(36,hint&0xff0000);
  if(!list)return 0;storage_flags=2;
 }
 bitmap_bytes=(entries+7)>>3;rounded_size=(entry_size+alignment-1)&-alignment;
 list->flags=storage_flags;list->entry_size=rounded_size;list->entries_per_block=entries;list->alignment=alignment;list->bitmap_bytes=bitmap_bytes;list->blocks.next=&list->blocks;list->blocks.previous=&list->blocks;
 bytes=bitmap_bytes+entries*rounded_size+8+alignment-1;
 while(preallocate--) {
  RwFreeLinkPS2 *block=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(bytes,hint);
  if(!block){func_002A6C08(list);return 0;}
  block->previous=&list->blocks;block->next=list->blocks.next;block->next->previous=block;list->blocks.next=block;func_0035C6EC(block+1,0,bitmap_bytes);
 }
 list->global.previous=&D_0040E5B0;list->global.next=D_0040E5B0.next;D_0040E5B0.next->previous=&list->global;D_0040E5B0.next=&list->global;
 return list;
}

#endif

#ifdef NONMATCHING_2A6340
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/freelist.h"
extern u8 D_00449438[];extern void *func_0035C6EC(void *,s32,u32);
void *func_002A6340(RwFreeListPS2 *list,u32 hint) {
 RwFreeLinkPS2 *block=list->blocks.next;u32 bytes=list->bitmap_bytes,byte_index,bit,remaining;
 for(;block!=&list->blocks;block=block->next) {
  u8 *bitmap=(u8 *)(block+1);remaining=list->entries_per_block;
  for(byte_index=0;byte_index<bytes;byte_index++) {
   u32 value=bitmap[byte_index];
   if(value==255) {remaining-=8;continue;}
   for(bit=0;remaining && bit<8;bit++,remaining--) {
    u8 mask=128>>bit;
    if(!(value&mask)) {bitmap[byte_index]|=mask;return (void *)((((u32)block+list->alignment+bytes+7)&-list->alignment)+(byte_index*8+bit)*list->entry_size);}
   }
  }
 }
 block=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(bytes+list->entries_per_block*list->entry_size+list->alignment+7,hint);
 if(!block)return 0;
 func_0035C6EC(block+1,0,bytes);
 block->next=list->blocks.next;list->blocks.next=block;block->next->previous=block;((u8 *)(block+1))[0]=128;block->previous=&list->blocks;
 return (void *)(((u32)block+list->alignment+bytes+7)&-list->alignment);
}

#endif

#ifdef NONMATCHING_2A66C8
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/freelist.h"
extern u8 D_00449438[];
RwFreeListPS2 *func_002A66C8(RwFreeListPS2 *list,void *memory) {
 RwFreeLinkPS2 *block=list->blocks.next;u32 bytes=list->bitmap_bytes;
 for(;block!=&list->blocks;block=block->next) {
  u32 first=(u32)(block+1)+bytes;
  if((u32)memory>=first && (u32)memory<=first+list->entries_per_block*list->entry_size) {
   u32 entry=((u32)memory-first)/list->entry_size,index=entry>>3,i,total=0;u8 *bitmap=(u8 *)(block+1);
   bitmap[index]&=~(128>>(entry-(index<<3)));
   if(!(list->flags&2))return list;
   for(i=0;i<bytes;i++)total+=bitmap[i];
   if(!total) {block->previous->next=block->next;block->next->previous=block->previous;M2C_FIELD(D_00449438,void (**)(void *),0x10c)(block);}
   return list;
  }
 }
 return list;
}

#endif

#ifdef NONMATCHING_2A6868
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/freelist.h"
extern u8 D_00449438[];extern void *func_0035C544(void *,const void *,u32);
RwFreeListPS2 *func_002A6868(RwFreeListPS2 *list,void (*callback)(void *,void *),void *context) {
 u32 bytes=list->bitmap_bytes;RwFreeLinkPS2 *block=list->blocks.next,*next;
 while(block!=&list->blocks) {
  u8 *snapshot=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(bytes,0x10000);u32 i,bit;
  if(!snapshot)return 0;func_0035C544(snapshot,block+1,bytes);next=block->next;
  for(i=0;i<bytes;i++) {u32 value=snapshot[i];if(value)for(bit=0;bit<8;bit++)if(value&(128>>bit))callback((void *)((((u32)block+list->alignment+bytes+7)&-list->alignment)+(i*8+bit)*list->entry_size),context);}
  M2C_FIELD(D_00449438,void (**)(void *),0x10c)(snapshot);block=next;
 }
 return list;
}

#endif

#ifdef NONMATCHING_2A6CC8
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/freelist.h"
extern u8 D_00449438[];extern s32 D_0040DEE4;extern void *D_0040DEEC;extern RwFreeLinkPS2 D_0040E5B0;
extern void func_002A6C08(RwFreeListPS2 *);extern void *func_0035C6EC(void *,s32,u32);
RwFreeListPS2 *func_002A6CC8(u32 entry_size,u32 entries,u32 alignment,s32 preallocate,RwFreeListPS2 *storage,u32 hint) {

 u32 storage_flags=3,bitmap_bytes,rounded_size,bytes;RwFreeListPS2 *list=storage;
 if(!D_0040DEE4)preallocate=0;
 if(!alignment)alignment=16;
 if(!list) {
  if(D_0040DEEC)list=M2C_FIELD(D_00449438,void *(**)(void *,u32),0x118)(D_0040DEEC,hint&0xff0000);
  else list=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(36,hint&0xff0000);
  if(!list)return 0;storage_flags=2;
 }
 bitmap_bytes=(entries+7)>>3;rounded_size=(entry_size+alignment-1)&-alignment;
 list->flags=storage_flags;list->entry_size=rounded_size;list->entries_per_block=entries;list->alignment=alignment;list->bitmap_bytes=bitmap_bytes;list->blocks.next=&list->blocks;list->blocks.previous=&list->blocks;
 bytes=bitmap_bytes+entries*rounded_size+8+alignment-1;
 while(preallocate--) {
  RwFreeLinkPS2 *block=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(bytes,hint);
  if(!block){func_002A6C08(list);return 0;}
  block->previous=&list->blocks;block->next=list->blocks.next;block->next->previous=block;list->blocks.next=block;func_0035C6EC(block+1,0,bitmap_bytes);
 }
 list->global.previous=&D_0040E5B0;list->global.next=D_0040E5B0.next;D_0040E5B0.next->previous=&list->global;D_0040E5B0.next=&list->global;
 return list;
}

#endif

#ifdef NONMATCHING_2A7050
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/stream.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern void *func_0035C544(void *,const void *,u32);extern u32 func_0032A750(void *,u32,u32,void *);extern s32 func_0032A8C8(void *);
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

#endif

#ifdef NONMATCHING_2A71E0
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/stream.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern void *func_0035C544(void *,const void *,u32);extern u32 func_0032A7A0(const void *,u32,u32,void *);
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

#endif

#ifdef NONMATCHING_2A73D8
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
#include "rw_core/stream.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern s32 func_0032A7F0(void *,u32,s32),func_0032A8C8(void *);
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

#endif

#ifdef NONMATCHING_2A5B98
// Unmatched: constant-address folding or FP scheduling remains different.
#include "rw_core/math.h"
extern u8 D_00449438[];extern s32 D_0040E5A8;extern void func_002A5640(RwMatrixPS2 *,const RwMatrixPS2 *,const RwMatrixPS2 *);
s32 func_002A5B98(void (*multiply)(RwMatrixPS2 *,const RwMatrixPS2 *,const RwMatrixPS2 *)) {if(!multiply)multiply=func_002A5640;M2C_FIELD(D_00449438+D_0040E5A8,void (**)(void),8)=(void (*)(void))multiply;return 1;}

#endif

#ifdef NONMATCHING_2A75F0
// Unmatched: constant-address folding or FP scheduling remains different.
#include "rw_core/math.h"
#include "rw_core/error.h"
extern s32 func_002A5548(s32,...);extern RwErrorRecordPS2 *func_002A55D8(RwErrorRecordPS2 *);
f32 func_002A75F0(RwVector3PS2 *destination,const RwVector3PS2 *source) {
 f32 squared=source->x*source->x+source->y*source->y+source->z*source->z,length,factor;
 __asm__("sqrt.s %0, %1":"=f"(length):"f"(squared));
 factor=length;if(length>0.0f)factor=1.0f/length;
 destination->x=source->x*factor;destination->y=source->y*factor;destination->z=source->z*factor;
 if(length<=0.0f) {RwErrorRecordPS2 error;error.plugin_id=1;error.error_code=func_002A5548(25);func_002A55D8(&error);}
 return length;
}

#endif

#ifdef NONMATCHING_2A76E0
// Unmatched: constant-address folding or FP scheduling remains different.
#include "rw_core/error.h"
extern s32 func_002A5548(s32,...);extern RwErrorRecordPS2 *func_002A55D8(RwErrorRecordPS2 *);
f32 func_002A76E0(f32 *destination,const f32 *source) {
 f32 squared=source[0]*source[0]+source[1]*source[1],length,factor;
 __asm__("sqrt.s %0, %1":"=f"(length):"f"(squared));
 factor=length;if(length>0.0f)factor=1.0f/length;
 destination[0]=source[0]*factor;destination[1]=source[1]*factor;
 if(length<=0.0f) {RwErrorRecordPS2 error;error.plugin_id=1;error.error_code=func_002A5548(25);func_002A55D8(&error);}
 return length;
}

#endif
