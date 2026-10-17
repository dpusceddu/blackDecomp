// Declarations of the Kynapse source module "index_queries" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_INDEX_QUERIES_HPP
#define BLACK_KYNAPSE_MODULE_INDEX_QUERIES_HPP
#include "kynapse/compat.hpp"

// Point-index range queries, a random node pick and a registry lookup by class name.

namespace Kaim {

struct NavNode {
    int id;
    float x, y, z;
    int unknown10;
};

struct NodeBank {
    unsigned char unknown00[8];
    float horizontalExtent;
    unsigned int capacity;
    unsigned char unknown10[4];
    unsigned int liveCount;
    NavNode* nodes;

    NavNode* NodeAt(unsigned int ordinal)
    {
        if (ordinal >= capacity)
            return 0;
        NavNode* node = &nodes[ordinal];
        return node->id == -1 ? 0 : node;
    }
};

struct PointIndex {
    unsigned char unknown00[4];
    NodeBank* graph;
    int stride;                            // 0x08 (entries per axis)
    unsigned int* sorted;                  // 0x0c (node ordinals sorted per axis)
    int* inverse;                          // 0x10 (rank of each node per axis)
    int* output;

    int ExtendEqualRange(int position, float coordinate, int axis, int lower);
    int FindBoundary(float coordinate, int axis, int lower);
    int QueryAxis(const float* center, float extent, int axis, int* low, int* high);
    int QueryBox(const float* center, float verticalExtent, int** result);
};



struct RandomPicker {
    unsigned char unknown00[0xc];
    int unknown0c;
    float x, y, z;
    unsigned int pickedOrdinal;
    int unknown20;
    unsigned char unknown24[4];
    NodeBank* bank;

    void Pick();
};



struct ClassInfo;
struct ItemList {
    int IdByName(const char* name);
};
struct EntityObject {
    ItemList* FindByClass(ClassInfo* wanted);
};
extern EntityObject* gEngine;
extern ClassInfo gTypeRegistryClass;

struct NameSource {
    unsigned char unknown00[0xc];
    const char* name;
};

struct IdHolder {
    int unknown00;
    int id;

    bool Resolve(NameSource* source);
};



}  // namespace Kaim

namespace Kaim {

static inline float Coordinate(const NavNode* node, int axis)
{
    if (axis == 0)
        return node->x;
    else if (axis == 1)
        return node->y;
    return node->z;
}


// Unmatched: transcribed from the decompilation (652 vs 604 bytes, 629 differing).



// Unmatched: coordinate value lifetime improves x87 scheduling; boundary/search registers still differ (575 vs 576 bytes, 549 differing).



// Unmatched: center/axis registers and range-array frame scheduling differ; four local-order variants tried (263 vs 262 bytes, 209 differing).


}  // namespace Kaim

#endif
