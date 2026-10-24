#ifndef BLACK_MOD_EFFECT_EMITTER_METHODS_HPP
#define BLACK_MOD_EFFECT_EMITTER_METHODS_HPP
#include "game/effects/runtime.hpp"
#include "game/effects/attachments.h"
#include "game/effects/emitter.h"
#include "game/effects/emitter_list.h"
namespace ModEffects {
// Descriptive nonvirtual methods over observed PS2 storage. Original names unknown.
class Flights : public BkModAttachedEffectsPS2 {
public:
    int Clear() __asm__("func_001BEC68");
};
class EmitterRecord : public BkEffectEmitterRecordPS2 {
public:
    int Clear() __asm__("func_001BF720");
    int Reset() __asm__("func_001BFEA0");
};
class Emitters : public BkEffectEmittersPS2 {
public:
    void Construct() __asm__("func_001BFED0");
    BkEffectEmitterRecordPS2 *Allocate(void*, unsigned short, const Matrix*, float) __asm__("func_001C01E0");
    void Render() __asm__("func_001C0518");
    int Clear() __asm__("func_001C0600");
};
class Lights : public BkEffectLightsPS2 {
public:
    BkEffectLightPS2 *Allocate(void*, unsigned short, const Matrix*, float) __asm__("func_001C1740");
    void Update() __asm__("func_001C1810");
    int Clear() __asm__("func_001C19B0");
};
}
#endif
