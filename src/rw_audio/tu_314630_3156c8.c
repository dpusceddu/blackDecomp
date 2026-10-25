#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
#ifdef NON_MATCHING
#include "rw_audio/sound.h"
#endif
extern s32 func_003152C8(s32 *);

s32 func_003156C8(s32 arg0, void *arg1) {
    M2C_UNK *var_16;
    s32 *var_4;
    void *temp_17;

    temp_17 = (void *) (((s8 *) arg1) + 0x20);
    var_16 = M2C_FIELD(arg1, M2C_UNK **, 0x20);
    if (var_16 != temp_17) {
        var_4 = (s32 *) (((s8 *) var_16) + -0x50);
        do {
            var_16 = *var_16;
            func_003152C8(var_4);
            var_4 = (s32 *) (((s8 *) var_16) + -0x50);
        } while (var_16 != temp_17);
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_314630_3156c8", func_00315718);
#ifdef NON_MATCHING
extern void *func_0035C544(void *,const void *,u32);
extern s32 func_00315440(RwaSoundDriver *,RwaFormat *);
extern s32 func_00315048(RwaFormat *,RwaFormat *,s32);
extern s32 func_00314D60(RwaFormat *,RwaFormat *);
extern u32 func_00321F10(RwaFormat *,void *,RwaFormat *);
extern u32 func_00321EE0(RwaFormat *,void *,u32,RwaFormat *);
extern s32 func_0031EC28(RwaFormat *,void *,s32,RwaFormat *,void *);
extern void *func_00312C48(u32,u32);
extern void *func_00312CC8(u32,u32);
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
// Unmatched: allocation failure control flow and saved registers differ.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_314630_3156c8", func_00315790);
#endif
#ifdef NON_MATCHING
// Unmatched: format selection register allocation and control flow differ.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_314630_3156c8", func_003159C8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_314630_3156c8", func_00315B58);
