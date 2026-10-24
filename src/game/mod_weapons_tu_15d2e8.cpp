// Unmatched: 0015D2E8: catalog/count load allocation remains two instructions apart.
#if 0
#include "game/weapons/manager_methods.hpp"
namespace ModWeapons {
int WeaponManagerMethods::Valid(EeS8 id){int result=0;if(id>=0)result=id<((BkModWeaponCatalogPS2*)catalog)->count;return result;}
}
#endif
