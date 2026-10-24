// Ported from an unpublished companion project.
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x304d98
bool IsSet15C::IsSet() const { if (value != 0) return true; return false; }

// /SLUS_213.76 0x304da8
bool IsSet160::IsSet() const { if (value != 0) return true; return false; }
