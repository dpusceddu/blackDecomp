#include "include_asm.h"

// Methods recovered through PS2 class views; unknown original names retain their addresses.
#include "kynapse/classes/Kaim_CHideAgent.hpp"
#include "kynapse/classes/Kaim_CBasicAllocator.hpp"

namespace BlackPS2Classes {

int Kaim_CHideAgent::Function_002D5178()
{
    if (Field_0010())
        return Field_000C() != 0;
    return 0;
}

void Kaim_CBasicAllocator::Function_002E6F90(int value)
{
    Field_0010()(value);
}

void Kaim_CBasicAllocator::Function_002E7008(int value)
{
    Field_0014()(value);
}

}

