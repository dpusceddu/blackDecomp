#include "game/ai_movement_modes_decls.hpp"
namespace BlackGame {
extern bool MotionSubmit(MovementModeBase*,PositionArg,float,bool,float) __asm__("func_001917A0");

void RouteMode::Update()
{
    UpdateStallRecovery();
    if (active) active->Pump();
    if (alternate) alternate->Pump();
    int phase = state;
    if (phase == 1 || phase == 7 || phase == 4) {
        if (state == 4 && resubmit && active && alternate) {
            bool activeDone = active->kind == 9;
            if (activeDone) {
                bool alternateDone = alternate->kind == 9;
                if (alternateDone) {
                    JoinCompletedRoute(this, alternate);
                    alternate = 0;
                    resubmit = 0;
                }
            }
        }
        while (StepPhase()) {}
        Controller& controller = brain->controller;
        if (controller.routePending && (state == 7 || state == 1))
            MotionSubmit(this,Load(target),controller.speed,false,0.1f);
    } else if (phase == 8 && !arrived) {
        bool pendingAlternate = alternate && !resubmit;
        if (IsMovementObstructed(&brain->controller, Load(target), true)) {
            state = 2;
            ReleaseMovementRoute(this);
        } else {
            PositionArg goal = Load(target);
            float speed = FamilySpeed(&brain->familyRef);
            if (MotionSubmit(this,goal,speed,!pendingAlternate,0.1f)) arrived = 1;
        }
    }
}
}
