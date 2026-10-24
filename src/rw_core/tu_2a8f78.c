#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 (*D_004494D4)();
extern s32 func_002AC6E8(s32);
extern s32 func_002A8688();
extern s32 func_002A7DD0();
extern s32 func_002A8DA0();
extern s32 func_002A8860();
extern void * func_002D0910();
extern s32 func_002CFAC0();
extern M2C_UNK D_003C3210;

#ifdef NON_MATCHING
/* PS2 camera, engine, image and frame models within this provisional grouping. */

#ifdef NONMATCHING_2A8F78
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "ps2/prelude.h"
#include "rw_core/camera.h"
#include "ps2/recovered_types.h"

extern M2C_UNK D_00449438;
extern u32 D_0040E5C8;
extern void * func_002A9518(void *);
extern s32 func_002A95E0(u32);
extern s32 func_002A9588(s32);
extern void * func_002CFDF8(void *, void *);
extern s32 D_003C31F8;

RwCameraPS2 *func_002A8F78(void) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;
    RwCameraPS2 *camera;

    camera = M2C_FIELD(&D_00449438, void *(**)(s32, M2C_UNK), 0x118)(M2C_FIELD((D_0040E5C8 + ((s32) &D_00449438)), s32 *, 0), 0x30005);
    if (camera == NULL) {
        return 0;
    }
    camera->subtype = 0;
    camera->type = 4;
    camera->flags = 0;
    camera->private_flags = 0;
    camera->frame = 0;
    camera->sync = func_002A9518;
    camera->view_offset[0] = 0.0f;
    camera->near_plane = 0.05f;
    camera->far_plane = 10.0f;
    camera->view_offset[1] = 0.0f;
    camera->begin_update = func_002A95E0;
    camera->end_update = func_002A9588;
    camera->reciprocal_window[0] = 1.0f;
    camera->fog_plane = 5.0f;
    camera->projection = 1;
    camera->view_window[1] = 1.0f;
    camera->view_window[0] = 1.0f;
    camera->reciprocal_window[1] = 1.0f;
    camera->color_raster = 0;
    camera->depth_raster = 0;
    temp_f2 = (M2C_FIELD(&D_00449438, f32 *, 0x1C) - M2C_FIELD(&D_00449438, f32 *, 0x18)) * 0.0001f;
    temp_f1 = M2C_FIELD(&D_00449438, f32 *, 0x18) + temp_f2;
    temp_f0 = M2C_FIELD(&D_00449438, f32 *, 0x1C) - temp_f2;
    temp_f3 = (temp_f0 - temp_f1) / -19.9f;
    camera->z_scale = temp_f3;
    camera->z_shift = (f32) (((temp_f0 + temp_f1) - (temp_f3 * 20.1f)) * 0.5f);
    M2C_FIELD(camera, s32 *, 0x2C) = 0;
    func_002CFDF8(&D_003C31F8, camera);
    return camera;
}

#endif

#ifdef NONMATCHING_2A9640
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

extern s32 func_002A9DF0(s32, s32, s32, s32);
extern s32 func_002A5588(s32, u32);
extern s32 func_002A55B8(s32);
extern s32 func_002A7868(s32, u32);
extern s32 func_002A78C0(s32);
extern s32 func_002CF5E0(s32);
extern s32 func_002CF5F8(s32);
extern s32 func_002A5BC8(s32, u32);
extern s32 func_002A5C80(s32);
extern s32 func_002AA488(s32, u32);
extern s32 func_002AA420(s32);
extern s32 func_002A7520(s32, u32);
extern s32 func_002A7598(s32);
extern s32 func_002A9498(s32, u32);
extern s32 func_002A9430(s32);
extern s32 func_002AA570(s32, u32);
extern s32 func_002AA710(s32);
extern s32 func_002AC388(s32, u32);
extern s32 func_002AC8A0(s32);
extern s32 func_002AEEE0(s32, u32);
extern s32 func_002AED50(s32);
extern s32 func_002CE950(s32, u32);
extern s32 func_002CE980(s32);
extern s32 func_002D0078(s32, u32);
extern s32 func_002D00F0(s32);
extern s32 func_002CE9A8();
extern s32 func_002CE708(s32, u32);
extern s32 func_002CE7C8(s32);
extern s32 func_002CF610(s32, u32);
extern s32 func_002CF910(s32);

