// Declarations of the Kynapse source module "small_misc" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_SMALL_MISC_HPP
#define BLACK_KYNAPSE_MODULE_SMALL_MISC_HPP
#include "kynapse/compat.hpp"

// Small Kynapse leaf functions: global accessors, thin forwarders and one-field constructors.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

struct Disposable {
    virtual ~Disposable();
};

extern bool gFlag;
extern float (*gFloatHook)();
extern const float kDefaultFloat;
extern int gSavedValue;
extern int gCurrentValue;
extern Disposable* gService;
extern unsigned int gSelected;

struct Slot { unsigned char unknown0[0x14]; };
struct SlotTable {
    unsigned char unknown00[4];
    Slot* slots;
};
struct SlotOwner {
    unsigned char unknown00[0x10];
    unsigned int slotCount;
    SlotTable* table;
};
extern SlotOwner* gSlotOwner;

struct SlotUser {
    unsigned char unknown00[0x14];
    Slot* slot;

    int GetIndex() const;
};

#pragma auto_inline(off)



#pragma auto_inline(on)


void Kaim_Nop();



bool Kaim_GetFlag();


namespace Kaim {
struct Tagged {
    int tag;
    Tagged(int value);
    virtual ~Tagged();
};
}


float Kaim_QueryFloat();


struct FloatTable {
    unsigned char unknown00[0x1c];
    int slotValue;
    unsigned char unknown20[0x10];
    float* values;

    void SetSlot(int value);
    float GetValue(int index);
};






void Kaim_SnapshotValue();



void Kaim_ReleaseService();



void __stdcall Kaim_SelectUser(SlotUser* user);


struct Notifiable {
    void Update(int argument);
    void Reset();
    bool Accept(const SlotUser* user);
};


void Notifiable_Update(Notifiable* target, int argument);



void Notifiable_Reset(Notifiable* target);



bool Notifiable_TryAccept(Notifiable* target, SlotUser* user);


#endif
