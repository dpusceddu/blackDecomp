#include "include_asm.h"

// Child-buffer names are inferred from the PS2 layout and the parent reconstruction.
#include "kynapse/child_buffers.hpp"
namespace Kaim {
    

ChildBuffers* ChildBuffers::FindByFirst(const char* key) const
    {
        if (!key) return 0;
        for (unsigned int i = 0; i < count; ++i)
            if (items[i]->first && !_stricmp(items[i]->first, key))
            return items[i];
        return 0;
    }
}