s32 func_002A9640(void) {
    s32 result;
    result = func_002A9DF0(8, 0x40F, (s32) func_002A5588, (s32) func_002A55B8);
    result |= func_002A9DF0(0x18, 0x401, (s32) func_002A7868, (s32) func_002A78C0);
    result |= func_002A9DF0(0, 0x40D, (s32) func_002CF5E0, (s32) func_002CF5F8);
    result |= func_002A9DF0(0x18, 0x402, (s32) func_002A5BC8, (s32) func_002A5C80);
    result |= func_002A9DF0(4, 0x403, (s32) func_002AA488, (s32) func_002AA420);
    result |= func_002A9DF0(4, 0x404, (s32) func_002A7520, (s32) func_002A7598);
    result |= func_002A9DF0(4, 0x405, (s32) func_002A9498, (s32) func_002A9430);
    result |= func_002A9DF0(0x220, 0x406, (s32) func_002AA570, (s32) func_002AA710);
    result |= func_002A9DF0(0x64, 0x407, (s32) func_002AC388, (s32) func_002AC8A0);
    result |= func_002A9DF0(0x34, 0x408, (s32) func_002AEEE0, (s32) func_002AED50);
    result |= func_002A9DF0(0x60, 0x409, (s32) func_002CE950, (s32) func_002CE980);
    result |= func_002A9DF0(4, 0x412, (s32) func_002D0078, (s32) func_002D00F0);
    result |= func_002CE9A8();
    result |= func_002A9DF0(0x7C, 0x40A, (s32) func_002CE708, (s32) func_002CE7C8);
    result |= func_002A9DF0(0x28, 0x40B, (s32) func_002CF610, (s32) func_002CF910);
    return result > -1;
}

#endif

#ifdef NONMATCHING_2A9B70
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "ps2/prelude.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 D_0040DF14;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern void *func_002BFE58(void);
extern s32 func_002A9F08(void *,s32,void *,void *,s32);
s32 func_002A9B70(void *parameters) {
 void *device;
 if(M2C_FIELD(D_00449438,s32 *,0x124)!=1) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000001);func_002A55D8(&error);return 0;}
 if(!parameters) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000016);func_002A55D8(&error);return 0;}
 device=func_002BFE58();if(!device)return 0;
 func_002A9F08(device,4,D_00449438+0x10,D_00449438+0x108,0);
 if(!func_002A9F08(device,0,0,parameters,0))return 0;
 func_002A9F08(device,11,D_00449438+0x48,0,29);D_0040DF14++;M2C_FIELD(D_00449438,s32 *,0x124)=2;return 1;
}

#endif

#ifdef NONMATCHING_2A9CB8
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

extern M2C_UNK D_00449438;
extern s32 func_002AA040(s32, s32);
extern s32 func_002AA018(s32 *);
extern s32 func_002A6C00(s32);
extern void * func_002A66C8(void *, s32);
extern s32 func_002A6340(void *, s32);
extern s32 func_002D0178();
extern s32 func_002A6B08(s32);
extern s32 func_002CFD98();
extern s32 func_002A9640();
extern s32 func_002C0038();
extern s32 func_002CF990();
extern s32 func_002A6AB8();
extern s32 func_002D0678();

s32 func_002A9CB8(s32 memory_functions, s32 flags, s32 pool_size) {
    s32 temp_2;
    s32 temp_2_2;
    s32 success;
    s32 var_2;

    success = 0;
    if (flags & 1) {
        M2C_FIELD(&D_00449438, s32 (**)(s32, s32), 0x11C) = func_002AA040;
        M2C_FIELD(&D_00449438, s32 (**)(s32 *), 0x118) = func_002AA018;
        func_002A6C00(0);
    } else {
        M2C_FIELD(&D_00449438, s32 (**)(s32, s32), 0x11C) = (s32 (*)(s32, s32)) func_002A66C8;
        M2C_FIELD(&D_00449438, s32 (**)(s32 *), 0x118) = (s32 (*)(s32 *)) func_002A6340;
        func_002A6C00(1);
    }
    M2C_FIELD(&D_00449438, s32 *, 0x128) = pool_size;
    if (M2C_FIELD(&D_00449438, s32 *, 0x124) == 0) {
        temp_2_2 = func_002D0178();
        var_2 = temp_2_2;
        if (temp_2_2 != 0) {
            success = func_002A6B08(memory_functions);
            if (success != 0) {
                success = func_002CFD98();
                if (success != 0) {
                    success = func_002A9640();
                    if (success != 0) {
                        temp_2 = func_002C0038();
                        success = temp_2;
                        if (success != 0) {
                            M2C_FIELD(&D_00449438, s32 *, 0x124) = 1 /* initialized */;
                            return temp_2;
                        }
                    }
                    func_002CF990();
                    goto block_11;
                }
block_11:
                func_002A6AB8();
                goto block_12;
            }
block_12:
            func_002D0678();
            goto block_13;
        }
        /* Duplicate return node #14. Try simplifying control flow for better match */
        return var_2;
    }
block_13:
    var_2 = success;
    return var_2;
}

