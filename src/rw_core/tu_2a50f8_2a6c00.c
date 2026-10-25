#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "rw_core/stream.h"
#include "ps2/recovered_types.h"
#include "rw_core/freelist.h"
#endif

extern s32 D_0040DEE4;

void func_002A6C00(s32 arg0) {
    D_0040DEE4 = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a6c00", func_002A6C08);
#ifdef NON_MATCHING
extern u8 D_00449438[];extern s32 D_0040DEE4;extern void *D_0040DEEC;extern RwFreeLinkPS2 D_0040E5B0;
// Unmatched: loop expansion, FP scheduling or stack aggregate lifetime still differs.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a50f8_2a6c00", func_002A6CC8);
#endif
