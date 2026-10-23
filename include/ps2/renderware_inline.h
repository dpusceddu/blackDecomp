#ifndef BLACK_PS2_RENDERWARE_INLINE_H
#define BLACK_PS2_RENDERWARE_INLINE_H
#include "rw_core/math.h"
#include "rw_core/image.h"

/* Exact-backed accessed fields only; these helpers do not verify entire SDK classes. */
static inline RwMatrixPS2 *RwInvalidateMatrixFlagsPS2(RwMatrixPS2 *matrix)
{
    matrix->components.flags &= 0xFFFDFFFC;
    return matrix;
}
static inline void RwCopyMatrixTolerancePS2(RwMatrixTolerancePS2 *to,
        const RwMatrixTolerancePS2 *from)
{
    *to = *from;
}
static inline RwImagePS2 *RwReleaseImagePixelsPS2(RwImagePS2 *image, void (*release)(void *))
{
    release(image->pixels);
    image->pixels = 0;
    image->palette = 0;
    image->flags &= ~1;
    return image;
}
#endif
