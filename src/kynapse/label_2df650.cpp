#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/label.hpp"

// /SLUS_213.76 0x2df650

void Label::SetChanged(char value)
{
    changed = value;
}
