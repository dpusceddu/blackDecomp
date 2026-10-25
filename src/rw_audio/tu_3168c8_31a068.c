#include "rw_audio/emitter.h"

#include "ps2/prototypes.h"

AudioPlayback *func_0031A068(AudioPlayback *playback,u32 selector,const f32 *value) {
    playback->emitter.priority=(u8)(*value*255.0f);
    return playback;
}
AudioPlayback *func_0031A0B8(AudioPlayback *playback,u32 selector,const f32 *value) {
    playback->emitter.blend=(u8)(*value*255.0f);
    return playback;
}
