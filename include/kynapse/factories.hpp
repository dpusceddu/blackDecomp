// Declarations of the Kynapse source module "factories" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_FACTORIES_HPP
#define BLACK_KYNAPSE_MODULE_FACTORIES_HPP
#include "kynapse/compat.hpp"

// Factory functions: allocate through the Kynapse allocator service and construct the object.
// Classes are named after the address of the constructor (or vtable) until they are recovered.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
};

struct Object4E410 : ObjectBase {
    unsigned char data[12];
    Object4E410();
    virtual ~Object4E410();
};
ObjectBase* CreateObject4E410();


struct Object4E750 : ObjectBase {
    unsigned char data[12];
    Object4E750();
    virtual ~Object4E750();
};
ObjectBase* CreateObject4E750();


struct Object55180 : ObjectBase {
    unsigned char data[20];
    Object55180(int a, int b);
    virtual ~Object55180();
};
ObjectBase* CreateObject55180(int a, int b);


struct Object56980 : ObjectBase {
    unsigned char data[16];
    Object56980();
    virtual ~Object56980();
};
ObjectBase* CreateObject56980();


struct Object59AC0 : ObjectBase {
    unsigned char data[24];
    Object59AC0();
    virtual ~Object59AC0();
};
ObjectBase* CreateObject59AC0();


struct ObjectV284F64 : ObjectBase {
    unsigned char data[0];
    virtual ~ObjectV284F64();
};
ObjectBase* CreateObjectV284F64();


struct ObjectV284F84 : ObjectBase {
    unsigned char data[0];
    virtual ~ObjectV284F84();
};
ObjectBase* CreateObjectV284F84();


struct ObjectV284F94 : ObjectBase {
    unsigned char data[0];
    virtual ~ObjectV284F94();
};
ObjectBase* CreateObjectV284F94();


struct ObjectV284FA4 : ObjectBase {
    unsigned char data[4];
    ObjectV284FA4() { *(int*)data = 0; }
    virtual ~ObjectV284FA4();
};
ObjectBase* CreateObjectV284FA4();


struct Object59D40 : ObjectBase {
    unsigned char data[92];
    Object59D40();
    virtual ~Object59D40();
};
ObjectBase* CreateObject59D40();


struct Object59DB0 : ObjectBase {
    unsigned char data[336];
    Object59DB0();
    virtual ~Object59DB0();
};
ObjectBase* CreateObject59DB0();


struct Object5A210 : ObjectBase {
    unsigned char data[336];
    Object5A210();
    virtual ~Object5A210();
};
ObjectBase* CreateObject5A210();


struct ObjectV285188 : ObjectBase {
    unsigned char data[4];
    ObjectV285188() { *(int*)data = 0; }
    virtual ~ObjectV285188();
};
ObjectBase* CreateObjectV285188();


struct Object5CD50 : ObjectBase {
    unsigned char data[20];
    Object5CD50(int a);
    virtual ~Object5CD50();
};
ObjectBase* CreateObject5CD50(int a);


struct Object619F0 : ObjectBase {
    unsigned char data[436];
    Object619F0(int a);
    virtual ~Object619F0();
};
ObjectBase* CreateObject619F0(int a);


struct Object62D40 : ObjectBase {
    unsigned char data[236];
    Object62D40(int a);
    virtual ~Object62D40();
};
ObjectBase* CreateObject62D40(int a);


struct Object67FC0 : ObjectBase {
    unsigned char data[80];
    Object67FC0(int a);
    virtual ~Object67FC0();
};
ObjectBase* CreateObject67FC0(int a);



#endif
