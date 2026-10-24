#ifndef BLACK_PHYSICS_RELOCATION_HPP
#define BLACK_PHYSICS_RELOCATION_HPP
#include "ps2/prelude.h"
// Prefix views used by the PS2 relocation callback; object extents remain unknown.
struct PhysicsRelocationContext {unsigned char unknown00[8];const void* originalBase;};
struct PhysicsRelocatedHandle {
 unsigned data;unsigned char unknown04[12];
 int Relocate(const PhysicsRelocationContext*) __asm__("func_0033B858");
};
extern "C" int func_00341B48(void*,const PhysicsRelocationContext*);
#endif
