#ifndef BLACK_PS2_MATRIX_HPP
#define BLACK_PS2_MATRIX_HPP
#include "ps2/vu0.hpp"

namespace BlackPS2 {
namespace VU0 {
// Four 16-byte basis/translation values. This is storage, not an engine/RwMatrix class.
struct Matrix4 { Value basis[4]; } __attribute__((aligned(16)));
typedef char MatrixStorageIs64[sizeof(Matrix4) == 64 ? 1 : -1];
typedef char MatrixStorageIsAligned16[__alignof__(Matrix4) == 16 ? 1 : -1];

// Only xyz is defined. The fourth lane can hold flags or unrelated payloads.
static inline Value TransformDirection(const Value *basis, Value point)
{
    Value result;
    asm("vmulax.xyz ACC, basisx, pointvx\n\t"
        "vmadday.xyz ACC, basisy, pointvy\n\t"
        "vmaddz.xyz outputv, basisz, pointvz"
        : "=j outputv"(result)
        : "j basisx"(basis[0]), "j basisy"(basis[1]),
          "j basisz"(basis[2]), "j pointv"(point));
    return result;
}
// Vector-first expression form. Operand order is part of the SN inline contract:
// the actor matrix-return consumer uses this form, while existing callers use
// the basis-first form above.
static inline Value TransformDirection(Value point, const Value *basis)
{
    Value result;
    asm("vmulax.xyz ACC, basisx, pointvx\n\t"
        "vmadday.xyz ACC, basisy, pointvy\n\t"
        "vmaddz.xyz outputv, basisz, pointvz"
        : "=j outputv"(result)
        : "j pointv"(point), "j basisx"(basis[0]),
          "j basisy"(basis[1]), "j basisz"(basis[2]));
    return result;
}
static inline Value TransformPoint(const Value *basis, Value point)
{
    Value result;
    asm("vmulax.xyz ACC, basisx, pointvx\n\t"
        "vmadday.xyz ACC, basisy, pointvy\n\t"
        "vmaddaz.xyz ACC, basisz, pointvz\n\t"
        "vmaddw.xyz outputv, positionv, vf0w"
        : "=j outputv"(result)
        : "j basisx"(basis[0]), "j basisy"(basis[1]),
          "j basisz"(basis[2]), "j positionv"(basis[3]), "j pointv"(point));
    return result;
}
}
}
#endif
