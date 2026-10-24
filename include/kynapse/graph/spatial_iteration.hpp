#ifndef BLACK_CAMPAIGN_GRAPH_SPATIAL_ITERATION_HPP
#define BLACK_CAMPAIGN_GRAPH_SPATIAL_ITERATION_HPP
#include "kynapse/graph/spatial.hpp"
namespace Kaim {
// Unsigned sentinels, indexed access and counter lifetimes are verified by
// the complete matching RemoveNode implementation.
template<bool incoming>inline SpatialEdge *IncidentEdge(SpatialNode *node,unsigned int which){
 CSpatialGraph *g=node->graph;
 int *heads=incoming?g->firstEdgeTo:g->firstEdgeFrom;
 if(!heads){unsigned int found=0,slot=0,seen=0;
  while(seen<g->EdgeCount()){
   SpatialEdge *edge=g->edges+slot;
   if(edge->GetIndex()!=(unsigned int)-1){++seen;if((unsigned int)(incoming?g->edgeEnd[slot]:g->edgeStart[slot])==node->id.value){if(found==which)return g->edges+slot;++found;}}
   ++slot;
  }
 }else{unsigned int found=0;for(unsigned int i=heads[node->id];i!=(unsigned int)-1;i=(incoming?g->edgeNext:g->edgeTable40)[i]){if(found==which)return g->edges+i;++found;}}
 return 0;
}
}
#endif
