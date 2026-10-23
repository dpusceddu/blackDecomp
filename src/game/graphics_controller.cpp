#include "campaign/graphics/controller.hpp"

bool CampaignGraphics::Controller::Open(unsigned int backendHandle, unsigned int portIndex) {
    if (!backendHandle || portIndex >= 2) return false;
    backend = backendHandle;
    port = portIndex;
    return true;
}
