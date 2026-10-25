#include "include_asm.h"
#include "ps2/prelude.h"


#include "ps2/prelude.h"















#ifdef NON_MATCHING
typedef struct AudioDescriptor { u8 prefix[0x14]; u16 rows, columns; } AudioDescriptor;
typedef struct AudioBuildRequest {
    s32 mode, reserved4, reserved8;
    void *(*allocate)(u32, void *);
    void *state;
    void *user;
} AudioBuildRequest;
typedef struct AudioChannelOptions { s32 count; s32 **items; } AudioChannelOptions;
extern u8 D_00409610[16], D_00409400[16];
extern AudioDescriptor *func_00311DB8(void *);
extern void *func_00312C48(s32,s32);
extern void *func_003176D0(u32,void *);
extern s32 *func_00310338(void *,AudioDescriptor *,AudioBuildRequest *);
extern void func_00312C70(void *);
extern void func_00310478(s32 *,s32);
extern s32 *D_0040E1B0;
extern s32 **D_0040E790;
extern s32 D_0040E1B8,D_0040E1AC;
extern s32 func_00310698(void *,s32,s32,void *);
extern void *D_0040E1B4;
extern void *func_00310870(void *,s32,s32,void *);
static inline s32 AudioObjectBytes(AudioDescriptor *d,s32 prefix) { return d->rows*8+(d->columns*8+prefix); }
static inline void AudioBuildRequestInit(AudioBuildRequest *p,u8 **c,u8 *memory) {
    p->reserved8=0; p->mode=2; p->reserved4=0;
    p->allocate=func_003176D0;
    p->state=c;
    p->user=memory;
    *c=memory+24;
}
// Unmatched: 28 instructions in allocation failure layout and request store scheduling.
s32 func_00316C38(void *input,void **inputs,s32 length) {
    AudioChannelOptions options;
    AudioBuildRequest request __attribute__((aligned(16)));
    u8 *cursor;
    AudioDescriptor *first,*second;
    u8 *memory;
    u32 index;
    first=func_00311DB8(D_00409610);
    second=func_00311DB8(D_00409400);
    memory=func_00312C48((length+1)*24 + AudioObjectBytes(first,28)+AudioObjectBytes(second,40) + length*4,0x3080E);
    if (memory==NULL) return 0;
    AudioBuildRequestInit(&request,&cursor,memory);
    D_0040E1B0=func_00310338(input,first,&request);
    if (D_0040E1B0==NULL) {func_00312C70(memory);return 0;}
    memory=cursor;
    D_0040E790=(s32 **)memory;
    memory+=length*4;
    index=0;
    if (length!=0) {
        do {
            cursor=memory+24;
            request.user=memory;
            D_0040E790[index]=func_00310338(inputs[index],second,&request);
            if (D_0040E790[index]==NULL) {
                while (index-- != 0) func_00310478(D_0040E790[index],0);
                func_00310478(D_0040E1B0,0);
                D_0040E1B8=0;
                D_0040E1B0=NULL;
                return 0;
            }
            ++index;
            memory=cursor;
        } while(index<(u32)length);
    }
    options.count=length;
    options.items=D_0040E790;
    D_0040E1AC=1;
    D_0040E1B8=length;
    func_00310698(D_0040E1B0,5,1,&options);
    D_0040E1B4=func_00310870(D_0040E1B0,1,2,NULL);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316C38);
#endif
#ifdef NON_MATCHING
extern u32 func_0031D510(void),func_0031D520(void);
extern u32 D_0040E1C8,D_0040E1C4;
// Unmatched: 14 instructions in integer allocation around unsigned-to-float conversions.
void func_003174F0(void) {
    u32 now=func_0031D510();
    u32 frequency=func_0031D520();
    u32 elapsed;
    if(now<D_0040E1C8) {elapsed=now-1;elapsed-=D_0040E1C8;}
    else elapsed=now-D_0040E1C8;
    D_0040E1C4=(s32)(((f32)elapsed/(f32)frequency)*1000.0f)+D_0040E1C4;
    D_0040E1C8=now;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003174F0);
#endif


#include "ps2/recovered_types.h"
extern void * D_0040E780;

s32 func_00317300(void *arg0) {
    void *temp_5;

    temp_5 = arg0 + 0x28;
    M2C_FIELD(temp_5, void ***, 4) = NULL;
    M2C_FIELD(arg0, void **, 0x28) = NULL;
    M2C_FIELD(arg0, void **, 0x28) = (void *) D_0040E780;
    M2C_FIELD(temp_5, void ***, 4) = &D_0040E780;
    M2C_FIELD(D_0040E780, void **, 4) = temp_5;
    D_0040E780 = temp_5;
    M2C_FIELD(temp_5, u8 *, 0x62) = (u8) (M2C_FIELD(temp_5, u8 *, 0x62) & 0xFE);
    return 1;
}


#include "ps2/recovered_types.h"
extern s32 func_00319CA8();
extern s32 D_0040E1A8;

s32 func_003174D0(void) {
    s32 temp_v0;

    temp_v0 = func_00319CA8();
    D_0040E1A8 = 0;
    return temp_v0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003175C0);
