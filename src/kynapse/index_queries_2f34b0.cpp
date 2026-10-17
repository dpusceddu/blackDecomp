// Ported from the companion project (an unpublished companion project).
#include "kynapse/index_queries.hpp"

namespace Kaim {
// /SLUS_213.76 0x2f34b0
bool IdHolder::Resolve(NameSource* source)
{
    if (!source)
        return false;
    const char* value = source->name;
    if (!value)
        return false;
    ItemList* registry = gEngine->FindByClass(&gTypeRegistryClass);
    if (!registry)
        return false;
    id = registry->IdByName(value);
    if (id)
        return true;
    return false;
}

}  // namespace Kaim
