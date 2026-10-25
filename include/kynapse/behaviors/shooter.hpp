// Declarations of the Kynapse source module "shooter_agent" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_SHOOTER_AGENT_HPP
#define BLACK_SHOOTER_AGENT_HPP
#include "kynapse/compat.hpp"
#include "kynapse/alloc.hpp"
extern void (*gKaimFree)(void*);
#include "kynapse/classes/Kaim_CShooterAgent.hpp"

// The wander agent's per-frame update and the shooter agent behaviour (aims at and fires on a target
// bot while keeping the danger cone clear), plus the shared name-table accessor and the angle helper.
#include "kynapse/alloc.hpp"

extern "C" int __cdecl _stricmp(const char*, const char*);

extern "C" long func_0035E730(const char*);
extern "C" float func_00291C68(long);
#include "kynapse/list.hpp"
namespace Kaim {

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float v):x(v),y(v),z(v) {}
    Vec3(const Vec3& v) : x(v.x),y(v.y),z(v.z) {}
    void Set(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }
    Vec3& operator=(const Vec3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
};
Vec3* Direction_Orientation(Vec3* output, const Vec3* direction);
Vec3 Direction_FromAngles(const float* angles);
extern Vec3 gOrigin;
extern Vec3 gDefaultAim;
extern float gUnit;
static const float kDefaultFloat=0;
extern float gNow;

struct ActionBank {
    virtual void Slot0();
    virtual void Select(int id);        // slot 1
    void ClearActivation();
    void* GetItem(const void* key);
};

struct ChildBuffers {
    const char* GetSecond() const;
    const char* GetValue() const;
};

struct NameTable {
    int FindName(const char* name);
};

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
};

struct ParameterTables : ObjectBase {
    ParameterTables();
    bool Consume(int index, void* user);
    void Accumulate(int index, void* user);
    unsigned char unknown04[0x50];
};
extern ParameterTables* gTables;


// The lazily created parameter tables, also searched by name.
NameTable* GetNameTables();



bool InCone(const Vec3* point, const Vec3* origin, const Vec3* axis, float angle, float range);
float Radians_Cosine(float units);

struct AuthoredProperty {
    unsigned char unknown00[4];
    float x, y, z;
};
struct Actor {
    unsigned char unknown00[0x14];
    ListNode<Actor*>* node;
    unsigned char unknown18[4];
    unsigned int flags;
    unsigned char unknown20[0x10];
    Vec3 position;
    unsigned char unknown3c[4];
    float yaw;
    AuthoredProperty* GetAuthoredProperty(const void* key);
};

struct TargetBase { virtual void Slot0(); };
struct TargetEntity : TargetBase {
    unsigned char unknown04[4];
    int id;
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual bool Query(void* data);   // slot 5
    virtual bool QueryTransform(void* data);     // slot 6
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual bool IsActive();            // slot 10
};

// Per-actor perception record (0x14 bytes each), looked up by actor.
struct Perception;
struct PerceptionRecord {
    unsigned char unknown00[4];
    float field04;
    float field08;
    float distance;
    unsigned char unknown10;
    bool hidden;
    unsigned char unknown12;
    bool blocked;
};
struct Perception {
    PerceptionRecord* GetRecord(Actor* actor);
};
extern const unsigned int gTargetFlag;

struct Engine {
    unsigned char unknown00[0x0c];
    float unit;
    unsigned char unknown10[4];
    List<Actor*>* actors;
    Actor* FindByName(const char* name);
};
extern Engine* gEngine;

struct ClassInfo;
struct BehaviorContext {
    unsigned char unknown00[0x14];
    Actor* actor;
    TargetEntity* FindTarget(ClassInfo* wanted);
    Perception* FindPerception(ClassInfo* wanted);
};
extern ClassInfo gTargetClass;
extern ClassInfo gPerceptionClass;

