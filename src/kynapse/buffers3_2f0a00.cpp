#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/buffers3.hpp"

// /SLUS_213.76 0x2f0a00

BoundBuffers::BoundBuffers(BufferOwner* bound)
    : BoundBase(bound)
{
    handle = bound->handle;
    first = 0;
    second = 0;
    third = 0;
    count = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F0A30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F0AD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F0B98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F0C80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F0D68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F0D88);
