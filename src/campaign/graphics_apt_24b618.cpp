#include "campaign/graphics/apt_value.hpp"
using namespace AptPS2;
namespace AptPS2 {
struct PropertySpec { int unknown; int code; };
struct Token { unsigned short refs,length;int unknown;char text[1]; };
struct StringHandle {
 Token* token;
 StringHandle(const char*) __asm__("func_003872E0");
 ~StringHandle() __asm__("func_00387328");
};
struct PooledValue {
 int flags; void* table;
 union { PooledValue* next; int integer; float real; unsigned char boolean; } value;
 PooledValue* textNext;
 inline void Revive() {
  flags|=4;
  D_003BE8E0->Queue((Value*)this);
 }
};
extern "C" {
 PropertySpec* func_0024B4A8(const char*,unsigned short);
 void* func_00250058(void*,int);
 PooledValue* func_00386EC8(PooledValue*,int);
 PooledValue* func_0024AD08(void*);
 int func_003872A8(void*);
 void func_002530E8(void*,int);
 void func_00387398(void*,const void*);
 extern PooledValue *D_003BFAE4,*D_003BFAE8,*D_003BFAEC,*D_003BFB10,*D_0043DF40;
 extern void* D_0043DEE0;
 extern char D_003E2120,D_003E2098,D_003E2230,D_0043DC18;
 extern unsigned short D_003BFAF8;
}
inline PooledValue* Integer(int value) {
 PooledValue* result=D_003BFAEC;
 if(result) {D_003BFAEC=result->value.next;result->Revive();result->value.integer=value;}
 else {result=(PooledValue*)func_00250058(D_0043DEE0,12);func_00386EC8(result,7);result->value.integer=value;result->table=&D_003E2230;}
 return result;
}
inline PooledValue* Boolean(unsigned char value) {
 PooledValue* result=D_003BFAE4;
 if(result) {D_003BFAE4=result->value.next;result->Revive();result->value.boolean=value;}
 else {result=(PooledValue*)func_00250058(D_0043DEE0,12);func_00386EC8(result,5);result->value.boolean=value;result->table=&D_003E2120;}
 return result;
}
inline PooledValue* Real(float value) {
 PooledValue* result=D_003BFAE8;
 if(result) {D_003BFAE8=result->value.next;result->Revive();result->value.real=value;}
 else {result=(PooledValue*)func_00250058(D_0043DEE0,12);func_00386EC8(result,6);result->value.real=value;result->table=&D_003E2098;}
 return result;
}
inline PooledValue* Text() {
 PooledValue* result=D_003BFB10;
 if(result) {D_003BFB10=result->textNext;result->Revive();if(!func_003872A8(&result->value))func_002530E8(&result->value,0);}
 else result=func_0024AD08(func_00250058(D_0043DEE0,16));
 return result;
}
}
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
