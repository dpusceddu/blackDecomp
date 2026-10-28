#include "game/camera/pad_backend.hpp"

using namespace Graphics;

bool PadBackend::Attach(Controller* controller, unsigned port) {
    bool inRange = port < 2;
    bool valid = controller != 0;
    if (inRange) {
        if (!valid) goto fail;
        valid = controller->field_4 == state[port];
    }
    if (!valid || !inRange) return false;
    if (controllers[port]) return false;
    controllers[port] = controller;
    ++count;
    controller->Open((unsigned)this, port);
    return true;
fail:
    return false;
}

void PadBackend::Detach(Controller* controller, unsigned port) {
    bool valid = controller != 0;
    if (port < 2) {
        if (!valid) return;
        valid = controllers[port] == controller;
    }
    if (valid && port < 2) {
        controllers[port] = 0;
        --count;
        controller->Close();
    }
}

extern "C" {
int func_0029C708(const void*, void*);
int func_0029CA10(int);
int func_0029C940(int, void*);
int func_0029C868(int, void*);
int func_0029C810(int);
}

extern const Graphics::PadOpenParameters defaultPadParameters __asm__("D_004001D0");

static inline int* SlotAtByteOffset(int* array, unsigned offset) { return (int*)((char*)array + offset); }

void PadBackend::PollPort(int port) {
    unsigned int info[4];
    PadOpenParameters config = defaultPadParameters;
    switch (port) {
        case 0: config.port = 0; break;
        case 1: config.port = 1; break;
        default: return;
    }
    unsigned offset = port * sizeof(int);
    int* handle = SlotAtByteOffset(handles, offset);
    if (*handle < 0) {
        *handle = func_0029C708(&config, buffers[port]);
    } else {
        int status = func_0029CA10(*handle);
        if (status == 1) {
            int* mode = SlotAtByteOffset(state, offset);
            if (*mode == 0) {
                if (func_0029C940(*handle, info) > 0) {
                    if (info[0] == 0xFFFFFFFFu)
                        *mode = 4;
                    else if (info[0] == 0xFFFF0F00u)
                        *mode = 3;
                }
            } else {
                func_0029C868(*handle, packets[port]);
            }
        } else if (status == 0) {
            func_0029C810(*handle);
            *handle = -1;
            state[port] = 0;
        }
    }
}
