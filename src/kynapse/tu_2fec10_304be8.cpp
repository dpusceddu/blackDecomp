#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/pathfinder.hpp"
#endif

#ifdef NON_MATCHING
namespace Kaim {
struct ServiceClass {int index;unsigned char unknown04[0x104];ServiceClass*parent;};
extern ServiceClass allowedServiceClass __asm__("D_00451778");
extern "C" void func_002E5218(CPathFinder*,const void*);
inline bool ServiceIsA(const ServiceClass*want,const ServiceClass*info){do{if(want==info)return true;info=info->parent;}while(info);return false;}
// Unmatched: remaining class-call context, lifetime or scheduling differences.
bool CPathFinder::InstallService(const void*descriptor){const ServiceClass*which=(const ServiceClass*)descriptor;if(!ServiceIsA(&allowedServiceClass,which))return false;ServiceObject *prior=serviceList[which->index];func_002E5218(this,which);if(!prior)serviceList[which->index]->SetGraph(graph);return true;}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00304BE8);
#endif
