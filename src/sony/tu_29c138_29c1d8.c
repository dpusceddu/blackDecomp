#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern void * D_003C1588;
extern s32 func_0029C1B0();
extern void func_0029C138();

void func_0029C1D8(s8 *arg0, s32 arg1) {
    s32 var_2;
    s8 *var_4;

    var_4 = arg0;
    var_2 = arg1 - 1;
    if (arg1 != 0) {
        do {
            *var_4 = 0;
            var_2 -= 1;
            var_4 += 1;
        } while (var_2 != -1);
    }
}

void * func_0029C210(u32 arg0) {
    if (arg0 < 0xAU) {
        return (&D_003C1588)[arg0];
    }
    return NULL;
}

#ifdef NON_MATCHING
// Unmatched: MMIO store scheduling and result-register allocation differ.
// Partial DMA channel register view; names are UNVERIFIED.
typedef struct DmaRegsDraft {
    volatile unsigned field00;
    char unknown04[0xc];
    volatile unsigned field10;
    char unknown14[0x1c];
    volatile unsigned field30;
    char unknown34[0xc];
    volatile unsigned field40;
    char unknown44[0xc];
    volatile unsigned field50;
    char unknown54[0x2c];
    volatile unsigned field80;
} DmaRegsDraft;
static const int dmaCapabilitiesDraft[10] = {1, 1, 1, 1, 1, 0, 0, 0, 1, 1};
extern int func_0029C318();
int func_0029C238(int enable) {
    unsigned status = *(volatile unsigned*)0x1000e000 & 1;
    DmaRegsDraft** channels = (DmaRegsDraft**)&D_003C1588;
    char packet[20];
    int i;
    for (i = 0; i < 10; i++) {
        if (dmaCapabilitiesDraft[i]) {
            DmaRegsDraft* channel = channels[i];
            channel->field80 = 0;
            channel->field00 = 0;
            channel->field30 = 0;
            channel->field10 = 0;
            channel->field50 = 0;
            channel->field40 = 0;
        }
    }
    *(volatile unsigned*)0x1000e010 = 0xff1f;
    *(volatile unsigned*)0x1000e010 &= 0xff1f0000;
    func_0029C1D8(packet, 20);
    func_0029C318(packet);
    if (enable == 1) *(volatile unsigned*)0x1000e000 |= 1;
    return status;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C238);
#endif
#ifdef NON_MATCHING
// Unmatched: MMIO capture and write scheduling differ; table placement is unverified.
// Partial DMA configuration layout; field meanings are UNVERIFIED.
typedef struct DmaConfigDraft { unsigned char mode[4]; unsigned short value[4]; unsigned first, second; } DmaConfigDraft;
extern DmaConfigDraft D_00445D88;
static const unsigned char dmaMap0Draft[10]={0,0,0,3,0,1,0,0,2,0};
static const unsigned char dmaMap1Draft[10]={0,1,2,0,0,0,3,0,0,0};
static const unsigned char dmaMap2Draft[10]={0,2,3,0,0,0,0,0,0,0};
int func_0029C318(DmaConfigDraft* p) {
    unsigned control=*(volatile unsigned*)0x1000e000;
    unsigned a=*(volatile unsigned*)0x1000e020;
    unsigned b=*(volatile unsigned*)0x1000e030;
    unsigned c=*(volatile unsigned*)0x1000e050;
    unsigned d=*(volatile unsigned*)0x1000e040;
    if(p->mode[0]>=10) return -1;
    if(p->mode[1]>=10) return -2;
    if(p->mode[2]>=10) return -3;
    if(p->mode[3]>=7) return -4;
    control=(control & ~0x30u) | (dmaMap0Draft[p->mode[0]]<<4);
    control=(control & ~0xc0u) | (dmaMap1Draft[p->mode[1]]<<6);
    control=(control & ~0x0cu) | (dmaMap2Draft[p->mode[2]]<<2);
    if(p->mode[3]) control=((control | 2) & ~0x300u) | ((p->mode[3]-1)<<8);
    else control &= ~2u;
    a=(p->value[0]<<16)|p->value[1];
    b=(p->value[3]<<16)|p->value[2];
    c=p->first; d=p->second;
    *(volatile unsigned*)0x1000e000=control;
    *(volatile unsigned*)0x1000e020=a;
    *(volatile unsigned*)0x1000e030=b;
    *(volatile unsigned*)0x1000e050=c;
    *(volatile unsigned*)0x1000e040=d;
    D_00445D88=*p;
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C318);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C4F0);

void func_0029C4F8(s32 *arg0, s32 arg1)
{
  s32 temp_17;
  temp_17 = func_0029C1B0(arg1);
  func_0029C138(arg0);
  if (arg0 && arg0)
  {
 arg0++; arg0--; } if ((M2C_FIELD(arg0, s32 *, 0x30)) != 0xFFFFFFFF) {
    M2C_FIELD(arg0, s32 *, 0x30) = temp_17;
  }
  M2C_FIELD(arg0, s32 *, 0x20) = 0;
  M2C_FIELD(arg0, s32 *, 0) = ((M2C_FIELD(arg0, s32 *, 0)) & (~0xC)) | 0x105;
}

// Partial view; field meanings and the surrounding layout are UNVERIFIED.
typedef struct SonyConfigView {
    int flags;
    char unknown04[12];
    unsigned field10;
    char unknown14[12];
    int field20;
} SonyConfigView;

void func_0029C560(SonyConfigView* self, int value, int mode) {
    int result = func_0029C1B0(value);
    func_0029C138(self);
    if (self->field10 != 0xffffffffu) self->field10 = result;
    self->field20 = mode;
    self->flags = (self->flags & ~0xc) | 0x101;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C5D8);

s32 func_0029C5E8(u32 *arg0, s32 arg1) {
    if (arg1 == 1) {
        return ((u32) *arg0 >> 8) & 1;
    }
    func_0029C138();
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C620);
extern int func_0036D518(void);
extern void func_0036D568(void);

unsigned func_0029C628(volatile unsigned* flags) {
    int intr = func_0036D518();
    unsigned control = *(volatile unsigned*)0x1000f520;
    unsigned old;
    if (!(control & 0x10000)) *(volatile unsigned*)0x1000f590 = control | 0x10000;
    (void)*(volatile unsigned*)0x1000e000;
    old = *flags;
    *flags = old & ~0x100u;
    *(volatile unsigned*)0x1000f590 = control;
    if (intr) func_0036D568();
    return old;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C6C0);
