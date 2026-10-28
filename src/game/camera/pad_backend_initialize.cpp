#include "game/camera/pad_backend.hpp"

extern "C" {
void* func_0035C6EC(void*, int, unsigned int);
int func_0029B558();
int func_0029C6C8(int);
int func_0029C708(const void*, void*);
}

// The packed 32-byte copy and port offset are confirmed; other field meanings are UNVERIFIED.
struct PadOpenParameters {
    int unknown00;
    int port;
    EeU8 unknown08[24];
} __attribute__((packed));

// Shared with PollPort; its native storage remains assembly-backed.
extern const PadOpenParameters defaultPadParameters __asm__("D_004001D0");

using namespace Graphics;

void PadBackend::Initialize(unsigned single) {
    PadOpenParameters config = defaultPadParameters;
    for (int i = 1; i >= 0; --i) controllers[i] = 0;
    singlePort = single;
    EeU8* buffer = buffers[0];
    count = 0;
    EeU8 (*data)[32] = packets;
    feedback = 0;
    int* current = state;
    int i = 1;
    do {
        *current = 0;
        func_0035C6EC(data, 0, 32);
        ++data;
        --i;
        ++current;
    } while (i >= 0);
    func_0029B558();
    func_0029C6C8(0);
    handles[0] = func_0029C708(&config, buffer);
    if (singlePort) {
        handles[1] = -1;
    } else {
        config.port = 1;
        handles[1] = func_0029C708(&config, buffers[1]);
    }
    lastMode = -1;
}
