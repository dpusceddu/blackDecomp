#ifndef BLACK_RENDERWARE_CORE_MATH_H
#define BLACK_RENDERWARE_CORE_MATH_H
#include "ps2/prelude.h"
/* VERIFIED accessed fields: matching flag reset uses the fourth integer lane.
   Matrix arithmetic fields remain PS2 access views; the tolerance copy matches. */
typedef struct RwVector3PS2 {f32 x,y,z;} RwVector3PS2;
typedef union RwMatrixPS2 {
 s128 rows[4];
 struct {RwVector3PS2 right;u32 flags;RwVector3PS2 up;u32 pad1;RwVector3PS2 at;u32 pad2;RwVector3PS2 position;u32 pad3;} components;
} RwMatrixPS2;
typedef struct RwMatrixTolerancePS2 {f32 normal,orthogonal,identity;} RwMatrixTolerancePS2;
#endif
