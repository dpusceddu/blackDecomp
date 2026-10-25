#include "include_asm.h"

#include "game/camera/controller.hpp"
#include "game/ai_vector.hpp"

namespace ActorParts {
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
        if (Game::Y(Game::Load(*(Game::Position4 *)
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
void CameraController::SetTarget(Game::PositionArg a, Game::PositionArg b,
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

void CameraController::Configure(Game::PositionArg a, Game::PositionArg b,
        float firstTime, unsigned char firstFlag, signed char secondFlag,
        float secondTime, long data)
{
    Child *child = GetChild();
    if (child) child->V4(a, b, firstTime, firstFlag, secondFlag, secondTime, data);
}
}

#ifdef NON_MATCHING
// Unmatched: 0x140e48 scalar-to-VU temporary allocated V1 instead of final argument A1.
// Unmatched: 0x140ea8 original matrix return and shared Y-scratch address lifetime.
// Unmatched: 0x141008 VU normalization/copy helpers, register allocation and spill ordering.
// Unmatched: 0x141308 original pending-selection iterator and early-success return layout.
// Unmatched: 0x141460 small-data/byte-flag constant lifetime and return-tail scheduling.
// Unmatched: 0x1414a0 original narrow predicate and VU component-readback/spill ordering.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00140E48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00140EA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00141008);
#endif

#ifdef NON_MATCHING
#include "game/camera/controller.hpp"
#include "ps2/matrix.hpp"

// Unmatched: 0x141008 VU normalization copies and scalar/temporary scheduling.
// Unmatched: 0x140E48 scalar-to-VU scratch-register allocation (two operands).
// Unmatched: 0x140EA8 vector-component accessor lifetime and virtual matrix return.
// Unmatched: 0x141308 queued child-selection loop and success-return control flow.
// Unmatched: 0x141460 small-data byte access and duplicate boolean constant lifetimes.
// Unmatched: 0x1414A0 component-spill reuse and narrow-predicate control flow.
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00141000);

#ifdef NON_MATCHING
// Unmatched: 0x141008 signed-angle VU normalization, temporary spills and scheduling remain after original camera reconstruction.
#endif

