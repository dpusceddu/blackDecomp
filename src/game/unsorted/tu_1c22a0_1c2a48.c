#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/scratchpad_buffers.h"

/* Partial views of the buffer-backed draw records; original class names and
 * the unaccessed portions of each layout are UNVERIFIED. */
typedef struct DrawDefinition {
    float scale;
    int count;
    unsigned char (*records)[32];
    unsigned int unk_0c;
    unsigned char* unk_10;
    unsigned char* unk_14;
    unsigned char unk_18[8];
    unsigned char unk_20[1];
} DrawDefinition;

typedef union DrawVectorTemporary {
    volatile float f[4];
    s128 bits;
} DrawVectorTemporary __attribute__((aligned(16)));

typedef struct DrawObjectView {
    DrawDefinition* definition;
    int* slots;
    unsigned char unk_08[8];
    s128 first, second;
    unsigned char unk_30[0x440];
    float rate;
} DrawObjectView;

typedef struct DrawQueueView {
    unsigned char unk_00[0x20];
    int unk_20;
    float unk_24;
    unsigned char unk_28[0x400];
    int count;
    float unk_42c, unk_430, unk_434;
    void* unk_438;
    unsigned char* unk_43c;
    unsigned char* unk_440;
    int unk_444;
} DrawQueueView;

typedef char DrawObjectFirstOffset[(unsigned int)&((DrawObjectView*)0)->first == 0x10 ? 1 : -1];
typedef char DrawObjectRateOffset[(unsigned int)&((DrawObjectView*)0)->rate == 0x470 ? 1 : -1];
typedef char DrawQueueCountOffset[(unsigned int)&((DrawQueueView*)0)->count == 0x428 ? 1 : -1];

extern void func_001D5028(void*, DrawDefinition*);
extern int func_001D5048(void*);
extern void* func_00107D20(unsigned int);
extern void func_001C2EA8(int*, int);

static inline float DrawZero(void) { return 0.0f; }


void func_001C2A48(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0x70002000;
    M2C_FIELD(arg0, s32 *, 4) = 0x70002800;
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

void func_001C2AB0(DrawObjectView* self, DrawDefinition* definition) {
    DrawVectorTemporary temp;
    s128 first, second;
    self->definition = definition;
    func_001D5028((char*)self + 0x10, definition);
    temp.f[0] = 0.012f;
    temp.f[1] = DrawZero();
    temp.f[2] = 0.008f;
    temp.f[3] = 0.012256f;
    first = temp.bits;
    temp.f[0] = 1.0f;
    temp.f[1] = DrawZero();
    temp.f[2] = DrawZero();
    temp.f[3] = DrawZero();
    second = temp.bits;
    self->rate = 0.3f;
    self->first = first;
    self->second = second;
    self->slots = 0;
    if (definition && definition->count > 0) {
        int i = 0;
        self->slots = func_00107D20(definition->count * 4);
        for (; i < definition->count; ++i) { func_001C2EA8(&self->slots[i], (int)&definition->records[i]); }
    }
}
int func_001C2BC0(DrawObjectView* self) {
    DrawVectorTemporary temp;
    s128 first, second;
    func_001D5048((char*)self + 0x10);
    temp.f[0] = 0.012000000104308128f;
    temp.f[1] = DrawZero();
    temp.f[2] = 0.00800000037997961f;
    temp.f[3] = 0.012256000190973282f;
    first = temp.bits;
    temp.f[0] = 1.0f;
    temp.f[1] = DrawZero();
    temp.f[2] = DrawZero();
    temp.f[3] = DrawZero();
    self->first = first;
    second = temp.bits;
    self->second = second;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C2C50);
void func_001C2D90(DrawQueueView* self, DrawDefinition* resource) {
    self->unk_20 = 0;
    self->unk_24 = 1.0f;
    self->count = 0;
    self->unk_438 = 0;
    self->unk_43c = 0;
    self->unk_440 = 0;
    self->unk_42c = 0;
    self->unk_430 = 0;
    self->unk_434 = 0;
    self->unk_444 = 0;
    if (resource) {
        unsigned char* data;
        self->unk_43c = resource->unk_14;
        self->unk_440 = resource->unk_10;
        self->unk_43c[0] = 14;
        self->unk_43c[1] = 50;
        self->unk_440[0] = 14;
        self->unk_438 = resource->unk_20;
        data = self->unk_43c;
        self->unk_430 = *(float*)(data + 0x14);
        self->unk_434 = *(float*)(data + 0x18);
        self->unk_42c = *(float*)(data + 0x10);
        self->unk_444 = *(unsigned short*)(data + 0xc);
    }
}

s32 func_001C2E30(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x428) = 0;
    return 1;
}

s32 func_001C2E40(void *arg0, void *arg1)
{
  f32 new_var;
  void *new_var2;
  s32 var_2;
  new_var = M2C_FIELD(arg0, f32 *, 4);
  var_2 = -1;
  new_var2 = arg1;
  if (!((M2C_FIELD(new_var2, f32 *, 4)) < new_var))
  {
    var_2 = 1;
  }
  return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C2E68);

void func_001C2EA8(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C2EB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C3020);

s128 func_001C31E0(s128 **arg0) {
    return **arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C31F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C31F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C3228);
