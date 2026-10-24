#include "game/weapons/manager_methods.hpp"
#include "game/weapons/delayed.hpp"

namespace ModWeapons {
void WeaponManagerMethods::QueueDelayed(float time,float distance,Instance *source,
                                       int unused,Vec point,Vec direction,EeS8 flags)
{
    DelayedShotMethods *shot=(DelayedShotMethods*)delayed;
    EeS8 index=0;
    do {
        if(!shot->active) {
            shot->Initialize(time,distance,source,unused,point,direction,flags);
            return;
        }
        ++shot;
        ++index;
    } while(index<36);
}
}
