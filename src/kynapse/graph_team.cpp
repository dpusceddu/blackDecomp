#include "include_asm.h"

#include "kynapse/graph/team.hpp"
namespace Kaim {

CTeam::CTeam(unsigned int count,const char *teamName) {
    flag=0;
    if(teamName) {name=(char*)Allocate(func_0035CCD8(teamName)+1);func_0035CBC0(name,teamName);}
    else name=0;
    members=new CVarList<CEntity*>(count);
}
// Unplaced draft, not compiled: readable code kept for reference whose PS2 address is not established (docs/units.md, "Drafts").
#if 0
// Unmatched: iterator temporary ownership and unsigned index return layout.
CTeam::~CTeam() {
    while(members->head)Unregister(members->head->value);
    if(name)D_003C87E0(name);
    delete members;
}
#endif
// Unplaced draft, not compiled: readable code kept for reference whose PS2 address is not established (docs/units.md, "Drafts").
#if 0
// Unmatched: iterator temporary ownership and unsigned index return layout.
bool CTeam::Register(CEntity *entity) {
    if(members->activeCount==members->capacity)return false;
    CEntity *item=entity;
    members->Insert(item,CVarList<CEntity*>::CIterator(0));
    entity->AddTeam(this);
    return true;
}
#endif
void CTeam::Unregister(CEntity *entity) {
    entity->RemoveTeam(this);
    for(CVarList<CEntity*>::CIterator i(members->head);i.node;++i) {
        if(i.node->value==entity) {members->Remove(i);return;}
    }
}
// Unplaced draft, not compiled: readable code kept for reference whose PS2 address is not established (docs/units.md, "Drafts").
#if 0
// Unmatched: iterator temporary ownership and unsigned index return layout.
CTeam *CTeam::FromIndex(unsigned int index) {
    CVarList<CTeam*>::CIterator i=gTeamWorld->teams->At(index);
    if(i.node && i.node->active)return i.node->value;
    return 0;
}
#endif
unsigned int CTeam::GetIndex() {
    if(!slot.node)return (unsigned int)-1;
    return ((unsigned int)slot.node-(unsigned int)gTeamWorld->teams->storage)/20U;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EC4B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EC5B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EC7D8);
