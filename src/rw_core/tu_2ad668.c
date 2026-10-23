// RenderWare texture allocation and image callbacks; names inferred.
#include "rw_core/image_campaign.h"

int func_002AF158(RwRasterView *raster,RwImageView *image) {
 return ((RwRasterView *(*)(RwRasterView *,RwImageView *))IMAGE_PLUGIN->mipmapGenerate)(raster,image)!=0;
}

extern unsigned char D_003C3370[];
void func_002CFDF8(void *,void *);
RwTextureView *func_002AF300(RwRasterView *raster) {
 RwTextureView *texture=D_00449438.poolAlloc(IMAGE_PLUGIN->texturePool,0x30006);
 if(texture){texture->raster=raster;texture->dictionary=0;texture->name[0]=0;texture->mask[0]=0;texture->references=1;texture->filter=0x1101;func_002CFDF8(D_003C3370,texture);}
 return texture;
}

// Unmatched: func_002AD668 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AD9F8 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002ADE38 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AE0B0 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AE790 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AED50 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AEEE0 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF0F8 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF118 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF190 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF1A0 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF240 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF2E0 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF388 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF430 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF438 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF528 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF530 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF5A0 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF5F0 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF608 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF6A8 needs matching image/plugin control flow and callback scheduling.
// Unmatched: func_002AF6F0 needs matching image/plugin control flow and callback scheduling.
