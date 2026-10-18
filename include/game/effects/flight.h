#ifndef BLACK_EFFECTS_FLIGHT_H
#define BLACK_EFFECTS_FLIGHT_H
#include "game/effects/pool.h"
#include "game/effects/vector.h"
typedef struct {
 s128 initial[4],world[4];BkEffectPointPS2 origin,velocity; s128 localOffset;
 BkEffectEntryPS2 child;f32 lifetime;u8 active,relative,padding[10];
} BkEffectFlightPS2;
#endif
