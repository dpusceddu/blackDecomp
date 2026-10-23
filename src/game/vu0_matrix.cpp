#include "ps2/matrix.hpp"
using BlackPS2::VU0::Value;
extern "C" {
extern BlackPS2::VU0::Matrix4 D_00415830;
extern char D_00415810;
void func_0017C828(Value, const void *);
void func_0017BDF0(Value point)
{
    Value transformed=BlackPS2::VU0::TransformPoint(D_00415830.basis,point);
    func_0017C828(transformed,&D_00415810);
}
}

// Partial PS2 prefixes verified only at the accessed fields below. Class names are provisional.
namespace BlackPS2 {
struct MotionSample { unsigned char unknown00[0x40]; BlackGame::Point3 displacement; };
struct BasisOwner { unsigned char unknown00[0x70]; VU0::Matrix4 frame; };
struct DirectionSource { BasisOwner *owner; unsigned char unknown04[0x50]; MotionSample *sample; };
}
extern "C" {
extern BlackGame::Position4 D_004432A0;
BlackGame::Vec func_001A71F8(BlackPS2::DirectionSource *source)
{
    BlackGame::Vec direction=BlackGame::WidenVec(source->sample->displacement);
    if (BlackPS2::VU0::Length3Word(direction)>=10.0f) direction=BlackGame::Load(D_004432A0);
    return BlackPS2::VU0::TransformDirection(source->owner->frame.basis,direction);
}
}
