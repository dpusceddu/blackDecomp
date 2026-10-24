#ifndef BLACK_CAMPAIGN_GRAPH_TEAM_HPP
#define BLACK_CAMPAIGN_GRAPH_TEAM_HPP
#include "kynapse/graph/allocators.hpp"
#include "kynapse/classes/Kaim_CTeam.hpp"
namespace Kaim {
struct CTeam;
struct CEntity : CObject {
    void AddTeam(CTeam*) __asm__("func_002E4860");
    void RemoveTeam(CTeam*) __asm__("func_002E4B98");
};
struct CTeam : CObject {
    CTeam(unsigned int,const char*);
    virtual ~CTeam();
    virtual void *GetClassInfo();
    virtual bool Register(CEntity*);
    virtual void Unregister(CEntity*);
    virtual void SetFlag(unsigned char);
    virtual unsigned char Configure(ChildBuffers*);
    virtual unsigned char IsPrivate(ChildBuffers*);
    char *name;
    CVarList<CEntity*> *members;
    CVarList<CTeam*>::CIterator slot;
    unsigned char flag;
    static CTeam *FromIndex(unsigned int);
    unsigned int GetIndex();
};
struct TeamWorld {unsigned char unknown00[0x1c];CVarList<CTeam*> *teams;};
extern TeamWorld *gTeamWorld __asm__("D_003C9ED4");
typedef char TeamIteratorOffset[(unsigned int)&((CTeam*)0)->slot==0xc?1:-1];
typedef char TeamFlagOffset[(unsigned int)&((CTeam*)0)->flag==0x14?1:-1];
// Accessed prefixes only; unused CEntity members and CTeam registration state are UNVERIFIED.
}
#endif
