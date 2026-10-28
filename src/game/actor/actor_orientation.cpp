#include "include_asm.h"

#include "game/actor/orientation.hpp"

namespace ActorParts {

extern "C" {
extern EeS128 D_004432A0;
int func_0013EC10(OrientationState* self, int mode);
}

int OrientationState::Initialize() {
    target = D_004432A0;
    scalarB0 = 5.0f;
    scalarB4 = 5.0f;
    active = 0;
    locked = 0;
    started = 0;
    changed = 1;
    state = 0;
    previousState = 0;
    elapsed = 0;
    return func_0013EC10(this, 4);
}

int OrientationState::Begin(void *actor)
{
    if (started) return 1;
    active = 0;
    elapsed = 0;
    state = 0;
    previousState = 0;
    locked = 0;
    changed = 1;
    Attach(actor);
    started = 1;
    return 1;
}

int OrientationState::SetTarget(EeS128 value, float firstScalar, float secondScalar, unsigned char lock) {
    target = value;
    elapsed = 0;
    active = 1;
    scalarB0 = firstScalar;
    scalarB4 = secondScalar;
    locked = lock;
    changed = 1;
    previousState = state;
    state = 1;
    return 1;
}

}