#endif

#ifdef NONMATCHING_2AA570
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image_globals.h"
extern u8 D_00449438[],D_0044D460[],D_0044D488[];extern s32 D_0040E5D8,D_0040E5DC,D_003C3340,D_0040DF20,D_0040DF24,D_0040DF2C;
extern void *func_002A6010(s32,s32,s32,s32,void *,s32);extern void func_002A65F0(void *);extern s32 func_002ABE90(f32);
#define IMAGE_GLOBALS ((RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8))
void *func_002AA570(void *instance,s32 offset) {
 D_0040E5D8=offset;
 IMAGE_GLOBALS->images=func_002A6010(D_003C3340,D_0040DF20,4,D_0040DF24,D_0044D460,0x40018);if(!IMAGE_GLOBALS->images)return 0;
 IMAGE_GLOBALS->format_pool=func_002A6010(52,D_0040DF20,4,D_0040DF2C,D_0044D488,0x40406);if(!IMAGE_GLOBALS->format_pool)goto image_error;
 IMAGE_GLOBALS->path_capacity=256;IMAGE_GLOBALS->path=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(256,0x1040406);if(!IMAGE_GLOBALS->path)goto format_error;
 *IMAGE_GLOBALS->path=0;D_0040E5DC++;func_002ABE90(1.0f);IMAGE_GLOBALS->scratch_capacity=256;IMAGE_GLOBALS->formats=0;
 IMAGE_GLOBALS->scratch=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(256,0x1040018);if(IMAGE_GLOBALS->scratch)return instance;
 M2C_FIELD(D_00449438,void (**)(void *),0x10c)(IMAGE_GLOBALS->path);IMAGE_GLOBALS->path=0;IMAGE_GLOBALS->path_capacity=0;
 format_error:func_002A65F0(IMAGE_GLOBALS->format_pool);IMAGE_GLOBALS->format_pool=0;
 image_error:func_002A65F0(IMAGE_GLOBALS->images);IMAGE_GLOBALS->images=0;return 0;
}
#undef IMAGE_GLOBALS

#endif

#ifdef NONMATCHING_2AA710
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image_globals.h"
extern u8 D_00449438[];extern s32 D_0040E5D8,D_0040E5DC;
extern void func_002A65F0(void *);
void *func_002AA710(void *instance) {
 RwImageGlobalsPS2 *globals=(RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8);
 if(globals->scratch) {M2C_FIELD(D_00449438,void (**)(void *),0x10c)(globals->scratch);globals=(RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8);globals->scratch_capacity=0;globals->scratch=0;}
 if(globals->path) {M2C_FIELD(D_00449438,void (**)(void *),0x10c)(globals->path);globals=(RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8);globals->path_capacity=0;globals->path=0;}
 while(globals->formats) {RwImageFormatPS2 *format=globals->formats;globals->formats=format->next;M2C_FIELD(D_00449438,void (**)(void *,void *),0x11c)(globals->format_pool,format);globals=(RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8);}
 if(globals->format_pool) {func_002A65F0(globals->format_pool);globals=(RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8);globals->format_pool=0;}
 if(globals->images) {func_002A65F0(globals->images);globals=(RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8);globals->images=0;}
 D_0040E5DC--;return instance;
}

#endif

