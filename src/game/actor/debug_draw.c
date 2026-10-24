#include "include_asm.h"

#include "ps2/prelude.h"
typedef struct {int unknown,count,capacity;void **items;} BkDebugListPS2;
extern void func_00266088(void),func_00268250(int),func_002662A8(void);
extern void func_001AB6C0(void *,const char *,...);extern void func_001AB468(void *,void *);
extern int D_003BCFB4,D_003D1CD4;extern char *D_0040F514;

void func_001AB500(char *debug) {
 int i; BkDebugListPS2 *first,*second;
 if(M2C_FIELD(debug,u8 *,0x42)) {
  volatile float color[4] __attribute__((aligned(16)));
  color[0]=0.8f;color[1]=0.8f;color[2]=0.4f;color[3]=1.0f;
  M2C_FIELD(debug,int *,0x28)=12;M2C_FIELD(debug,int *,0x2c)=0;M2C_FIELD(debug,s128 *,0x30)=*(s128 *)color;
  func_00266088();func_00268250(0);
  func_001AB6C0(debug,"  CBkActor::Update");func_001AB6C0(debug,"  Blackadder DecodeFrame");
  M2C_FIELD(debug,int *,0x28)=12;M2C_FIELD(debug,int *,0x2c)=16;
  func_001AB6C0(debug,"%d",D_003BCFB4);func_001AB6C0(debug,"%d",D_003D1CD4);
  M2C_FIELD(debug,int *,0x28)=12;M2C_FIELD(debug,int *,0x2c)=20;
  func_001AB6C0(debug,"%d",M2C_FIELD(debug,int *,0x44));func_001AB6C0(debug,"%d",M2C_FIELD(debug,int *,0x50));func_002662A8();
 }
 if(M2C_FIELD(debug,u8 *,0x41)) {
  first=(BkDebugListPS2 *)(D_0040F514+0x79a0);second=(BkDebugListPS2 *)(D_0040F514+0x79b0);
  for(i=0;i<first->count;i++)if(first->items[i])func_001AB468(debug,first->items[i]);
  for(i=0;i<second->count;i++)if(second->items[i])func_001AB468(debug,second->items[i]);
 }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AB6C0);
