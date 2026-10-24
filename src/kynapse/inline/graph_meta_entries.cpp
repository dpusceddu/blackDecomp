#include "include_asm.h"

#include "kynapse/graph/meta_entries.hpp"

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F190);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F1D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F200);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F2A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F2B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F2F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F330);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F3A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F3E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F458);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F490);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F508);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F5E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F618);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038F668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038FF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038FFC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038FFD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038FFD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038FFE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038FFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038FFF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0038FFF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390038);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003900D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003901C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003901F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390248);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390270);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003902A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003902F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390308);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390310);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390318);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390350);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003903A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003903B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003903B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003903F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390450);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390458);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390460);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390580);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003905A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003905E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390630);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003906C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003906F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390748);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390768);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003907A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003907F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00390808);
