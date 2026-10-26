#include "include_asm.h"

#include "kynapse/graph/meta_entries.hpp"
#include "kynapse/array_cleanup.h"

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/inline/graph_meta_entries", func_0038F2B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/inline/graph_meta_entries", func_0038F2F0);
extern "C" int D_003EBE60;
extern "C" void func_0038F508(Recovered_KynapseSmallArrayOwner* self, int flags) {
    KynapseSmallArray_Destroy(self, flags, &D_003EBE60);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/inline/graph_meta_entries", func_0038F668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/inline/graph_meta_entries", func_00390640);
