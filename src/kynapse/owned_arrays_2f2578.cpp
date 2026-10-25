#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/owned_arrays.hpp"
#ifdef NON_MATCHING
#include "kynapse/graph/manager.hpp"
#endif

namespace Kaim {
// /SLUS_213.76 0x2f2578

PoolArray::~PoolArray()
{
    for (unsigned int i = 0; i < count; ++i) {
        if (items[i])
            delete items[i];
        items[i] = 0;
    }
    memoryRelease(items);
    items = 0;
    ReleaseSharedPool();
}

}  // namespace Kaim

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: lookup branch placement and allocation-loop scheduling.
bool CGraphManager::AddGraph(const char*name,CSpatialGraph *graph,unsigned char update){
 if(!name||!graph)return 0;
 if(!FindGraph(name)){
 if(count==capacity){capacity+=capacity;CGraphMap **grown=new CGraphMap*[capacity];for(unsigned int i=0;i<count;++i)grown[i]=items[i];D_003C87E0(items);items=grown;}
 items[count]=new CGraphMap(name,graph,update);++count;return true;}return false;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F2BF8);
#endif
