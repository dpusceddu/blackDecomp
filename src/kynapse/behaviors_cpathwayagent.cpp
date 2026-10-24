#include "include_asm.h"

#include "kynapse/behaviors/pathway.hpp"
// Unmatched: the remaining C++ member context is still being recovered.

#include "kynapse/behaviors/pathway.hpp"
namespace Kaim {

PathWayAgent* PathWayAgent::Create(Context* context) { return new PathWayAgent(context); }
}

namespace Kaim {
void PathWayAgent::SetPathWay(PathWay* path) {
    if(pathWay==path)return;
    pathWay=path;
    if(pointIndex==0 || pointIndex>=path->count) {
        if(reverse)pointIndex=path->count-1;else pointIndex=0;
    }
    waiting=false;finished=false;paused=false;rotating=false;orienting=false;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D5498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D5650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D59F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D61B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D6218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D6278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D62D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D63C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D63D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D63E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D6440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D6460);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D6480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D64D8);
