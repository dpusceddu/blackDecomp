#ifndef RENDERWARE_CORE_IMAGE_H
#define RENDERWARE_CORE_IMAGE_H
#include "rw_core/quantize.h"
/* Accessed prefixes inferred from PS2 field accesses. */
typedef struct RwImageView {int flags,width,height,depth,stride;QuantByte *pixels;QuantRGBA *palette;} RwImageView;
typedef struct RwRasterView {unsigned char prefix[12];int width,height,depth;unsigned char pixels[8];unsigned char type,flags21,flags22,format;} RwRasterView;
typedef struct RwLink {struct RwLink *next,*previous;} RwLink;
typedef struct RwDictionaryView {unsigned char type,subtype,flags,privateFlags;int object;RwLink textures,link;} RwDictionaryView;
typedef struct RwTextureView {RwRasterView *raster;RwDictionaryView *dictionary;RwLink link;char name[32],mask[32];int filter;int references;} RwTextureView;
typedef struct RwImagePlugin {RwLink dictionaries;void *texturePool,*dictionaryPool;RwDictionaryView *current;void *find,*read;int mipmap,automipmap;void *path;unsigned short loaded;unsigned short padding;void *mipmapGenerate,*mipmapName;} RwImagePlugin;
typedef struct RwEngineImageView {
 unsigned char prefix[0xd0];char *(*copy)(char *,const char *,unsigned);char *(*append)(char *,const char *);
 unsigned char gapD8[0xf4-0xd8];unsigned (*length)(const char *);
 unsigned char gapF8[0x10c-0xf8];void (*free)(void *);
 unsigned char gap110[0x118-0x110];void *(*poolAlloc)(void *,unsigned);void (*poolFree)(void *,void *);
} RwEngineImageView;
extern RwEngineImageView D_00449438;
extern int D_0040E5E8,D_0040E5EC;
#define IMAGE_PLUGIN ((RwImagePlugin *)((char *)&D_00449438+D_0040E5E8))
typedef struct RwErrorView {int plugin,error;} RwErrorView;
int func_002A5548(int,...);void func_002A55D8(RwErrorView *);
RwImageView *func_002ABAF8(int,int,int);RwImageView *func_002ABC08(RwImageView *);void func_002ABB98(RwImageView *);void func_002AB8E0(RwImageView *);
RwImageView *func_002AB378(const char *,const char *);int func_002ABD68(RwImageView *,const RwImageView *);int func_002ACE68(RwImageView *,const RwImageView *);
int func_002AC090(const char *);int func_002AC2E0(const RwImageView *,int,int *,int *,int *,unsigned *);
RwRasterView *func_002AC468(int,int,int,unsigned);void func_002AC568(RwRasterView *);RwRasterView *func_002AC278(RwRasterView *,const RwImageView *);int func_002AC210(RwImageView *,const RwRasterView *);
unsigned func_002AC5D8(RwRasterView *);RwRasterView *func_002AC750(RwRasterView *,unsigned char,int);void func_002AC790(RwRasterView *);
RwImageView *func_002AD1B0(const RwImageView *,int,int);
RwTextureView *func_002AF300(RwRasterView *);RwTextureView *func_002AF1A0(RwTextureView *,const char *);RwTextureView *func_002AF240(RwTextureView *,const char *);
int func_002AF118(char *,char *,unsigned char,int);
void *func_002B1E68(void *);void func_002B1F90(void *);void func_002AFDB0(float,void *,const RwImageView *);unsigned func_002B0DA0(QuantRGBA *,unsigned,void *);void func_002B17C8(QuantByte *,int,int,int,void *,const RwImageView *);
int func_002AD668(QuantRGBA *,RwImageView *,RwImageView **,unsigned,int);
RwImageView *func_002AD9F8(const char *,const char *,int,int *,int *,int *,unsigned *);
#endif
