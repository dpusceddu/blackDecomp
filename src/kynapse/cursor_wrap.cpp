#include "include_asm.h"

#include "kynapse/leaf_functions.hpp"

void Cursor::Wrap()
{
    if (index == 0 || index >= list->count) {
        if (wrap)
            index = list->count - 1;
        else
            index = 0;
    }
    flag40 = false;
    flag41 = false;
    flag43 = false;
    flag48 = false;
    flag50 = false;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D64D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D6520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D6580);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D65A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D65C8);
