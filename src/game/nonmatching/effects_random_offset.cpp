#include "game/effects/vector.h"
#include "game/effects/random.h"
// Unmatched: VU scalar lane extraction spills and random-state scheduling.
#ifdef NONMATCHING
extern "C" s128 func_001BCA30(void *,s128 range,f32 scale) {
 BkEffectPointPS2 source= BkEffectSpillPS2(range),result;
 result.x=source.x*BkEffectRandomPS2()*scale;
 result.y=source.y*BkEffectRandomPS2()*scale;
 result.z=source.z*BkEffectRandomPS2()*scale;
 return *(s128 *)&result;
}
#endif // NONMATCHING
