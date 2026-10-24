#ifndef BLACK_RENDERWARE_CORE_CAMERA_H
#define BLACK_RENDERWARE_CORE_CAMERA_H
#include "ps2/prelude.h"
/* UNVERIFIED PS2 camera prefix, offsets checked against creation and update. */
typedef struct RwCameraPS2 {
 u8 type,subtype,flags,private_flags;void *frame;u32 links[2];
 void *sync; s32 projection; void *begin_update,*end_update;
 f32 matrix[16];void *color_raster,*depth_raster;
 f32 view_window[2],reciprocal_window[2],view_offset[2];
 f32 near_plane,far_plane,fog_plane,z_scale,z_shift;
} RwCameraPS2;
typedef char RwCameraPS2_raster_offset[(unsigned)&((RwCameraPS2 *)0)->color_raster == 0x60?1:-1];
#endif
