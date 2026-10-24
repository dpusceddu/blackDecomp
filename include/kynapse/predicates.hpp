// Declarations of the Kynapse source module "predicates" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_PREDICATES_HPP
#define BLACK_KYNAPSE_MODULE_PREDICATES_HPP
#include "kynapse/compat.hpp"

// Small Kynapse predicates and accessors on behaviour and parameter objects.
// Fields keep their offsets; unrecovered owners are placeholder structs.

#define PAD(n) unsigned char unknown##n[n]

struct IsSet24 {
    unsigned char unknown00[0x24];
    int value;
    bool IsSet() const;
};


struct IsSet0C {
    unsigned char unknown00[0x0c];
    int value;
    bool IsSet() const;
};


struct IsSet10 {
    unsigned char unknown00[0x10];
    int value;
    bool IsSet() const;
};


struct IsSet50 {
    unsigned char unknown00[0x50];
    int value;
    bool IsSet() const;
};


struct IsSet15C {
    unsigned char unknown00[0x15c];
    int value;
    bool IsSet() const;
};


struct IsSet160 {
    unsigned char unknown00[0x160];
    int value;
    bool IsSet() const;
};


struct HasId68 {
    unsigned char unknown00[0x68];
    int id;
    bool HasId() const;
};


struct HasId2C {
    unsigned char unknown00[0x2c];
    int id;
    bool HasId() const;
};


struct BothIds28 {
    unsigned char unknown00[0x28];
    int first;
    unsigned char unknown2c[4];
    int second;
    bool HasBoth() const;
};


struct BothIds60 {
    unsigned char unknown00[0x60];
    int first;
    unsigned char unknown64[8];
    int second;
    bool HasBoth() const;
};


struct Chain50 {
    unsigned char unknown00[0x4c];
    int second;
    int first;
    bool IsSet() const;
};


struct Chain10 {
    unsigned char unknown00[0x0c];
    int second;
    int first;
    bool IsSet() const;
};


struct Chain0C {
    unsigned char unknown00[0x0c];
    int first;
    unsigned char unknown10[4];
    int second;
    bool IsSet() const;
};


struct Either54 {
    unsigned char unknown00[0x54];
    int a;
    int b;
    int c;
    bool IsSet() const;
};


struct Linked38 {
    unsigned char unknown00[4];
    int value;
};
struct HasLink {
    unsigned char unknown00[0x38];
    Linked38* link;
    bool IsSet() const;
};


struct Active4B140 {
    unsigned char unknown00[0x10];
    int enabled;
    unsigned char unknown14[0x0c];
    int a;
    unsigned char unknown24[8];
    int b;
    bool IsActive() const;
};


struct Flags5F550 {
    unsigned char unknown00[0xb0];
    bool value;
    unsigned char unknownb1;
    bool blocked;
    unsigned char unknownb3;
    bool enabled;
    bool Get() const;
};


struct Exclusive5E890 {
    unsigned char unknown00[0x168];
    int first;
    int second;
    bool HasExactlyOne() const;
};


struct Exclusive5E8C0 {
    unsigned char unknown00[0x170];
    int first;
    int second;
    bool HasExactlyOne() const;
};


struct Budget68BA0 {
    unsigned char unknown00[8];
    int limit;
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    bool Fits() const;
};


struct Constant4B160 {
    bool Yes(int) const;
};
bool __stdcall Constant4B160_Yes(int);


#endif
