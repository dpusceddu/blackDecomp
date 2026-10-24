#include "include_asm.h"

#include "game/effects/pool.h"

void func_001B8640(BkEffectRecordsPS2 *list,u32 pass) {
 int i;
 for(i=0;i<list->count;i++) {
  if(*(u8 *)((char *)&list->records[i]+0x10e)==pass) {
   --list->count;
   if(i!=list->count)list->records[i]=list->records[list->count];
   --i;
  }
 }
}
