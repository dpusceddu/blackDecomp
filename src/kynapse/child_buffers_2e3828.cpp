#include "include_asm.h"

// Child-buffer names are inferred from the PS2 layout and the parent reconstruction.
#include "kynapse/child_buffers.hpp"
namespace Kaim {
    

void ChildBuffers::RemoveChild(ChildBuffers* child)
    {
        unsigned int i;
        for (i = 0; i < count; ++i)
            if (items[i] == child) break;
        if (i < count && child) delete child;
        for (++i; i < count; ++i) items[i - 1] = items[i];
        items[count - 1] = 0;
        --count;
    }
}
