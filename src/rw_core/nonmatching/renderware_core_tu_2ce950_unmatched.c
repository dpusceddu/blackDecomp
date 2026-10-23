/* Typed PS2 hypotheses for the provisional heap/plugin/image grouping. */

#ifdef NONMATCHING_2CEBE0
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "rw_core/heap.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);
s32 func_002CEBE0(RwHeapSegmentPS2 *segment,RwHeapSegmentPS2 *previous,RwHeapPS2 *heap) {
 RwHeapEntryPS2 *entries=heap->entries,*entry;u32 count=heap->count,i;
 RwHeapBlockPS2 *start,*last,*free_block;
 if(count>=heap->capacity) {
  heap->capacity+=32;
  entries=M2C_FIELD(D_00449438,void *(**)(void *,u32,u32),0x110)(entries,heap->capacity*8,0x1030409);
  if(!entries) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,heap->capacity*8);func_002A55D8(&error);heap->capacity-=32;}
  else {if(entries!=heap->entries)for(i=count;i;i--)entries[count-i].block->free_entry=&entries[count-i];heap->entries=entries;}
 }
 if(!entries)return 0;
 entry=&entries[heap->count++];if(!entry)return 0;
 start=segment->start;last=(RwHeapBlockPS2 *)((u8 *)start+segment->bytes-32);free_block=start+1;
 start->previous=0;start->next=0;start->bytes=0;start->free_entry=0;*last=*start;
 start->next=free_block;free_block->previous=start;free_block->next=last;last->previous=free_block;
 free_block->bytes=(u8 *)last-(u8 *)free_block-32;free_block->free_entry=entry;
 entry->block=free_block;entry->bytes=free_block->bytes;
 if(previous) {RwHeapBlockPS2 *end=(RwHeapBlockPS2 *)((u8 *)previous->start+previous->bytes-32);end->next=start;start->previous=end;}
 return 1;
}

#endif

#ifdef NONMATCHING_2CEE38
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "rw_core/heap.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);
void func_002CEE38(RwHeapPS2 *heap,void *memory) {
 RwHeapBlockPS2 *block=(RwHeapBlockPS2 *)((u8 *)memory-32),*previous=block->previous,*next=block->next;
 s32 previous_free=previous && previous->free_entry,next_free=next && next->free_entry;
 if(previous_free && next_free) {
  RwHeapEntryPS2 *entry=next->free_entry,*last=&heap->entries[heap->count-1];
  if(entry!=last) {*entry=*last;entry->block->free_entry=entry;}
  heap->count--;previous=block->previous;next=block->next;
  previous->bytes+=64+block->bytes+next->bytes;previous->free_entry->bytes=previous->bytes;
  previous->next=next->next;if(next->next)next->next->previous=previous;
 } else if(previous_free) {
  previous->bytes+=32+block->bytes;previous->free_entry->bytes=previous->bytes;
  previous->next=next;if(next)next->previous=previous;
 } else if(next_free) {
  block->bytes+=32+next->bytes;block->free_entry=next->free_entry;
  next->free_entry->block=block;next->free_entry->bytes=block->bytes;
  block->next=next->next;if(next->next)next->next->previous=block;
 } else {
  RwHeapEntryPS2 *entries=heap->entries,*entry;u32 count=heap->count,i;
  if(heap->capacity<=count) {
   heap->capacity+=32;entries=M2C_FIELD(D_00449438,void *(**)(void *,u32,u32),0x110)(entries,heap->capacity*8,0x1030409);
   if(!entries) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,heap->capacity*8);func_002A55D8(&error);heap->capacity-=32;}
   else {if(entries!=heap->entries)for(i=count;i;i--)entries[count-i].block->free_entry=&entries[count-i];heap->entries=entries;}
  }
  if(entries) {entry=&entries[heap->count++];if(entry){entry->block=block;entry->bytes=block->bytes;block->free_entry=entry;}}
 }
}

#endif

