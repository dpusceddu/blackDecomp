#ifndef BLACK_GRAPH_NEAREST_HPP
#define BLACK_GRAPH_NEAREST_HPP
#include "kynapse/graph/tables.hpp"
#include "kynapse/classes/Kaim_CFindNearestData.hpp"
namespace Kaim {
struct CFindNearestData : CGraphData {
    virtual ~CFindNearestData();
    virtual int Init(ChildBuffers *);
    virtual int Build();
    virtual int Save(const void *);
    int count;
    int *order, *rank, *aux;
    void (*progress)(int);
    void CopyRank(const int *);
    void CopyOrder(const int *);
    int LoadFile(const void *);
    int Load(const void *) __asm__("func_002EF1A0");
    int EqualBoundary(int, int, unsigned char, float) __asm__("func_002F02E8");
    int FindBound(int, unsigned char, float);
    inline SearchNode *OrderedNode(int axis, int index) { return graph->GetNode(order[axis * count + index]); }
    int CollectColumn(const Vec3 *, int **, float);
    int CollectBox(const Vec3 *, int **, float);
    float Coordinate(const Vec3 *, int) __asm__("func_00390038");
    int GetRange(const Vec3 *, int, int *, int *, float) __asm__("func_002F0AD8");
    inline float DefaultRadius() const { return *(const float *)((const char *)graph + 8); }
};
// Offset assertions preserve the PS2 prefix. Complete size and unused methods
// remain UNVERIFIED until additional members are matched.
#define NEAREST_OFFSET(member, offset) typedef char CFindNearestData_##member##_offset[(unsigned int)&((CFindNearestData *)0)->member == offset ? 1 : -1]
NEAREST_OFFSET(count,8);
NEAREST_OFFSET(order,12);
NEAREST_OFFSET(rank,16);
NEAREST_OFFSET(aux,20);
NEAREST_OFFSET(progress,24);
#undef NEAREST_OFFSET
}
#endif
