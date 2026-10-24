// PS2 query temporary: vptr at 0, axis at 0x24, component at 0x30.
#ifndef BLACK_CAMPAIGN_FLEE_QUERIES_HPP
#define BLACK_CAMPAIGN_FLEE_QUERIES_HPP
#include "kynapse/behaviors/flee.hpp"
namespace FleeRecovery {struct InitAgent:FleeAgent {InitAgent(Context*);int Initialize(ChildBuffers*) __asm__("func_002D1918");};}
namespace FleeQueries {
struct Root { virtual ~Root() {} };
struct Base:Root {
    int fields[8];
    Base() __asm__("func_002E7360");
    virtual ~Base() {}
};
struct Vec3 {
    float x,y,z;
    Vec3(const FleeRecovery::Vec3& v):x(v.x),y(v.y),z(v.z) {}
};
struct Query:Base {
    Vec3 axis;
    int component,extra;
    Query(const FleeRecovery::Vec3& source,int c,int e):axis(source),component(c),extra(e) {}
    virtual ~Query() {}
};
// Prepare/Validate return a full PS2 integer, independently of Xbox bool declarations.
struct Checks:Root {
    virtual ~Checks();
    virtual void Slot1();virtual void Slot2();virtual void Slot3();virtual void Slot4();virtual void Slot5();virtual void Slot6();
    virtual int Prepare();
    virtual int Validate() __asm__("func_002D2F48");
    unsigned char unknown04[12];
    void* graph;
    unsigned char unknown14[12];
    unsigned pointCount;
    unsigned char unknown24[8];
    unsigned entityCount;
};
struct PointCell {
    FleeRecovery::Vec3 value;
    PointCell() {}
    ~PointCell() {}
    static void* operator new[](unsigned size) {return KaimAllocate(size);}
};
struct Hooks {
    unsigned char unknown00[0x28];
    unsigned char (*visibility)(const FleeRecovery::Vec3*,const FleeRecovery::Vec3*,void*,int);
};
extern Hooks hooks;
typedef char QuerySize[sizeof(Query)==0x38?1:-1];
}
#endif
