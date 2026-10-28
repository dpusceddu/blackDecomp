#ifndef BLACK_ACTOR_ORIENTATION_HPP
#define BLACK_ACTOR_ORIENTATION_HPP

#include "ps2/ee_types.h"

namespace ActorParts {
// Provisional class identity. Begin verifies the named fields below; the opaque
// prefix includes other state and does not establish an allocation size or base.
struct OrientationState {
    unsigned char unknown00[0x90];
    int state;
    unsigned char unknown94[0xC];
    EeS128 target;
    // Scalar offsets are verified; their specific rate/limit meanings are UNVERIFIED.
    float scalarB0, scalarB4;
    unsigned char active, locked;
    unsigned char unknownBA[2];
    int elapsed;
    unsigned char started, changed;
    unsigned char unknownC2[2];
    int previousState;

    int Initialize();
    int Begin(void *actor);
    int SetTarget(EeS128 value, float firstScalar, float secondScalar, unsigned char lock);
    int Attach(void *actor) __asm__("func_0013EC38");
};
}
#endif
