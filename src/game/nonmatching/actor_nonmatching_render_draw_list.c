// Unmatched: 0x1af298: sorted/direct batch traversal register allocation.
#ifdef NONMATCHING
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

#endif
