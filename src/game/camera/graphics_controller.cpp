#include "include_asm.h"

#include "game/camera/pad.hpp"

bool Graphics::Controller::Open(unsigned int backendHandle, unsigned int portIndex) {
    if (!backendHandle || portIndex >= 2) return false;
    backend = backendHandle;
    port = portIndex;
    return true;
}
