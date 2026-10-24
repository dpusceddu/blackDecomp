#include "game/camera/axes.hpp"
namespace ActorInventory7 {
extern "C" {extern AxisWorld*D_0040F4D0;float func_00124840(void*,int);int func_0013EE28(void*);}
inline AxisWorld*GetWorld(){return D_0040F4D0;}
void InputAxes::Update(){if(func_00124840(input,1)!=0)lateral+=func_00124840(input,1)*GetWorld()->delta;else if(func_00124840(input,2)!=0)lateral-=func_00124840(input,2)*GetWorld()->delta;if(func_00124840(input,3)!=0)forward+=func_00124840(input,3)*GetWorld()->delta;else if(func_00124840(input,4)!=0)forward-=func_00124840(input,4)*GetWorld()->delta;}
int InputBinding::Clear(){if(!func_0013EE28(this))return 0;input=0;active=0;return 1;}
}
// Unmatched: 0x13db40 native field/helper allocation and scheduling.
// Unmatched: 0x13dc00 native field/helper allocation and scheduling.
// Unmatched: 0x13df58 matrix copy and axis-angle helper contracts.
// Unmatched: 0x13eb00 native field/helper allocation and scheduling.
// Unmatched: 0x13ec38 normalization and persistent dot temporary context.
// Unmatched: 0x13ed98 native field/helper allocation and scheduling.
// Unmatched: 0x13ef28 signed-angle normalization and vector spill context.
// Unmatched: 0x13f0d8 native field/helper allocation and scheduling.
// Unmatched: 0x13f328 native field/helper allocation and scheduling.
// Unmatched: 0x13f3e0 configuration reader argument scheduling and field types.
// Unmatched: 0x13f618 input predicates and vector temporary lifetimes.
// Unmatched: 0x140068 vector lvalue normalization and component helper context.
// Unmatched: 0x140468 native field/helper allocation and scheduling.
// Unmatched: 0x1404a8 FPU allocation and scheduling.
// Unmatched: 0x1407c8 inverse matrix and vector temporary context.
