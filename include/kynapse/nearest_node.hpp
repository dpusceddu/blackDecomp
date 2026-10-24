// Declarations of the Kynapse source module "nearest_node" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_NEAREST_NODE_HPP
#define BLACK_KYNAPSE_MODULE_NEAREST_NODE_HPP
#include "kynapse/compat.hpp"

// Navigation graph traversal and the nearest-node visitors.
extern "C" int __cdecl _stricmp(const char*, const char*);

struct Vec3 {
    float x, y, z;
};

struct NavNode {
    int id;                                // 0x00 (-1 marks a free slot)
    Vec3 position;
    int unknown10;
    unsigned int CountOutgoing();
    unsigned int CountIncoming();
};

float Kaim_ManhattanDistance(const Vec3* a, const Vec3* b);
extern const double kZeroDouble;

struct NodeGraph {
    unsigned char unknown00[0xc];
    unsigned int capacity;
    unsigned char unknown10[4];
    unsigned int liveCount;
    NavNode* nodes;                        // 0x18 (0x14 bytes each)
};

struct NodeVisitor {
    virtual ~NodeVisitor() {}
    virtual void Begin(NodeGraph*) {}              // slot 1
    virtual void Slot2() {}
    virtual bool Consider(NavNode*) { return true; }   // slot 3
    virtual void Slot4() {}

    bool VisitNodes(NodeGraph* graph);
};



// The nearest node by Manhattan distance (static visitor, vtable 0x285160): begin 0x5c3a0, consider 0x5c3c0.
struct NearestSimpleVisitor : NodeVisitor {
    double best;
    NavNode* result;
    Vec3 point;
    bool needOutgoing;
    bool needIncoming;

    NearestSimpleVisitor() {}
    virtual ~NearestSimpleVisitor() {}
    virtual void Begin(NodeGraph* graph);
    virtual bool Consider(NavNode* node);
};






NavNode* Kaim_FindNearestNodeSimple(NodeGraph* graph, const Vec3* point, bool needOutgoing, bool needIncoming);


// The nearest node within a radius of a point (vtable 0x28514c): begin 0x5c330, consider 0x5c470.
struct AuthoredProperty {
    unsigned char unknown00[4];
    float value;
};
struct EntityObject { unsigned char unknown00[0xc]; float frameTime; };
extern EntityObject* gEngine;
extern const float kDefaultFloat;
extern int gAuthoredHeightKey;
struct Actor {
    AuthoredProperty* GetAuthoredProperty(const void* key);
};
bool Kaim_TestSegment(const float* from, const float* to, Actor* actor, int mode, float radius);

struct NearestNodeVisitor : NodeVisitor {
    double best;
    float radius;
    int unknown14;
    NavNode* result;
    Vec3 point;
    float height;
    Actor* actor;
    bool withinRadius;
    bool visible;
    float radiusSquared;
    unsigned char needOutgoing;
    unsigned char needIncoming;

    NearestNodeVisitor() {}
    virtual ~NearestNodeVisitor() {}
    virtual void Begin(NodeGraph* graph);
    virtual bool Consider(NavNode* node);
};



static inline double SquaredDistance(const Vec3* a, const Vec3* b)
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    double dz = a->z - b->z;
    return dz * dz + dy * dy + dx * dx;
}




NavNode* Kaim_FindNearestNode(NodeGraph* graph, const Vec3* point, Actor* actor, float radius, unsigned int needOutgoing,
                              unsigned int needIncoming);


#endif
