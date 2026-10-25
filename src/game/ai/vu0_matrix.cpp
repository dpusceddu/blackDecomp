#include "include_asm.h"

#include "ps2/matrix.hpp"
using Ps2Math::VU0::Value;
extern "C" {
extern Ps2Math::VU0::Matrix4 D_00415830;
extern char D_00415810;
void func_0017C828(Value, const void *);

void func_0017BDF0(Value point)
{
    Value transformed=Ps2Math::VU0::TransformPoint(D_00415830.basis,point);
    func_0017C828(transformed,&D_00415810);
}
}

// Partial PS2 prefixes verified only at the accessed fields below. Class names are provisional.
namespace Ps2Math {
struct MotionSample { unsigned char unknown00[0x40]; Game::Point3 displacement; };
struct BasisOwner { unsigned char unknown00[0x70]; VU0::Matrix4 frame; };
struct DirectionSource { BasisOwner *owner; unsigned char unknown04[0x50]; MotionSample *sample; };
}
extern "C" {
extern Game::Position4 D_004432A0;
Game::Vec func_001A71F8(Ps2Math::DirectionSource *source)
{
    Game::Vec direction=Game::WidenVec(source->sample->displacement);
    if (Ps2Math::VU0::Length3Word(direction)>=10.0f) direction=Game::Load(D_004432A0);
    return Ps2Math::VU0::TransformDirection(source->owner->frame.basis,direction);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017BE40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017C828);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00180090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001800B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001803E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00180438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00181F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001830A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183160);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001831E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183238);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00185D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187D78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187EC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00188B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00188B98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018A380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018A540);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018AA18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018AB08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018AB98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018ABE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018AC80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018AD88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C1E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018CE78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018CEE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018CFD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D870);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D8A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D8E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018DB58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018DBC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018DC48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001951F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00195950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00195A00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00195AA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00195BC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001962F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00196428);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001964E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00196578);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00196648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00196758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001967F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00196958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001969E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00196E58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00197040);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001971A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001971E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00197460);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00197638);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00197678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00197858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001979E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00197AE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00197C60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00197DA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00198388);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001984C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019A798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019B150);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019B270);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019B320);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019B868);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019BE70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019C100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019C210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019C968);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019CAC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019CC80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019CD90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019CFC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019D080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019D1F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019D300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019D558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019F590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019FE28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019FF20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A06C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A0738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A13F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A1640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A1DE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A1EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A1F98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A1FE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A2090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A21B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A2368);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A4FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A51C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A5738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A59D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A5B10);
