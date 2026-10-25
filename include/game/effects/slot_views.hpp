#ifndef BLACK_EFFECTS_MOD_SLOT_VIEWS_HPP
#define BLACK_EFFECTS_MOD_SLOT_VIEWS_HPP
#include "game/effects/slot.h"

namespace Effects {
struct ActorPrefix { char opaque[0x10]; };
// A descriptive ABI interface. The original class identity and hierarchy are unknown.
// Keeping all data in Actor would put GCC 2.95's vptr after that data instead of at 0x10.
class ActorInterface : public ActorPrefix {
public:
    virtual void V0(); virtual void V1(); virtual void V2(); virtual void V3();
    virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7();
    virtual void V8(); virtual void V9(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13();
    virtual void Release(unsigned char);
};
class Actor : public ActorInterface {
public:
    char unknown14[0x19c];
    unsigned short *indices;
    char unknown1b4[0x42];
    unsigned char boneCount;
};
class Bank {
public:
    inline BkEffectSlotPS2 &At(unsigned i) { return ((BkEffectSlotPS2 *)this)[i]; }
    void RemoveBone(Actor *, unsigned char);
};
}
#endif
