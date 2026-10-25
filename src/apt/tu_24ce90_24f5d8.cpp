#include "include_asm.h"

#ifdef NON_MATCHING
#include "apt/apt_value.hpp"
using namespace AptViews;
// Unmatched: reference-count and collection helper scheduling.
void Value::Release()
{
 unsigned int next=((flags>>6)&0xfff)-1;
 unsigned int count=next;
 if(next>=0x1000) {count=0xfff;flags=(flags&0xfeffffff)|0x1000000;}
 flags=(flags&0xfffc003f)|((count&0xfff)<<6);
 if(next==0 && (!D_0040DE48 || !RetainForCollection())) {
  if(Permanent()) flags=(flags&0xfffc003f)|0x3ffc0;
  else if(!Deferred()) Dispose();
  else if(!Queued()) {
   if(!D_003BE8E0->Full()) {
    flags|=4;
    D_003BE8E0->Queue(this);
   } else Dispose();
  }
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24f5d8", func_0024F5D8);
#endif
