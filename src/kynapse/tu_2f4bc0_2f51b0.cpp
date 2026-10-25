#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/path_manager.hpp"
#endif

#ifdef NON_MATCHING
using namespace Kaim;
// Unmatched: mirror-call virtual target registers differ despite matching control flow.
bool CPathObjectManager::Add(CPathObject *object)
{
    if (count >= capacity)
        return false;
    items[count] = object;
    ++count;
    if (!registry) {
        registry = (PathTypeRegistry*)func_002EC058(D_003C9ED4, &pathTypeRegistryClass);
        if (!registry)
            return false;
        for (unsigned int t = 0; t < registry->count; ++t) {
            PathTypeEntry *type = registry->entries[t];
            if (type->mirrored) {
                for (unsigned int i = 0; i < count; ++i)
                    items[i]->MirrorType(type->typeId);
            }
        }
    } else {
        for (unsigned int t = 0; t < registry->count; ++t) {
            PathTypeEntry *type = registry->entries[t];
            if (type->mirrored)
                object->MirrorType(type->typeId);
        }
    }
    return true;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2f4bc0_2f51b0", func_002F51B0);
#endif
