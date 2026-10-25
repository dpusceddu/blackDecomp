#include "include_asm.h"

#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "rw_core/image.h"
#endif
extern u8 D_00449438[];

void *func_002AA040(void *instance,void *memory) {M2C_FIELD(D_00449438,void (**)(void *),0x10c)(memory);return instance;}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA2E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA2E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA340);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA3F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA420);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA510);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA570);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA710);
#ifdef NON_MATCHING
extern s32 (*D_004494D4)();
static __inline__ void set_max_alpha(RwColorPS2 *color) {u8 alpha=color->red;if(alpha<color->green)alpha=color->green;if(alpha<color->blue)alpha=color->blue;color->alpha=alpha;}
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
RwImagePS2 *func_002AA840(RwImagePS2 *image) {
 s32 x,y,n;RwColorPS2 *color;
 if(image->depth==4 || image->depth==8) {n=1<<image->depth;color=image->palette;while(n-- >0)set_max_alpha(color++);}
 else if(image->depth==32) {u8 *row=image->pixels;for(y=0;y<image->height;y++,row+=image->stride){color=(RwColorPS2 *)row;for(x=0;x<image->width;x++)set_max_alpha(color++);}}
 return image;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AA840);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AAA68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AAF48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AB250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AB378);
#ifdef NON_MATCHING
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern void *func_0035C544(void *,const void *,u32);
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
s32 func_002AB538(RwImagePS2 *destination,const RwImagePS2 *source) {
 u32 conversion=(source->depth<<8)|destination->depth;s32 width=destination->width,height=destination->height,x,y;
 u8 *to=destination->pixels;const u8 *from=source->pixels;
 if(conversion==0x404 || conversion==0x808 || conversion==0x2020)return 1;
 if(conversion==0x408) {for(y=height;y>0;y--) {func_0035C544(to,from,width);from+=source->stride;to+=destination->stride;}return 1;}
 if(conversion==0x420 || conversion==0x820) {
  const RwColorPS2 *palette=source->palette;
  for(y=0;y<height;y++) {RwColorPS2 *pixel=(RwColorPS2 *)to;for(x=width;x>0;x--)*pixel++=palette[*from++];from+=source->stride-width;to+=destination->stride;}return 1;
 }
 {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000009);func_002A55D8(&error);return 0;}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AB538);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002AB8E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002ABAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002ABAF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002ABB98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78_2aa040", func_002ABC08);
