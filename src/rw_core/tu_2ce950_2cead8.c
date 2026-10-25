#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "rw_core/heap.h"
#endif

extern s32 D_0040E0B0;

s32 func_002CEAD8(void) {
    return D_0040E0B0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CEAE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CEBB0);

/* Typed PS2 hypotheses for the provisional heap/plugin/image grouping. */












#ifdef NON_MATCHING
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CEBE0);
#endif
#ifdef NON_MATCHING
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CEE38);
#endif
#ifdef NON_MATCHING
extern u8 D_00449438[];
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CF150);
#endif
#ifdef NON_MATCHING
typedef struct RwCallbacksPS2 {s32 entries[11];} __attribute__((packed)) RwCallbacksPS2;
extern u8 D_00449438[];extern s32 D_0040E6F0;
extern struct {u8 bytes[4];} D_0040E0C0;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CF440);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CF148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CF2E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CF388);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CF438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2cead8", func_002CF5A8);
