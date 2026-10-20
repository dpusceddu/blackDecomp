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
using namespace AptPS2;
// Unmatched: native pooled constants and cached function-value constructor lifetimes.
Value* BuiltinValue::Lookup(Value* owner,Token** name)
{
 PropertySpec* spec=0;
 if(owner) {
  unsigned int bits=owner->flags;
  int present=0;
  if((bits>>25)==0x18)present=((int)bits>>4)&1;
  if(present&255)spec=func_00245690((*name)->text,(*name)->length,name,present);
 }
 if(!spec)return 0;
 switch(spec->code) {
 case 1:return (Value*)Integer(8);case 2:return (Value*)Integer(20);
 case 3:return (Value*)Integer(17);case 4:return (Value*)Integer(46);
 case 5:return (Value*)Integer(40);case 6:return (Value*)Integer(35);
 case 7:return (Value*)Integer(13);case 8:return (Value*)Integer(27);
 case 9:return (Value*)Integer(36);case 10:return (Value*)Integer(45);
 case 11:return (Value*)Integer(37);case 12:return (Value*)Integer(34);
 case 13:return (Value*)Integer(33);case 14:return (Value*)Integer(39);
 case 15:return (Value*)Integer(16);case 16:return (Value*)Integer(32);
 case 17:return (Value*)Integer(9);case 18:return (Value*)Integer(38);
 case 100:return Function(D_003BF024,func_00246060);
 case 101:return Function(D_003BF028,func_00246248);
 case 102:return Function(D_003BF02C,func_00246308);
 case 103:return Function(D_003BF034,func_00246560);
 case 104:return Function(D_003BF038,func_00246638);
 case 105:return Function(D_003BF03C,func_002467B0);
 case 106:return Function(D_003BF040,func_00246A78);
 case 107:return Function(D_003BF030,func_00246420);
 default:return 0;
 }
}
