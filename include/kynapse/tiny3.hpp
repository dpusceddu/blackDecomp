// Declarations of the Kynapse source module "tiny3" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_TINY3_HPP
#define BLACK_KYNAPSE_MODULE_TINY3_HPP
#include "kynapse/compat.hpp"

// Small virtual methods and constructors of assorted classes.
namespace Kaim {

struct PathEdge {
    int index;
    struct NavigationGraph* graph;
    float GetAuthoredLength() const;
};

struct Probe {
    virtual void Slot0();
    virtual bool NoValue(int a, int b, int c, int* out);
    virtual bool AuthoredLength(int a, const PathEdge* edge, float* out);
};





// Two classes that reset a double-precision cursor to -1.
struct Cursor5C330 {
    char unknown00[8];
    double value;
    char unknown10[4];
    int a;
    int b;
    void Reset(int);
};



struct Cursor5C3A0 {
    char unknown00[8];
    double value;
    int a;
    void Reset(int);
};



}  // namespace Kaim

#endif
