#include "apt/apt_pair.hpp"
using namespace AptPS2;
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
