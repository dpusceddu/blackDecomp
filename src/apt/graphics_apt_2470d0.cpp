#include "apt/apt_pair.hpp"
using namespace AptPS2;
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
