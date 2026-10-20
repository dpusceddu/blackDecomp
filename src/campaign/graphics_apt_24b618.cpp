#include "campaign/graphics/apt_pool.hpp"
using namespace AptPS2;
// Unmatched: native pooled-value helpers, string cleanup and switch allocation.
Value* PropertyValue::Read(int present,void* nameHandle) {
 PropertySpec* spec=0;
 if(present) {Token* token=*(Token**)nameHandle;spec=func_0024B4A8(token->text,token->length);}
 if(!spec)return 0;
 switch(spec->code) {
 case 1: {
  PooledValue* value=Text();
  switch(mode) {
  case 0:func_00387398(&value->value,&D_0043DC18+0x158);return (Value*)value;
  case 1:func_00387398(&value->value,&D_0043DC18+0x1f8);return (Value*)value;
  case 2:func_00387398(&value->value,&D_0043DC18+0xa4);return (Value*)value;
  default:return (Value*)D_0043DF40;
  }
 }
 case 3: if(state&0x10000)return (Value*)Boolean(state&1);break;
 case 5: if(index!=-1)return (Value*)Integer(index&0xffffff);break;
 case 6: if(text!=&D_003BFAF8) {PooledValue*value=Text();StringHandle string((char*)text+8);func_00387398(&value->value,&string);return (Value*)value;}break;
 case 7: if(otherIndex[0]!=-1)return (Value*)Integer(otherIndex[0]);break;
 case 8: if(state&0x100000)return (Value*)Boolean((state&0x10)!=0);break;
 case 10:if(otherIndex[1]!=-1)return (Value*)Integer(otherIndex[1]);break;
 case 11:if(otherIndex[2]!=-1)return (Value*)Integer(otherIndex[2]);break;
 case 14:if(real!=-1.0f)return (Value*)Real(real);break;
 case 15:if(state&0x1000000)return (Value*)Boolean((state&0x100)!=0);break;
 default:return 0;
 }
 return (Value*)D_0043DF40;
}
