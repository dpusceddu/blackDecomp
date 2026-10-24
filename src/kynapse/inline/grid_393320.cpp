#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/grid.hpp"

// /SLUS_213.76 0x393320

void Grid::AllocateFlags(const GridSource* source)
{
    flags = (char*)KaimAllocate(source->flagCount);
}

// /SLUS_213.76 0x393398
bool Grid::Classify(GridCell* cell)
{
    unsigned int index = cell->index;
    flags[index] = (char)Kaim_TestPoints(&origin, &cell->position, 0, 1);
    return true;
}

// /SLUS_213.76 0x3933f0
void Grid::AllocateValues(const GridSource* source)
{
    values = (short*)KaimAllocate(source->valueCount * 2);
    count = 0;
}
