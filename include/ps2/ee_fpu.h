#ifndef BLACK_PS2_EE_FPU_H
#define BLACK_PS2_EE_FPU_H

/* Scoped EE divide pipeline recipe. Catalog Sony GCC's measured
   -mhandle-ee-div-pipeline-bug option emits these two guard instructions;
   SN 1.36 has no equivalent option. Use only for independently verified
   consumers, not as a global compiler-identity or hardware-safety claim.
   See docs/matching-handbook.md. */
typedef char BkEeFloatIs32[sizeof(float) == 4 ? 1 : -1];
static inline float BkEeDividePipelineGuarded(float numerator, float denominator)
{
    float result;
    __asm__ volatile("nop\n\tnop\n\tdiv.s %0,%1,%2"
                     : "=f"(result) : "f"(numerator), "f"(denominator));
    return result;
}

/* Value form: the compiler may schedule independent work around this operation.
   Keep the volatile form above for consumers whose verified ordering needs it. */
static inline float BkEeDividePipelineGuardedValue(float numerator, float denominator)
{
    float result;
    __asm__("nop\n\tnop\n\tdiv.s %0,%1,%2"
            : "=f"(result) : "f"(numerator), "f"(denominator));
    return result;
}

#endif
