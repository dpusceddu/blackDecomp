/* Medium-confidence format and sound TU, grouped by calls and shared data. */
#ifdef NONMATCHING_RWA_314848
// Unmatched: format read/write cursor aliasing and scheduling differ.
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
extern char D_004092E0[],D_004092D0[],D_004092F0[],D_00409360[],D_00409300[],D_00409310[],D_00409370[],D_00409330[],D_00409340[],D_00409350[];
typedef struct {u32 value;} __attribute__((packed)) RwaPackedWord;
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

#endif

#ifdef NONMATCHING_RWA_314F08
// Unmatched: exact external-float body needs owned GP-relative literal placement.
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
extern char D_004092E0[],D_004092D0[],D_004092F0[],D_00409360[],D_00409300[],D_00409310[],D_00409370[],D_00409330[],D_00409340[],D_00409350[];
typedef struct {u32 value;} __attribute__((packed)) RwaPackedWord;
extern f32 D_0040D894;
s32 func_00314F08(RwaFormat *format,u32 count) {
    u32 block=func_00314B98(format),unit=func_00314630(format),result;
    if((!func_00316400(format->encoding,D_00409310)||!func_00316400(format->encoding,D_00409370))&&format->channels==2) {f32 numerator=(f32)count,denominator=(f32)unit;result=(s32)(D_0040D894*(numerator/denominator));}
    else result=block*(count/unit);
    if(!(format->flags&4))result/=format->channels;
    return result;
}

#endif

#ifdef NONMATCHING_RWA_315790
// Unmatched: allocation failure control flow and saved registers differ.
#include "rw_audio/sound.h"
extern s32 func_00315440(RwaSoundDriver *,RwaFormat *);
extern s32 func_00315048(RwaFormat *,RwaFormat *,s32);
extern s32 func_00314D60(RwaFormat *,RwaFormat *);
extern u32 func_00321F10(RwaFormat *,void *,RwaFormat *);
extern u32 func_00321EE0(RwaFormat *,void *,u32,RwaFormat *);
extern s32 func_0031EC28(RwaFormat *,void *,s32,RwaFormat *,void *);
extern void *func_00312C48(u32,u32);
extern void *func_00312CC8(u32,u32);
extern void *func_0035C544(void *,const void *,u32);
extern void func_00312D08(void *);
extern void func_00316190(RwaSound *);
extern RwaSound *D_0040E18C;
extern u32 D_0040E190;
extern void *func_00317E40(u32,u32,u32,u32,void *,u32);
extern void *func_00317A78(void *,u32);
extern void func_00316758(void *);
extern void func_00316240(RwaSound *);
extern void func_003144C8(void *,RwaSound *);
extern void *func_00314538(void);
extern u8 D_004563A8[];
RwaSound *func_00315790(RwaSoundDriver *driver,void *user,RwaFormat *format,RwaFormat *output,s32 enabled,RwaSound *sound) {
    void *pool;RwaSound *created;
    if(sound){sound->flags=4;goto initialized;}
    if(driver->work_size){
        if(driver->pool||(driver->pool=func_00317E40(0x5c,8,1,1,0,0x30806))!=0){pool=driver->pool;goto allocate;}
        goto failure;
    }
    pool=D_004563A8;
allocate:
    created=func_00317A78(pool,0x30806);
    if(!created)goto failure;
    sound=created;created->flags=1;
initialized:
    func_00316758(sound);sound->field4c=0;sound->driver=driver;sound->field48=0;sound->user=user;
    sound->source_format.rate=0;sound->source_format.encoding=0;sound->source_format.extent=0;sound->source_format.bits=0;sound->source_format.channels=0;sound->source_format.flags=0;sound->source_format.field19=0;sound->source_format.extension=0;sound->source_format.extension_size=0;
    sound->source_format=*format;
    if(format->extension&&format->extension_size){sound->source_format.extension=func_00312C48(format->extension_size,0x30806);if(!sound->source_format.extension)return 0;func_0035C544(sound->source_format.extension,format->extension,format->extension_size);}
    func_003159C8(sound,format,output);
    if(sound->output_format.channels==1){u32 flags=sound->flags;sound->flags=enabled?flags|2:flags;}
    if(sound->driver->work_size){sound->work=func_00312C48(driver->work_size,0x30806);sound->flags|=8;}else sound->work=0;
    if(sound->driver->initialize&&!sound->driver->initialize(sound,user)){func_00316240(sound);return 0;}
    func_003144C8(func_00314538(),sound);return sound;
failure:return 0;
}

#endif

