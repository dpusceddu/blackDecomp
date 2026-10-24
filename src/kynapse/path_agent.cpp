#include "include_asm.h"

#include "kynapse/path_agent.hpp"

namespace Kaim {

bool PathWayAgent::Init(ChildBuffers* config)
{
    paused = false;
    pauseEnd = 0;
    rotating = false;
    rotateTarget = 0;
    orienting = false;
    orientTarget = 0;
    reverse = false;
    if (config) {
        provider = context->FindTarget(&gTargetClass);
        pathways = ((Engine2*)gEngine)->FindRegistry(&gPathClass);
        if (Prepare()) {
            if (Validate()) {
                if (ConfigureAll(config)) {
                    PathWayAgent::Wrap();
                    limit = (Control*)provider->bank->GetItem(&gKeyForward);
                    strafe = (Control*)provider->bank->GetItem(&gKeyTurn);
                    forward = (Control*)bank->GetItem(&gKeyForward);
                    turn = (Control*)bank->GetItem(&gKeyTurn);
                    yawControl = (Control*)bank->GetItem(&gKeyYaw);
                    lookControl = (Control*)bank->GetItem(&gKeyLook);
                    crouch = (FlagControl*)bank->GetItem(&gKeyCrouch);
                    jump = (FlagControl*)bank->GetItem(&gKeyJump);
                    if (Refresh()) {
                        speedProperty = (SpeedProperty*)context->actor->GetAuthoredProperty(&gKeySpeed);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
} // namespace Kaim
