#include "include_asm.h"
#include "ps2/prelude.h"
#include "rw_core/plugin.h"
#include "ps2/prototypes.h"
#ifdef NON_MATCHING
#include "rw_core/image.h"
#include "rw_core/heap.h"
#endif

extern M2C_UNK D_0040A991;

s32 func_002CF5C0(void) {
    return 1;
}

s32 func_002CF5C8(void) {
    return 1;
}

void func_002CF5D0(void) {

}

void func_002CF5D8(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF5E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF5F8);
#ifdef NON_MATCHING
typedef struct RwLinkPS2 {struct RwLinkPS2 *next,*previous;} RwLinkPS2;
typedef struct RwPoolPS2 {s32 size, reserved[2];void *memory;RwLinkPS2 used,free;RwLinkPS2 *last_free,*last_used;} RwPoolPS2;
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 D_0040E700,D_0040E704;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern s32 func_002CFF58(void *,s32);
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
void *func_002CF610(void *instance,s32 offset) {
 RwPoolPS2 *pool=(RwPoolPS2 *)(D_00449438+offset);
 s32 size=M2C_FIELD(D_00449438,s32 *,0x128);
 D_0040E700=offset;
 if(size) {
  pool->memory=M2C_FIELD(D_00449438,void *(**)(s32,u32),0x108)(size,0x4040b);
  if(!pool->memory) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,size);func_002A55D8(&error);return 0;}
  if(!func_002CFF58(pool->memory,size)) {RwErrorPS2 error;M2C_FIELD(D_00449438,void (**)(void *),0x10c)(pool->memory);error.plugin=1;error.code=func_002A5548(12,0);func_002A55D8(&error);return 0;}
 } else pool->memory=0;
 pool->last_used=&pool->used;pool->last_free=&pool->free;pool->size=size;
 pool->used.next=&pool->used;pool->used.previous=&pool->used;
 pool->free.next=&pool->free;pool->free.previous=&pool->free;
 pool->reserved[0]=0;pool->reserved[1]=0;D_0040E704++;return instance;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF610);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF748);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF750);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF878);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF888);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFAC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFD98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFDE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFDF8);

/* Walk registered plugins from the tail towards the head, invoking destructors. */
RwRegistryPS2 *func_002CFE90(RwRegistryPS2 *registry, s32 object) {
    RwPluginPS2 *plugin = registry->last;
    if (plugin != NULL) {
        do {
            ((s32 (*)(s32, s32, s32))plugin->destruct)(object, plugin->offset, plugin->size);
            plugin = plugin->previous;
        } while (plugin != NULL);
    }
    return registry;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFEF0);

s32 func_002CFF40(s32 arg0) {
    return arg0;
}

s32 func_002CFF48(s32 arg0) {
    return arg0;
}

s32 func_002CFF50(s32 arg0) {
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFF58);

s32 func_002CFFB0(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFFB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFFC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D00F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0178);
#ifdef NON_MATCHING
typedef struct RwChunkHeaderPS2 {u32 type,length,version,build;} RwChunkHeaderPS2;
extern u8 D_00449438[];extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);
extern s32 func_002A5420(void *,u32 *,u32 *,u32 *,u32 *);
extern u32 func_002A7050(void *,void *,u32);extern void *func_002A73D8(void *,u32);
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
char *func_002D0280(char *destination,void *stream) {
 RwChunkHeaderPS2 chunk;u8 narrow[64],wide[128];char *output;u32 remaining; s32 allocated=0;
 for(;;) {
  if(!func_002A5420(stream,&chunk.type,&chunk.length,&chunk.version,0))return 0;
  if(chunk.version-0x35000>0x2002) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000004);func_002A55D8(&error);return 0;}
  if(chunk.type==2 || chunk.type==19)break;
  if(!func_002A73D8(stream,chunk.length))return 0;
 }
 if(!destination) {destination=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(chunk.length,0x30002);allocated=1;
  if(!destination) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,chunk.length);func_002A55D8(&error);return 0;}}
 output=destination;remaining=chunk.length;
 while(remaining) {
  u32 amount,i;u8 *buffer;
  if(chunk.type==2) {amount=remaining<65?remaining:64;buffer=narrow;}else {amount=remaining<129?remaining:128;buffer=wide;}
  if(func_002A7050(stream,buffer,amount)!=amount) {if(allocated)M2C_FIELD(D_00449438,void (**)(void *),0x10c)(destination);return 0;}
  remaining-=amount;
  if(chunk.type==2) {for(i=0;i<amount;i++)*output++=buffer[i];}else {for(i=0;i<amount/2;i++)*output++=buffer[i*2];}
 }
 return destination;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0280);
#endif

void func_002D0678(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0680);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D06B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0758);

s8 * func_002D07C8(s8 *text) {
    s8 *cursor;
    s8 character;

    if (text != NULL) {
        cursor = text;
        if (*text != 0) {
            do {
                character = *cursor;
                if ((u32) (character - 0x61) < 0x1AU) {
                    *cursor = character - 0x20;
                }
                cursor += 1;
            } while (*cursor != 0);
        }
    }
    return text;
}

s8 * func_002D0810(s8 *text) {
    s8 *cursor;
    s8 character;

    if (text != NULL) {
        cursor = text;
        if (*text != 0) {
            do {
                character = *cursor;
                if ((u32) (character - 0x41) < 0x1AU) {
                    *cursor = character + 0x20;
                }
                cursor += 1;
            } while (*cursor != 0);
        }
    }
    return text;
}

