#include "campaign/weapons/manager_methods.hpp"

namespace ModWeapons {
extern "C" int func_00159148(Instance*);

void WeaponManagerMethods::ReleaseInstance(Instance *instance)
{
    EeS8 index=0;
    if(instance) {
        Instance *cursor=instances;
        while(instance!=cursor) {
            ++cursor;
            ++index;
        }
        func_00159148(instances+index);
        instanceFlags[index]=0;
    }
}
}
