// Declarations of the Kynapse source module "engine_create" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_ENGINE_CREATE_HPP
#define BLACK_KYNAPSE_MODULE_ENGINE_CREATE_HPP
#include "kynapse/compat.hpp"

// Engine bootstrap: checks that every class id has been registered, and creates the engine
// object in the first free engine slot.
#include "kynapse/kynapse.hpp"

extern void (*memoryRelease)(void*);

namespace Kaim {

extern int gClassId2B4874;
extern int gClassId2B547C;
extern int gClassId2B475C;
extern int gClassId2B5364;
extern int gClassId2B524C;
extern int gClassId2B4644;
extern int gClassId2B3B54;
extern int gClassId2B4414;
extern int gClassId2B3C6C;
extern int gClassId2B452C;
extern int gClassId2B5134;
extern int gClassId2B498C;
extern int gClassId2B501C;
extern int gClassId2B41E4;
extern int gClassId2B4F04;
extern int gClassId2B40CC;
extern int gClassId2B4DEC;
extern int gClassId2B3FB4;
extern int gClassId2B42FC;
extern int gClassId2B4CD4;
extern int gClassId2B4BBC;
extern int gClassId2B3D84;
extern int gClassId2B4AA4;


bool Kaim_AllClassesRegistered();


bool Kaim_GetFlag();

struct InitConfig;

struct Engine : Object {
    unsigned char unknown04[0x28];
    int slot;
    Engine(Object* context);
    bool Init(InitConfig* config);
};

extern unsigned char gCheckTable[0x5b];
extern unsigned int gEngineSlotCount;
extern Engine** gEngineSlots;
extern unsigned int gEnginesUsed;
extern Engine* gEngine;

// The global settings record (29 slots, see settings.cpp); only the leading fields are used here.
struct Settings {
    unsigned int objectCapacity;
    unsigned int engineSlots;
    Settings& operator=(const Settings& other);
};
extern Settings gSettings;

struct EngineObject : Object {
    unsigned char unknown04[0x24];
};
extern KaimAllocator* gDefaultAllocator;
extern List<EngineObject*>* gObjectList;
extern bool gInitialized;
void Kaim_DestroyEngine(Engine* engine);


// Takes over the settings and allocates the engine slots and the list of live engine objects.
bool Kaim_Initialize(const Settings* settings);



// Destroys every engine and every remaining engine object.
void Kaim_Shutdown();



// Public entry point of the engine library.
bool Kaim_Startup(const Settings* settings);



void Kaim_Cleanup();



Engine* Kaim_CreateEngine(InitConfig* config, Object* context);


}  // namespace Kaim

#endif
