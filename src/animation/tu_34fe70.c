#include "include_asm.h"
#include "animation/sampling.h"
#ifdef NON_MATCHING
#include "ps2/ee_fpu.h"
#endif

SamplingPair *func_0034FE70(SamplingPair *pair) {
    pair->first=0;
    pair->second=0;
    pair->weight=0;
    pair->wrapped=0;
    return pair;
}

#ifdef NON_MATCHING
/* Parameter meanings are UNVERIFIED. */
// Unmatched: division, float register and branch ordering differ.
int func_0034FE88(SamplingPair* pair, int count, float time, float duration, float interval) {
    int last = count - 1;
    float frame = BkEeDividePipelineGuardedValue(time, interval);
    int beyond = 1;
    int wrapped;
    if (!((float)last <= frame)) beyond = 0;
    if (count >= 2 && beyond) {
        float end = (float)count;
        float fraction;
        pair->first = last;
        fraction = (frame - end) + 1.0f;
        pair->second = 0;
        if (fraction == 0.0f) {
            pair->weight = 0.0f;
        } else {
            float period = (BkEeDividePipelineGuardedValue(duration, interval) - end) + 1.0f;
            if (period == 0.0f)
                pair->weight = 0.0f;
            else
                pair->weight = BkEeDividePipelineGuardedValue(fraction, period);
        }
    } else {
        int first = (int)frame;
        pair->first = first;
        pair->weight = frame - (float)first;
        pair->second = (first + 1) % (int)duration;
    }
    wrapped = pair->second < pair->first;
    pair->wrapped = wrapped;
    return wrapped;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34fe70", func_0034FE88);
#endif
#ifdef NON_MATCHING
/* Parameter meanings are UNVERIFIED. */
// Unmatched: division result and branch/register scheduling differ.
int func_0034FFA0(SamplingPair* pair, int count, float time, float duration, float interval) {
    float frame = BkEeDividePipelineGuardedValue(time, interval);
    int first, second;
    float base;
    if (count < 2) {
        pair->first = 0;
        pair->second = 0;
        pair->weight = 0.0f;
    } else if (frame < 0.0f) {
        pair->weight = frame;
        pair->second = 1;
        pair->first = 0;
    } else {
        second = count - 1;
        first = count - 2;
        if ((float)second < frame) {
            base = (float)first;
        } else {
            first = (int)frame;
            base = (float)first;
            second = first + 1;
        }
        pair->second = second;
        pair->first = first;
        pair->weight = frame - base;
    }
    pair->wrapped = pair->second < pair->first;
    return pair->wrapped;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34fe70", func_0034FFA0);
#endif
