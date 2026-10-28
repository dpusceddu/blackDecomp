#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/ee_types.h"

#include "ps2/recovered_types.h"
extern s8 D_0040D9F3;
extern void * D_0040EB18;

s32 func_001D3078(void) {
    D_0040D9F3 = 0;
    D_0040EB18 = NULL;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78_1d3078", func_001D3090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78_1d3078", func_001D3368);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78_1d3078", func_001D3408);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78_1d3078", func_001D37C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78_1d3078", func_001D3C90);
#ifdef NON_MATCHING
/* UNVERIFIED: partial layout inferred from this function's accesses. */
typedef struct Unk1D3D80Vector {
    float x, y, z, w;
} Unk1D3D80Vector;
typedef struct Unk1D3D80Work {
    char pad[0xBE0];
    EeS128 value;
    int flag;
} Unk1D3D80Work;
extern void func_001D3DE0(void *);
extern void func_001D3EA0(void);

static inline float Unk1D3D80Zero(void) { return 0.0f; }

// Unmatched: local vector initialization stores are scheduled in a different order.
int func_001D3D80(Unk1D3D80Work *self) {
    Unk1D3D80Vector value;
    value.x = Unk1D3D80Zero();
    value.y = Unk1D3D80Zero();
    value.z = Unk1D3D80Zero();
    value.w = 1.00390625f;
    self->value = *(EeS128 *)&value;
    func_001D3DE0(self);
    func_001D3EA0();
    self->flag = 0;
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78_1d3078", func_001D3D80);
#endif
#ifdef NON_MATCHING
/* UNVERIFIED: partial packet layout inferred from this function's accesses. */
typedef struct Unk1D3DE0Row {
    EeS128 a, b, c, d;
} Unk1D3DE0Row;
typedef struct Unk1D3DE0Work {
    EeU64 header;
    int unk8, unkc, unk10, unk14, unk18, unk1c;
    Unk1D3DE0Row rows[20];
    int unk520, unk524, unk528, unk52c;
    char pad[0x140];
    int unk670, unk674, unk678, unk67c;
    char pad2[0x140];
    EeU64 unk7c0;
    int unk7c8, unk7cc;
    char pad3[0x410];
    EeS128 value;
} Unk1D3DE0Work;

// Unmatched: loop counter is lowered in units of rows rather than quadwords.
void func_001D3DE0(void *arg) {
    Unk1D3DE0Work *self = (Unk1D3DE0Work *)arg;
    int i;
    self->header = 0x1000007B;
    self->unk8 = 0;
    self->unkc = 0;
    self->unk10 = 0;
    self->unk14 = 0x05000000;
    self->unk18 = 0x01000103;
    self->unk1c = 0x6C508000;
    for (i = 0; i < 20; i++) {
        self->rows[i].a = self->value;
        self->rows[i].b = self->value;
        self->rows[i].c = 0;
        self->rows[i].d = 0;
    }
    self->unk520 = 0;
    self->unk524 = 0x05000000;
    self->unk528 = 0x01000103;
    self->unk52c = 0x65508001;
    self->unk670 = 0;
    self->unk674 = 0x05000000;
    self->unk678 = 0x01000103;
    self->unk67c = 0x6E508002;
    self->unk7c0 = 0x10000000;
    self->unk7cc = 0x17000000;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78_1d3078", func_001D3DE0);
#endif
/* UNVERIFIED: partial layouts inferred from the accesses below. */
typedef struct Unk1D3FC0Payload {
    int x, y;
    EeU64 a, b, c;
} Unk1D3FC0Payload;
typedef struct Unk1D3FC0Request {
    void *resource;
    Unk1D3FC0Payload *payload;
} Unk1D3FC0Request;

extern void func_0026A6F0(void *);
extern void func_0026A460(EeU64, EeU64, EeU64, EeU64, void *, int);

void func_001D3FC0(Unk1D3FC0Request *request) {
    Unk1D3FC0Payload *payload = request->payload;
    if (!payload) {
        func_0026A6F0(request->resource);
    } else {
        func_0026A460(payload->a, payload->b,
                     (EeU64)(unsigned int)(0x8000 - payload->x * 8) |
                         ((EeU64)(0x8000 - payload->y * 8) << 32),
                     payload->c, request->resource, 0);
    }
}
