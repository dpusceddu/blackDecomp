#include "include_asm.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_245690", func_00245690);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_245690", func_00245838);

#ifdef NON_MATCHING
#include "apt/apt_function.hpp"
using namespace AptViews;
// Unmatched: original pooled constants and cached function-value constructor lifetimes.
Value* BuiltinValue::Lookup(Value* owner,Token** name)
{
 PropertySpec* spec=0;
 if(owner) {
  unsigned int bits=owner->flags;
  int present=0;
  if((bits>>25)==0x18)present=((int)bits>>4)&1;
  if(present&255)spec=func_00245690((*name)->text,(*name)->hash,name,present);
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_245690", func_00245840);
#endif
