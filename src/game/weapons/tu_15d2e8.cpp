#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: 0015D2E8: catalog/count load allocation remains two instructions apart.
#include "game/weapons/manager_methods.hpp"
namespace Weapons {
int WeaponManagerMethods::Valid(EeS8 id){int result=0;if(id>=0)result=id<((BkWeaponCatalogPS2*)catalog)->count;return result;}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0015D2E8);
#endif
