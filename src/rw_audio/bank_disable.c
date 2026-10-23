#include "rw_audio/sound.h"

extern void func_00315EE8(RwaSound *, s32);

RwaSound *func_00313F90(RwaSound *sound, s32 argument) {
    sound->driver->enable(sound, argument, 0);
    func_00315EE8(sound, 0);
    return sound;
}
