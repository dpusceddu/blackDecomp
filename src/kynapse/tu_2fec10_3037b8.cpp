#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/pathfinder.hpp"
#endif

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: remaining class-call context, lifetime or scheduling differences.
bool CPathFinder::SetGraph(NavigationGraph*newGraph)
{
 if(!newGraph){graph=0;routeTable=0;graphId=-1;looseGraph=0;}
 else{
  GraphRegistry*registry=gEngineHandle->FindByClass(&gGraphRegistryClass);if(!registry)return false;
  graph=newGraph;
  if(converter){const char*name=0;for(unsigned int i=0;i<registry->count;++i){if(registry->items[i]->graph==graph){name=registry->items[i]->name;break;}}if(name){if(!converter->NameToId(name,&graphId))graphId=-1;}else graphId=-1;}
  else graphId=-1;
  routeTable=(RouteTable*)registry->Find((int)newGraph,&gRouteTableClass);looseGraph=(NavigationGraph*)registry->Find((int)newGraph,&gLooseGraphClass);
 }
 for(unsigned int i=0;i<agentCount;++i)if(agentList[i])agentList[i]->SetGraph(graph);
 for(unsigned int i=0;i<serviceCount;++i)if(serviceList[i])serviceList[i]->SetGraph(graph);
 return true;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003037B8);
#endif
