#ifndef BLACK_RENDERWARE_CORE_IMAGE_GLOBALS_H
#define BLACK_RENDERWARE_CORE_IMAGE_GLOBALS_H
#include "rw_core/image.h"
/* UNVERIFIED layout; image plugin registration reserves 0x220 PS2 bytes. */
typedef struct RwImageFormatPS2 { u8 prefix[0x30]; struct RwImageFormatPS2 *next; } RwImageFormatPS2;
typedef struct RwImageGlobalsPS2 {
 void *images; char *path; u32 path_capacity;
 u8 gamma[256], inverse_gamma[256]; f32 gamma_value;
 char *scratch; u32 scratch_capacity; void *format_pool; RwImageFormatPS2 *formats;
} RwImageGlobalsPS2;
typedef char RwImageGlobalsPS2_size[sizeof(RwImageGlobalsPS2)==0x220?1:-1];
#endif
