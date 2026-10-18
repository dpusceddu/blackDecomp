// Child-buffer names are inferred from the PS2 layout and the parent reconstruction.
#include "kynapse/child_buffers.hpp"
namespace Kaim {
    ChildBuffers& ChildBuffers::operator=(const ChildBuffers& other)
    {
        if (this != &other) {
            DeleteChildren();
            if (first) memoryRelease(first);
            if (third) memoryRelease(third);
            if (second) memoryRelease(second);
            if (capacity) memoryRelease(items);
            unknown08 = other.unknown08;
            unknown04 = other.unknown04;
            if (other.first) {
                first = (char*)KaimAllocate(strlen(other.first) + 1);
                strcpy(first, other.first);
            }
            else first = 0;
            if (other.second) {
                second = (char*)KaimAllocate(strlen(other.second) + 1);
                strcpy(second, other.second);
            }
            else second = 0;
            unsigned int size = other.count;
            for (unsigned int i = 0; i < size; ++i)
            {
                ChildBuffers* child;
                if (i >= other.count) child = 0;
                else child = other.items[i];
                AddCopy(child);
            }
            if (other.third) {
                third = (char*)KaimAllocate(strlen(other.third) + 1);
                strcpy(third, other.third);
            }
            else third = 0;
        }
        return *this;
    }
}