#ifdef NONMATCHING_2CF150
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "rw_core/heap.h"
extern u8 D_00449438[];
extern s32 func_002CEBE0(RwHeapSegmentPS2 *,RwHeapSegmentPS2 *,RwHeapPS2 *);
RwHeapPS2 *func_002CF150(u32 bytes) {
 RwHeapPS2 *heap; RwHeapSegmentPS2 *segment,*previous,*p; s32 success;
 if(bytes<1024)bytes=1024;
 heap=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(sizeof(RwHeapPS2),0x40409);
 if(heap) {
  bytes=(bytes+31)&~31;if(bytes<128)bytes=128;
  segment=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(bytes+139,0x1040409);
  if(segment) {
   segment->bytes=bytes;segment->next=0;segment->start=(RwHeapBlockPS2 *)(((u32)segment+139)&~127);
   heap->bytes=bytes;heap->dirty=1;heap->segments=segment;heap->entries=0;heap->capacity=0;heap->count=0;
   previous=0;p=segment->next;
   while(p) {if(!func_002CEBE0(p,previous,heap)){success=0;goto done;}if(!previous)heap->first=p->start;previous=p;p=p->next;}
   p=heap->segments;success=func_002CEBE0(p,previous,heap);
   if(success) {if(!previous)heap->first=p->start;heap->dirty=0;}
 done:
   if(success)return heap;
   if(segment)M2C_FIELD(D_00449438,void (**)(void *),0x10c)(segment);
  }
  M2C_FIELD(D_00449438,void (**)(void *),0x10c)(heap);
 }
 return 0;
}

#endif

#ifdef NONMATCHING_2CF440
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "auto/prelude.h"
typedef struct RwCallbacksPS2 {s32 entries[11];} __attribute__((packed)) RwCallbacksPS2;
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 D_0040E6F0;
extern struct {u8 bytes[4];} D_0040E0C0;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);
RwCallbacksPS2 *func_002CF440(RwCallbacksPS2 *callbacks) {
 if(!callbacks) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000016);func_002A55D8(&error);return 0;}
 if(M2C_FIELD(D_00449438,s32 *,0x124)==3) {*callbacks=*(RwCallbacksPS2 *)(D_00449438+D_0040E6F0+4);return callbacks;}
 if(callbacks!=(RwCallbacksPS2 *)(D_00449438+D_0040E6F0+4)) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000018);func_002A55D8(&error);return 0;}
 callbacks->entries[0]=7;callbacks->entries[2]=5;callbacks->entries[3]=6;
 callbacks->entries[6]=1;callbacks->entries[7]=2;callbacks->entries[1]=2;
 callbacks->entries[4]=0;callbacks->entries[5]=1;
 __builtin_memcpy(&callbacks->entries[8],&D_0040E0C0,4);
 callbacks->entries[9]=0;__builtin_memcpy(&callbacks->entries[10],&D_0040E0C0,4);return callbacks;
}

#endif

#ifdef NONMATCHING_2CF610
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "auto/prelude.h"
typedef struct RwLinkPS2 {struct RwLinkPS2 *next,*previous;} RwLinkPS2;
typedef struct RwPoolPS2 {s32 size, reserved[2];void *memory;RwLinkPS2 used,free;RwLinkPS2 *last_free,*last_used;} RwPoolPS2;
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 D_0040E700,D_0040E704;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern s32 func_002CFF58(void *,s32);
void *func_002CF610(void *instance,s32 offset) {
 RwPoolPS2 *pool=(RwPoolPS2 *)(D_00449438+offset);
 s32 size=M2C_FIELD(D_00449438,s32 *,0x128);
 D_0040E700=offset;
 if(size) {
  pool->memory=M2C_FIELD(D_00449438,void *(**)(s32,u32),0x108)(size,0x4040b);
  if(!pool->memory) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,size);func_002A55D8(&error);return 0;}
  if(!func_002CFF58(pool->memory,size)) {RwErrorPS2 error;M2C_FIELD(D_00449438,void (**)(void *),0x10c)(pool->memory);error.plugin=1;error.code=func_002A5548(12,0);func_002A55D8(&error);return 0;}
 } else pool->memory=0;
 pool->last_used=&pool->used;pool->last_free=&pool->free;pool->size=size;
 pool->used.next=&pool->used;pool->used.previous=&pool->used;
 pool->free.next=&pool->free;pool->free.previous=&pool->free;
 pool->reserved[0]=0;pool->reserved[1]=0;D_0040E704++;return instance;
}

#endif

