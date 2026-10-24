#include "game/camera/controller.hpp"
#include "game/ai_vector.hpp"

namespace CampaignActor {
extern "C" {
extern void *D_0040F508;
void func_0011D158(void *, CameraController *);
void func_0013EE28(CameraController *);
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

int CameraController::Clear()
{
    Child **child = &ChildAt(0);
    int count = 8;
    do {
        count--;
        (*child++)->V3();
    } while (count >= 0);
    Current() = -1;
    func_0013EE28(this);
    return 1;
}

void CameraController::Configure(BlackGame::PositionArg a, BlackGame::PositionArg b,
        float firstTime, unsigned char firstFlag, signed char secondFlag,
        float secondTime, long data)
{
    Child *child = GetChild();
    if (child) child->V4(a, b, firstTime, firstFlag, secondFlag, secondTime, data);
}
}
