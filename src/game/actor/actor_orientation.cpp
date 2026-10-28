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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/actor_orientation", func_0013DC00);

}
