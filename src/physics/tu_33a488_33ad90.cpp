#include "include_asm.h"

// Segment ray queries and the bounded hit buffer.
#include "physics/segment_query.hpp"
#include "ps2/matrix.hpp"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_33a488_33ad90", func_0033A488);






static inline int Complete(const PhysicsSegmentQuery* query){
 int complete=0;
 if(query->rootCursor==query->rootCount&&!*(unsigned*)((char*)query+0x50)&&!query->compoundCount&&!query->leafCount)complete=1;
 return complete;
}
template<class T>static inline T LocalMin(const T& a,const T& b){return a<b?a:b;}
PhysicsSegmentHit* PhysicsSegmentQuery::FindNearest(){
 unsigned found=0;mode=2;unsigned limit=5;unsigned count=capacity;maxHits=LocalMin(limit,count);
 PhysicsSegmentHit closest;
 while(!Complete(this)){
  unsigned count=Execute();
  for(unsigned i=0;i<count;++i){
   if(found){if(closest.fraction>hits[i].fraction){closest=hits[i];fractionLimit=closest.fraction;}}
   else{found=1;closest=hits[i];}
  }
 }
 if(found){*hits=closest;return hits;}return 0;
}

extern "C" PhysicsStorageRequirement *func_0033AD90(PhysicsStorageRequirement *storage, s32 first, s32 second)
{
  int new_var;
  new_var = 0x110;
  storage->alignment = 0x10;
  storage->size = (s32) (((((((first << 5) << 2) + new_var) + (second << 7)) + (second * 0x60)) + (second * 0xD0)) + 0x2880);
  return storage;
}


int PhysicsSegmentQuery::CollectHits()
{
    mode = 0;
    maxHits = capacity;
    return Execute();
}

PhysicsSegmentHit* PhysicsSegmentQuery::AnyHit()
{
    mode = 1;
    maxHits = 1;
    if (Execute())
        return hits;
    return 0;
}


extern "C" void func_0033AC48(int,int);
extern "C" void func_0033AEA8(){func_0033AC48(1,65535);}
extern "C" void func_0033AEC8(){func_0033AC48(0,65535);}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_33a488_33ad90", func_0033AC48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_33a488_33ad90", func_0033ADD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_33a488_33ad90", func_0033AE38);
