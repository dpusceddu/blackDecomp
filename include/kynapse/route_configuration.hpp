#ifndef BLACK_ROUTE_CONFIGURATION_HPP
#define BLACK_ROUTE_CONFIGURATION_HPP
#include "kynapse/compat.hpp"
// Guarded model: complete type not verified by a linked matching function.
namespace Kaim {

struct ChildBuffers {
    const char* GetSecond() const;
    const char* GetValue() const;
};

struct WorldUnit { unsigned char unknown00[0xc]; float unit; };
extern WorldUnit* gEngine;
float Kaim_WorldUnit();
float Degrees_WrapUnsigned(float degrees);
bool Kaim_IsHiddenName(ChildBuffers* property);
void* FindValue61D30(const char* name);
void* FindValue61E40(const char* name);
void* FindValue61F50(const char* name);
void* FindValue62060(const char* name);

struct Avoidance {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual bool Configure(ChildBuffers* property);   // slot 3
};

struct RouteTable {
    unsigned char unknown00[0x28];
    void SetMaxPathSize(long size);
};

struct RouteConfigurationBase { virtual void Slot0(); };
struct RouteFollowerConfig : RouteConfigurationBase {
    virtual void Slot1(); virtual void Slot2(); virtual void Slot3(); virtual void Slot4();
    virtual void Slot5(); virtual void Slot6(); virtual void Slot7(); virtual void Slot8();
    virtual void Slot9(); virtual void Slot10(); virtual void Slot11(); virtual void Slot12();
    virtual bool SetGraph(const char* name);          // slot 13
    unsigned char unknown04[0x0c];
    unsigned int recordCount;
    unsigned char unknown14[0x10];
    float distMinNewGoal;
    float distGoal;
    float distStop;
    float distSlowDown;
    float distGoalSlowDown;
    float maxDeltaHeight;
    unsigned char unknown3c[4];
    float distSubgoalMax;
    float maxDeltaAngle;
    float maxYawSpeed;
    int maxSubgoals;
    float holeHeight;
    float holeDistToEdge;
    float widthRatio;
    float cpuPrudence;
    bool avoidCpuPeaks;
    bool updateTorsoRotate;
    bool yawSmoothing;
    unsigned char unknown63[9];
    RouteTable route;
    void* stopPolicy;
    void* vertexPolicy;
    void* canGoPolicy;
    void* nextSubgoalPolicy;
    void* moveModePolicy;
    void* simpleMovePolicy;
    void* complexMovePolicy;
    unsigned char unknownb0[0xfc];
    unsigned char* records;
    Avoidance* avoidance;

    bool Configure(ChildBuffers* property);
};


}
#endif
