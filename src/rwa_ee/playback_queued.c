#include "rwa_ee/voice.h"

void *func_0031CCE8(void *state, s32 *queued) {
    s32 bytes = M2C_FIELD(state, s32 *, 0x70);
    if (bytes) {
        *queued = 1;
        return state;
    }
    *queued = 0;
    return 0;
}
