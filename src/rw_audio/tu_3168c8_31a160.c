#include "rw_audio/emitter.h"

#include "ps2/prototypes.h"

AudioPlayback *func_0031A160(AudioPlayback *playback,u32 selector,RwaVec3 *value) {
    *value=*(RwaVec3 *)playback->emitter.position;
    return playback;
}
AudioPlayback *func_0031A1E0(AudioPlayback *playback,u32 selector,RwaVec3 *value) {
    *value=*(RwaVec3 *)playback->emitter.velocity;
    return playback;
}
AudioPlayback *func_0031A260(AudioPlayback *playback,u32 selector,RwaVec3 *value) {
    *value=*(RwaVec3 *)playback->emitter.local_position;
    return playback;
}
AudioPlayback *func_0031A2E0(AudioPlayback *playback,u32 selector,RwaVec3 *value) {
    *value=*(RwaVec3 *)playback->emitter.local_velocity;
    return playback;
}
