#include "include_asm.h"

#include "kynapse/graph/team.hpp"
namespace Kaim {

CTeam::CTeam(unsigned int count,const char *teamName) {
    flag=0;
    if(teamName) {name=(char*)Allocate(func_0035CCD8(teamName)+1);func_0035CBC0(name,teamName);}
    else name=0;
    members=new CVarList<CEntity*>(count);
}
void CTeam::Unregister(CEntity *entity) {
    entity->RemoveTeam(this);
    for(CVarList<CEntity*>::CIterator i(members->head);i.node;++i) {
        if(i.node->value==entity) {members->Remove(i);return;}
    }
}
unsigned int CTeam::GetIndex() {
    if(!slot.node)return (unsigned int)-1;
    return ((unsigned int)slot.node-(unsigned int)gTeamWorld->teams->storage)/20U;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_team", func_002EC4B0);
#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: iterator temporary ownership and unsigned index return layout.
bool CTeam::Register(CEntity *entity) {
    if(members->activeCount==members->capacity)return false;
    CEntity *item=entity;
    members->Insert(item,CVarList<CEntity*>::CIterator(0));
    entity->AddTeam(this);
    return true;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_team", func_002EC5B8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_team", func_002EC7D8);
