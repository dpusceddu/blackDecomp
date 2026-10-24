// Ported from an unpublished companion project.
#include "kynapse/forwarders.hpp"

// /SLUS_213.76 0x2e1280
bool Entity_Query(EntityObject* entity, int argument)
{
    if (!entity)
        return false;
    return entity->Query(argument);
}
