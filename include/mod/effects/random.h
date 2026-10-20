#ifndef BLACK_MOD_EFFECT_RANDOM_H
#define BLACK_MOD_EFFECT_RANDOM_H
#include "ps2/ee_types.h"
typedef struct BkModEffectRandomStatePS2 { EeU32 state, accumulator; } BkModEffectRandomStatePS2;
/* Source control 382348 proves this seed recipe and both 32-bit fields. */
static inline void BkModEffectRandomSeedPS2(BkModEffectRandomStatePS2 *random, EeU32 seed)
{
    random->accumulator=seed;
    random->state=~seed;
}
/* Muzzle instruction recipe only (1BD508/1BCDF8): no source control yet proves
   the return/allocation context of this inline step or its float conversion. */
static inline EeU32 BkModEffectRandomSignedStepPS2(BkModEffectRandomStatePS2 *random)
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
