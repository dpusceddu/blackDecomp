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
extern char D_004092E0[],D_004092D0[],D_004092F0[],D_00409360[],D_00409300[],D_00409310[],D_00409370[],D_00409330[],D_00409340[],D_00409350[];
typedef struct {u32 value;} __attribute__((packed)) RwaPackedWord;

void func_00315B60(RwaSound *sound) {
    RwaSound copy;u8 *cursor=(u8 *)&copy;
    func_003164D0(sound);
    *(RwaObjectHeader *)cursor=sound->object;cursor+=12;
    *(RwaPackedWord *)cursor=*(RwaPackedWord *)&sound->driver;cursor+=4;
    func_00314DE0(&sound->source_format);
    *(RwaPackedFormat *)cursor=*(RwaPackedFormat *)&sound->source_format;cursor+=28;
    func_00314DE0(&sound->output_format);
    *(RwaPackedFormat *)cursor=*(RwaPackedFormat *)&sound->output_format;cursor+=28;
    func_00318600(&cursor,&sound->field48,4);func_00318600(&cursor,&sound->field4c,4);func_00318600(&cursor,&sound->work,4);func_00318600(&cursor,&sound->flags,4);
    *(RwaPackedWord *)cursor=*(RwaPackedWord *)&sound->user;cursor+=4;
    *sound=copy;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315EE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315F18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315F28);
#ifdef NON_MATCHING
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
// Unmatched: temporary format lifetime and conversion call scheduling differ.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315FF0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316180);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003161C8);
