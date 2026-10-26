#include "include_asm.h"
#include "game/ai/point_history.h"

extern void* D_0040F4D0;

/* Seed all retained samples with the same point. */
s32 func_00173450(Recovered_PointHistory* self, s128 point) {
    s32 remaining = 2;
    s128* sample = &self->samples[2];
    do {
        *sample = point;
        remaining--;
        sample--;
    } while (remaining >= 0);
    self->lastSampleTime = M2C_FIELD(D_0040F4D0, f32*, 0x20);
    return 1;
}

#ifdef NON_MATCHING
#include "ps2/vu0_math.h"
static inline BkVuVector PointHistory_FloatVector(f32 value) {
    s32 word;
    __asm__("mfc1 wordv, scalarf" : "=r wordv"(word) : "f scalarf"(value));
    return (BkVuVector)word;
}
static inline s128 PointHistory_VectorWords(BkVuVector value) {
    s128 words;
    __asm__("qmfc2.ni wordsv, vectorv" : "=r wordsv"(words) : "j vectorv"(value));
    return words;
}
// Unmatched: native scratch construction, VU allocation and returned W transport remain unresolved.
s128 func_00173488(Recovered_PointHistory* self) {
    f32 fraction = (M2C_FIELD(D_0040F4D0, f32*, 0x20) - self->lastSampleTime) / 0.35f;
    BkVuVector blends[2];
    const s128* sample = &self->samples[1];
    BkVuVector* out = blends;
    s8 remaining = 2;
    do {
        BkVuVector older = BkVuScaleXYZ(sample[1], PointHistory_FloatVector(1.0f - fraction));
        BkVuVector newer = BkVuScaleXYZ(sample[0], PointHistory_FloatVector(fraction));
        *out = BkVuAddXYZ(older, newer);
        out++;
        sample--;
        remaining--;
    } while (remaining > 0);
    return PointHistory_VectorWords(BkVuSubXYZ(BkVuScaleXYZ(blends[1], PointHistory_FloatVector(2.0f)), blends[0]));
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548_173450", func_00173488);
#endif

/* Keep the two older samples only when the native sampling interval has elapsed. */
#ifdef NON_MATCHING
// Unmatched: point-store and clock-reload scheduling differs.
s32 func_00173560(Recovered_PointHistory* self, s128 point) {
    if (M2C_FIELD(D_0040F4D0, f32*, 0x20) < self->lastSampleTime + 0.35f) return 0;
    {
        s8 remaining = 2;
        s128* sample = &self->samples[2];
        do {
            *sample = sample[-1];
            remaining--;
            sample--;
        } while (remaining > 0);
    }
    self->samples[0] = point;
    self->lastSampleTime = M2C_FIELD(D_0040F4D0, f32*, 0x20);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548_173450", func_00173560);
#endif
