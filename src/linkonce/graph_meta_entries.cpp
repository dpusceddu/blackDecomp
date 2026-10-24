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
