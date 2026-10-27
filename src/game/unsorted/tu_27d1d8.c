#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/vu0_lowering.h"

typedef struct {
    f32 x, y, z, w;
} VectorFields __attribute__((aligned(16)));

static inline f32 DotXYZ(BkVuVector a, BkVuVector b, BkVuVector one) {
    return __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(a, b), one));
}

static inline BkVuVector AddW(BkVuVector a, BkVuVector b) {
    BkVuVector result;
    __asm__("vaddw.w outv, av, bvw" : "=j outv"(result) : "j av"(a), "j bv"(b));
    return result;
}

static inline BkVuVector SubW(BkVuVector a, BkVuVector b) {
    BkVuVector result;
    __asm__("vsubw.w outv, av, bvw" : "=j outv"(result) : "j av"(a), "j bv"(b));
    return result;
}

static inline f32 ReadW(BkVuVector value) {
    VectorFields spill;
    *(BkVuVector*)&spill = value;
    return spill.w;
}

#ifdef NON_MATCHING
/* UNVERIFIED partial capsule layout; these offsets are only draft evidence. */
typedef struct {
    BkVuVector start, end;
    f32 radius;
} CapsuleView;

extern BkVuVector D_00440250;

static inline f32 ReadY(BkVuVector value) {
    VectorFields spill;
    *(BkVuVector*)&spill = value;
    return spill.y;
}
static inline f32 ReadZ(BkVuVector value) {
    VectorFields spill;
    *(BkVuVector*)&spill = value;
    return spill.z;
}
static inline BkVuVector FloatVector(f32 value) {
    s32 word;
    BkVuVector result;
    __asm__("mfc1 %0, %1" : "=r"(word) : "f"(value));
    __asm__("qmtc2.ni wordv, resultv" : "=j resultv"(result) : "r wordv"(word));
    return result;
}
static inline BkVuVector FloatVectorAtomic(f32 value) {
    s32 word;
    BkVuVector result;
    __asm__("mfc1 wordv, valuef\n\tqmtc2.ni wordv, resultv"
            : "=r wordv"(word), "=j resultv"(result)
            : "f valuef"(value));
    return result;
}
static inline f32 ClampFraction(f32 value) {
    f32 lower = 0.0f;
    f32 upper = 1.0f;
    lower = __ee_max_s(value, lower);
    return __ee_min_s(lower, upper);
}
static inline BkVuVector WordVector(s32 word) {
    BkVuVector result;
    __asm__("qmtc2.ni wordv, resultv" : "=j resultv"(result) : "r wordv"(word));
    return result;
}
static inline BkVuVector MulW(BkVuVector a, BkVuVector b) {
    BkVuVector result;
    __asm__("vmulw.w outv, av, bvw" : "=j outv"(result) : "j av"(a), "j bv"(b));
    return result;
}
static inline BkVuVector AbsXYZ(BkVuVector value) {
    BkVuVector result;
    __asm__("vabs.xyz outv, vv" : "=j outv"(result) : "j vv"(value));
    return result;
}
static inline BkVuVector MaxXYZ(BkVuVector a, BkVuVector b) {
    BkVuVector result;
    __asm__("vmax.xyz outv, av, bv" : "=j outv"(result) : "j av"(a), "j bv"(b));
    return result;
}
static inline BkVuVector AddScalarW(BkVuVector a, BkVuVector scalar) {
    BkVuVector result;
    __asm__("vaddx.w outv, av, scalarvx" : "=j outv"(result) : "j av"(a), "j scalarv"(scalar));
    return result;
}
static inline s32 TinyDirection(f32 value) {
    union {
        f32 f;
        u32 u;
    } bits;
    bits.f = value;
    return (bits.u & 0x7F800000U) <= 0x37800000U;
}
static inline s32 Compare(f32 a, f32 b) {
    s32 result = 1;
    if (!(a < b)) result = 0;
    return result;
}
static inline u8 CompareByte(f32 a, f32 b) { return Compare(a, b); }
#endif

extern s32 D_003C0E04;

/* Partial serialized view; the prefix and discriminator meaning are UNVERIFIED. */
typedef struct {
    u8 unk_00[0x20];
    u32 dataOffset;
    u32 recordsOffset;
    u16 recordCount;
    u16 unk_2A;
    s32 unk_2C;
} Recovered_RelocatableRecords;

