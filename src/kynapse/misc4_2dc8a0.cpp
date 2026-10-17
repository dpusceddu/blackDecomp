// Ported from the companion project (an unpublished companion project).
#include "kynapse/misc4.hpp"

// /SLUS_213.76 0x2dc8a0
bool NameList::FindIndex(const char* name, unsigned int* index)
{
    *index = 0;
    if (count > 0) {
        do {
            if (!_stricmp(name, names[*index]))
                return true;
            ++*index;
        } while (*index < count);
    }
    return false;
}
