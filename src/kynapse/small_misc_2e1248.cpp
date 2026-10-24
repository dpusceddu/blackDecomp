// Ported from an unpublished companion project.
#include "kynapse/small_misc.hpp"

// /SLUS_213.76 0x2e1248
bool Notifiable_TryAccept(Notifiable* target, SlotUser* user)
{
    if (!target)
        return false;
    if (user->slot)
        return false;
    return target->Accept(user);
}
