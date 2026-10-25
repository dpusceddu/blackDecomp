#include "include_asm.h"

#include "physics/startup_constants.h"
// SN requires the sized extern before this initializer to select its GP form.
__asm__(".extern D_0040E8C8,8\n.extern D_0040E8D0,8");

using namespace PhysicsStartup;

extern "C" {
extern StartupToken D_0040E8C8, D_0040E8D0;
extern ConstantQuad D_0045CE30, D_0045CE40, D_0045CE50, D_0045CE60;
void* func_00100228(StartupToken*);
void* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}

extern "C" void func_00334120(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E8C8);
            func_00100258(&D_0040E8D0);
            VectorTemporary first(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 firstValue = first;
            VectorTemporary second(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 secondValue = second;
            VectorTemporary third(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 thirdValue = third;
            VectorTemporary fourth(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 fourthValue = fourth;
            D_0045CE30.value = firstValue;
            D_0045CE40.value = secondValue;
            D_0045CE50.value = thirdValue;
            D_0045CE60.value = fourthValue;
        } else {
            func_00100260(&D_0040E8D0, 2);
            func_00100230(&D_0040E8C8, 2);
        }
    }
}

struct Descriptor;

namespace ShapeViews {
struct ShapeType;
struct Matrix { EeS128 right, up, at, position; };
struct Shape {
    Matrix frame;
    float dimensions[3];
    float radius;
    unsigned int unknown50, unknown54;
    const ShapeType* type;
    unsigned int unknown5c;
};
struct Holder { Shape* shape; };
}
using namespace ShapeViews;
extern "C" {
extern void* D_0048F6F0[6];
extern Matrix* D_0040E438[];
extern Descriptor D_003D1368, D_003D1468, D_003D1430, D_003D14A0, D_003D13A0;
}


extern "C" int func_00334340()
{
    D_0048F6F0[0] = 0;
    D_0048F6F0[1] = &D_003D1468;
    D_0048F6F0[2] = &D_003D1430;
    D_0048F6F0[3] = &D_003D14A0;
    D_0048F6F0[4] = &D_003D13A0;
    D_0048F6F0[5] = &D_003D1368;
    return 1;
}

extern "C" void func_00334390() { func_00334120(1, 65535); }
extern "C" void func_003343B0() { func_00334120(0, 65535); }

extern "C" {
StartupToken D_0040E8C8 __attribute__((section(".sbss")));
StartupToken D_0040E8D0 __attribute__((section(".sbss")));
ConstantQuad D_0045CE30;
ConstantQuad D_0045CE40;
ConstantQuad D_0045CE50;
ConstantQuad D_0045CE60;
}

// Pointer-to-member layout control; callback contracts remain opaque.
struct OpaqueShape {
 int F_0033B8D0(...) const __asm__("func_0033B8D0");
 int F_0033BBD8(...) const __asm__("func_0033BBD8");
 int F_0033BBE0(...) const __asm__("func_0033BBE0");
 int F_0033C7C8(...) const __asm__("func_0033C7C8");
 int F_0033C918(...) const __asm__("func_0033C918");
 int F_0033D808(...) const __asm__("func_0033D808");
 int F_0033DA90(...) const __asm__("func_0033DA90");
 int F_0033DA98(...) const __asm__("func_0033DA98");
 int F_0033DAF8(...) const __asm__("func_0033DAF8");
 int F_0033DE40(...) const __asm__("func_0033DE40");
 int F_0033DF68(...) const __asm__("func_0033DF68");
 int F_0033E220(...) const __asm__("func_0033E220");
 int F_0033EB88(...) const __asm__("func_0033EB88");
 int F_0033EBD0(...) const __asm__("func_0033EBD0");
 int F_0033ECF8(...) const __asm__("func_0033ECF8");
 int F_0033EF60(...) const __asm__("func_0033EF60");
 int F_0033F2C8(...) const __asm__("func_0033F2C8");
 int F_0033F2D0(...) const __asm__("func_0033F2D0");
 int F_0033F328(...) const __asm__("func_0033F328");
 int F_0033FC38(...) const __asm__("func_0033FC38");
 int F_0033FF48(...) const __asm__("func_0033FF48");
 int F_003411C8(...) const __asm__("func_003411C8");
 int F_00341670(...) const __asm__("func_00341670");
};
typedef int (OpaqueShape::*OpaqueMethod)(...) const;
struct Descriptor { unsigned kind; OpaqueMethod bounds,query,core,support,last; const char* name; unsigned reserved0,reserved1; };
typedef char OpaqueMethodIs8[sizeof(OpaqueMethod)==8?1:-1];
typedef char DescriptorIs56[sizeof(Descriptor)==56?1:-1];
extern "C" {
extern const char D_0040A4C0[];
extern const char D_0040A4E0[];
extern const char D_0040A500[];
extern const char D_0040A520[];
extern const char D_0040A540[];
Descriptor D_003D1368 __attribute__((section(".data.shape_3d1368"))) = {5, &OpaqueShape::F_0033B8D0, 0, &OpaqueShape::F_0033BBE0, &OpaqueShape::F_0033BBD8, 0, D_0040A4C0, 0, 0};
Descriptor D_003D13A0 __attribute__((section(".data.shape_3d13a0"))) = {4, &OpaqueShape::F_0033D808, &OpaqueShape::F_0033DA90, &OpaqueShape::F_0033DA98, &OpaqueShape::F_0033C7C8, &OpaqueShape::F_0033C918, D_0040A4E0, 0, 0};
Descriptor D_003D1430 __attribute__((section(".data.shape_3d1430"))) = {2, &OpaqueShape::F_0033DAF8, &OpaqueShape::F_0033EB88, &OpaqueShape::F_0033DF68, &OpaqueShape::F_0033DE40, &OpaqueShape::F_0033E220, D_0040A500, 0, 0};
Descriptor D_003D1468 __attribute__((section(".data.shape_3d1468"))) = {1, &OpaqueShape::F_0033EBD0, &OpaqueShape::F_0033F2C8, &OpaqueShape::F_0033F2D0, &OpaqueShape::F_0033ECF8, &OpaqueShape::F_0033EF60, D_0040A520, 0, 0};
Descriptor D_003D14A0 __attribute__((section(".data.shape_3d14a0"))) = {3, &OpaqueShape::F_0033F328, &OpaqueShape::F_00341670, &OpaqueShape::F_0033FF48, &OpaqueShape::F_0033FC38, &OpaqueShape::F_003411C8, D_0040A540, 0, 0};
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334120", func_00334268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334120", func_003342D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334120", func_00334338);
