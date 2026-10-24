// Methods recovered through PS2 class views; unknown original names retain their addresses.
#include "game/classes/UnknownVtable_003DC838.hpp"
#include "game/classes/UnknownVtable_003DC5F8.hpp"
#include "game/classes/UnknownVtable_003DC100.hpp"
#include "game/classes/UnknownVtable_003DB1F8.hpp"
#include "game/classes/UnknownVtable_003DB828.hpp"
#include "game/classes/UnknownVtable_003DC130.hpp"
#include "game/classes/other/UnknownVtable_003E07F8.hpp"
#include "game/classes/other/UnknownVtable_003E06C8.hpp"
#include "game/classes/other/UnknownVtable_003E0688.hpp"
#include "game/classes/other/UnknownVtable_003E0058.hpp"
#include "game/classes/other/UnknownVtable_003E0140.hpp"

namespace BlackPS2Classes {

unsigned short* UnknownVtable_003DC838::Function_00149158(unsigned char index)
{
    unsigned short* entries = Field_01B0();
    entries[index] = 0xffff;
    return entries;
}

// Unmatched: exact body, but its section leaves an unexplained zero gap before the next function.
#if 0
void UnknownVtable_003DC5F8::Function_00383920()
{
    Field_00C4() = 2;
}
#endif

void UnknownVtable_003E07F8::Function_001EE278(int active)
{
    if (active)
        Field_0054() = 0.0f;
    else
        Field_0054() = 1.0f;
}

void UnknownVtable_003E06C8::Function_001CDA00(void* data)
{
    unsigned int* fields = (unsigned int*)data;
    if (fields[2])
        fields[2] += (unsigned int)data;
    if (fields[1])
        fields[1] += (unsigned int)data;
}

void UnknownVtable_003E0688::Function_001CDAB0(void* data)
{
    unsigned int* fields = (unsigned int*)data;
    if (fields[2])
        fields[2] += (unsigned int)data;
    if (fields[1])
        fields[1] += (unsigned int)data;
    if (fields[3])
        fields[3] += (unsigned int)data;
}

int UnknownVtable_003E0058::Function_00384360(int value)
{
    return ((ABI_UnknownVtable_003E0058*)this)->Slot007(value);
}

int UnknownVtable_003E0140::Function_001ADF98(int value)
{
    return ((ABI_UnknownVtable_003E0140*)this)->Slot005(value);
}

int UnknownVtable_003DC100::Function_001653A8()
{
    unsigned char result = Field_001C();
    if (!result) {
        ((ABI_UnknownVtable_003DC100*)this)->Slot001();
        result = 1;
        Field_001C() = 1;
    }
    return result;
}

void UnknownVtable_003DB1F8::Function_00114160()
{
    Field_0010() = 0;
}

void UnknownVtable_003DB828::Function_00163DA8()
{
    Field_0080() ^= 1;
}

void UnknownVtable_003DC130::Function_001652E0()
{
    Field_0018() = 1;
}

}
