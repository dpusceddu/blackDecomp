// Unmatched: 0x1bef70: 44 flight slots, true 64-bit IDs, VU I/ACC trig orientation and 128-bit particle state.
// Unmatched: 0x1bf918: signed rounding and packed count clamp, emitter fraction and mixed-width spawn callback ABI.
// Unmatched: 0x1c0a78: signed fractional light counts, VU I/ACC random basis and vector-valued spawn arguments.
#ifdef NONMATCHING
#include "game/effects/emitter.h"
#include "game/effects/flight.h"
extern "C" int func_001BEF70(BkEffectFlightPS2 *,s128,void *);
extern "C" int func_001BF918(BkEffectEmitterRecordPS2 *,BkEffectEmitterNodePS2 **,f32);
extern "C" int func_001C0A78(BkEffectLightPS2 *,f32);
#endif
