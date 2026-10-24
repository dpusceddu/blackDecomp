#include "kynapse/graph/allocators.hpp"
namespace Kaim {
CBaseAllocator::~CBaseAllocator() { delete children; }
CAllocator::~CAllocator() {}
CPoolBasedAllocator::~CPoolBasedAllocator() {
    if(owner)((CAllocator*)owner)->Release((unsigned int)buffer);
    if(next)next->Remove(this);
}
}
