#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/configure.hpp"

namespace Kaim {
// /SLUS_213.76 0x2fd8c8

bool RawDataUser::Apply(ChildBuffers* config)
{
    return Load(config->FindBySecond("RawData"));
}

}  // namespace Kaim

