#include "context/behaviors/repulsor.hpp"

namespace KaimAvoidance {
Steering::Steering(RouteFollower* source)
    : route(source),width(0),radius(0),height(0),target(),targetPosition(0,0,0),orientation(0,0,0),
      frameMarker(0),reservedFrame(0),contactActive(0),contactEntity(0),
      contactOffset(0,0,0),contactTime(0),contactCount(0),selectedDirection(0,0,0),
      graceActive(0),graceDeadline(0),attractionRatio(.5f),graceDuration(.1f),
      minimumTime(-1),maximumTime(10),slowSpeedFactor(.5f),verySlowSpeedFactor(.25f),
      detectionDistanceSquared(25),alignmentThreshold(.7f),slowdownTime(5)
{
    memset(contacts,0,sizeof(contacts));
    if (route) {
        ScalarProperty* p=RouteEntity(route)->GetAuthoredProperty(&obstacleWidthKey);
        if (p) { width=p->value; if (width==0) width=WorldUnits(); } else width=WorldUnits();
        p=RouteEntity(route)->GetAuthoredProperty(&obstacleHeightKey); if (p) height=p->value;
        p=RouteEntity(route)->GetAuthoredProperty(&movementSpeedKey); if (p) target.x=p->value;
    } else width=WorldUnits();
}
unsigned char Steering::Configure(const Property* property) {
    if(!_stricmp(property->GetKey(),"DynDelayTime")) {graceDuration=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"DynRatioAttrRep")) {attractionRatio=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"TimeMinTrigger")) {minimumTime=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"TimeMaxTrigger")) {maximumTime=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"SlowSpeedFactor")) {slowSpeedFactor=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"VerySlowSpeedFactor")) {verySlowSpeedFactor=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"DetectionDistanceRatio")) {float value=(float)atof(property->GetText()); detectionDistanceSquared=value*value;return 1;}
    return 0;
}
// Unmatched: PredictContacts (1508 B) and SelectDirection (972 B) require the original vector temporary and iterator lifetimes.
// Unmatched: SteeringContactTimes (336 B) differs in coefficient scheduling and float-register allocation.
void Steering::PublishMove(Movement* move) {
    Entity* self=RouteEntity(route);if(!self)return;
    float alignment=self->forward.Dot(selectedDirection);
    float factor;
    if(alignment>alignmentThreshold) {
        if(contactTime<slowdownTime) {move->direction=selectedDirection;move->speed=target.x;return;}
        factor=slowSpeedFactor;
    } else {
        move->direction=selectedDirection;
        if(contactTime<slowdownTime)factor=verySlowSpeedFactor;else factor=slowSpeedFactor;
    }
    move->speed=target.x*factor;
}
void Steering::GenerateMove(const Vec3* goal,Movement* move)
{
    PredictContacts(goal);
    Vec3 originalForward(RouteEntity(route)->forward);
    if (contactActive) {
        SelectDirection(goal); PublishMove(move);
        float deadline=gameTime+graceDuration;
        graceActive=1; graceDeadline=deadline;
    } else if (graceActive==1) {
        PublishMove(move); if (graceDeadline<gameTime) graceActive=0;
    } else GenerateRouteMove(route,move,goal);
}
}
