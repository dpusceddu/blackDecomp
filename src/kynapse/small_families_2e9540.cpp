// Ported from the companion project (an unpublished companion project).
#include "kynapse/small_families.hpp"

// /SLUS_213.76 0x2e9540
void ParameterTables::SetFloatB(int index, float value)
{
    if (index >= 0 && (unsigned int)index < countB)
        floatsB[index] = value;
}

// /SLUS_213.76 0x2e9570
void ParameterTables::SetFloatC(int index, float value)
{
    if (index >= 0 && (unsigned int)index < countB)
        floatsC[index] = value;
}

// /SLUS_213.76 0x2e95a0
void ParameterTables::SetIntB(int index, int value)
{
    if (index >= 0 && (unsigned int)index < countB)
        intsB[index] = value;
}

// /SLUS_213.76 0x2e95d0
void ParameterTables::SetFloatA(int index, float value)
{
    if (index >= 0 && (unsigned int)index < countA)
        floatsA[index] = value;
}

// /SLUS_213.76 0x2e9600
void ParameterTables::SetFloatC2(int index, float value)
{
    if (index >= 0 && (unsigned int)index < countC)
        floatsC2[index] = value;
}