struct Control {
    unsigned char unknown00[4];
    bool active;
    unsigned char unknown05[3];
    float value;
    void Set(float v)
    {
        value = v;
        active = true;
    }
};
struct AimControl {
    unsigned char unknown00[4];
    bool active;
    unsigned char unknown05[3];
    Vec3 direction;
    bool fire;
    void SetDirection(const Vec3& d)
    {
        direction = d;
        active = true;
    }
    void SetFire(bool f)
    {
        fire = f;
        active = true;
    }
};
extern const unsigned char gBankKeyA, gBankKeyB, gBankKeyC;   // 0x2b3b50, 0x2b4528, 0x2b4410
extern const void* gKeyA;
extern const void* gKeyB;

struct Behavior : PolyRoot {
    Behavior();
    Behavior(BehaviorContext*);
    virtual ~Behavior();
    virtual bool Init(ChildBuffers* config);   // slot 1
    bool ConfigureAll(ChildBuffers* config);   // shared routine at 0x54bf0
    ActionBank* bank;
    BehaviorContext* context;
};

// Temporary transform handed to the target while the wander agent is following an index.
struct ZeroedBase : PolyRoot {
    virtual ~ZeroedBase() {}
    int field04, field08, field0c, field10, field14, field18, field1c, field20;
    ZeroedBase();
};
struct FollowQuery : ZeroedBase {
    int axisX, axisY, axisZ;
    int component0;
    int extra;
    FollowQuery(const int* source, int component, int value)
        : axisX(source[0]), axisY(source[1]), axisZ(source[2]), component0(component), extra(value) {}
    virtual ~FollowQuery() {}
};

struct WanderAgent : Behavior {
    int index;
    int vector[3];
    int fieldC;
    int fieldD;
    TargetEntity* provider;
    void* pending;
    bool reached;

    virtual void Slot2(); virtual void Slot3(); virtual void Slot4(); virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Refresh();             // slot 8 (0x20)

    bool Update();
};



// Fires on a named target bot: keeps its aim and trigger controls current, and only shoots when no
// other actor stands inside the danger cone.
struct ShooterAgent : Behavior {
    ShooterAgent(BehaviorContext*);
    static ShooterAgent* Create(BehaviorContext*);
    static void* operator new(unsigned int size) {return KaimAllocate(size);}
    static void operator delete(void* p) {gKaimFree(p);}
    Actor* target;
    float gunRange;
    float dangerousConeAngle;
    float maxInaccuracy;
    float targetDistance;
    Vec3 aimOrigin;
    Vec3 aimDirection;
    float aimYaw;
    bool fire;
    Vec3 targetPosition;
    Perception* perception;
    TargetEntity* provider;
    Control* yawControl;
    Control* turnControl;
    AimControl* aimControl;
    AuthoredProperty* propertyA;
    AuthoredProperty* propertyB;
    int nameIndex;
    float nextTime;
    float interval;

    virtual bool Init(ChildBuffers* config);
    virtual bool Configure(ChildBuffers* entry);   // slot 2
    virtual void Slot3();
    virtual void Slot4();
    virtual bool Prepare();             // slot 5
    virtual bool Update();              // slot 6
    virtual bool Slot7();
    virtual bool Slot8();
    virtual bool Slot9();
    virtual bool IsClear(const Vec3* direction);   // slot 10

    void Aim();
};











// Turns towards the target with a random error of up to the maximum inaccuracy.






// True when no other actor stands inside the danger cone of the shot.



// True when `point` lies inside the cone of half-angle `angle` around `axis` from `origin`, within `range`
// (a negative range is unlimited).
bool InCone(const Vec3* point, const Vec3* origin, const Vec3* axis, float angle, float range);


}  // namespace Kaim

typedef char ShooterAgentSize[sizeof(Kaim::ShooterAgent) == 0x74 ? 1 : -1];
typedef char ActorIteratorSize[sizeof(Kaim::ActorIterator) == 8 ? 1 : -1];

#endif
