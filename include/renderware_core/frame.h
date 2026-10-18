#ifndef BLACK_RENDERWARE_CORE_FRAME_H
#define BLACK_RENDERWARE_CORE_FRAME_H
#include "auto/prelude.h"
#include "renderware_core/math.h"
/* UNVERIFIED PS2 frame prefix. Matrix rows require EE quadword alignment. */
typedef struct RwFramePS2 RwFramePS2;
typedef struct RwObjectLinkPS2 {struct RwObjectLinkPS2 *next,*previous;} RwObjectLinkPS2;
struct RwFramePS2 {
 u8 type,subtype,flags,private_flags; RwFramePS2 *parent;u32 links[2];
 RwMatrixPS2 modelling,world;RwObjectLinkPS2 objects;RwFramePS2 *child,*sibling,*root;
};
typedef char RwFramePS2_objects_offset[(unsigned)&((RwFramePS2 *)0)->objects==0x90?1:-1];
#endif