extern s32 func_0027F708(void* record);
extern s32 func_0027F6D8(void* record);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027D1D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027D7A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027DD60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027E308);
void func_0027E760(Recovered_RelocatableRecords* self) {
    u16 i;

    if (self->dataOffset) { self->dataOffset = (u32)self + self->dataOffset; }
    if (self->recordsOffset) { self->recordsOffset = (u32)self + self->recordsOffset; }
    if (self->unk_2C) {
        for (i = 0; i < self->recordCount; i++) { func_0027F708((void*)(self->recordsOffset + i * 16)); }
    } else {
        for (i = 0; i < self->recordCount; i++) { func_0027F6D8((void*)(self->recordsOffset + i * 16)); }
    }
}
#ifdef NON_MATCHING
// Unmatched: exponent-guard GPR allocation and the origin FPR lifetime differ.
s32 func_0027E820(void* unused, f32 start, f32 end, f32 lower, f32 upper, f32* entry, f32* exit) {
    f32 delta;
    f32 origin = start;
    f32 near, far;
    s32 hit;
    delta = end - origin;
    if (TinyDirection(delta)) return lower <= origin && origin <= upper;
    start = 1.0f / delta;
    if (start > 0.0f) {
        near = (lower - origin) * start;
        far = (upper - origin) * start;
    } else {
        near = (upper - origin) * start;
        far = (lower - origin) * start;
    }
    hit = *entry <= far && near <= *exit;
    if (hit) {
        *entry = __ee_max_s(*entry, near);
        *exit = __ee_min_s(*exit, far);
    }
    return hit;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027E820);
#endif
#ifdef NON_MATCHING
// Unmatched: box/sphere VU register allocation and W-spill scheduling differ.
s32 func_0027E900(const BkVuVector* box, BkVuVector sphere) {
    f32 radius = ReadW(MulW(sphere, sphere));
    BkVuVector lower = box[1];
    BkVuVector scale = WordVector(0x3f000000);
    BkVuVector half = box[0];
    BkVuVector delta;
    half = BkVuSubXYZ(half, lower);
    half = BkVuScaleXYZ(half, scale);
    lower = BkVuAddXYZ(lower, half);
    delta = BkVuSubXYZ(sphere, lower);
    delta = AbsXYZ(delta);
    delta = BkVuSubXYZ(delta, half);
    delta = MaxXYZ(delta, D_00440250);
    return DotXYZ(delta, delta, BkVuOneX()) < radius;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027E900);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027E988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027E9B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027EFE0);
s32 func_0027EFE8(BkVuVector a, BkVuVector b) {
    f32 radii = ReadW(AddW(a, b));
    f32 distance = DotXYZ(BkVuSubXYZ(a, b), BkVuSubXYZ(a, b), BkVuOneX());
    f32 difference;
    if (radii * radii < distance) return 0;
    difference = ReadW(SubW(b, a));
    if (difference < 0.0f) return 1;
    if (distance < difference * difference) return 2;
    return 1;
}
#ifdef NON_MATCHING
// Unmatched: direction-copy lifetime, paired dot scheduling and containment return join differ.
s32 func_0027F070(BkVuVector sphere, const CapsuleView* capsule) {
    BkVuVector one = BkVuOneX();
    BkVuVector direction = BkVuSubXYZ(capsule->end, capsule->start);
    BkVuVector delta = BkVuSubXYZ(sphere, capsule->start);
    f32 numerator = DotXYZ(delta, direction, one);
    f32 denominator = DotXYZ(direction, direction, one);
    f32 t = numerator / denominator;
    f32 distance;
    f32 radius;
    BkVuVector combined;
    if (t <= 0.0f)
        distance = DotXYZ(delta, delta, one);
    else if (1.0f <= t) {
        delta = BkVuSubXYZ(sphere, capsule->end);
        distance = DotXYZ(delta, delta, one);
    } else {
        delta = BkVuSubXYZ(sphere, BkVuAddXYZ(capsule->start, BkVuScaleXYZ(direction, FloatVector(t))));
        distance = DotXYZ(delta, delta, one);
    }
    radius = capsule->radius;
    combined = AddScalarW(sphere, FloatVector(radius));
    if (ReadW(MulW(combined, combined)) < distance) return 0;
    return (ReadW(AddScalarW(sphere, FloatVector(__ee_sqrt_s(distance)))) < radius) ? 2 : 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F070);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F1C0);
