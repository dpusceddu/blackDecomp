// Ported from the companion project (an unpublished companion project).
#include "kynapse/source_objects.hpp"

namespace Kaim {
// /SLUS_213.76 0x2f36a8
SquareTable::SquareTable(Description* newSource)
    : ObjectWithSource(newSource), unknown10(0), unknown14(0)
{
    size = newSource->size;
    if (size)
        cells = (unsigned char*)KaimAllocate(size * size);
    else
        cells = 0;
}

}  // namespace Kaim
