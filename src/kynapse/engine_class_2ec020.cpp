// Ported from the companion project (an unpublished companion project).
#include "kynapse/engine_class.hpp"

namespace Kaim {
// /SLUS_213.76 0x2ec020
Engine::Engine(Object* newContext)
{
    scale = 1.0f;
    context = newContext;
}

}  // namespace Kaim