#ifdef NONMATCHING_2AA840
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image.h"
static __inline__ void set_max_alpha(RwColorPS2 *color) {u8 alpha=color->red;if(alpha<color->green)alpha=color->green;if(alpha<color->blue)alpha=color->blue;color->alpha=alpha;}
RwImagePS2 *func_002AA840(RwImagePS2 *image) {
 s32 x,y,n;RwColorPS2 *color;
 if(image->depth==4 || image->depth==8) {n=1<<image->depth;color=image->palette;while(n-- >0)set_max_alpha(color++);}
 else if(image->depth==32) {u8 *row=image->pixels;for(y=0;y<image->height;y++,row+=image->stride){color=(RwColorPS2 *)row;for(x=0;x<image->width;x++)set_max_alpha(color++);}}
 return image;
}

#endif

#ifdef NONMATCHING_2AAA68
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image_globals.h"
#include "rw_core/plugin.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 D_0040E5D8;extern RwRegistryPS2 D_003C3340;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern RwImagePS2 *func_002ABD68(RwImagePS2 *,const RwImagePS2 *);extern void func_002CFDF8(void *,void *),func_002CFE90(void *,void *);
#define IMAGE_GLOBALS ((RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8))
static __inline__ void free_pixels(RwImagePS2 *image) {M2C_FIELD(D_00449438,void (**)(void *),0x10c)(image->pixels);image->pixels=0;image->palette=0;image->flags&=~1;}
static __inline__ void release_image(RwImagePS2 *image) {if(image->flags&1)free_pixels(image);func_002CFE90(&D_003C3340,image);M2C_FIELD(D_00449438,void (**)(void *,void *),0x11c)(IMAGE_GLOBALS->images,image);}
RwImagePS2 *func_002AAA68(RwImagePS2 *destination,const RwImagePS2 *mask) {
 s32 x,y;
 if(destination->width!=mask->width || destination->height!=mask->height) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x8000000a);func_002A55D8(&error);return 0;}
 if(destination->depth==4 || destination->depth==8) {
  RwImagePS2 *temporary=M2C_FIELD(D_00449438,void *(**)(void *,u32),0x118)(IMAGE_GLOBALS->images,0x30018);
  s32 palette_bytes,bytes;
  if(!temporary)return 0;
  temporary->width=destination->width;temporary->height=destination->height;temporary->depth=destination->depth;temporary->pixels=0;temporary->palette=0;temporary->flags=0;func_002CFDF8(&D_003C3340,temporary);
  palette_bytes=(4<<temporary->depth);temporary->stride=(((temporary->depth+7)>>3)*temporary->width+3)&~3;bytes=temporary->stride*temporary->height;
  temporary->pixels=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(bytes+palette_bytes,0x30018);
  if(!temporary->pixels) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,bytes+palette_bytes);func_002A55D8(&error);release_image(temporary);return 0;}
  temporary->palette=(RwColorPS2 *)(temporary->pixels+bytes);temporary->flags|=1;func_002ABD68(temporary,destination);
  if(destination->flags&1)free_pixels(destination);destination->depth=32;destination->stride=destination->width*4;bytes=destination->stride*destination->height;
  destination->pixels=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(bytes,0x30018);
  if(!destination->pixels) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,bytes);func_002A55D8(&error);}else {destination->palette=0;destination->flags|=1;}
  func_002ABD68(destination,temporary);free_pixels(temporary);release_image(temporary);
 } else if(destination->depth!=32) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000009);func_002A55D8(&error);return 0;}
 for(y=0;y<destination->height;y++) {
  RwColorPS2 *output=(RwColorPS2 *)(destination->pixels+y*destination->stride);const u8 *row=mask->pixels+y*mask->stride;
  if(mask->depth==4 || mask->depth==8)for(x=0;x<destination->width;x++)output[x].alpha=mask->palette[row[x]].alpha;
  else if(mask->depth==32)for(x=0;x<destination->width;x++)output[x].alpha=((const RwColorPS2 *)row)[x].alpha;
 }
 return destination;
}
#undef IMAGE_GLOBALS

#endif

