#include "rw_audio/emitter.h"

#include "ps2/prototypes.h"

/* Narrow scalar property ABI; this compiler choice is scoped to these getters. */
typedef char PlaybackPointerIs32[sizeof(void*)==4?1:-1];
typedef char PlaybackFloatIs32[sizeof(f32)==4?1:-1];
typedef char PlaybackPriorityAt84[((int)&((AudioPlayback*)0)->emitter.priority==0x84)?1:-1];
typedef char PlaybackBlendAt87[((int)&((AudioPlayback*)0)->emitter.blend==0x87)?1:-1];
typedef char PlaybackGainAt85[((int)&((AudioPlayback*)0)->emitter.gain==0x85)?1:-1];
AudioPlayback *func_0031A090(AudioPlayback *playback,u32 selector,f32 *value) {
    *value=(f32)playback->emitter.priority/255.0f;
    return playback;
}
AudioPlayback *func_0031A0E0(AudioPlayback *playback,u32 selector,f32 *value) {
    *value=(f32)playback->emitter.blend/255.0f;
    return playback;
}
AudioPlayback *func_0031A470(AudioPlayback *playback,u32 selector,f32 *value) {
    *value=(f32)playback->emitter.gain/255.0f;
    return playback;
}
