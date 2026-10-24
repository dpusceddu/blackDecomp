// Declarations of the Kynapse source module "engine_class" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_ENGINE_CLASS_HPP
#define BLACK_KYNAPSE_MODULE_ENGINE_CLASS_HPP
#include "kynapse/compat.hpp"

// The engine object: owns the entity list, helper lists and the callback tables, registers
// entities and tears everything down in its destructor.
#include "kynapse/kynapse.hpp"

extern void (*memoryRelease)(void*);

namespace Kaim {

struct ParameterTables {
    void Update(float step);
    int NextSlot();
    void Snapshot();
};
ParameterTables* GetNameTables();

struct Service : Object {
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Tick();                         // slot 4
};

struct Entity;

// Sub-objects of an entity: handlers are told when the entity leaves its engine.
struct EntityHandler : Object {
    virtual void Slot1();
    virtual void Slot2();
    virtual void Detach(Entity* entity);         // slot 3
};

struct EntityAttachment : Object {
    unsigned char unknown04[0x14];
    EntityHandler* handler;
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual bool IsReady();                      // slot 5
};

// An entity is on the global list (node at 0x0c) and on its engine's list (node at 0x14).
struct Entity : Object {
    unsigned char unknown04[8];
    ListNode<Entity*>* globalNode;
    unsigned char unknown10[4];
    ListNode<Entity*>* node;
    EntityAttachment* attachment;
    unsigned char unknown1c[0xc];
    struct Engine* owner;
    List<EntityHandler*>* handlers;
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Tick();                         // slot 4
};

typedef void (*EntityCallback)(Entity* entity, void* context);

bool Kaim_DestroyObject(Entity* object);
void Kaim_ReleaseService();

extern List<Entity*>* gObjectList;

extern unsigned int gFirstCapacity;
extern unsigned int gFirstCount;
extern EntityCallback* gFirstFunctions;
extern void** gFirstContexts;
extern unsigned int gSecondCapacity;
extern unsigned int gSecondCount;
extern EntityCallback* gSecondFunctions;
extern void** gSecondContexts;

struct EngineBase : Object {
    Object* context;
    unsigned char unknown08[4];
    float scale;
    unsigned int limit;
    List<Entity*>* entities;
    unsigned char unknown18[4];
    List<Object*>* owned;
    Object** services;
    unsigned int serviceCount;
    unsigned int serviceCapacity;

    EngineBase() : limit(0), entities(0), owned(0), serviceCount(0), serviceCapacity(0) {}
};

struct Engine : EngineBase {
    Engine(Object* newContext);
    void AddService(Object* service);
    void Update(float step);
    bool Register(Entity* entity);
    bool Unregister(Entity* entity);
    virtual __declspec(noinline) ~Engine();      // 0x53890 (deleting 0x53a30)
    static void operator delete(void* block) { memoryRelease(block); }
};








// Unmatched: iterator destructor store and callback alignment differ; outer lifetime and external Insert specialization were no better (139 vs 155 bytes).



// Unmatched: original handler loop tests at its head; compiler rotates it and adds alignment (193 vs 179 bytes, five loop variants).




}  // namespace Kaim

#endif
