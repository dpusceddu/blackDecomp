#ifndef BLACK_CAMPAIGN_GRAPH_META_ENTRIES_HPP
#define BLACK_CAMPAIGN_GRAPH_META_ENTRIES_HPP
#include "kynapse/compat.hpp"
#include "classes/kynapse/Kaim_CMetaClass_Kaim_CTeam_Kaim_CTeam_unsigned_int_const_char_6cbd356840f7.hpp"
// CTeam metadata identity is RTTI-backed. The second metadata owner remains
// unknown; its factory signature is provisional. Record fields and the registry
// prefix are verified by the matching PS2 constructors.
namespace Kaim {
struct CTeam;
struct UnknownMetaOwner;
template<class T,class Factory> struct CMetaClass {
    int index;
    Factory factory;
    char name[256];
    int attributes;
    unsigned int mask;
    virtual ~CMetaClass();
    CMetaClass(const char*,Factory,int,unsigned char,unsigned char);
};
typedef CTeam *(*TeamFactory)(unsigned int,const char*);
typedef UnknownMetaOwner *(*UnknownFactory)(unsigned int,const char*);
typedef CMetaClass<CTeam,TeamFactory> TeamMetadata;
typedef CMetaClass<UnknownMetaOwner,UnknownFactory> UnknownMetadata;
typedef char TeamMetadataSize[sizeof(TeamMetadata)==0x114?1:-1];
typedef char TeamMetadataNameOffset[(unsigned int)&((TeamMetadata*)0)->name==8?1:-1];
typedef char TeamMetadataMaskOffset[(unsigned int)&((TeamMetadata*)0)->mask==0x10c?1:-1];
template<class T> struct MetaRegistry {T *slots[256];int count;};
MetaRegistry<TeamMetadata> &TeamRegistry() __asm__("func_0038BE50");
MetaRegistry<UnknownMetadata> &UnknownRegistry() __asm__("func_00390168");
extern unsigned int MetaFlags __asm__("D_003C7A20");
extern "C" unsigned int func_002E10B8();
template<class T> inline bool RegisterMeta(MetaRegistry<T> &registry,T *entry,const char *name) {
    for(int i=0;i<registry.count;++i) {
        if(!strcmp(registry.slots[i]->name,name)){registry.slots[i]=entry;return true;}
    }
    if(registry.count==256)return false;
    registry.slots[registry.count]=entry;++registry.count;return true;
}
}
#endif
