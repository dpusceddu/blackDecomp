// Child-buffer names are inferred from the PS2 layout and the parent reconstruction.
#include "kynapse/child_buffers.hpp"
namespace Kaim {
    ChildBuffers::ChildBuffers(const char* text)
    {
        unknown04 = 0;
        capacity = 0;
        count = 0;
        unknown08 = 0;
        items = 0;
        first = (char*)KaimAllocate(strlen(text) + 1);
        strcpy(first, text);
        second = 0;
        third = 0;
    }
}
