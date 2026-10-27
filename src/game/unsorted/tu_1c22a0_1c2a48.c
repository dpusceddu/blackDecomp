#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/vu0_lowering.h"

#include "game/scratchpad_buffers.h"

/* Partial views of the buffer-backed draw records; original class names and
 * the unaccessed portions of each layout are UNVERIFIED. */
typedef struct DrawInputView {
    BkVuVector position;
    unsigned int* colors; // UNVERIFIED: packed colour source in the draft converter.
    int count; // UNVERIFIED: draw-count input in the culling draft.
    unsigned char unk_18[8];
} DrawInputView;

/* UNVERIFIED: entry layout used by the enqueue/render assembly and drafts. */
typedef struct DrawQueuedRecord {
    DrawInputView** source;
    float distance;
    float amount;
    unsigned char count;
    unsigned char unk_0d;
    unsigned char unk_0e[2];
} DrawQueuedRecord;

typedef struct DrawDefinition {
    float scale; // UNVERIFIED: sphere radius consumed by the culling draft.
    int count;
    DrawInputView* records;
    unsigned int unk_0c;
    unsigned char* unk_10;
    unsigned char* unk_14;
    unsigned char unk_18[8];
    unsigned char unk_20[1];
} DrawDefinition;

/* The native constructors store scalar lanes before loading each quadword. */
typedef union DrawVectorTemporary {
    volatile float f[4];
    s128 bits;
} DrawVectorTemporary __attribute__((aligned(16)));

typedef struct DrawObjectView {
    DrawDefinition* definition;
    DrawInputView** slots;
    unsigned char unk_08[8];
    s128 first, second;
    unsigned char unk_30[0x440];
    float rate;
} DrawObjectView;

typedef struct DrawQueueView {
    unsigned char unk_00[0x20];
    int unk_20;
    float unk_24;
    DrawQueuedRecord records[63]; // UNVERIFIED: signed capacity test and 16-byte indexing in the enqueue draft.
    unsigned char unk_418[0x10];
    int count;
    float unk_42c, unk_430, unk_434;
    void* unk_438;
    unsigned char* unk_43c;
    unsigned char* unk_440;
    int unk_444;
} DrawQueueView;

typedef char DrawInputStride[sizeof(DrawInputView) == 32 ? 1 : -1];
typedef char DrawQueuedRecordStride[sizeof(DrawQueuedRecord) == 16 ? 1 : -1];
typedef char DrawObjectFirstOffset[(unsigned int)&((DrawObjectView*)0)->first == 0x10 ? 1 : -1];
typedef char DrawObjectRateOffset[(unsigned int)&((DrawObjectView*)0)->rate == 0x470 ? 1 : -1];
typedef char DrawQueueCountOffset[(unsigned int)&((DrawQueueView*)0)->count == 0x428 ? 1 : -1];

extern void func_001D5028(void*, DrawDefinition*);
extern int func_001D5048(void*);
extern void* func_00107D20(unsigned int);
extern void func_001C2EA8(DrawInputView**, DrawInputView*);

#ifdef NON_MATCHING
/* UNVERIFIED: these draft-only views are based on native accesses, not exact source. */
typedef struct DrawClockView {
    unsigned char unk_00[0x20];
    float time;
} DrawClockView;
typedef struct CullContextView {
    unsigned char unk_00[0x7d0];
    BkVuVector origin;
    unsigned char unk_7e0[0xe80];
    float factor;
} CullContextView;
typedef struct DrawZeroView {
    BkVuVector position;
    int unk_10, unk_14, unk_18;
    unsigned char unk_1c[4];
    unsigned char active;
} DrawZeroView;
extern DrawClockView* D_0040F4D0;
extern unsigned char* D_0040F4C0;
extern CullContextView* D_0040F4BC;
extern DrawQueueView* D_003BD1D0;
extern float D_003BD1D8, D_003BD1D4;
extern float func_0029DA28(float);
extern float func_0029DC18(float);
extern int func_0026F0B0(BkVuVector, void*);
extern void func_001D5068(DrawQueueView*);
extern void func_001C2EB0(DrawInputView**, void*, DrawQueueView*, float);
extern void func_001C2E68(DrawQueueView*, DrawInputView**, float, float, int, int);

