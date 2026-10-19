#include "campaign/actor/camera.hpp"
#include "game/ai_vector.hpp"

namespace CampaignActor {
extern "C" {
extern void *D_0040F508;
void func_0011D158(void *, CameraController *);
}

void CameraController::Update()
{
    Child *child = GetChild();
    if (child) {
        child->Update();
        if (BlackGame::Y(BlackGame::Load(*(BlackGame::Position4 *)
                ((char *)Owner() + 0xA0))) < -100.0f) {
            child->Deactivate();
            Current() = -1;
            func_0011D158(D_0040F508, this);
        } else {
            if (child->active) {
                if (!Ready()) {
                    child->Deactivate();
                    Current() = -1;
                    func_0011D158(D_0040F508, this);
                } else {
                    GetChild()->Activate();
                }
            } else {
                if (Ready()) GetChild()->Activate();
            }
            Tick();
        }
    }
}

int CameraController::Choose(int n)
{
    if (ChildAt(n)->Available()) {
        Child *child = GetChild();
        if (!child) {
            Current() = n;
        } else {
            child->Deactivate();
            Current() = n;
        }
        return 1;
    }
    return 0;
}
void CameraController::SetTarget(BlackGame::PositionArg a, BlackGame::PositionArg b,
        float time, long kind)
{
    Child *child = GetChild();
    if (child) child->Target(a, b, time, kind);
}
}