#ifdef NONMATCHING_2AAF48
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image_globals.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 D_0040E5D8;extern s32 func_002A5548(s32,...),func_002D08C8(const char *);extern void func_002A55D8(RwErrorPS2 *);extern void *func_0035C544(void *,const void *,u32);
#define IMAGE_GLOBALS ((RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8))
static __inline__ char *reserve_scratch(s32 length) {
 if(IMAGE_GLOBALS->scratch_capacity<length) {
  char *buffer;
  if(IMAGE_GLOBALS->scratch)buffer=M2C_FIELD(D_00449438,void *(**)(void *,u32,u32),0x110)(IMAGE_GLOBALS->scratch,length,0x1040018);
  else buffer=M2C_FIELD(D_00449438,void *(**)(u32,u32),0x108)(length,0x1040018);
  if(!buffer) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000013,length);func_002A55D8(&error);return 0;}
  IMAGE_GLOBALS->scratch_capacity=length;IMAGE_GLOBALS->scratch=buffer;
 }
 return IMAGE_GLOBALS->scratch;
}
const char *func_002AAF48(const char *name,s32 extra,s32 (*callback)(char *,void *),void *context) {
 const char *path=IMAGE_GLOBALS->path;
 if(!func_002D08C8(name) && path && *path) {
  do {
   const char *next;char *buffer;s32 prefix,length;
   M2C_FIELD(D_00449438,char *(**)(const char *,s32),0xe0)(path,';');
   next=M2C_FIELD(D_00449438,char *(**)(const char *,s32),0xe0)(path,';');
   if(next){prefix=next-path;next++;}else prefix=M2C_FIELD(D_00449438,s32 (**)(const char *),0xf4)(path);
   length=prefix+M2C_FIELD(D_00449438,s32 (**)(const char *),0xf4)(name)+extra;
   buffer=reserve_scratch(length);if(!buffer)return 0;
   func_0035C544(buffer,path,prefix);M2C_FIELD(D_00449438,char *(**)(char *,const char *),0xcc)(buffer+prefix,name);
   if(!callback(buffer,context) || !next || !*next)return name;path=next;
  }while(1);
 }
 {s32 length=M2C_FIELD(D_00449438,s32 (**)(const char *),0xf4)(name)+extra;char *buffer=reserve_scratch(length);if(!buffer)return 0;
 M2C_FIELD(D_00449438,char *(**)(char *,const char *),0xcc)(buffer,name);callback(buffer,context);return name;}
}
#undef IMAGE_GLOBALS

#endif

#ifdef NONMATCHING_2AB378
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image_globals.h"
#include "rw_core/plugin.h"
extern u8 D_00449438[];extern s32 D_0040E5D8;extern RwRegistryPS2 D_003C3340;
extern RwImagePS2 *func_002AB250(const char *),*func_002ABD18(RwImagePS2 *),*func_002AA840(RwImagePS2 *),*func_002AAA68(RwImagePS2 *,RwImagePS2 *);
extern RwRegistryPS2 *func_002CFE90(RwRegistryPS2 *,s32);
static __inline__ void destroy_image(RwImagePS2 *image) {
 if(image->flags&1)func_002ABD18(image);func_002CFE90(&D_003C3340,(s32)image);
 M2C_FIELD(D_00449438,void (**)(void *,void *),0x11c)(((RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8))->images,image);
}
RwImagePS2 *func_002AB378(const char *name,const char *mask_name) {
 RwImagePS2 *image=func_002AB250(name),*mask;
 if(!image || !mask_name || !*mask_name)return image;
 mask=func_002AB250(mask_name);if(!mask){destroy_image(image);return 0;}
 if(func_002AA840(mask) && func_002AAA68(image,mask)) {destroy_image(mask);return image;}
 destroy_image(image);destroy_image(mask);return 0;
}

#endif

#ifdef NONMATCHING_2AB538
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern void *func_0035C544(void *,const void *,u32);
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

#endif

#ifdef NONMATCHING_2AB8E0
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image_globals.h"
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 D_0040E5D8;extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);
RwImagePS2 *func_002AB8E0(RwImagePS2 *image) {
 s32 y,n;RwColorPS2 *color;u8 *gamma=((RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8))->gamma;
 if(image->depth==4 || image->depth==8) {color=image->palette;n=1<<image->depth;
  if(!color)goto missing;while(n--) {u8 alpha=color->alpha;color->red=gamma[color->red];color->green=gamma[color->green];color->blue=gamma[color->blue];color->alpha=alpha;color++;}}
 else if(image->depth==32) {u8 *row=image->pixels;if(!row)goto missing;
  for(y=0;y<image->height;y++,row+=image->stride) {color=(RwColorPS2 *)row;for(n=image->width;n;n--) {u8 alpha=color->alpha;color->red=gamma[color->red];color->green=gamma[color->green];color->blue=gamma[color->blue];color->alpha=alpha;color++;}}}
 else {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000008);func_002A55D8(&error);return 0;}
 image->flags|=2;return image;
 missing: {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000016);func_002A55D8(&error);return 0;}
}