/* Only X is consumed after the native word-to-quadword transfer. */
static inline BkVuVector DrawScalar(float scalar) {
    BkVuVector bits;
    __asm__("mfc1 bitsv, scalarf" : "=r bitsv"(bits) : "f scalarf"(scalar));
    return bits;
}
/* Construct XYZ/radius without assigning a meaning to any other input lanes. */
static inline BkVuVector DrawSphere(BkVuVector position, BkVuVector radius) {
    BkVuVector result;
    __asm__("vadd.xyz resultv,vf0,positionv\n\tvsubw.w resultv,vf0,vf0w\n\tvaddx.w resultv,resultv,radiusvx"
            : "=&j resultv"(result)
            : "j positionv"(position), "j radiusv"(radius));
    return result;
}
/* Preserve the native packed signed minimum and low-word extraction. */
static inline int DrawMinCount(int a, int b) {
    BkVuVector packed;
    int low;
    __asm__("pminw packedv,av,bv\n\tpextlw lowv,$0,packedv"
            : "=r packedv"(packed), "=r lowv"(low)
            : "r av"(a), "r bv"(b));
    return low;
}
/* Construct the temporary as well as returning its VU value; W is unspecified. */
static inline BkVuVector ConstructZeroXYZ(volatile BkVuVector* storage) {
    BkVuVector value;
    __asm__("vadd.xyz vectorv, vf0, vf0" : "=j vectorv"(value));
    *storage = value;
    return value;
}
static inline BkVuVector DrawScaleXYZW(BkVuVector value, BkVuVector scalar) {
    BkVuVector result;
    __asm__("vmove.xyzw resultv,valuev\n\tvmulx.xyzw resultv,resultv,scalarvx"
            : "=&j resultv"(result)
            : "j valuev"(value), "j scalarv"(scalar));
    return result;
}
static inline BkVuVector DrawSubXYZW(BkVuVector a, BkVuVector b) {
    __asm__("vsub.xyzw resultv,resultv,bv" : "+j resultv"(a) : "j bv"(b));
    return a;
}
static inline BkVuVector DrawSetW(BkVuVector value, BkVuVector scalar) {
    __asm__("vmulx.w resultv,vf0,scalarvx" : "+j resultv"(value) : "j scalarv"(scalar));
    return value;
}
#endif

static inline float DrawZero(void) { return 0.0f; }

void func_001C2A48(ScratchpadBuffers* self) {
    self->addresses[0] = 0x70002000;
    self->addresses[1] = 0x70002800;
    self->currentIndex = 0;
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
        for (; i < definition->count; ++i) { func_001C2EA8(&self->slots[i], &definition->records[i]); }
    }
}

