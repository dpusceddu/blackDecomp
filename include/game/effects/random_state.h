#ifndef BLACK_MOD_EFFECT_RANDOM_H
#define BLACK_MOD_EFFECT_RANDOM_H
#include "ps2/ee_types.h"
typedef struct BkEffectRandomStatePS2 { EeU32 state, accumulator; } BkEffectRandomStatePS2;
/* Source control 382348 proves this seed recipe and both 32-bit fields. */
static inline void BkEffectRandomSeedPS2(BkEffectRandomStatePS2 *random, EeU32 seed)
{
    random->accumulator=seed;
    random->state=~seed;
}
/* Arithmetic instruction recipe. The original state-member form in random.hpp
   is exact at1BD508/1BCDF8; this local-return C form has a different unverified
   return/allocation shape and is retained independently. */
static inline EeU32 BkEffectRandomSignedStepPS2(BkEffectRandomStatePS2 *random)
{
    EeU32 value=(random->state<<16)+((EeS32)random->state>>16)+random->accumulator;
    random->accumulator+=value;
    random->state=value;
    return value;
}
/* Both muzzle high-half shifts are SRA-by-16 in retail. The SRL-by-1
   instructions belong to unsigned-to-float conversion, not the RNG step.
   Preserve each site's floating multiplication order. */
#endif
