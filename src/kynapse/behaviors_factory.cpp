#include "include_asm.h"

#include "kynapse/agents/factory.hpp"
namespace KaimFactory {

Engine*CreateEngine(InitConfig*config,ObjectRoot*context) {
 if(!IsStarted())return 0;unsigned int sum=0;for(unsigned int i=0;i<0x5b;++i)sum+=gCheckTable[i];if(sum!=0x4106)return 0;
 unsigned int i=0;for(;i<gSettings.engineSlots;++i)if(!gEngineSlots[i]){if(i>=gEnginesUsed)++gEnginesUsed;break;}
 Engine*e=new Engine(context);gEngine=e;if(!e->Init(config)){if(e)delete e;return 0;}e->slot=i;gEngineSlots[i]=e;return e;
}

TeamDefinition*GetTeamDefinition(Engine*e,const char*name){
 if(e){ChildData*config=e->config;if(!config)return 0;TeamDefinition*out=new TeamDefinition;ChildData*teams=config->FindByName("Teams");if(teams){ChildData*team=teams->FindChild("Team",name);if(!team)return 0;*static_cast<ChildData*>(out)=*team;return out;}}return 0;
}

EntityDefinition*MakeEntityDefinition(const char*name){EntityDefinition*out=new EntityDefinition;ChildData*c=out->AddChild();c->SetName(classKey);c->SetValue(name);return out;}

TeamDefinition*MakeTeamDefinition(const char*name){TeamDefinition*out=new TeamDefinition;ChildData*c=out->AddChild();c->SetName(classKey);c->SetValue(name);return out;}

void DestroyTeam(Team*t){for(Iterator<Entity*>it(t->entities->head);it.node;it.node=it.node->next)it.node->value->Detach((Handler*)t);gEngine->teams->Remove(t->node);delete t;}

void UpdateAll(float step){for(unsigned int i=0;i<gEnginesUsed;++i)if(gEngineSlots[i])gEngineSlots[i]->Update(step);}

int DestroyEntity(Entity*e){if(e->owner)e->owner->Unregister(e);gObjectList->Remove(e->globalNode);delete e;return 1;}

void DeleteEntity(Entity*e){delete e;}

void DeleteTeam(Team*t){delete t;}

void Method3(Entity*e,void*x){e->Method3(x);}

void Method4(Entity*e,unsigned char b){e->Method4(b);}
// Unmatched: entity-definition expansion retains temporary lifetimes and branch ordering differences.
// Unmatched: entity/team creation retains iterator-return copies and branch merging differences.
// Unmatched: the registered-entity forwarder retains an unresolved return contract and branch layout.
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E0410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E0750);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E0D20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1038);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1058);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E10B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E10D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E10F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E11A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1248);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1280);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E13B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1470);