s8 * func_002D0890(s8 *arg0, s8 arg1) {
    s8 *var_4;
    s8 *var_6;
    s8 *var_7;
    s8 temp_3;

    var_4 = arg0;
    var_7 = NULL;
    var_6 = var_4;
    do {
        temp_3 = *var_6;
        var_6 += 1;
        var_7 = ((temp_3 ^ arg1) == 0) ? var_4 : var_7;
        var_4 += 1;
    } while (temp_3 != 0);
    return var_7;
}

/* Find the first signed-byte character, including the terminator. */
s8 *func_002D0858(s8 *text,s8 character) {
 s8 *result=0,*cursor=text; s8 value;
 do {value=*cursor++;if(value==character){result=text;break;}text++;}while(value);
 return result;
}

s32 func_002D08C8(void *arg0) {
    s32 var_5;
    s8 temp_3;

    var_5 = 0;
    if ((arg0 != NULL) && ((temp_3 = M2C_FIELD(arg0, s8 *, 0), (temp_3 == 0x5C)) || ((M2C_FIELD((temp_3 + ((s32) &D_0040A991)), u8 *, 0) & 3) && (M2C_FIELD(arg0, s8 *, 1) == 0x3A)))) {
        var_5 = 1;
    }
    return var_5;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0A08);

#include "ps2/recovered_types.h"
extern s32 func_002D1530(void *, s32, u32, u32, u32);
extern M2C_UNK D_003C3370;

s32 func_002D0A18(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_002D1530(&D_003C3370, arg0, (u32) arg1, (u32) arg2, (u32) arg3);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0A50);
#ifdef NON_MATCHING
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
s32 func_002D0A78(const RwImagePS2 *image) {
 s32 translucent=0,x,y; const u8 *row=image->pixels;
 if(image->depth==4 || image->depth==8) {
  for(y=0;y<image->height;y++,row+=image->stride)for(x=0;x<image->width;x++) {
   u32 alpha=image->palette[row[x]].alpha;
   if(alpha<240) {translucent=1;if(alpha>15)return 3;}
  }
 } else if(image->depth==32) {
  for(y=0;y<image->height;y++,row+=image->stride)for(x=0;x<image->width;x++) {
   u32 alpha=((const RwColorPS2 *)row)[x].alpha;
   if(alpha!=255) {translucent=1;if(alpha>15)return 3;}
  }
 }
 return translucent?2:1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0A78);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0D98);
#ifdef NON_MATCHING
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
void func_002D0DA0(RwColorPS2 *out, const u8 *pixels, const RwImagePS2 *image, s32 shift) {
 s32 n=1<<shift, red=0,green=0,blue=0,alpha=0,x,y;
 for(y=0;y<n;y++) {
  const u8 *p=pixels;
  for(x=n;x>0;x--) {
   RwColorPS2 *c=&image->palette[*p++];
   alpha+=c->alpha;red+=c->red;green+=c->green;blue+=c->blue;
  }
  pixels+=image->stride;
 }
 shift*=2;out->alpha=alpha>>shift;out->red=red>>shift;out->green=green>>shift;out->blue=blue>>shift;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0DA0);
#endif
#ifdef NON_MATCHING
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
void func_002D0FD8(RwColorPS2 *out, const RwColorPS2 *pixels, const RwImagePS2 *image, s32 shift) {
 s32 n=1<<shift, red=0,green=0,blue=0,alpha=0,x,y;
 for(y=0;y<n;y++) {
  const RwColorPS2 *p=pixels;
  for(x=n;x>0;x--) { red+=p->red;green+=p->green;blue+=p->blue;alpha+=p->alpha;p++; }
  pixels=(const RwColorPS2 *)((const u8 *)pixels+image->stride);
 }
 shift*=2;out->alpha=alpha>>shift;out->red=red>>shift;out->green=green>>shift;out->blue=blue>>shift;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0FD8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D11C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D11D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D1238);
#ifdef NON_MATCHING
extern s32 D_0040E0B0;
typedef struct RwClusterPS2 { u32 flags; void *data; u32 stride, allocated, used; void *definition; u32 reserved; } RwClusterPS2;
typedef struct RwPipelinePrefixPS2 { u32 reserved[4]; s32 packet_state; } RwPipelinePrefixPS2;
typedef struct RwPacketPS2 { u16 flags, count; RwPipelinePrefixPS2 *pipeline; u32 reserved[3]; RwClusterPS2 clusters[1]; } RwPacketPS2;
extern void func_002CEE38(RwHeapPS2 *,void *);
// Unmatched: stack aggregates, loop expansion and scheduling still differ from the PS2 body.
void func_002D1240(RwPacketPS2 *packet) {
 RwClusterPS2 *cluster=packet->clusters;u32 count=packet->count;
 packet->pipeline->packet_state=1;
 while(count--) {
  if(cluster->definition) {
   if(cluster->data && !(cluster->flags&2))func_002CEE38(D_0040E0B0,cluster->data);
   cluster->flags=0;cluster->data=0;cluster->allocated=0;cluster->used=0;cluster->definition=0;
  }
  cluster++;
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D1240);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D1530);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D1570);
