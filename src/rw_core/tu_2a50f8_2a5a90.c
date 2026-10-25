#include "include_asm.h"

#include "ps2/renderware_inline.h"
#ifdef NON_MATCHING
#include "ps2/prelude.h"
#include "rw_core/stream.h"
#include "ps2/recovered_types.h"
#include "rw_core/math.h"
#include "rw_core/freelist.h"
#endif
extern u8 D_00449444[];extern s32 D_0040E5A8;

s32 func_002A5A90(const RwMatrixTolerancePS2 *tolerance) {
 RwCopyMatrixTolerancePS2((RwMatrixTolerancePS2 *)(D_00449444+D_0040E5A8),tolerance);return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5AC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5B48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5B80);
#ifdef NON_MATCHING
extern u8 D_00449438[];extern s32 D_0040E5A8;extern void func_002A5640(RwMatrixPS2 *,const RwMatrixPS2 *,const RwMatrixPS2 *);
// Unmatched: constant-address folding or FP scheduling remains different.
s32 func_002A5B98(void (*multiply)(RwMatrixPS2 *,const RwMatrixPS2 *,const RwMatrixPS2 *)) {if(!multiply)multiply=func_002A5640;M2C_FIELD(D_00449438+D_0040E5A8,void (**)(void),8)=(void (*)(void))multiply;return 1;}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5B98);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5C80);
#ifdef NON_MATCHING
extern u8 D_00449438[];extern s32 D_0040DEE4;extern void *D_0040DEEC;extern RwFreeLinkPS2 D_0040E5B0;
extern void func_002A6C08(RwFreeListPS2 *);extern void *func_0035C6EC(void *,s32,u32);
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5CE8);
#endif
#ifdef NON_MATCHING
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A6010);
#endif
#ifdef NON_MATCHING
extern u8 D_00449438[];extern void *func_0035C6EC(void *,s32,u32);
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A6340);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A65F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A66C0);
#ifdef NON_MATCHING
extern u8 D_00449438[];
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A66C8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A6860);
#ifdef NON_MATCHING
extern u8 D_00449438[];extern void *func_0035C544(void *,const void *,u32);
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A6868);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A6AB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A6B08);
