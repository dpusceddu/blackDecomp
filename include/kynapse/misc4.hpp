// Declarations of the Kynapse source module "misc4" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_MISC4_HPP
#define BLACK_KYNAPSE_MODULE_MISC4_HPP
#include "kynapse/compat.hpp"

// Small Kynapse accessors, reset routines and a name search (fourth batch).

extern "C" int __cdecl _stricmp(const char*, const char*);

struct Vec3 {
    float x, y, z;
};

struct PositionOwner {
    unsigned char unknown00[0x24];
    Vec3 position;
    Vec3* GetPosition();
};


struct PairOwner {
    unsigned char unknown00[0x30];
    int first;
    int second;
    bool GetPair(int* outFirst, int* outSecond);
};


struct SpanOwner {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Restart();   // slot 8
    unsigned char unknown04[0x18];
    int limit;
    unsigned char unknown20[8];
    int pending;

    bool Start();
};


struct RangeOwner {
    unsigned char unknown00[0x5c];
    float low;
    float high;
    void ResetRange();
};


struct Sampler {
    int Divide(int unused, int count, float value, int steps);
};

float __stdcall Kaim_ScaleSample(void*, int count, float value, int steps);


void __stdcall Kaim_NoOp(int);


struct NameList {
    unsigned char unknown00[0x0c];
    unsigned int count;
    unsigned char unknown10[4];
    const char** names;

    bool FindIndex(const char* name, unsigned int* index);
};


struct FlagOwner {
    unsigned char unknown00[0x14];
    bool flag;
    void SetFlag(bool value);
};


#endif
