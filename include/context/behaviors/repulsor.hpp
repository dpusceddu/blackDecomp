#ifndef BLACK_CONTEXT_BEHAVIORS_REPULSOR_HPP
#define BLACK_CONTEXT_BEHAVIORS_REPULSOR_HPP
#include "context/behaviors/avoidance_engine.hpp"
#include "ps2/kynapse/list.hpp"
namespace KaimAvoidance {
struct Object : Kaim::PolyRoot {virtual ~Object() {} };
struct Steering : Object {
    RouteFollower* route;
    float width,radius,height;
    struct RequestedSpeed {float x;RequestedSpeed() {}} target;
    Vec3 targetPosition;
    Vec3 orientation;
    unsigned char frameMarker;
    unsigned char unknown31[3];
    unsigned int reservedFrame;
    unsigned char contactActive;
    unsigned char unknown38[3];
    Entity* contactEntity;
    Vec3 contactOffset;
    float contactTime;
    unsigned int contactCount;
    Entity* contacts[25];
    Vec3 selectedDirection;
    unsigned char graceActive;
    unsigned char unknownc5[3];
    float graceDeadline;
    float attractionRatio, graceDuration, minimumTime, maximumTime;
    float slowSpeedFactor, verySlowSpeedFactor, detectionDistanceSquared;
    float alignmentThreshold, slowdownTime;
    Steering(RouteFollower* source) __asm__("func_003055E0");
    virtual const ClassDefinition* GetDefinition();
    virtual void GenerateMove(const Vec3* goal, Movement* move) __asm__("func_00306448");
    virtual unsigned char Configure(const Property* property) __asm__("func_003057E8");
    virtual void ResetFrame() {}
    virtual void RefreshTrackedActors() {}
    void PublishMove(Movement* move) __asm__("func_00306688");
    unsigned char SelectDirection(const Vec3* goal) __asm__("func_00305FD8");
    unsigned char PredictContacts(const Vec3* goal) __asm__("func_003059F0");
    unsigned char SteeringContactTimes(const Vec3* velocity,Vec3 displacement,
        const float* radius,float* first,float* last) __asm__("func_00306538");
};

}
#endif
