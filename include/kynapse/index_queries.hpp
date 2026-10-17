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
int PointIndex::ExtendEqualRange(int position, float coordinate, int axis, int lower)
{
    NodeBank* bank = graph;
    int count = bank->liveCount;
    int axisBase = stride * axis;
    unsigned int found;
    int low;
    int high;
    if (!(lower & 0xff)) {
        if (position == count - 1)
            return position;
        unsigned int* table = sorted;
        if (Coordinate(bank->NodeAt(table[axisBase + position + 1]), axis) != coordinate)
            return position;
        int left = position - 1;
        int right = count - 1;
        low = left;
        if (left < count - 2) {
            do {
                low = (left + right) / 2;
                float value = Coordinate(bank->NodeAt(table[axisBase + low]), axis);
                if (value < coordinate)
                    return position;
                if (coordinate < value) {
                    right = low;
                    low = left;
                }
                left = low;
            } while (low < right - 1);
        }
        high = right;
        found = table[axisBase + low];
    } else {
        if (position == 0)
            return 0;
        unsigned int* table = sorted;
        if (Coordinate(bank->NodeAt(table[axisBase + position - 1]), axis) != coordinate)
            return position;
        low = 0;
        int right = position - 1;
        high = right;
        if (position != 2 && position - 2 >= 0) {
            do {
                int mid = (low + right) / 2;
                float value = Coordinate(bank->NodeAt(table[axisBase + mid]), axis);
                if (coordinate < value)
                    return position;
                high = mid;
                if (value < coordinate) {
                    high = right;
                    low = mid;
                }
                right = high;
            } while (low < high - 1);
        }
        found = table[axisBase + low];
    }
    NavNode* node = bank->NodeAt(found);
    if ((double)coordinate != (double)Coordinate(node, axis))
        return high;
    return low;
}


// Unmatched: coordinate value lifetime improves x87 scheduling; boundary/search registers still differ (575 vs 576 bytes, 549 differing).
int PointIndex::FindBoundary(float coordinate, int axis, int lower)
{
    NodeBank* bank = graph;
    int count = bank->liveCount;
    int low = 0;
    int high = count - 1;
    int best = 0;
    if (count != 2 && count - 2 >= 0) {
        int limit = high;
        do {
            int position = (limit + low) / 2;
            double value = Coordinate(bank->NodeAt(sorted[stride * axis + position]), axis);
            high = position;
            if (value <= coordinate) {
                low = position;
                high = limit;
                best = position;
                if (coordinate <= value)
                    return ExtendEqualRange(position, value, axis, lower);
            }
            limit = high;
        } while (low < high - 1);
    }
    int base = stride * axis;
    float lowValue = Coordinate(bank->NodeAt(sorted[base + low]), axis);
    float highValue = Coordinate(bank->NodeAt(sorted[base + high]), axis);
    if (lower & 0xff) {
        if (lowValue < coordinate && highValue < coordinate)
            return -1;
        if (lowValue < coordinate)
            return ExtendEqualRange(high, highValue, axis, lower);
        return ExtendEqualRange(best, lowValue, axis, lower);
    }
    if (coordinate < lowValue && coordinate < highValue)
        return -1;
    if (highValue < coordinate == (highValue == coordinate))
        return ExtendEqualRange(best, lowValue, axis, 0);
    return ExtendEqualRange(high, highValue, axis, 0);
}


// Unmatched: center/axis registers and range-array frame scheduling differ; four local-order variants tried (263 vs 262 bytes, 209 differing).
int PointIndex::QueryBox(const float* center, float verticalExtent, int** result)
{
    float horizontal = graph->horizontalExtent;
    int axis = 0;
    int smallest = -1;
    int count = 0;
    int smallestCount = -1;
    int ranges[6];
    do {
        int* high;
        int* low;
        float extent;
        if (axis == 1) {
            high = ranges + 1;
            low = ranges + 4;
            extent = verticalExtent;
        } else {
            high = ranges + axis;
            low = ranges + axis + 3;
            extent = horizontal;
        }
        int hits = QueryAxis(center, extent, axis, low, high);
        if (hits == 0)
            return 0;
        if (smallest == -1 || hits < smallestCount) {
            smallest = axis;
            smallestCount = hits;
        }
        ++axis;
    } while (axis < 3);
    int index = ranges[smallest + 3];
    if (index <= ranges[smallest]) {
        do {
            int ordinal = sorted[stride * smallest + index];
            int other = 0;
            int offset = ordinal * 4;
            do {
                if (other != smallest) {
                    int rank = *(int*)((char*)inverse + offset);
                    if (rank < ranges[other + 3] || rank > ranges[other])
                        break;
                }
                ++other;
                offset += stride * 4;
            } while (other < 3);
            if (other == 3) {
                output[count] = ordinal;
                ++count;
            }
            ++index;
        } while (index <= ranges[smallest]);
    }
    *result = output;
    return count;
}

}  // namespace Kaim

#endif
