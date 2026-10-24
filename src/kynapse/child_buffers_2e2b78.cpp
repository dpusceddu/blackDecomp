#include "include_asm.h"

// Child-buffer names are inferred from the PS2 layout and the parent reconstruction.
#include "kynapse/child_buffers.hpp"
namespace Kaim {
    

ChildBuffers* ChildBuffers::AddText(const char* text)
    {
        bool grow = false;
        if (count == 0) {
            capacity = 8;
            grow = true;
        }
        else if (count == capacity) {
            capacity = count * 2;
            grow = true;
        }
        if (grow) {
            ChildBuffers** grown = (ChildBuffers**)KaimAllocate(capacity * 4);
            for (unsigned int i = 0; i < count; ++i)
                grown[i] = items[i];
            if (count > 0)
                memoryRelease(items);
            items = grown;
        }
        ChildBuffers* child = new ChildBuffers(text);
        items[count] = child;
        ++count;
        return child;
    }
}
