// Declarations of the Kynapse source module "behavior_methods" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_BEHAVIOR_METHODS_HPP
#define BLACK_KYNAPSE_MODULE_BEHAVIOR_METHODS_HPP
#include "kynapse/compat.hpp"

// Methods of Kynapse behaviours that drive an action bank from a target entity.

namespace Kaim {

struct ActionBank {
    virtual void Slot0();
    virtual void Select(int id);    // slot 1
    void ClearActivation();
};

struct TargetEntity {
    unsigned char unknown04[4];
    int id;
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual bool Query(void* data); // slot 6
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual bool IsActive();        // slot 10
};

struct Vec3 {
    float x, y, z;
    Vec3& operator=(const Vec3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
};
extern Vec3 gOrigin;

struct ClassInfo;
struct ClassRegistryA {
    TargetEntity* FindByClass(ClassInfo* wanted);
};
extern ClassInfo gTargetClass;

struct ChildBuffers;

struct Behavior {
    virtual ~Behavior();
    virtual void Slot1();
    bool ConfigureAll(ChildBuffers* config);   // shared routine at 0x54bf0
    ActionBank* bank;
    ClassRegistryA* context;
};

// Behaviour that keeps the bank in step with a target entity and records whether it is active.
struct Behavior2844F4 : Behavior {
    TargetEntity* target;
    bool active;
    unsigned char unknown11[3];
    int field14;
    Vec3 data;

    virtual void Slot2(); virtual void Slot3(); virtual void Slot4(); virtual void Slot5();
    virtual void Slot6();
    virtual bool Prepare();         // slot 7 (0x1c)

    bool Init(ChildBuffers* config);
    bool Update();
};





// Behaviour with vtable 0x2842cc.
struct Behavior2842CC : Behavior {
    unsigned char unknown0c[4];
    Vec3 position;
    int limit;
    unsigned char unknown20[4];
    TargetEntity* target;
    int field28;
    bool flag2c;

    virtual void Slot2(); virtual void Slot3(); virtual void Slot4(); virtual void Slot5();
    virtual void Slot6();
    virtual bool Prepare();         // slot 7 (0x1c)

    bool Init(ChildBuffers* config);
};



// Behaviour with vtable 0x28441c (see behaviors.cpp for its constructor).
struct Behavior28441C : Behavior {
    unsigned char unknown0c[8];
    Vec3 position;
    unsigned char unknown20[4];
    int limit;
    unsigned char unknown28[0x0c];
    bool flag34;
    bool flag35;
    unsigned char unknown36[0x12];
    int field48;
    unsigned char unknown4c[8];
    bool flag54;
    bool flag55;
    unsigned char unknown56[2];
    int field58;
    float low;
    float high;
    float lowest;
    bool flag68;

    void ResetState();
};



}  // namespace Kaim

#endif
