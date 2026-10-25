#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/accessways.hpp"
#endif

#ifdef NON_MATCHING
using namespace Kaim;
extern char D_00407D50[];
// Unmatched: vertex/edge iterator and grid lifetime context differs.
bool ComputeAccessWaysTraversal::Consider(SpatialNode *node){
 ComputeVisibilityTraversal grid;grid.origin.x=node->x;grid.origin.y=node->y;grid.origin.z=node->z;grid.owner=owner;
 grid.VisitNodes(graph);grid.VisitAll(graph);short n=grid.count;owner->counts[node->id]=n;int bytes=n<<1;short *block=new short[n];owner->lists[node->id]=block;memcpy(owner->lists[node->id],grid.values,bytes);
 if(owner->progress)owner->progress((unsigned int)(node->id*100)/graph->nodeCount);return true;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00392E50);
#endif
