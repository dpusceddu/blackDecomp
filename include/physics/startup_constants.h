#ifndef BLACK_PHYSICS_STARTUP_CONSTANTS_H
#define BLACK_PHYSICS_STARTUP_CONSTANTS_H
#include "ps2/ee_types.h"

namespace PhysicsStartup {
// The original constructors access no fields. Only this storage extent is known.
struct StartupToken {} __attribute__((aligned(8)));
struct ConstantQuad { EeS128 value; };

// XYZ are assigned; the original transports the fourth stack lane unchanged.
// Both volatile scalar writes and the volatile native read preserve EE ordering.
struct VectorTemporary {
    volatile float x, y, z, unspecifiedW;
    VectorTemporary(float first, float second, float third)
        : x(first), y(second), z(third) {}
    operator EeS128() const { return *(const volatile EeS128*)this; }
} __attribute__((aligned(16)));

typedef char StartupTokenIs8[sizeof(StartupToken) == 8 ? 1 : -1];
typedef char ConstantQuadIs16[sizeof(ConstantQuad) == 16 ? 1 : -1];
}
#endif
