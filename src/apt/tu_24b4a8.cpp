#include "include_asm.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0024B4A8);

#ifdef NON_MATCHING
#include "apt/apt_pool.hpp"
using namespace AptPS2;
// Unmatched: native pooled-value helpers, string cleanup and switch allocation.
Value* PropertyValue::Read(int present,void* nameHandle) {
 PropertySpec* spec=0;
 if(present) {Token* token=*(Token**)nameHandle;spec=func_0024B4A8(token->text,token->hash);}
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0024B618);
#endif

#ifdef NON_MATCHING
#include "apt/apt_value.hpp"
using namespace AptPS2;
namespace AptPS2 {
struct Token { short refs;unsigned short unknown,length;short unknown6;char text[1]; };
extern "C" {
 extern Token D_003BFAF8;
 extern void* D_0043DEE0;
 extern char D_003FCD90,D_003FCD98,D_003FCDA0,D_003FCDA8,D_003FEFC0,D_003FEFC8;
 void func_00250198(void*,Token*,int);
 void* func_0024B4A8(char*,unsigned short);
 void func_0024C6D0(Value*,void*);
 int func_0035CA74(const char*,const char*);
 int func_0024C300(Value*);
 float func_0024C410(Value*);
}
struct TextHandle {
 Token* token;
 TextHandle():token(&D_003BFAF8) {++token->refs;}
 ~TextHandle() {if(!--token->refs)func_00250198(D_0043DEE0,token,token->length+9);}
 inline const char* Text() const {return token->text;}
 inline bool Equals(const char* text)const {return func_0035CA74(Text(),text)==0;}
};
}
// Unmatched: string temporary cleanup and property-switch register allocation.
int PropertyValue::Write(int present,void* nameHandle,Value* incoming)
{
 void* spec=0;
 if(present) {Token* name=*(Token**)nameHandle;spec=func_0024B4A8(name->text,name->unknown);}
 if(!spec)return 0;
 switch(*(int*)((char*)spec+4)) {
 case 1: {
  TextHandle text;func_0024C6D0(incoming,&text);
  if(text.Equals(&D_003FCD90)||text.Equals(&D_003FCD98))mode=0;
  else if(text.Equals(&D_003FCDA0))mode=2;
  else if(text.Equals(&D_003FCDA8))mode=1;
  else if(text.Equals(&D_003FEFC0)||text.Equals(&D_003FEFC8))mode=3;
  break;
 }
 case 3: {
  TextHandle text;func_0024C6D0(incoming,&text);
  if(text.Equals(&D_003FCD98))state|=0x10001;
  if(text.Equals(&D_003FEFC0)) {unsigned int old=state;state=old|0x10000;if(old&1)state^=1;}
  break;
 }
 case 5:index=func_0024C300(incoming)&0xffffff;break;
 case 6:func_0024C6D0(incoming,&text);return 1;
 case 7:otherIndex[0]=func_0024C300(incoming);break;
 case 8: {
  TextHandle text;func_0024C6D0(incoming,&text);
  if(text.Equals(&D_003FCD98))state|=0x100010;
  else if(text.Equals(&D_003FEFC0)) {unsigned int old=state;state=old|0x100000;if(old&0x10)state^=0x10;}
  else state=(state|0x10)^0x10;
  break;
 }
 case 10:otherIndex[1]=func_0024C300(incoming);break;
 case 11:otherIndex[2]=func_0024C300(incoming);break;
 case 14:real=func_0024C410(incoming);break;
 case 15: {
  TextHandle text;func_0024C6D0(incoming,&text);
  if(text.Equals(&D_003FCD98))state|=0x1000100;
  else if(text.Equals(&D_003FEFC0)) {unsigned int old=state;state=old|0x1000000;if(old&0x100)state^=0x100;}
  else state=(state|0x1000000)^0x100;
  break;
 }
 case 2:case 4:case 9:case 12:case 13:case 16:break;
 default:return 0;
 }
 return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0024BC80);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0024C0E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0024C300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0024C410);
