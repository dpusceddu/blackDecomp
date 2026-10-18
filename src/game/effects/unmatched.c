// Unmatched: 0x1b89c8: 0x110-byte simulation records; VU I-register rotation and stack matrices.
// Unmatched: 0x1b9b58: twenty-fragment geometry/UV tables, 128-bit values and 0x3b0-byte frame.
// Unmatched: 0x1bb190: sixteen-point fracture workspaces, vector-valued returns and shared edge tables.
#ifdef NONMATCHING
#include "game/effects/geometry.h"
extern "C" void func_001B89C8(void *);
extern "C" void func_001B9B58(void *,BkEffectGeometryPS2 *,s128,s128,u32,u32,u32,f32);
extern "C" void func_001BB190(void *,BkEffectGeometryPS2 *,s128,s128,u32,u32,u32,f32);
#endif
