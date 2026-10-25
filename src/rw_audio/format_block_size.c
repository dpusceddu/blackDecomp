#include "include_asm.h"

#include "rw_audio/sound.h"
extern void func_003164D0(void *);
extern void func_00314DE0(RwaFormat *);
extern void func_00318600(u8 **,const void *,u32);
extern void *func_0035C6EC(void *,s32,u32);
extern void *func_0035C544(void *,const void *,u32);
extern void func_00316770(void *,void *,s32);
extern void *func_00315208(void *);
extern s32 func_00316400(const void *,const void *);
extern u32 func_00314630(RwaFormat *);
extern char D_004092E0[],D_004092D0[],D_004092F0[],D_00409360[],D_00409300[],D_00409310[],D_00409370[],D_00409330[];
typedef struct {u32 value;} __attribute__((packed)) RwaPackedWord;
const RwaFormatId codecGuid409340 __asm__("D_00409340") __attribute__((aligned(8))) = {{0x34d09a54,0x409e57d3,0xc82bada6,0x39c3ae45}};
const RwaFormatId codecGuid409350 __asm__("D_00409350") __attribute__((aligned(8))) = {{0x04c15ba7,0x40abf907,0xfeee9fa4,0x96d2c4f8}};

/* Medium-confidence format and sound TU, grouped by calls and shared data. */




INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/format_block_size", func_00314630);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/format_block_size", func_00314760);
#ifdef NON_MATCHING
// Unmatched: format read/write cursor aliasing and scheduling differ.
RwaFormat *func_00314848(RwaFormat *format,u8 *bytes,s32 writing,s32 swap) {
    u8 *cursor,*out;
    u32 has_codec;
    if(writing){
        cursor=bytes;
        if(swap){
            has_codec=format->encoding!=0;
            func_00318600(&cursor,&format->rate,4);func_00318600(&cursor,&has_codec,4);func_00318600(&cursor,&format->extent,4);func_00318600(&cursor,&format->bits,1);func_00318600(&cursor,&format->channels,1);func_0035C6EC(cursor,0,2);cursor+=2;
            func_00318600(&cursor,&format->extension,4);func_00318600(&cursor,&format->extension_size,4);func_00318600(&cursor,&format->flags,1);func_00318600(&cursor,&format->field19,1);func_0035C6EC(cursor,0,2);cursor+=2;
        }else{*(RwaFormat *)bytes=*format;cursor+=28;}
        if(format->encoding){func_00316770((void *)format->encoding,cursor,swap);cursor+=16;}
        if(format->extension){func_0035C544(cursor,format->extension,format->extension_size);format->flags|=2;cursor+=format->extension_size;}
        return format;
    }
    if(swap){
        out=(u8 *)format;
        func_00318600(&out,bytes,4);bytes+=4;func_00318600(&out,bytes,4);bytes+=4;func_00318600(&out,bytes,4);bytes+=4;func_00318600(&out,bytes,1);++bytes;func_00318600(&out,bytes,1);++bytes;bytes+=2;func_0035C6EC(out,0,2);out+=2;
        func_00318600(&out,bytes,4);bytes+=4;func_00318600(&out,bytes,4);bytes+=4;func_00318600(&out,bytes,1);++bytes;func_00318600(&out,bytes,1);++bytes;bytes+=2;func_0035C6EC(out,0,2);out+=2;
        cursor=bytes;
    }else{*format=*(RwaFormat *)bytes;cursor=bytes+28;}
    if(format->encoding){func_00316770(cursor,cursor,swap);format->encoding=func_00315208(cursor);if(!format->encoding)return 0;cursor+=16;}
    if(format->extension)format->extension=cursor;
    return format;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/format_block_size", func_00314848);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/format_block_size", func_00314D60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/format_block_size", func_00314DE0);
#ifdef NON_MATCHING
extern f32 D_0040D894;
// Unmatched: exact external-float body needs owned GP-relative literal placement.
s32 func_00314F08(RwaFormat *format,u32 count) {
    u32 block=func_00314B98(format),unit=func_00314630(format),result;
    if((!func_00316400(format->encoding,D_00409310)||!func_00316400(format->encoding,D_00409370))&&format->channels==2) {f32 numerator=(f32)count,denominator=(f32)unit;result=(s32)(D_0040D894*(numerator/denominator));}
    else result=block*(count/unit);
    if(!(format->flags&4))result/=format->channels;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/format_block_size", func_00314F08);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/format_block_size", func_00315048);

u32 func_00314B98(RwaFormat *format) {
    if(!func_00316400(format->encoding,D_004092E0))return 1;
    if(!func_00316400(format->encoding,D_004092D0))return 0x1c;
    if(!func_00316400(format->encoding,D_004092F0))return 1;
    if(!func_00316400(format->encoding,D_00409360))return 0x600;
    if(!func_00316400(format->encoding,D_00409300))return 0xe;
    if(!func_00316400(format->encoding,D_00409310)||!func_00316400(format->encoding,D_00409370)){
        RwaFormat mono;u32 samples,unit;
        if(format->channels==1)return 0x40;
        mono=*format;mono.channels=1;samples=func_00314B98(&mono);unit=func_00314630(&mono);
        return samples/(unit/func_00314630(format));
    }
    if(!func_00316400(format->encoding,D_00409330))return 0x480;
    if(!func_00316400(format->encoding,&codecGuid409340))return 0x480;
    return !func_00316400(format->encoding,&codecGuid409350)?0:0x180;
}
