// Ported from the companion project (an unpublished companion project).
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x2d63c0
bool IsSet0C::IsSet() const { if (value != 0) return true; return false; }

// /SLUS_213.76 0x2d63d0
bool IsSet10::IsSet() const { if (value != 0) return true; return false; }
