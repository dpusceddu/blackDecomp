#include "include_asm.h"

#ifdef NON_MATCHING
#include "apt/apt_pair.hpp"
using namespace AptViews;
// Unmatched: pooled text construction and named-property branch lifetimes.
Value* TextPair::Read(int unused,Token** name)
{
 if(func_0035CA74((*name)->text,&D_003FE460)==0) {
  PooledValue* result=Text();StringHandle string(first.token->text);
  func_00387398(&result->value,&string);return (Value*)result;
 }
 if(func_0035CA74((*name)->text,&D_003FE468)==0) {
  PooledValue* result=Text();StringHandle string(second.token->text);
  func_00387398(&result->value,&string);return (Value*)result;
 }
 if(func_0035CA74((*name)->text,&D_003FD8A8)==0)return Function(D_003BF044,func_00247560);
 return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_246060_2470d0", func_002470D0);
#endif

#ifdef NON_MATCHING
#include "apt/apt_pair.hpp"
using namespace AptViews;
// Unmatched: named string-property temporary and shared cleanup block.
int TextPair::Write(int unused,Token** name,Value* incoming)
{
 if(func_0035CA74((*name)->text,&D_003FE460)==0) {
  TextHandle string;func_0024C6D0(incoming,&string);func_00253058(&first,&string);return 1;
 }
 if(func_0035CA74((*name)->text,&D_003FE468)==0) {
  TextHandle string;func_0024C6D0(incoming,&string);func_00253058(&second,&string);return 1;
 }
 return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_246060_2470d0", func_00247388);
#endif

#ifdef NON_MATCHING
#include "apt/apt_pair.hpp"
using namespace AptViews;
// Unmatched: typed string destruction and deleting-destructor convention.
void TextPair::Destroy(int flags)
{
 *(void**)((char*)this+4)=&D_003E1320;
 second.~TextHandle();first.~TextHandle();
 *(void**)((char*)this+4)=&D_003E1E78;
 func_002486D8((char*)this+8,2);
 func_00387020(this,0);
 if(flags&1)func_0024FA98(D_0043DEE4,this,40);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_246060_2470d0", func_00247488);
#endif
