#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_001AF180();
extern M2C_UNK func_001CA258;
extern M2C_UNK func_001CA208;
extern s32 func_001AF1C0();
extern s32 func_001AF298();

s32 func_001AF1A0(void *draw_list, s32 batches, s32 sort_entries, s32 capacity) {
    M2C_FIELD(draw_list, s32 *, 4) = sort_entries;
    M2C_FIELD(draw_list, s32 *, 0xC) = capacity;
    M2C_FIELD(draw_list, s32 *, 0) = batches;
    M2C_FIELD(draw_list, s32 *, 8) = 0;
    return 1;
}

void func_001AF1B8(void *draw_list) {
    M2C_FIELD(draw_list, s32 *, 8) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AF1C0);

#ifdef NON_MATCHING
// Unmatched: 0x1af298: sorted/direct batch traversal register allocation.
#include "game/actor/vector_math.h"
typedef struct {int a,b,c,d,e;} BkDrawBatchPS2;
extern char *D_0040F4C0;extern BkVectorPS2 *D_0040E5F0;
extern void func_0035C544(void *,void *,int);
extern void func_001C62F0(int,int,unsigned int,unsigned int,unsigned int,int,int);
static inline void identity(BkVectorPS2 *matrix) {
 BkVectorPS2 a,b,c,d;
 __asm__("vsub.xyzw av, vf0, vf0\n\tvsub.xyzw bv, vf0, vf0\n\tvsub.xyzw cv, vf0, vf0\n\tvmove.xyzw dv, vf0\n\tvaddw.x av, vf0, vf0w\n\tvaddw.y bv, vf0, vf0w\n\tvaddw.z cv, vf0, vf0w":"=j av"(a),"=j bv"(b),"=j cv"(c),"=j dv"(d));
 matrix[0]=a;matrix[1]=b;matrix[2]=c;matrix[3]=d;
}
typedef struct {int a;short batchIndex;short b;} BkSortedBatchPS2;
typedef struct {BkDrawBatchPS2 *batches;BkSortedBatchPS2 *sorted;int count;int capacity;int kind;void *compare;} BkDrawListPS2;
extern void func_0035EC50(void *,int,int,void *),func_001AF8F8(void *,BkDrawBatchPS2 *);
void func_001AF298(BkDrawListPS2 *list) {
 BkVectorPS2 matrix[4] __attribute__((aligned(16))),packet;BkDrawBatchPS2 *batch;BkSortedBatchPS2 *entry;int i;
 s64 low=0x10000000,high=((s64)0x8800<<32 | 0x8800)<<13;
 if(list->sorted)func_0035EC50(list->sorted,list->count,8,list->compare);
 {int mode=(int)D_0040F4C0+0xcd70;*(int *)mode=0;}
 identity(matrix);func_0035C544((void *)0x70002d7c,matrix,64);
 if(list->sorted){entry=list->sorted;for(i=0;i<list->count;i++,entry++) {
  batch=&list->batches[entry->batchIndex];
  func_001C62F0(batch->a,batch->b,batch->c&0x7fffffff,batch->d&0x7fffffff,batch->e,(s64)batch->c<0,(s64)batch->d<0);
  if(((signed char *)(batch->c&0x7fffffff))[3]==2)func_001AF8F8(D_0040F4C0+0x14,batch);
 }} else for(i=0;i<list->count;i++) {
  batch=&list->batches[i];
  func_001C62F0(batch->a,batch->b,batch->c&0x7fffffff,batch->d&0x7fffffff,batch->e,(s64)batch->c<0,(s64)batch->d<0);
  if(((signed char *)(batch->c&0x7fffffff))[3]==2)func_001AF8F8(D_0040F4C0+0x14,batch);
 }
 __asm__("pcpyld pv, hv, lv":"=r pv"(packet):"r hv"(high),"r lv"(low));
 *D_0040E5F0++=packet;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AF298);
#endif

void func_001AF4C0(void *actor) {
    func_001AF180(actor + 0xCA58, 0, &func_001CA258);
    func_001AF180(actor + 0xCA70, 1, &func_001CA258);
    func_001AF180(actor + 0xCA88, 2, &func_001CA208);
    func_001AF180(actor + 0xCAA0, 3, NULL);
    func_001AF180(actor + 0xCAB8, 4, NULL);
    func_001AF180(actor + 0xCAD0, 5, NULL);
    func_001AF180(actor + 0xCAE8, 6, NULL);
}

s32 func_001AF580(s32 actor_address, const int *counts)
{
  s32 count0;
  int sort_entries_offset;
  s32 count01;
  s32 count012;
  s32 count0123;
  int batch_address;
  s32 count01234;
  func_001AF1A0(actor_address + 0xCA58, actor_address, actor_address + (sort_entries_offset = 0x9088), counts[0]);
  count0 = counts[0];
  func_001AF1A0(actor_address + 0xCA70, (count0 * 0x14) + actor_address, actor_address + ((count0 * 8) + sort_entries_offset), M2C_FIELD(counts, s32 *, 4));
  count01 = count0 + (M2C_FIELD(counts, s32 *, 4));
  batch_address = (count01 * 0x14) + actor_address;
  func_001AF1A0(actor_address + 0xCA88, batch_address, actor_address + ((count01 * 8) + sort_entries_offset), M2C_FIELD(counts, s32 *, 8));
  count012 = count01 + (M2C_FIELD(counts, s32 *, 8));
  func_001AF1A0(actor_address + 0xCAA0, (count012 * 0x14) + actor_address, 0, counts[3]);
  count0123 = count012 + (counts[3]);
  func_001AF1A0(actor_address + 0xCAB8, (count0123 * 0x14) + actor_address, 0, counts[4]);
  count01234 = count0123 + (counts[4]);
  func_001AF1A0(actor_address + 0xCAD0, (count01234 * 0x14) + actor_address, 0, counts[5]);
  func_001AF1A0(actor_address + 0xCAE8, ((count01234 + (counts[5])) * 0x14) + actor_address, 0, counts[6]);
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AF6D0);

void * func_001AF738(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6, void *arg7) {
    return func_001AF1C0(arg0 + ((M2C_FIELD(arg1, u8 *, 9) * 0x18) + 0xCA58), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

void func_001AF768(s32 actor_address, s32 index)
{
  int record_offset;
  s32 record_address;
 do { record_offset = (index * 0x18) + 0xCA58; record_address = record_offset; } while (0);
  func_001AF298(actor_address + record_address, record_address);
}