#ifdef NONMATCHING_RWA_3159C8
// Unmatched: format selection register allocation and control flow differ.
#include "rw_audio/sound.h"
extern s32 func_00315440(RwaSoundDriver *,RwaFormat *);
extern s32 func_00315048(RwaFormat *,RwaFormat *,s32);
extern s32 func_00314D60(RwaFormat *,RwaFormat *);
extern u32 func_00321F10(RwaFormat *,void *,RwaFormat *);
extern u32 func_00321EE0(RwaFormat *,void *,u32,RwaFormat *);
extern s32 func_0031EC28(RwaFormat *,void *,s32,RwaFormat *,void *);
extern void *func_00312C48(u32,u32);
extern void *func_00312CC8(u32,u32);
extern void *func_0035C544(void *,const void *,u32);
extern void func_00312D08(void *);
extern void func_00316190(RwaSound *);
extern RwaSound *D_0040E18C;
extern u32 D_0040E190;
extern void *func_00317E40(u32,u32,u32,u32,void *,u32);
extern void *func_00317A78(void *,u32);
extern void func_00316758(void *);
extern void func_00316240(RwaSound *);
extern void func_003144C8(void *,RwaSound *);
extern void *func_00314538(void);
extern u8 D_004563A8[];
u32 func_003159C8(RwaSound *sound,RwaFormat *source,RwaFormat *output) {
    RwaFormat local,*selected=output;RwaSoundDriver *driver=sound->driver;
    u32 result;
    if(selected&&selected->encoding&&driver->format_count){result=func_00315440(driver,selected);if(!result)return result;}
    else {
        RwaFormat *fallback=driver->formats?driver->formats[driver->format_index]:0;
        if(!fallback){if(!selected)selected=source;}
        else {func_00315048(fallback,&local,1);selected=&local;local.rate=source->rate;local.extension=source->extension;local.extension_size=source->extension_size;}
    }
    if(func_00314D60(source,selected)){selected->extension=source->extension;selected->extension_size=source->extension_size;}
    result=func_00321F10(source,0,selected);selected->extent=result;
    sound->output_format.rate=0;sound->output_format.encoding=0;sound->output_format.extent=0;sound->output_format.bits=0;sound->output_format.channels=0;sound->output_format.flags=0;sound->output_format.field19=0;sound->output_format.extension=0;sound->output_format.extension_size=0;
    if(selected){sound->output_format=*selected;if(selected->extension&&(result=selected->extension_size)!=0){result=(u32)func_00312C48(result,0x30806);sound->output_format.extension=(void *)result;if(result)result=(u32)func_0035C544((void *)result,selected->extension,selected->extension_size);}}
    return result;
}

#endif

#ifdef NONMATCHING_RWA_315FF0
// Unmatched: temporary format lifetime and conversion call scheduling differ.
#include "rw_audio/sound.h"
extern s32 func_00315440(RwaSoundDriver *,RwaFormat *);
extern s32 func_00315048(RwaFormat *,RwaFormat *,s32);
extern s32 func_00314D60(RwaFormat *,RwaFormat *);
extern u32 func_00321F10(RwaFormat *,void *,RwaFormat *);
extern u32 func_00321EE0(RwaFormat *,void *,u32,RwaFormat *);
extern s32 func_0031EC28(RwaFormat *,void *,s32,RwaFormat *,void *);
extern void *func_00312C48(u32,u32);
extern void *func_00312CC8(u32,u32);
extern void *func_0035C544(void *,const void *,u32);
extern void func_00312D08(void *);
extern void func_00316190(RwaSound *);
extern RwaSound *D_0040E18C;
extern u32 D_0040E190;
extern void *func_00317E40(u32,u32,u32,u32,void *,u32);
extern void *func_00317A78(void *,u32);
extern void func_00316758(void *);
extern void func_00316240(RwaSound *);
extern void func_003144C8(void *,RwaSound *);
extern void *func_00314538(void);
extern u8 D_004563A8[];
RwaSound *func_00315FF0(RwaSound *sound,u32 count,void *data,u32 requested) {
    RwaFormat local,*output=&sound->output_format;
    void *allocated=0;u32 amount=count,size;
    RwaSound *(*process)(RwaSound *,u32,void *,u32)=sound->driver->process;
    RwaSound *result;
    if(!process)return 0;
    if(!func_00314D60(&sound->source_format,output)){
        local=sound->source_format;amount=func_00321EE0(&local,data,count,output);local.extent=requested;size=func_00321F10(&local,data,output);allocated=func_00312CC8(size,0x30806);
        if(!allocated)return 0;
        if(!func_0031EC28(&local,data,0,output,allocated)){func_00312D08(allocated);return 0;}data=allocated;
    }else size=requested;
    D_0040E18C=sound;D_0040E190=amount;result=process(sound,amount,data,size);result->flags|=0x10;
    if(allocated){func_00316190(result);func_00312D08(allocated);}
    return result;
}

#endif
