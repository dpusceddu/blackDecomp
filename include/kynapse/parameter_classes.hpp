// Declarations of the Kynapse source module "parameter_classes" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_PARAMETER_CLASSES_HPP
#define BLACK_KYNAPSE_MODULE_PARAMETER_CLASSES_HPP
#include "kynapse/compat.hpp"

// Parameter classes: factory and class-info getter for each (see parameter_assign.cpp for the
// shared assignment operators). Names are the vtable addresses until the classes are named.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);
extern const float kZero;

struct ClassInfoEntry;

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
};

struct Engine {
    unsigned char unknown00[0x0c];
    float frameTime;
};
extern Engine* gEngine;

struct Parameter2846A0Base : ObjectBase {
    bool changed;
    unsigned char data[7];
    Parameter2846A0Base() { changed = false; }
};
struct Parameter2846A0 : Parameter2846A0Base {
    virtual ~Parameter2846A0();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B3B50;

ObjectBase* CreateParameter2846A0();


struct Parameter2846C4Base : ObjectBase {
    bool changed;
    unsigned char data[7];
    Parameter2846C4Base() { changed = false; }
};
struct Parameter2846C4 : Parameter2846C4Base {
    virtual ~Parameter2846C4();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B3C68;

ObjectBase* CreateParameter2846C4();


struct Parameter2846E4 : ObjectBase {
    unsigned char data[4];
    Parameter2846E4()
    {
        float* value = (float*)data;
        if (gEngine)
            *value = gEngine->frameTime * 0.7f;
        else
            *value = kZero * 0.7f;
    }
    virtual ~Parameter2846E4();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B3D80;

ObjectBase* CreateParameter2846E4();


struct Parameter284708 : ObjectBase {
    unsigned char data[4];
    Parameter284708()
    {
        float* value = (float*)data;
        if (gEngine)
            *value = gEngine->frameTime * 0.7f;
        else
            *value = kZero * 0.7f;
    }
    virtual ~Parameter284708();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B3E98;

ObjectBase* CreateParameter284708();


struct Parameter284728 : ObjectBase {
    unsigned char data[4];
    Parameter284728()
    {
        float* value = (float*)data;
        if (gEngine)
            *value = gEngine->frameTime * 0.5f;
        else
            *value = kZero * 0.5f;
    }
    virtual ~Parameter284728();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B3FB0;

ObjectBase* CreateParameter284728();


struct Parameter284748 : ObjectBase {
    unsigned char data[4];
    Parameter284748()
    {
        float* value = (float*)data;
        if (gEngine)
            *value = gEngine->frameTime * 1.8f;
        else
            *value = kZero * 1.8f;
    }
    virtual ~Parameter284748();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B40C8;

ObjectBase* CreateParameter284748();


struct Parameter284768 : ObjectBase {
    unsigned char data[12];
    virtual ~Parameter284768();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B41E0;

ObjectBase* CreateParameter284768();


struct Parameter28478C : ObjectBase {
    unsigned char data[4];
    Parameter28478C()
    {
        *(int*)data = -1;
    }
    virtual ~Parameter28478C();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B42F8;

ObjectBase* CreateParameter28478C();


struct Parameter2847ACBase : ObjectBase {
    bool changed;
    unsigned char data[19];
    Parameter2847ACBase() { changed = false; }
};
struct Parameter2847AC : Parameter2847ACBase {
    virtual ~Parameter2847AC();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4410;

ObjectBase* CreateParameter2847AC();


struct Parameter2847CCBase : ObjectBase {
    bool changed;
    unsigned char data[7];
    Parameter2847CCBase() { changed = false; }
};
struct Parameter2847CC : Parameter2847CCBase {
    virtual ~Parameter2847CC();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4528;

ObjectBase* CreateParameter2847CC();


struct Parameter2847ECBase : ObjectBase {
    bool changed;
    unsigned char data[7];
    Parameter2847ECBase() { changed = false; }
};
struct Parameter2847EC : Parameter2847ECBase {
    virtual ~Parameter2847EC();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4640;

ObjectBase* CreateParameter2847EC();


struct Parameter284808Base : ObjectBase {
    bool changed;
    unsigned char data[7];
    Parameter284808Base() { changed = false; }
};
struct Parameter284808 : Parameter284808Base {
    virtual ~Parameter284808();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4758;

ObjectBase* CreateParameter284808();


struct Parameter284828Base : ObjectBase {
    bool changed;
    unsigned char data[7];
    Parameter284828Base() { changed = false; }
};
struct Parameter284828 : Parameter284828Base {
    virtual ~Parameter284828();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4870;

ObjectBase* CreateParameter284828();


struct Parameter28484C : ObjectBase {
    unsigned char data[12];
    virtual ~Parameter28484C();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4988;

ObjectBase* CreateParameter28484C();


struct Parameter28486C : ObjectBase {
    unsigned char data[4];
    Parameter28486C()
    {
        data[0] = 0;
    }
    virtual ~Parameter28486C();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4AA0;

ObjectBase* CreateParameter28486C();


struct Parameter28488C : ObjectBase {
    unsigned char data[12];
    virtual ~Parameter28488C();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4BB8;

ObjectBase* CreateParameter28488C();


struct Parameter2848B4 : ObjectBase {
    unsigned char data[8];
    Parameter2848B4()
    {
        float* value = (float*)data;
        float t = gEngine ? gEngine->frameTime : kZero;
        value[0] = t * 100.0f;
        value[1] = 60.0f;
    }
    virtual ~Parameter2848B4();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4CD0;

ObjectBase* CreateParameter2848B4();


struct Parameter2848DC : ObjectBase {
    unsigned char data[12];
    virtual ~Parameter2848DC();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4DE8;

ObjectBase* CreateParameter2848DC();


struct Parameter284900 : ObjectBase {
    unsigned char data[4];
    virtual ~Parameter284900();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B4F00;

ObjectBase* CreateParameter284900();


struct Parameter284928 : ObjectBase {
    unsigned char data[12];
    virtual ~Parameter284928();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B5018;

ObjectBase* CreateParameter284928();


struct Parameter28494CBase : ObjectBase {
    bool changed;
    unsigned char data[7];
    Parameter28494CBase() { changed = false; }
};
struct Parameter28494C : Parameter28494CBase {
    virtual ~Parameter28494C();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B5130;

ObjectBase* CreateParameter28494C();


struct Parameter284974Base : ObjectBase {
    bool changed;
    unsigned char data[11];
    Parameter284974Base() { changed = false; }
};
struct Parameter284974 : Parameter284974Base {
    virtual ~Parameter284974();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B5248;

ObjectBase* CreateParameter284974();


struct Parameter284998Base : ObjectBase {
    bool changed;
    unsigned char data[11];
    Parameter284998Base() { changed = false; }
};
struct Parameter284998 : Parameter284998Base {
    virtual ~Parameter284998();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B5360;

ObjectBase* CreateParameter284998();


struct Parameter2849BCBase : ObjectBase {
    bool changed;
    unsigned char data[7];
    Parameter2849BCBase() { changed = false; }
};
struct Parameter2849BC : Parameter2849BCBase {
    virtual ~Parameter2849BC();
    virtual const ClassInfoEntry* GetClassInfo() const;
};
extern ClassInfoEntry gClassInfo2B5478;

ObjectBase* CreateParameter2849BC();



#endif
