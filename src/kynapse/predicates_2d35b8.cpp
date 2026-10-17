// Ported from the companion project (an unpublished companion project).
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x2d35b8
bool IsSet0C::IsSet() const { if (value != 0) return true; return false; }

// /SLUS_213.76 0x2d35c8
bool HasId2C::HasId() const { if (id != -1) return true; return false; }
