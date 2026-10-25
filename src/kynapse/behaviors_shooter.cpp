#include "include_asm.h"

#include "kynapse/behaviors/shooter_angles.hpp"
namespace Kaim {

bool ShooterAgent::Init(ChildBuffers* config)
{
    provider = context->FindTarget(&gTargetClass);
    perception = context->FindPerception(&gPerceptionClass);
    yawControl = (Control*)bank->GetItem(&gBankKeyA);
    turnControl = (Control*)bank->GetItem(&gBankKeyB);
    aimControl = (AimControl*)bank->GetItem(&gBankKeyC);
    propertyA = context->actor->GetAuthoredProperty(&gKeyA);
    propertyB = context->actor->GetAuthoredProperty(&gKeyB);
    NameTable* names = GetNameTables();
    nameIndex = names->FindName("CShooterAgent::BotShootAtEnemy");
    nextTime = 0;
    aimDirection = gDefaultAim;
    fire = false;
    targetPosition = gOrigin;
    aimYaw = 0;
    if (!config)return false;
    {
        dangerousConeAngle = 0;
        target = 0;
        gunRange = gEngine->unit * 30.0f;
        maxInaccuracy = 0;
        interval = 0.5f;
        if (!ConfigureAll(config))goto failed;
        if (!Slot7())goto failed;
        if (!Slot8())goto failed;
        if (Slot9())goto succeeded;
    }
failed:return false;
succeeded:return true;
}
bool ShooterAgent::Update()
{
    bank->ClearActivation();
    if (targetDistance < gunRange && !perception->GetRecord(target)->hidden) {
        float now = gNow;
        if (nextTime < now) {
            ParameterTables* tables = (ParameterTables*)GetNameTables();
            if (tables->Consume(nameIndex, context->actor)) {
                ((ShooterAimResult*)this)->AimValue();
                tables->Accumulate(nameIndex, context->actor);
                nextTime = now + interval;
            }
        }
    } else {
        fire = false;
    }
    if (yawControl) {
        yawControl->Set(aimYaw);
    } else {
        TurnVector turn=TurnVector(aimYaw)-((ShooterActorAngles*)context->actor)->angles;
        if (turn.y > 3.0f)
            turnControl->Set(1.0f);
        else if (turn.y < -3.0f)
            turnControl->Set(-1.0f);
        else
            turnControl->Set(0);
    }
    aimControl->SetDirection(aimDirection);
    aimControl->SetFire(fire);
    targetPosition = context->actor->position;
    if (!fire) {
        targetPosition = target->position;
        if (provider->Query(&targetPosition))goto selected;
        return false;
    }
    return true;
selected:
    bank->Select(provider->id);
    return true;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_shooter", func_002D6CB0);
