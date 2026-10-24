#include "apt/apt_pair.hpp"
using namespace AptPS2;
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
