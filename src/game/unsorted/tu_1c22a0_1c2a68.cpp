#include "game/scratchpad_buffers.h"

extern "C" unsigned int func_001C2A68(ScratchpadBuffers* self) {
    self->currentIndex = (self->currentIndex + 1) % 2;
    return self->addresses[self->currentIndex];
}
