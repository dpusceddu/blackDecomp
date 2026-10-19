#ifndef BLACK_KYNAPSE_PATH_AGENT_HPP
#define BLACK_KYNAPSE_PATH_AGENT_HPP
#include "kynapse/compat.hpp"

// PS2 path-following views. An inherited interface keeps the vptr before the data.
namespace Kaim {

struct Vec3 {
    float x, y, z;
};
extern Vec3 gOrigin;
static const float kDefaultFloat=0.0f;
extern float gNow;

struct Engine {
    unsigned char unknown00[0x0c];
    float unit;
};
extern Engine* gEngine;

struct PointerBank;
struct ActionBank {
    virtual void Slot0();
    virtual void Select(PointerBank* other);   // slot 1
    void ClearActivation();
    void* GetItem(const void* key);
};

struct ChildBuffers;

// Actor state read by behaviours.
struct Actor {
    unsigned char unknown00[0x3c];
    Vec3 angles;
    unsigned char unknown48[0x0c];
    float speed;
    void* GetAuthoredProperty(const void* key);
};

struct EntityInterfaceBase { virtual void Slot0(); };
struct TargetEntity : EntityInterfaceBase {
    unsigned char unknown04[4];
    ActionBank* bank;
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual bool Query(void* data);     // slot 6
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual bool IsActive();            // slot 10
};

struct Context {
    unsigned char unknown00[0x14];
    Actor* actor;
    TargetEntity* FindTarget(struct ClassInfo* wanted);
};
struct ClassInfo;
extern ClassInfo gTargetClass;
extern ClassInfo gPathClass;

struct PathWayRegistry;
struct Engine2 {
    PathWayRegistry* FindRegistry(ClassInfo* wanted);
};

struct Control {
    unsigned char unknown00[4];
    bool active;
    unsigned char unknown05[3];
    float value;
};
struct FlagControl {
    unsigned char unknown00[4];
    bool active;
    unsigned char unknown05[3];
    bool value;
};
struct SpeedProperty {
    unsigned char unknown00[4];
    float value;
};

extern const unsigned char gKeyForward;
extern const unsigned char gKeyTurn;
extern const unsigned char gKeyYaw;
extern const unsigned char gKeyLook;
extern const unsigned char gKeyCrouch;
extern const unsigned char gKeyJump;
extern const unsigned char gKeySpeed;

struct PathPoint {
    unsigned char unknown00[4];
    Vec3 position;
    char mode[8];
    char command[0x40];
};
struct PathWay {
    unsigned char unknown00[4];
    PathPoint* points;
    unsigned int count;
    bool loops;
};

extern "C" int __cdecl sscanf(const char*, const char*, ...);
Vec3* Vector3_Subtract(Vec3* output, const Vec3* a, const Vec3* b);

struct BehaviorObjectBase { virtual ~BehaviorObjectBase() {} };
struct Behavior : BehaviorObjectBase {
    virtual ~Behavior();
    virtual bool Init(ChildBuffers* config);   // slot 1
    bool ConfigureAll(ChildBuffers* config);
    ActionBank* bank;
    Context* context;
};

struct PathWayAgent : Behavior {
    TargetEntity* provider;
    PathWayRegistry* pathways;
    SpeedProperty* speedProperty;
    Control* forward;
    Control* turn;
    FlagControl* crouch;
    FlagControl* jump;
    Control* yawControl;
    Control* lookControl;
    Control* limit;
    Control* strafe;
    PathWay* pathWay;
    unsigned int pointIndex;
    bool waiting;
    bool finished;
    bool reverse;
    bool paused;
    float pauseEnd;
    bool rotating;
    unsigned char unknown49[3];
    float rotateTarget;
    bool orienting;
    unsigned char unknown51[3];
    float orientTarget;

    virtual bool Init(ChildBuffers* config);
    virtual bool Configure(ChildBuffers* entry);   // slot 2
    virtual void Wrap();                // slot 3
    virtual bool Slot4();
    virtual bool Slot5();
    virtual bool Update();              // slot 6
    virtual bool Prepare();             // slot 7
    virtual bool Validate();            // slot 8
    virtual bool Refresh();             // slot 9
    virtual bool ExecuteAction(unsigned int index);   // slot 10

    void StopMoving();
    void Turn(float amount);
};


} // namespace Kaim

typedef char PathOffset_Behavior_bank[((unsigned int)&((Kaim::Behavior*)0)->bank)==0x4?1:-1];
typedef char PathOffset_Behavior_context[((unsigned int)&((Kaim::Behavior*)0)->context)==0x8?1:-1];
typedef char PathOffset_PathWayAgent_provider[((unsigned int)&((Kaim::PathWayAgent*)0)->provider)==0xc?1:-1];
typedef char PathOffset_PathWayAgent_forward[((unsigned int)&((Kaim::PathWayAgent*)0)->forward)==0x18?1:-1];
typedef char PathOffset_PathWayAgent_pointIndex[((unsigned int)&((Kaim::PathWayAgent*)0)->pointIndex)==0x3c?1:-1];
typedef char PathOffset_PathWayAgent_waiting[((unsigned int)&((Kaim::PathWayAgent*)0)->waiting)==0x40?1:-1];
typedef char PathOffset_PathWayAgent_paused[((unsigned int)&((Kaim::PathWayAgent*)0)->paused)==0x43?1:-1];
typedef char PathOffset_PathWayAgent_orientTarget[((unsigned int)&((Kaim::PathWayAgent*)0)->orientTarget)==0x54?1:-1];
// The matching factory allocates 0x58 bytes; Init verifies the accessed fields.
typedef char PathWayAgentSize[sizeof(Kaim::PathWayAgent) == 0x58 ? 1 : -1];

#endif
