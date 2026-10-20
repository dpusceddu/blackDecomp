#ifndef BLACK_CAMPAIGN_APT_FUNCTION_HPP
#define BLACK_CAMPAIGN_APT_FUNCTION_HPP
// PS2 field-derived view; native constructor remains unverified.
#include "campaign/graphics/apt_pool.hpp"
namespace AptPS2 {
struct NativeFunction:Value {
 char unknown08[0x14];
 int options;
 void (*callback)();
};
struct BuiltinValue:Value {Value*Lookup(Value*,Token**);};
extern "C" {
 PropertySpec* func_00245690(const char*,unsigned short,Token**,int);
 NativeFunction* func_0024FA38(void*,int);
 void func_00248678(void*,int);
 extern void* D_0043DEE4;
 extern char D_003E1F88,D_003E1DF0;
 extern NativeFunction *D_003BF024,*D_003BF028,*D_003BF02C,*D_003BF030,*D_003BF034,*D_003BF038,*D_003BF03C,*D_003BF040;
 void func_00246060();void func_00246248();void func_00246308();void func_00246420();void func_00246560();void func_00246638();void func_002467B0();void func_00246A78();
}
inline NativeFunction* Function(NativeFunction*& slot,void(*callback)()) {
 NativeFunction* value=slot;
 if(!value) {
  value=func_0024FA38(D_0043DEE4,36);
  func_00386EC8((PooledValue*)value,9);
  *(void**)((char*)value+4)=&D_003E1F88;
  func_00248678((char*)value+8,8);
  *(unsigned char*)&value->options=0;
  *(void**)((char*)value+4)=&D_003E1DF0;
  value->callback=callback;
  value->options&=~0x100;
  value->options&=~0x200;
  slot=value;
  value->flags=(value->flags&0xff03ffff)|0x40000;
  slot->AddRef();
 }
 return slot;
}
}

#endif
