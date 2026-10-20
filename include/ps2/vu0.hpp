// Ported from the companion project (an unpublished companion project), PS2 branches only.
#ifndef BLACK_PS2_VU0_HPP
#define BLACK_PS2_VU0_HPP

// Vector operations of the movement code. On the PS2 the original keeps vectors in VU0 registers
// and writes each operation as inline assembly with named operands: SN's `j` constraint selects a
// VU0 register, the compiler assigns it (-mvu0-use-vf0-vfN) and moves quadwords between the GPR,
// memory and VU0 (qmtc2, qmfc2, lqc2, sqc2). Operand names are substituted textually, so they must
// not occur inside an opcode. The Xbox uses packed SSE intrinsics instead.
#include "ps2/vector_storage.hpp"
#include "ps2/vu0_math.h"

namespace BlackGame {
struct Point3 { float x, y, z; };
typedef PositionArg Vec;
// Builds a vector from three floats: the floats move to GPRs and are interleaved (pextlw twice);
// the compiler also keeps the quadword in a stack slot, as a spilled local would be.
static inline Vec Make3(float x, float y, float z)
{
    Vec t, r;
    asm("pextlw tmpv, zsrc, xsrc" : "=r tmpv" (t) : "r xsrc" (x), "r zsrc" (z));
    asm("pextlw resv, ysrc, tmpv" : "=r resv" (r) : "r ysrc" (y), "r tmpv" (t));
    return r;
}
static inline Vec WidenVec(const Point3& p)
{
    Position4 w;
    Store(w, Make3(p.x, p.y, p.z));
    return Load(w);
}
// dst.xyz = a.xyz - b.xyz
static inline Vec Sub3(Vec a, Vec b)
{
    return BkVuSubXYZ(a, b);
}
// dst.xyz = a.xyz + b.xyz
static inline Vec Add3(Vec a, Vec b)
{
    return BkVuAddXYZ(a, b);
}
// dst.xyz = a.xyz * b.xyz
static inline Vec Mul3(Vec a, Vec b)
{
    return BkVuMulXYZ(a, b);
}
// Squared length of the xyz part (the x lane of the result vector holds the sum).
static inline Vec SumSquares3(Vec v)
{
    Vec square = Mul3(v, v), one = BkVuOneX();
    return BkVuSumXYZ(square, one);
}
static inline float X(Vec v)
{
    float r;
    asm("qmfc2.ni resf, srcv" : "=r resf" (r) : "j srcv" (v));
    return r;
}
// The y and z lanes are read back through memory: the quadword is stored to a stack slot each time.
static inline float Y(Vec v) { Position4 p; Store(p, v); return p.y; }
static inline float Z(Vec v) { Position4 p; Store(p, v); return p.z; }
static inline void Assign3(Point3& to, Vec v) { to.x = X(v); to.y = Y(v); to.z = Z(v); }
// A copy of v with its y lane replaced by the x lane of `value`.
static inline Vec WithY(Vec v, Vec value)
{
    Vec r;
    asm("vmove.xyzw resv, srcv\n\tvaddx.y resv, vf0, valv" : "=&j resv" (r) : "j srcv" (v), "j valv" (value));
    return r;
}
// 0.0f as a vector: the integer zero moves from a GPR into a VU0 register.
static inline Vec ZeroVec() { int zero = 0; return (Vec)zero; }
// Scales the xyz lanes of v by the x lane of `scale` (a float moved from a GPR into a VU0 register).
static inline Vec Scale3(Vec v, Vec scale)
{
    return BkVuScaleXYZ(v, scale);
}
// A float's bits moved from a GPR into a VU0 register (qmtc2); the integer keeps the compiler from
// placing the constant in memory.
static inline Vec BitsVec(int bits) { return (Vec)bits; }
// |d| <= tolerance, written as the two comparisons the compiler emits.
static inline int Within(float d, float tolerance)
{
    int within = 0;
    if (d <= tolerance && -tolerance <= d) within = 1;
    return within;
}
static inline int NearlyEqual3(Vec a, Vec b, float tolerance)
{
    Vec d = Sub3(a, b);
    return Within(X(d), tolerance) && Within(Y(d), tolerance) && Within(Z(d), tolerance);
}
static inline float LengthSquared3(Vec v) { return X(SumSquares3(v)); }
static inline float Length3(Vec v)
{
    return X(BkVuSqrtX(SumSquares3(v)));
}
}

namespace BlackPS2 {
namespace VU0 {
typedef BlackGame::Vec Value;
// Keep the integer temporary's width explicit. An SF-mode asm output or a union
// bit cast can change allocation or retain a store in this SN compiler.
static inline float ReadXWord(Value value)
{
    int bits;
    float scalar;
    asm("qmfc2.ni resultv, inputv" : "=r resultv"(bits) : "j inputv"(value));
    asm("mtc1 bitsv, scalarf" : "=f scalarf"(scalar) : "r bitsv"(bits));
    return scalar;
}
static inline float Length3Word(Value value)
{
    return ReadXWord(BkVuSqrtX(BlackGame::SumSquares3(value)));
}
}
}
#endif
