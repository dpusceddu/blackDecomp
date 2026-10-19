// Shared PS2 storage/argument view from exact movement source; no engine layout dependency.
#ifndef BLACK_PS2_VECTOR_STORAGE_HPP
#define BLACK_PS2_VECTOR_STORAGE_HPP
#include "ps2/ee_types.h"
namespace BlackGame {
struct Vector4 { float x, y, z, w; };
// Vector values. The Xbox passes the address of an __m128 (copies are movaps) and reads single
// components through the float view of the same storage; the PS2 passes one 128-bit register
// (SN's 128-bit long long) that is spilled before any component access.
#define BLACK_ALIGNED16_BEFORE
#define BLACK_ALIGNED16 __attribute__((aligned(16)))
struct Position4 { float x, y, z, w; } BLACK_ALIGNED16;
typedef long long PositionArg;
typedef long long PositionResult;
typedef char SnPositionArgIs128[sizeof(PositionArg) == 16 ? 1 : -1];
inline void Store(Position4& to, PositionArg value) { *(PositionArg*)&to = value; }
inline PositionArg Load(const Position4& from) { return *(const PositionArg*)&from; }
inline PositionArg Load(const Vector4& from) { return *(const PositionArg*)&from; }
inline PositionArg ToArg(PositionResult value) { return value; }
inline Position4 Spill(PositionArg value) { Position4 p; Store(p, value); return p; }
#define PX(v) ((v).x)
#define PY(v) ((v).y)
#define PZ(v) ((v).z)
#define PW(v) ((v).w)
}
#endif
