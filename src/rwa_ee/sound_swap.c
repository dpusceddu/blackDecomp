#include "rwa_ee/sound.h"
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
