#ifndef BLACK_RENDERWARE_CORE_IMAGE_H
#define BLACK_RENDERWARE_CORE_IMAGE_H
#include "ps2/prelude.h"
/* VERIFIED accessed prefix: the matching pixel-release function uses flags, pixels and palette. Allocation extent is unknown. */
typedef struct RwColorPS2 { u8 red, green, blue, alpha; } RwColorPS2;
typedef struct RwImagePS2 {
    s32 flags, width, height, depth, stride;
    u8 *pixels;
    RwColorPS2 *palette;
} RwImagePS2;
typedef char RwImagePS2_stride_offset[(unsigned)&((RwImagePS2 *)0)->stride == 0x10 ? 1 : -1];
#endif