#ifdef NONMATCHING_2CF990
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "rw_core/plugin.h"
extern void *D_0040E708;
extern RwRegistryPS2 **D_0040E0C4;
extern u32 D_0040E0C8;
extern u8 D_00449438[];
extern void func_002A6868(void *, void *, void *);
extern void func_002CFEF0(void);
extern void func_002A6340(void);
extern void func_002A65F0(void *);
s32 func_002CF990(void) {
 if(D_0040E708) {
  u32 i;
  func_002A6868(D_0040E708,func_002CFEF0,D_0040E708);
  if(M2C_FIELD(D_00449438,void **,0x118)!=(void *)func_002A6340) {
   for(i=0;i<D_0040E0C8;i++) {
    RwPluginPS2 *p=D_0040E0C4[i]->first;
    RwRegistryPS2 *owner=0;
    if(p) {owner=p->registry;do {RwPluginPS2 *next=p->next;M2C_FIELD(D_00449438,void (**)(void *,RwPluginPS2 *),0x11c)(0,p);p=next;}while(p);}
    if(owner && owner->first) {owner->last=0;owner->size=owner->original_size;owner->first=0;}
   }
   if(D_0040E0C4) {M2C_FIELD(D_00449438,void (**)(void *),0x10c)(D_0040E0C4);D_0040E0C4=0;}
  }
  func_002A65F0(D_0040E708);D_0040E708=0;
 }
 return 1;
}

#endif

#ifdef NONMATCHING_2CFAC0
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "rw_core/plugin.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern void *D_0040E708;extern u32 D_0040E0C8;extern RwRegistryPS2 **D_0040E0C4;
extern s32 func_002AA010(void),func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);
extern void func_002A6340(void),func_002CFF40(void),func_002CFF48(void),func_002CFF50(void);
s32 func_002CFAC0(RwRegistryPS2 *registry,u32 size,s32 id,void *construct,void *destruct,void *copy) {
 RwPluginPS2 *plugin;u32 i;
 if(!D_0040E708)return -1;
 if(func_002AA010()) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000017);func_002A55D8(&error);return -1;}
 if(M2C_FIELD(D_00449438,void **,0x118)!=(void *)func_002A6340) {
  for(i=0;i<D_0040E0C8;i++)if(D_0040E0C4[i]==registry)break;
  if(i==D_0040E0C8) {
   RwRegistryPS2 **registries=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)((D_0040E0C8+1)*4,0x40000);
   i=0;if(D_0040E0C4) {for(;i<D_0040E0C8;i++)registries[i]=D_0040E0C4[i];M2C_FIELD(D_00449438,void (**)(void *),0x10c)(D_0040E0C4);}
   D_0040E0C8++;registries[i]=registry;D_0040E0C4=registries;
  }
 }
 for(plugin=registry->first;plugin;plugin=plugin->next)if(plugin->id==id) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000017);func_002A55D8(&error);return plugin->offset;}
 {s32 total=registry->size+((size+3)&~3);if(registry->max_size && registry->max_size<total)return -1;
 plugin=M2C_FIELD(D_00449438,void *(**)(void *,u32),0x118)(D_0040E708,0x40000);if(!plugin)return -1;
 plugin->offset=registry->size;registry->size=total;}
 plugin->size=size;plugin->id=id;plugin->read=0;plugin->write=0;plugin->stream_size=0;plugin->always=0;plugin->rights=0;
 plugin->construct=construct?construct:(void *)func_002CFF40;plugin->destruct=destruct?destruct:(void *)func_002CFF48;plugin->copy=copy?copy:(void *)func_002CFF50;
 plugin->unknown=0;plugin->next=0;plugin->previous=0;plugin->registry=registry;
 if(!registry->first) {registry->last=plugin;registry->first=plugin;}else {registry->last->next=plugin;plugin->previous=registry->last;registry->last=plugin;}
 return plugin->offset;
}

#endif

#ifdef NONMATCHING_2D0280
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "auto/prelude.h"
typedef struct RwChunkHeaderPS2 {u32 type,length,version,build;} RwChunkHeaderPS2;
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);
extern s32 func_002A5420(void *,u32 *,u32 *,u32 *,u32 *);
extern u32 func_002A7050(void *,void *,u32);extern void *func_002A73D8(void *,u32);
char *func_002D0280(char *destination,void *stream) {
 RwChunkHeaderPS2 chunk;u8 narrow[64],wide[128];char *output;u32 remaining; s32 allocated=0;
 for(;;) {
  if(!func_002A5420(stream,&chunk.type,&chunk.length,&chunk.version,0))return 0;
  if(chunk.version-0x35000>0x2002) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000004);func_002A55D8(&error);return 0;}
  if(chunk.type==2 || chunk.type==19)break;
  if(!func_002A73D8(stream,chunk.length))return 0;
 }
 if(!destination) {destination=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(chunk.length,0x30002);allocated=1;
  if(!destination) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,chunk.length);func_002A55D8(&error);return 0;}}
 output=destination;remaining=chunk.length;
 while(remaining) {
  u32 amount,i;u8 *buffer;
  if(chunk.type==2) {amount=remaining<65?remaining:64;buffer=narrow;}else {amount=remaining<129?remaining:128;buffer=wide;}
  if(func_002A7050(stream,buffer,amount)!=amount) {if(allocated)M2C_FIELD(D_00449438,void (**)(void *),0x10c)(destination);return 0;}
  remaining-=amount;
  if(chunk.type==2) {for(i=0;i<amount;i++)*output++=buffer[i];}else {for(i=0;i<amount/2;i++)*output++=buffer[i*2];}
 }
 return destination;
}

