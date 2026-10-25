#ifndef RWA_EE_EMITTER_H
#define RWA_EE_EMITTER_H
#include "rw_audio/sound.h"
/* Inferred names; these are PS2 access prefixes, not allocation sizes. */
typedef struct RwaEmitter RwaEmitter;
struct RwaEmitter {
    RwaEmitter *next, *previous;
    f32 position[3],velocity[3],local_position[3],local_velocity[3];
    void *handle;
    RwaSound *sound;
    void *user;
    u32 position_bytes,start_bytes,last_tick;
    f32 pitch,min_distance,max_distance;
    u8 priority,gain,field5e,blend,level,channels,flags;
    s8 pan;
};
/* Accessed prefix of a playback allocation, which is only partly audited: the emitter sits at 0x28. */
typedef struct AudioPlayback {u8 unknown00[0x28];RwaEmitter emitter;} AudioPlayback;
typedef struct RwaPoolBlock {struct RwaPoolBlock *next,*previous;u8 bits[1];} RwaPoolBlock;
typedef struct RwaPool {
    u32 stride,count,bitmap_bytes,alignment;
    RwaPoolBlock blocks;
} RwaPool;
typedef struct RwaVec3 {f32 x,y,z;} RwaVec3;
typedef struct RwaListener {u8 prefix[0x48];RwaVec3 position,velocity,right,up,forward;} RwaListener;
#endif