#endif

#ifdef NONMATCHING_2ABE90
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image_globals.h"
extern u8 D_00449438[];extern s32 D_0040E5D8;extern f32 func_0029E688(f32,f32);
s32 func_002ABE90(f32 gamma_value) {
 f32 reciprocal=1.0f/gamma_value; s32 i;
 RwImageGlobalsPS2 *globals=(RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8);
 globals->inverse_gamma[0]=0;globals->gamma_value=gamma_value;globals->gamma[0]=0;
 for(i=1;i<256;i++) {f32 value=(f32)i*0.003921569f;
  ((RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8))->gamma[i]=(u8)(s32)(func_0029E688(value,reciprocal)*255.0f+0.5f);
  ((RwImageGlobalsPS2 *)(D_00449438+D_0040E5D8))->inverse_gamma[i]=(u8)(s32)(func_0029E688(value,gamma_value)*255.0f+0.5f);
 }
 return 1;
}

#endif

#ifdef NONMATCHING_2AC908
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image.h"
typedef struct RwFloatColorPS2 {f32 red,green,blue,alpha;} RwFloatColorPS2;
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

#endif

#ifdef NONMATCHING_2ACBE8
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image.h"
typedef struct RwFloatColorPS2 {f32 red,green,blue,alpha;} RwFloatColorPS2;
extern void func_002AC908(const RwImagePS2 *,s32,s32,s32,RwFloatColorPS2 *);
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

#endif

#ifdef NONMATCHING_2ACE68
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/image.h"
typedef struct RwFloatColorPS2 {f32 red,green,blue,alpha;} RwFloatColorPS2;
extern void func_002ACBE8(const RwImagePS2 *,s32,s32,s32,s32,RwFloatColorPS2 *);
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

#endif

#ifdef NONMATCHING_2AD2C8
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
#include "rw_core/frame.h"
extern void func_002A5AC8(RwMatrixPS2 *,RwMatrixPS2 *,RwMatrixPS2 *),func_002AD510(RwFramePS2 *,u32),func_002AD5D8(RwFramePS2 *);
static __inline__ void sync_objects(RwFramePS2 *frame) {
 RwObjectLinkPS2 *link=frame->objects.next;
 while(link!=&frame->objects) {void *object=(u8 *)link-8;M2C_FIELD(object,void (**)(void *),0x10)(object);link=link->next;}
}
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

#endif
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A8F78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9B70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9CB8);
#endif

void func_002A90C8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(), 0x18)();
}

void func_002A90E8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(), 0x1C)();
}

s32 func_002A9108(s32 arg0) {
    return (D_004494D4() == 0) ? 0 : arg0;
}

void * func_002A9140(void *arg0) {
    return (func_002AC6E8(M2C_FIELD(arg0, s32 *, 0x60)) == 0) ? NULL : arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9170);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A91D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9310);

#include "ps2/recovered_types.h"
extern s32 func_002CFAC0(void *, u32, u32, u32, u32, s32);
extern s32 D_003C31F8;

s32 func_002A93E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_002CFAC0(&D_003C31F8, (u32) arg0, (u32) arg1, (u32) arg2, (u32) arg3, arg4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9428);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9498);

void * func_002A9518(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x14) == 1) {
        func_002A8688();
        func_002A7DD0(arg0);
    } else {
        func_002A8DA0(arg0);
        func_002A8860(arg0);
    }
    func_002D0910(arg0 + 0x10C, arg0 + 0x124, 8);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9588);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A95E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9830);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A98A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A99D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9AE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9CB0);

s32 func_002A9DF0(s32 size, s32 plugin_id, s32 construct, s32 destroy) {
    return func_002CFAC0(&D_003C3210, size, plugin_id, construct, destroy, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9E30);
