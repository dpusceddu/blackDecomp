#include "include_asm.h"

#include "kynapse/graph/meta_entries.hpp"
#include "kynapse/array_cleanup.h"
#include "kynapse/graph_index.h"

namespace Kaim {

template<> CMetaClass<CTeam,TeamFactory>::CMetaClass(const char *source,TeamFactory fn,int flags,unsigned char allocateMask,unsigned char publishMask) {
    char *entryName=name;
    strcpy(entryName,source);
    if(!RegisterMeta(TeamRegistry(),this,entryName))index=-1;
    else index=TeamRegistry().count-1;
    factory=fn;attributes=flags;
    if(allocateMask==1)mask=func_002E10B8();else mask=0;
    if(publishMask)MetaFlags|=mask;
}
template<> CMetaClass<UnknownMetaOwner,UnknownFactory>::CMetaClass(const char *source,UnknownFactory fn,int flags,unsigned char allocateMask,unsigned char publishMask) {
    char *entryName=name;
    strcpy(entryName,source);
    if(!RegisterMeta(UnknownRegistry(),this,entryName))index=-1;
    else index=UnknownRegistry().count-1;
    factory=fn;attributes=flags;
    if(allocateMask==1)mask=func_002E10B8();else mask=0;
    if(publishMask)MetaFlags|=mask;
}
}

extern "C" Recovered_KynapseGraphRecord* func_0038F2B0(Recovered_KynapseGraphIterator* it) {
    Recovered_KynapseGraphIndexOwner* owner = it->owner;
    if (it == &owner->end) return &owner->firstDefault;
    return &owner->records[owner->firstIndices[it->index]];
}
extern "C" Recovered_KynapseGraphRecord* func_0038F2F0(Recovered_KynapseGraphIterator* it) {
    Recovered_KynapseGraphIndexOwner* owner = it->owner;
    if (it == &owner->end) return &owner->secondDefault;
    return &owner->records[owner->secondIndices[it->index]];
}
extern "C" int D_003EBE60;
extern "C" void func_0038F508(Recovered_KynapseSmallArrayOwner* self, int flags) {
    KynapseSmallArray_Destroy(self, flags, &D_003EBE60);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/inline/graph_meta_entries", func_0038F668);
/* Partial point view; the leading field and complete extent are UNVERIFIED. */
typedef struct Recovered_KynapseDistanceVector {
    float x, y, z;
} Recovered_KynapseDistanceVector;
typedef struct Recovered_KynapseDistancePoint {
    int unk_00;
    Recovered_KynapseDistanceVector position;
} Recovered_KynapseDistancePoint;

static inline float KynapseGraphDistance(const Recovered_KynapseDistanceVector* a,
                                         const Recovered_KynapseDistanceVector* b) {
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dz = a->z - b->z;
    return sqrtf(dz * dz + dx * dx + dy * dy);
}

extern "C" int func_00390640(void* context, int mode, const Recovered_KynapseDistancePoint* a,
                             const Recovered_KynapseDistancePoint* b, float* out) {
    const Recovered_KynapseDistanceVector* pb = &b->position;
    const Recovered_KynapseDistanceVector* pa = &a->position;
    *out = KynapseGraphDistance(pa, pb);
    return 1;
}
