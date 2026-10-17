// Ported from the companion project (an unpublished companion project).
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x2d5238
bool IsSet50::IsSet() const { if (value != 0) return true; return false; }
