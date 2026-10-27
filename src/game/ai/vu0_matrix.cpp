#include "include_asm.h"

#include "ps2/matrix.hpp"
using Ps2Math::VU0::Value;

// UNVERIFIED class identities; only the accessed offsets are represented.
struct InitialState {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
};
struct ByteState {
    void* unk_00;
    unsigned char unk_04;
    signed char unk_05;
    signed char unk_06;
};
struct VectorState {
    void* unk_00;
    int unk_04, unk_08, unk_0C, unk_10;
    unsigned char unk_14[12];
    Game::Position4 unk_20;
    int unk_30;
};
#define LOCAL_OFFSET(T, member) ((unsigned)(&((T*)0)->member))
typedef char CursorIndexOffset[LOCAL_OFFSET(ByteState, unk_05) == 5 ? 1 : -1];
typedef char VectorStorageOffset[LOCAL_OFFSET(VectorState, unk_20) == 0x20 ? 1 : -1];
typedef char VectorTailOffset[LOCAL_OFFSET(VectorState, unk_30) == 0x30 ? 1 : -1];
#undef LOCAL_OFFSET
static inline Value SubtractY(Value a, Value b) {
    Value difference;
    asm("vsuby.y outputv, av, bvy" : "=j outputv"(difference) : "j av"(a), "j bv"(b));
    return difference;
}
static inline float ComponentY(Value value) {
    volatile Game::Position4 storage;
    *(volatile Value*)&storage = value;
    return storage.y;
}
static inline float ComponentZ(Value value) {
    volatile Game::Position4 storage;
    *(volatile Value*)&storage = value;
    return storage.z;
}

extern "C" {
signed char func_00183748(void*, signed char, unsigned char);
void* func_0013D400(void*);
}
extern "C" {
extern Ps2Math::VU0::Matrix4 D_00415830;
extern char D_00415810;
int func_0017C828(Value, const Game::Position4*);

void func_0017BDF0(Value point)
{
    Value transformed=Ps2Math::VU0::TransformPoint(D_00415830.basis,point);
    func_0017C828(transformed,(const Game::Position4*)&D_00415810);
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0017BE40);
extern "C" {
int func_0017C828(Value point, const Game::Position4* bounds) {
    int inside = 0;
    Value lower = Game::Load(bounds[1]);
    float x = Ps2Math::VU0::ReadXWord(point);
    if (Ps2Math::VU0::ReadXWord(lower) < x) {
        Value upper = Game::Load(bounds[0]);
        if (x < Ps2Math::VU0::ReadXWord(upper) && ComponentY(point) > 0.0f &&
            ComponentY(point) < ComponentY(SubtractY(upper, lower)) && ComponentZ(lower) < ComponentZ(point) &&
            ComponentZ(point) < ComponentZ(upper))
            inside = 1;
    }
    return inside;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00180090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001800B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001803E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00180438);
extern "C" {
int func_00181F28(InitialState* self) {
    self->unk_04 = 42;
    self->unk_08 = 0;
    self->unk_0C = 0;
    self->unk_10 = 0;
    return 1;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00182078);
extern "C" {
int func_00183080(ByteState* self) {
    int success = 1;
    self->unk_00 = 0;
    self->unk_04 = success;
    self->unk_05 = -success;
    self->unk_06 = -success;
    return success;
}
}

extern "C" {
int func_001830A0(ByteState* self) {
    self->unk_00 = 0;
    self->unk_04 = 1;
    self->unk_05 = 0;
    self->unk_06 = 0;
    return 1;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00183110);
extern "C" {
int func_00183160(ByteState* self) {
    self->unk_06 = self->unk_05;
    signed char next = func_00183748(self->unk_00, self->unk_05, self->unk_04);
    if (self->unk_05 < next)
        self->unk_04 = 1;
    else if (next < self->unk_05)
        self->unk_04 = 0;
    else
        return 0;
    self->unk_05 = next;
    return 1;
}
}

extern "C" {
int func_001831E0(VectorState* self) {
    self->unk_10 = 0;
    Game::Store(self->unk_20, Game::Load(D_004432A0));
    func_0013D400(self->unk_00);
    self->unk_04 = -1;
    self->unk_08 = -1;
    self->unk_0C = self->unk_30 = 0;
    return 1;
}
}

extern "C" {
void func_00183238(VectorState* self) {
    self->unk_10 = 0;
    Game::Store(self->unk_20, Game::Load(D_004432A0));
    self->unk_08 = -1;
    self->unk_30 = 0;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00185D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00187D78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00187E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00187EC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00188B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00188B98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018A380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018A540);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018AA18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018AB08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018AB98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018ABE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018AC80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018AD88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018C1E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018CE78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018CEE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018CFD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018D108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018D140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018D870);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018D8A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018D8E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018D918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018D950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018DB58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018DBC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018DC48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001951F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00195950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00195A00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00195AA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00195BC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001962F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00196428);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001964E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00196578);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00196648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00196758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001967F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00196958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001969E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00196E58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197040);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001971A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001971E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197460);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197638);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001979E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197AE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197C60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197DA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00198388);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001984C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019A798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019B150);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019B270);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019B320);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019B868);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019BE70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019C100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019C210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019C968);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019CAC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019CC80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019CD90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019CFC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019D080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019D1F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019D300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019D558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019F590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019FE28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019FF20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A06C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A0738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A13F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A1640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A1DE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A1EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A1F98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A1FE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A2090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A21B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A2368);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A4FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A51C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A5738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A59D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A5B10);
