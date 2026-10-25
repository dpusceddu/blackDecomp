#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
#ifdef NON_MATCHING
#include "rw_core/image.h"
#include "rw_core/frame.h"
#endif
extern s32 func_002CFAC0(void *, u32, u32, u32, u32, s32);
extern s32 D_003C3358;

s32 func_002AC850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_002CFAC0(&D_003C3358, (u32) arg0, (u32) arg1, (u32) arg2, (u32) arg3, arg4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC898);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC8A0);
#ifdef NON_MATCHING
typedef struct RwFloatColorPS2 {f32 red,green,blue,alpha;} RwFloatColorPS2;
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
void func_002AC908(const RwImagePS2 *image,s32 left,s32 right,s32 row,RwFloatColorPS2 *output) {
 s32 first=left>>16,last=right>>16,boundary;f32 span=(f32)(right-left)*0.000015258789f,weight;
 const RwColorPS2 *pixel=(const RwColorPS2 *)(image->pixels+(row>>16)*image->stride)+first;
 if(first==last) {
  u8 alpha=pixel->alpha,green=pixel->green,blue=pixel->blue;
  output->red=(f32)pixel->red*0.003921569f*span;output->alpha=(f32)alpha*0.003921569f*span;
  output->green=(f32)green*0.003921569f*span;output->blue=(f32)blue*0.003921569f*span;
 } else {
  f32 red,green,blue,alpha;boundary=(first+1)<<16;weight=(f32)(boundary-left)*0.000015258789f;
  red=(f32)pixel->red*0.003921569f*weight;alpha=(f32)pixel->alpha*0.003921569f*weight;
  green=(f32)pixel->green*0.003921569f*weight;blue=(f32)pixel->blue*0.003921569f*weight;
  output->red=red;output->alpha=alpha;output->green=green;output->blue=blue;pixel++;
  if((boundary>>16)!=last) {
   do {red+=(f32)pixel->red*0.003921569f;green+=(f32)pixel->green*0.003921569f;blue+=(f32)pixel->blue*0.003921569f;alpha+=(f32)pixel->alpha*0.003921569f;boundary+=65536;pixel++;}while((boundary>>16)!=last);
   output->alpha=alpha;output->blue=blue;output->green=green;output->red=red;
  }
  weight=(f32)(right-boundary)*0.000015258789f;
  output->red+=(f32)pixel->red*0.003921569f*weight;output->green+=(f32)pixel->green*0.003921569f*weight;output->blue+=(f32)pixel->blue*0.003921569f*weight;output->alpha+=(f32)pixel->alpha*0.003921569f*weight;
 }
 weight=1.0f/span;output->red*=weight;output->green*=weight;output->blue*=weight;output->alpha*=weight;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC908);
#endif
#ifdef NON_MATCHING
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
void func_002ACBE8(const RwImagePS2 *image,s32 left,s32 right,s32 top,s32 bottom,RwFloatColorPS2 *output) {
 f32 height=(f32)(bottom-top)*0.000015258789f,weight; s32 boundary;RwFloatColorPS2 color;
 if((top>>16)==(bottom>>16)) {func_002AC908(image,left,right,top,output);output->red*=height;output->green*=height;output->blue*=height;output->alpha*=height;}
 else {boundary=((top>>16)+1)<<16;func_002AC908(image,left,right,top,output);weight=(f32)(boundary-top)*0.000015258789f;
  output->red*=weight;output->green*=weight;output->blue*=weight;output->alpha*=weight;
  for(;(boundary>>16)!=(bottom>>16);boundary+=65536) {func_002AC908(image,left,right,boundary,&color);output->red+=color.red;output->green+=color.green;output->blue+=color.blue;output->alpha+=color.alpha;}
  func_002AC908(image,left,right,boundary,&color);weight=(f32)(bottom-boundary)*0.000015258789f;
  output->red+=color.red*weight;output->green+=color.green*weight;output->blue+=color.blue*weight;output->alpha+=color.alpha*weight;
 }
 weight=1.0f/height;output->red*=weight;output->green*=weight;output->blue*=weight;output->alpha*=weight;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ACBE8);
#endif
#ifdef NON_MATCHING
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
RwImagePS2 *func_002ACE68(RwImagePS2 *destination,const RwImagePS2 *source) {
 s32 x,y,left,top=0,dx=(s32)((f32)source->width/(f32)destination->width*65536.0f),dy=(s32)((f32)source->height/(f32)destination->height*65536.0f);
 RwFloatColorPS2 color;
 destination->flags|=source->flags&2;
 for(y=0;y<destination->height;y++,top+=dy) {
  RwColorPS2 *output=(RwColorPS2 *)(destination->pixels+y*destination->stride);left=0;
  for(x=0;x<destination->width;x++,left+=dx) {
   func_002ACBE8(source,left,left+dx-1,top,top+dy-1,&color);
   output->red=(u8)(s32)(color.red*255.0f+0.5f);output->green=(u8)(s32)(color.green*255.0f+0.5f);output->blue=(u8)(s32)(color.blue*255.0f+0.5f);output->alpha=(u8)(s32)(color.alpha*255.0f+0.5f);output++;
  }
 }
 return destination;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ACE68);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD1B0);
#ifdef NON_MATCHING
extern void func_002A5AC8(RwMatrixPS2 *,RwMatrixPS2 *,RwMatrixPS2 *),func_002AD510(RwFramePS2 *,u32),func_002AD5D8(RwFramePS2 *);
static __inline__ void sync_objects(RwFramePS2 *frame) {
 RwObjectLinkPS2 *link=frame->objects.next;
 while(link!=&frame->objects) {void *object=(u8 *)link-8;M2C_FIELD(object,void (**)(void *),0x10)(object);link=link->next;}
}
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
void func_002AD2C8(RwFramePS2 *frame) {
 u32 flags=frame->private_flags;RwFramePS2 *child;
 if(flags&1) {
  if(flags&4)frame->world=frame->modelling;
  sync_objects(frame);
  for(child=frame->child;child;child=child->sibling) {
   u32 child_flags=child->private_flags;
   if((flags|child_flags)&4)func_002A5AC8(&child->world,&child->modelling,&child->parent->world);
   sync_objects(child);child->private_flags&=0xf3;func_002AD510(child->child,(flags&4)|child_flags);
  }
 } else {
  sync_objects(frame);for(child=frame->child;child;child=child->sibling) {sync_objects(child);child->private_flags&=0xf7;func_002AD5D8(child->child);}
 }
 frame->private_flags=flags&0xf0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD2C8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD4A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD510);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD5D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD660);
