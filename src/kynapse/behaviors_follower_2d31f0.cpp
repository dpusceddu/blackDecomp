#include "campaign/behaviors/follower.hpp"
extern "C" float func_002E1FD0(float,const BehaviorCampaign::Vec3*,void*,BehaviorCampaign::Actor*,int);
namespace BehaviorCampaign {
bool Follower::Init(ChildBuffers* config) {
    arrived=false;position=gOrigin;NameTable* names=GetNames();
    nameIndex=names->FindName("CFollowerAgent::ComputeRealDistance");nextTime=0;
    float t=gEngine->unit;limit=t;distance=t;angle=180.0f;followed=0;
    if (ConfigureAll(config)) {
        target=(TargetEntity*)((Registry*)context)->FindByClass(&gTargetClass);
        property=((PropertyOwner*)context->actor)->GetProperty(&gKey);
        if (!HasTarget())goto failed;
        if (HasName())goto succeeded;
    }
failed:return false;
succeeded:return true;
}
bool Follower::Update() {
    bank->ClearActivation();Refresh();
    if (followed && target) {if (target->Query(&position))goto selected;return false;}
    return false;
selected:bank->Select(target->id);return true;
    return false;
}
void Follower::ComputeDistance(void* observer) {
    arrived=false;float now=gNow;
    if (nextTime<now) {
        ParameterTables* tables=(ParameterTables*)GetNames();
        if (tables->Consume(nameIndex,context->actor)) {
            float half;
            if (property)half=property->value*0.5f;
            else {float radius=0.0f;if (gEngine)radius=gEngine->unit;half=radius*0.5f;}

            distance=func_002E1FD0(limit+half,&followed->position,observer,followed,2)-half;
            if (distance<=0.0f)distance=0.0f;
            arrived=true;tables->Accumulate(nameIndex,context->actor);nextTime=now+0.1f;
        }
    }
}
// Unmatched: Refresh retains equality-result, copy-constructor scheduling and target-reference differences.
}
