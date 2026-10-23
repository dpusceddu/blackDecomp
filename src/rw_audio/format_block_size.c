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
