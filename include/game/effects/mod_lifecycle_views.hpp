#ifndef BLACK_EFFECTS_MOD_LIFECYCLE_VIEWS_HPP
#define BLACK_EFFECTS_MOD_LIFECYCLE_VIEWS_HPP
#include "ps2/matrix.hpp"

namespace ModEffects {
typedef BlackPS2::VU0::Value Value;
struct Matrix { Value row[4]; };
class Entry;
// Accessed PS2 prefixes. These names do not identify the original C++ classes.
class Child {
public:
    Matrix world;
    void *resource;
    Entry *parent;
    float time, started;
    void Clear();
    int Initialize(void *, Entry *, const Matrix *, float);
    int Reset();
};
class Entry {
public:
    Child *children[8];
    Matrix world;
    char *resource;
    float started;
    unsigned char flags;
    int Initialize(const Matrix *, char *, unsigned char, float);
    int Release();
    void Detach();
    int Active();
    void Unlink(Child *);
};
struct Pair { void *record; unsigned char count, padding[3]; };
class RecordSet {
public:
    Pair pairs[2];
    void Clear();
    int Release();
    void Remove(void *);
};

// XYZ identity construction. Retail leaves the four W lanes unspecified.
static inline void IdentityXYZ(Matrix &matrix)
{
    Value a, b, c, d;
    asm("vsub.xyz av, vf0, vf0\n\t"
        "vsub.xyz bv, vf0, vf0\n\t"
        "vsub.xyz cv, vf0, vf0\n\t"
        "vsub.xyz dv, vf0, vf0\n\t"
        "vaddw.x av, vf0, vf0w\n\t"
        "vaddw.y bv, vf0, vf0w\n\t"
        "vaddw.z cv, vf0, vf0w"
        : "=j av"(a), "=j bv"(b), "=j cv"(c), "=j dv"(d));
    matrix.row[0] = a;
    matrix.row[1] = b;
    matrix.row[2] = c;
    matrix.row[3] = d;
}
}
#endif
