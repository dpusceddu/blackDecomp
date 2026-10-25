#ifndef BLACK_APT_POOL_HPP
#define BLACK_APT_POOL_HPP
// PS2 field-derived pool helpers; unverified until a matching consumer uses them.
#include "apt/apt_value.hpp"
namespace AptPS2 {
struct PropertySpec { int unknown; int code; };
struct Token { unsigned short refs,hash,length,pad;char text[1]; };
extern "C" void func_00387328(void*,int);
struct StringHandle {
 Token* token;
 StringHandle(const char*) __asm__("func_003872E0");
 ~StringHandle() {func_00387328(this,2);}
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
 extern Token D_003BFAF8;
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

#endif