#endif

#ifdef NONMATCHING_2D0A78
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "rw_core/image.h"
s32 func_002D0A78(const RwImagePS2 *image) {
 s32 translucent=0,x,y; const u8 *row=image->pixels;
 if(image->depth==4 || image->depth==8) {
  for(y=0;y<image->height;y++,row+=image->stride)for(x=0;x<image->width;x++) {
   u32 alpha=image->palette[row[x]].alpha;
   if(alpha<240) {translucent=1;if(alpha>15)return 3;}
  }
 } else if(image->depth==32) {
  for(y=0;y<image->height;y++,row+=image->stride)for(x=0;x<image->width;x++) {
   u32 alpha=((const RwColorPS2 *)row)[x].alpha;
   if(alpha!=255) {translucent=1;if(alpha>15)return 3;}
  }
 }
 return translucent?2:1;
}

#endif

#ifdef NONMATCHING_2D0DA0
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "rw_core/image.h"
void func_002D0DA0(RwColorPS2 *out, const u8 *pixels, const RwImagePS2 *image, s32 shift) {
 s32 n=1<<shift, red=0,green=0,blue=0,alpha=0,x,y;
 for(y=0;y<n;y++) {
  const u8 *p=pixels;
  for(x=n;x>0;x--) {
   RwColorPS2 *c=&image->palette[*p++];
   alpha+=c->alpha;red+=c->red;green+=c->green;blue+=c->blue;
  }
  pixels+=image->stride;
 }
 shift*=2;out->alpha=alpha>>shift;out->red=red>>shift;out->green=green>>shift;out->blue=blue>>shift;
}

#endif

#ifdef NONMATCHING_2D0FD8
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "rw_core/image.h"
void func_002D0FD8(RwColorPS2 *out, const RwColorPS2 *pixels, const RwImagePS2 *image, s32 shift) {
 s32 n=1<<shift, red=0,green=0,blue=0,alpha=0,x,y;
 for(y=0;y<n;y++) {
  const RwColorPS2 *p=pixels;
  for(x=n;x>0;x--) { red+=p->red;green+=p->green;blue+=p->blue;alpha+=p->alpha;p++; }
  pixels=(const RwColorPS2 *)((const u8 *)pixels+image->stride);
 }
 shift*=2;out->alpha=alpha>>shift;out->red=red>>shift;out->green=green>>shift;out->blue=blue>>shift;
}

#endif

#ifdef NONMATCHING_2D1240
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
#include "rw_core/heap.h"
typedef struct RwClusterPS2 { u32 flags; void *data; u32 stride, allocated, used; void *definition; u32 reserved; } RwClusterPS2;
typedef struct RwPipelinePrefixPS2 { u32 reserved[4]; s32 packet_state; } RwPipelinePrefixPS2;
typedef struct RwPacketPS2 { u16 flags, count; RwPipelinePrefixPS2 *pipeline; u32 reserved[3]; RwClusterPS2 clusters[1]; } RwPacketPS2;
extern RwHeapPS2 *D_0040E0B0;
extern void func_002CEE38(RwHeapPS2 *,void *);
void func_002D1240(RwPacketPS2 *packet) {
 RwClusterPS2 *cluster=packet->clusters;u32 count=packet->count;
 packet->pipeline->packet_state=1;
 while(count--) {
  if(cluster->definition) {
   if(cluster->data && !(cluster->flags&2))func_002CEE38(D_0040E0B0,cluster->data);
   cluster->flags=0;cluster->data=0;cluster->allocated=0;cluster->used=0;cluster->definition=0;
  }
  cluster++;
 }
}

#endif