int func_001C2BC0(DrawObjectView* self) {
    DrawVectorTemporary temp;
    s128 first, second;
    func_001D5048((char*)self + 0x10);
    temp.f[0] = 0.012f;
    temp.f[1] = DrawZero();
    temp.f[2] = 0.008f;
    temp.f[3] = 0.012256f;
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
#ifdef NON_MATCHING
// Unmatched: native direction-store and queue/global pointer capture scheduling differ.
void func_001C2C50(DrawObjectView* self) {
    float degrees = D_0040F4D0->time * self->rate * 360.0f;
    float angle = (degrees - (float)(int)(degrees / 360.0f) * 360.0f) * 0.017453292f;
    float x = func_0029DA28(angle);
    float z = func_0029DC18(angle);
    DrawVectorTemporary temp;
    temp.f[0] = x;
    temp.f[1] = DrawZero();
    temp.f[2] = z;
    temp.f[3] = DrawZero();
    self->second = temp.bits;
    if (self->definition) {
        DrawQueueView* queue = (DrawQueueView*)((char*)self + 0x10);
        int i = 0;
        void* context;
        D_003BD1D0 = queue;
        context = D_0040F4C0 + 0xcfd0;
        for (; i < self->definition->count; ++i) {
            func_001C2EB0(&self->slots[i], context, queue, self->definition->scale);
        }
        func_001D5068(queue);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C2C50);
#endif
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

#ifdef NON_MATCHING
// Unmatched: the amount store moves ahead of the native source/distance/byte stores.
void func_001C2E68(DrawQueueView* self, DrawInputView** source, float distance, float amount, int a, int b) {
    if (self->count < 63) {
        DrawQueuedRecord* record = &self->records[self->count];
        record->unk_0d = b;
        record->source = source;
        record->distance = distance;
        record->count = a;
        record->amount = amount;
        self->count++;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C2E68);
#endif

void func_001C2EA8(DrawInputView** slot, DrawInputView* record) { *slot = record; }

#ifdef NON_MATCHING
// Unmatched: sphere VU allocation, count-view lifetime and fade FPR allocation differ.
void func_001C2EB0(DrawInputView** slot, void* planes, DrawQueueView* queue, float radius) {
    BkVuVector radiusVector = DrawScalar(radius);
    int classification = func_0026F0B0(DrawSphere((*slot)->position, radiusVector), planes);
    if (classification) {
        DrawInputView* record = *slot;
        CullContextView* context = D_0040F4BC;
        BkVuVector position = record->position;
        BkVuVector one = BkVuOneX();
        BkVuVector delta = BkVuSubXYZ(position, context->origin);
        float distance = __ee_vu_read_x(BkVuSqrtX(BkVuSumXYZ(BkVuMulXYZ(delta, delta), one)));
        float coefficient = context->factor;
        float start = D_003BD1D0->unk_430;
        float range = D_003BD1D0->unk_434;
        float ratio = (distance - start) / range;
        float scale = 1.0f - __ee_min_s(__ee_max_s(ratio * coefficient, 0.0f), 1.0f);
        int count;
        float amount;
        if (scale < 1.0f) {
            int original = record->count;
            amount = (float)((int)((float)original * 0.25f) + original) * scale;
            count = DrawMinCount((int)amount, original);
        } else {
            count = record->count;
            amount = (float)count * 1.25f;
        }
        if (count > 0) { func_001C2E68(queue, slot, distance, amount, count, classification == 2); }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C2EB0);
#endif
#ifdef NON_MATCHING
// Unmatched: bias transport, packed-component joins and VU output allocation differ.
void func_001C3020(DrawInputView** slot, volatile BkVuVector* output, int count, float amount) {
    DrawVectorTemporary temp;
    BkVuVector bias;
    unsigned int* input;
    float alpha;
    temp.f[0] = amount;
    temp.f[1] = amount;
    temp.f[2] = amount;
    temp.f[3] = amount;
    input = (*slot)->colors;
    amount /= 127.0f;
    bias = *(const volatile BkVuVector*)&temp;
    alpha = D_003BD1D8 / 255.0f;
    if (count > 0) {
        do {
            unsigned int color = *input;
            BkVuVector value;
            float w;
            float red = (float)(color & 0xff);
            float green = (float)((color & 0xff00) >> 8);
            float blue = (float)((color & 0xff0000) >> 16);
            temp.f[0] = red;
            temp.f[1] = green;
            temp.f[2] = blue;
            temp.f[3] = DrawZero();
            value = DrawScaleXYZW(temp.bits, DrawScalar(amount));
            *output = value;
            value = DrawSubXYZW(value, bias);
            *output = value;
            w = (float)((color & 0xff000000) >> 24) * alpha + D_003BD1D4;
            value = *output;
            *output = DrawSetW(value, DrawScalar(w));
            ++input;
            --count;
            ++output;
        } while (count);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C3020);
#endif

s128 func_001C31E0(DrawInputView** slot) { return (*slot)->position; }

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C31F0);
#ifdef NON_MATCHING
// Unmatched: scalar zero stores move before the native vector stores.
void func_001C31F8(DrawZeroView* self) {
    volatile EeS128 temp;
    self->active = 1;
    self->position = ConstructZeroXYZ(&temp);
    self->unk_14 = 0;
    self->unk_18 = 0;
    self->unk_10 = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2a48", func_001C31F8);
#endif
typedef struct DrawParameterView {
    char unk_00[0x10];
    float value;
} DrawParameterView;
typedef struct DrawActorView {
    char unk_00[0x58];
    void* target;
    char unk_5c[0x28];
    float value;
} DrawActorView;
extern void func_001C3DC0(DrawParameterView*, float, float*, float*);
extern void* func_002A9240(void*, float);
void func_001C3228(DrawParameterView* self, DrawActorView* actor, float value) {
    float result, unused;
    self->value = value;
    func_001C3DC0(self, value, &result, &unused);
    actor->value = result;
    func_002A9240(actor->target, result);
}