s32 func_0027F218(BkVuVector point, BkVuVector normal, BkVuVector a, BkVuVector b, BkVuVector c, BkVuVector d) {
    BkVuVector one = BkVuOneX();
    if (DotXYZ(BkVuCrossXYZ(normal, BkVuSubXYZ(b, a)), BkVuSubXYZ(point, a), one) < 0.0f) return 0;
    if (DotXYZ(BkVuCrossXYZ(normal, BkVuSubXYZ(c, b)), BkVuSubXYZ(point, b), one) < 0.0f) return 0;
    if (DotXYZ(BkVuCrossXYZ(normal, BkVuSubXYZ(d, c)), BkVuSubXYZ(point, c), one) < 0.0f) return 0;
    if (DotXYZ(BkVuCrossXYZ(normal, BkVuSubXYZ(a, d)), BkVuSubXYZ(point, d), one) < 0.0f) return 0;
    return 1;
}
#ifdef NON_MATCHING
// Unmatched: byte predicate narrowing and component-spill evaluation order differ.
s32 func_0027F338(BkVuVector lower, BkVuVector upper, BkVuVector point) {
    s32 code;
    if (CompareByte(__ee_vu_read_x(upper), __ee_vu_read_x(point)))
        code = 1;
    else
        code = Compare(__ee_vu_read_x(point), __ee_vu_read_x(lower)) << 1;
    if (CompareByte(ReadY(upper), ReadY(point)))
        code |= 4;
    else if (Compare(ReadY(point), ReadY(lower)))
        code |= 8;
    if (CompareByte(ReadZ(upper), ReadZ(point)))
        code |= 32;
    else if (Compare(ReadZ(point), ReadZ(lower)))
        code |= 16;
    return code;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F338);
#endif
#ifdef NON_MATCHING
// Unmatched: clamp input and bound FPR allocation differ.
void func_0027F470(BkVuVector start, BkVuVector direction, BkVuVector point, BkVuVector* result, f32* fraction) {
    BkVuVector one = BkVuOneX();
    f32 length = DotXYZ(direction, direction, one);
    f32 t;
    if (length < 2.3283064e-10f) {
        *result = start;
        return;
    }
    t = DotXYZ(direction, BkVuSubXYZ(point, start), one) / length;
    t = ClampFraction(t);
    {
        BkVuVector scale = FloatVectorAtomic(t);
        *fraction = t;
        *result = BkVuAddXYZ(start, BkVuScaleXYZ(direction, scale));
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F470);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F508);
#ifdef NON_MATCHING
// Unmatched: native direction/one VU copies and quotient FPR allocation differ.
f32 func_0027F518(BkVuVector point, const BkVuVector* segment) {
    BkVuVector one = BkVuOneX();
    BkVuVector direction = BkVuSubXYZ(segment[1], segment[0]);
    BkVuVector delta = BkVuSubXYZ(point, segment[0]);
    f32 projection = DotXYZ(direction, delta, one);
    if (projection > 0.0f) {
        f32 length = DotXYZ(direction, direction, one);
        if (length <= projection)
            delta = BkVuSubXYZ(delta, direction);
        else
            delta = BkVuSubXYZ(delta, BkVuScaleXYZ(direction, FloatVector(projection / length)));
    }
    return DotXYZ(delta, delta, one);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F518);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F5D0);

s32 func_0027F5E0(void) {
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F5E8);
/* This native encoding uses fixed 31-day months and 372-day years. */
typedef struct {
    u16 year, month, day, hour, minute, second;
} CalendarFields;
u32 func_0027F640(CalendarFields* date) {
    return date->second + date->minute * 60 + date->hour * 3600 + (date->day - 1) * 86400 +
           (date->month - 1) * 2678400 + (date->year % 100) * 32140800;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F6B8);

void func_0027F778(void) {
    D_003C0E04 += 1;
}
