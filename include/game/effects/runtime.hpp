#ifndef BLACK_EFFECTS_MOD_LIFECYCLE_VIEWS_HPP
#define BLACK_EFFECTS_MOD_LIFECYCLE_VIEWS_HPP
#include "ps2/matrix.hpp"
#include "game/effects/random_state.h"
#include "game/effects/vu_math.h"

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

// Remaining views are PS2 instruction evidence only. No native source control
// yet proves these semantic names, original classes or complete allocations.
struct MuzzleConfig {
    unsigned char unknown00[0x20];
    void *textures[3];
    unsigned color;
    int alpha[3];
    float size[3], alternateHeight;
    float extent;
    unsigned char quantized;
};
struct MuzzleResource { unsigned char unknown00[0x10]; MuzzleConfig *config; };
struct Muzzle {
    unsigned char unknown00[0xc0];
    float rotation;
    MuzzleResource *resource;
    signed char variant, phase;
};
// This is an 80-entry attachment manager, not the generic 0x300-entry pool.
struct AttachmentManager {
    Entry entries[80];
    void *actors[80];
    int kinds[80], modes[80];
    unsigned char unknown26c0[0x3440-0x26c0];
    unsigned short *indices;
    unsigned char unknown3444[4];
    short activeCount;
    unsigned char unknown344a[6];
    int pending;
    float previousTime;
};
struct TimedTransformSlot {
    int tag;
    unsigned char unknown04[0xc];
    Matrix input, output;
    float offset, rate, started, expires;
    float fade, unknowna4, alpha, unknownac;
};
struct TimedTransformBank { TimedTransformSlot slots[8]; };
typedef char MuzzleResourceC4[(unsigned)&((Muzzle*)0)->resource==0xc4?1:-1];
typedef char AttachmentActors2300[(unsigned)&((AttachmentManager*)0)->actors==0x2300?1:-1];
typedef char AttachmentIndices3440[(unsigned)&((AttachmentManager*)0)->indices==0x3440?1:-1];
typedef char TimedTransformStrideB0[sizeof(TimedTransformSlot)==0xb0?1:-1];
}
#endif
