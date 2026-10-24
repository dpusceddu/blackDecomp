#ifndef BLACK_CONTEXT_BEHAVIORS_CONSTRAINTS_HPP
#define BLACK_CONTEXT_BEHAVIORS_CONSTRAINTS_HPP
#include "kynapse/compat.hpp"
#include "kynapse/alloc.hpp"
#include "kynapse/list.hpp"
namespace Kaim {
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3(const Vec3& p):x(p.x),y(p.y),z(p.z) {}
    Vec3& operator=(const Vec3& p){x=p.x;y=p.y;z=p.z;return *this;}
    Vec3 operator-(const Vec3& p) const {return Vec3(x-p.x,y-p.y,z-p.z);}
    Vec3 operator+(const Vec3& p) const {return Vec3(x+p.x,y+p.y,z+p.z);}
    Vec3 operator*(float scale) const {return Vec3(scale*x,scale*y,scale*z);}
    float Dot(const Vec3& p) const {return x*p.x+y*p.y+z*p.z;}
    float DistanceTo(const Vec3& p) const {float dz=z-p.z,dx=x-p.x,dy=y-p.y;return sqrtf(dz*dz+dx*dx+dy*dy);}
    float SquaredInline() const {return z*z+x*x+y*y;}
    float Squared() const __asm__("func_00389140");
};

struct NodeGraph;

struct NavNode {
    int id;                                // 0x00
    Vec3 position;                         // 0x04
    NodeGraph* graph;                      // 0x10
};

struct NavEdge {
    int index;
    NodeGraph* graph;
    float GetAuthoredLength() const;
    NavNode* StartNode();
    NavNode* RawStart() __asm__("func_0038F2B0");
    NavNode* RawEnd() __asm__("func_0038F2F0");
    NavNode* EndNode();
};

struct NodeGraph {
    unsigned char unknown00[0x18];
    NavNode* nodes;                        // 0x18
    unsigned char unknown1c[0x1c];
    int* edgeEnd;                          // 0x38
    int* edgeStart;                        // 0x3c
    unsigned char unknown40[8];
    float* edgeLengths;
    unsigned char unknown4c[0x10];
    NavEdge syntheticEdge;                 // 0x5c
    NavNode syntheticEnd;                  // 0x64
    NavNode syntheticStart;                // 0x78
    float syntheticLength;
};

inline NavNode* NavEdge::EndNode()
{
    NodeGraph* owner = graph;
    if (this == &owner->syntheticEdge)
        return &owner->syntheticEnd;
    return &owner->nodes[owner->edgeEnd[index]];
}

inline NavNode* NavEdge::StartNode()
{
    NodeGraph* owner = graph;
    if (this == &owner->syntheticEdge)
        return &owner->syntheticStart;
    return &owner->nodes[owner->edgeStart[index]];
}

extern const float kDefaultFloat;          // 0x295cdc
extern const float kOne;                   // 0x295c94
struct ConstraintCallbacks { unsigned char unknown00[0x28]; int (*visibility)(const Vec3*,const Vec3*,void*,int); };
extern ConstraintCallbacks gConstraintCallbacks;   // 0x297f40

struct Actor {
    unsigned char unknown00[0x30];
    Vec3 position;                         // 0x30
};

bool Kaim_InSightCone(const Vec3* from, Actor* actor) __asm__("func_002D8578");   // 0x4c120

// Restricts the search to edges that start inside a sphere.
struct SphereConstraint : PolyRoot {
    SphereConstraint():center(0,0,0),radius(0){}
    static void* operator new(unsigned size){return KaimAllocate(size);}
    static SphereConstraint* Create() __asm__("func_002F1B58");
    virtual ~SphereConstraint();
    virtual void Slot1();
    virtual bool Cost(void* context, NavEdge* edge, float* cost) __asm__("func_002F1BD8");   // slot 2 (Xbox /default.xbe 0x5a6c0)
    Vec3 center;                           // 0x04
    float radius;                          // 0x10
};



// Each visible observer adds the configured edge penalty.
struct PointToFleeConstraint : PolyRoot {
    PointToFleeConstraint() __asm__("func_002F0F80");
    bool AddPoint(const Vec3&) __asm__("func_002F2180");
    bool AddEntity(Actor*) __asm__("func_002F21D8");
    virtual ~PointToFleeConstraint();
    virtual void Slot1();
    virtual bool Cost(void* context, NavEdge* edge, float* cost) __asm__("func_002F0FF8");   // slot 2 (0x5a270)
    Vec3 points[20];                       // 0x04
    Actor* entities[20];                   // 0xf4
    unsigned int pointCount;               // 0x144
    unsigned int entityCount;              // 0x148
    float penalty;                         // 0x14c
    float range;                           // 0x150
};



// As above, but only entities whose sight cone covers the edge start count.
struct ConeVisionConstraint : PolyRoot {
    bool AddEntity(Actor*) __asm__("func_002F2210");
    virtual ~ConeVisionConstraint();
    virtual void Slot1();
    virtual bool Cost(void* context, NavEdge* edge, float* cost) __asm__("func_002F13B0");   // slot 2 (0x5a420)
    Actor* entities[20];                   // 0x04
    unsigned int entityCount;              // 0x54
    float penalty;                         // 0x58
    float range;                           // 0x5c
};



// Scales the edge cost by how close the edge passes to the watched points and entities.
struct StealthConstraint : PolyRoot {
    bool AddPoint(const Vec3&) __asm__("func_002F2248");
    bool AddEntity(Actor*) __asm__("func_002F22A0");
    virtual ~StealthConstraint();
    virtual void Slot1();
    virtual bool Cost(void* context, NavEdge* edge, float* cost) __asm__("func_002F18D8");   // slot 2 (0x5a580)
    Vec3 points[20];                       // 0x04
    Actor* entities[20];                   // 0xf4
    unsigned int pointCount;               // 0x144
    unsigned int entityCount;              // 0x148
    float penalty;                         // 0x14c
    float range;                           // 0x150

    float Factor(void* context, NavEdge* edge, const Vec3* position, const Vec3* direction, float length) __asm__("func_002F16E0");   // 0x59e10
};





typedef char SphereSize[sizeof(SphereConstraint)==0x14?1:-1];
typedef char PointConstraintSize[sizeof(PointToFleeConstraint)==0x154?1:-1];
typedef char ConeConstraintSize[sizeof(ConeVisionConstraint)==0x60?1:-1];
typedef char StealthConstraintSize[sizeof(StealthConstraint)==0x154?1:-1];
typedef char NodeGraphPrefixSize[sizeof(NodeGraph)==0x90?1:-1];
}
#endif
