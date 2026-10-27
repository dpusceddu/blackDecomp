#include "include_asm.h"

#include "ps2/matrix.hpp"
#include "game/ai_action.hpp"
#include "game/actor/state.hpp"
extern "C" {
#include "game/actor_records.h"
#include "game/actor_slots.h"
#include "game/movement_history.h"
}
using Ps2Math::VU0::Value;

struct RangeSelection {
    Game::Brain* owner;
    int kind;
};

extern "C" {
extern int* D_00414D54;
}
static inline int TagCategory(const signed char* tag) {
    signed char index = *tag;
    if (index == -1) return 0;
    return D_00414D54[index];
}
static inline int HasCategoryThree(const RangeSelection* selection) {
    signed char* tag = (signed char*)((ActorParts::Owner*)selection->owner->actor)->Action();
    int special = 0;
    if (tag) {
        int kind = TagCategory(tag);
        special = kind == 3;
    }
    return special;
}

extern "C" {
int func_0035CA74(const char*, const char*);
}

struct NameQuery {
    unsigned char unk_00[0x30];
    const char* first;
    const char* second;
    unsigned int mode;
};



struct PoolRecord {
    int index;
    unsigned char ordinal;
    unsigned char unk_05[0x5B];
};
struct PoolState {
    PoolRecord records[3];
    int unk_120, unk_124;
    Game::ActionTimer timer;
    int unk_12C;
    unsigned char unk_130[4];
    unsigned char unk_134;
};

extern "C" {
struct BindingPayload;
void func_00163F30(BindingPayload*, ActorParts::Controller*);
void func_00163FD0(BindingPayload*, ActorParts::Controller*);
}

struct BindingPayload {
    unsigned char unk_00[0x5C];
    unsigned char payload;
};
struct BindingAnimation {
    unsigned char unk_00[0xCC];
    void* payload;
};
struct ActiveBinding {
    ActorParts::Controller* controller;
    BindingPayload* target;
    unsigned char active;
};
static inline BindingAnimation* Animation(ActiveBinding* self) {
    return (BindingAnimation*)self->controller->OwnerRef()->Animation();
}

struct MovementControl;

extern "C" {
void func_00193980(void*, const void*);
void func_00193988(Game::Action*);
void func_00193A28(Game::Action*, unsigned int, int);
void func_00173690(Game::ActionTimer*);
void func_001880D8(MovementControl*);
void func_00188148(MovementControl*, signed char);
void func_00187FE0(MovementControl*, int);
void func_001825B0(Game::Controller*);
}

struct MovementControl {
    unsigned char active;
    unsigned char unk_01;
};
struct ActorFlagView {
    unsigned char unk_00[0x3B8];
    unsigned char unk_3B8;
};
struct RequestFlagView {
    unsigned char unk_00[0x30];
    unsigned char unk_30;
};
static inline MovementControl* Movement(Game::Brain* brain) {
    return (MovementControl*)((unsigned char*)brain + 0x290);
}

extern "C" {
int func_0018EB78(Game::Recovered_DispatchedMode*);
}

// UNVERIFIED class identity; extends the existing slot view without data members.
struct DispatchSlots : Game::Recovered_DispatchedMode {
    virtual int Unknown15(void*);
    virtual void Unknown16(void*, unsigned int, Game::PositionArg);
    virtual void Unknown17(void*);
    virtual int Unknown18();
};

extern "C" {
void* func_00183710(void*, signed char);
}

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

static inline Game::Recovered_DispatchedMode* EmbeddedMode(Game::ModeDispatcher* self, unsigned int offset) {
    return (Game::Recovered_DispatchedMode*)((unsigned char*)self + offset);
}
static inline Game::Recovered_DispatchedMode*& IndexedMode(Game::Recovered_DispatchedMode** base, int index) {
    return base[index];
}

extern "C" {
void func_0018AB80(ActiveBinding*, Game::Brain*);
void func_0018AB88(ActiveBinding*);
void func_0018E2E8(Game::Recovered_DispatchedMode*, Game::Brain*);
int func_0018DF28(void*);
int func_0018DDD8(void*);
extern unsigned char* D_0040F4D4;
}

// UNVERIFIED policy identity; the native stores establish these field types.
struct ActionPolicyFields {
    int kind;
    float unk_04;
    unsigned char unk_08[0x18];
    float unk_20;
    float unk_24;
    float unk_28;
    unsigned char unk_2C[4];
    float unk_30;
    float unk_34;
    unsigned char unk_38[0x20];
    int unk_58;
    float unk_5C, unk_60;
    unsigned char unk_64[4];
    int unk_68;
    union {
        int unk_6C;
        float scalar_6C;
    };
    int unk_70;
    unsigned char unk_74[4];
    unsigned char unk_78;
    unsigned char unk_79[3];
    int unk_7C;
    float unk_80;
    int unk_84;
};
struct PolicyBrainFlags {
    unsigned char unk_00[0x104];
    unsigned char unk_104;
    unsigned char unk_105[0xB];
    unsigned char unk_110;
};
struct PolicyRequestFlags {
    unsigned char unk_00[0x35];
    unsigned char unk_35;
};
typedef char PolicyFieldsSize[sizeof(ActionPolicyFields) == sizeof(Game::ActionPolicy) ? 1 : -1];

extern "C" {
ActionPolicyFields* func_00193B98(Game::Action*);
void func_00193A60(Game::Action*, int, float);
void func_00193A28(Game::Action*, unsigned int, int);
}

static inline unsigned char& WaitActive(Game::Action* self) { return *(unsigned char*)&self->phase; }

extern "C" {
int func_001A7DF0(void*, int, int);
void func_00193990(Game::Action*, unsigned char);
int func_001829E8(Game::Controller*);
unsigned char func_001829A8(Game::Controller*);
void func_001825B0(Game::Controller*);
}

struct TimedFlagAction {
    Game::ActionBase base;
    Game::ActionTimer timer;
    unsigned char value, pending;
};
struct TimedFlagEvent {
    int kind;
    unsigned char unk_04[4];
    unsigned char value;
};

extern "C" {
void func_00193980(void*, const void*);
void func_00193990(Game::Action*, unsigned char);
void func_00173640(Game::ActionTimer*, float);
float func_0016DE70(void*, float, float);
extern unsigned char* D_0040F4D4;
}

// UNVERIFIED class identities; these prefixes represent the accessed native fields.
struct AnimationState {
    unsigned char unk_00[0x90];
    int* unk_90;
    int* unk_94;
};
struct ActionState {
    unsigned char unk_00[0xD8];
    unsigned int unk_D8;
};
struct OwnerView {
    unsigned char unk_00[0x2A4];
    ActionState* action;
    unsigned char unk_2A8[0x88];
    AnimationState* animation;
    unsigned char unk_334[0x75];
    unsigned char unk_3A9, unk_3AA;
};
struct ControllerView {
    unsigned char unk_00[0x30];
    unsigned char unk_30;
    unsigned char unk_31[0x4B];
    OwnerView* owner;
};
struct QueryState {
    unsigned char unk_00[0x14];
    Game::ActionTimer timer;
    unsigned char unk_18[0x28];
    int unk_40;
    ControllerView* controller;
};

typedef char QueryControllerOffset[(unsigned)&((QueryState*)0)->controller == 0x44 ? 1 : -1];
typedef char OwnerAnimationOffset[(unsigned)&((OwnerView*)0)->animation == 0x330 ? 1 : -1];
typedef char OwnerFlagOffset[(unsigned)&((OwnerView*)0)->unk_3A9 == 0x3A9 ? 1 : -1];

// UNVERIFIED action identity; only accessed members are represented.
struct CategoryPolicyAction {
    Game::ActionBase base;
    void* query;
    Game::ActionTimer first, second;
    int category;
    unsigned char active, unk_19, unk_1A;
};

static inline Recovered_ActorRecords* RecordsFor(Game::Brain* brain) {
    return (Recovered_ActorRecords*)((unsigned char*)brain + 0x150);
}
static inline QueryState* QueryFor(Game::Brain* brain) { return (QueryState*)((unsigned char*)brain + 0x650); }

static inline unsigned char RouteGate(Game::Brain* brain) { return ((unsigned char*)brain)[0xD27]; }

struct FollowAction {
    Game::ActionBase base;
    Game::Actor* target;
};

extern "C" {
int func_00188F10(Recovered_ActorRecords*);
int func_0018AB08(Recovered_ActorRecords*);
Game::PositionArg func_00189048(Recovered_ActorRecords*);
int func_0017E428(QueryState*, Game::PositionArg);
void func_0017DB98(QueryState*, Game::PositionArg);
unsigned char func_00188350(MovementControl*);
int func_001829E8(Game::Controller*);
float func_00189310(Recovered_ActorRecords*);
void func_00193990(Game::Action*, unsigned char);
void func_00193A60(Game::Action*, int, float);
int func_00184238(void*, int);
int func_00193AF8(Game::Action*);
}

// UNVERIFIED reset family; native slot and field offsets only.
// The four-byte inherited payload precedes GNU's vptr.
struct ResetData {
    void* owner;
};
struct ResetMode : ResetData {
    virtual int Reset();
};
struct ResetOwner {
    unsigned char unk_00[0xF0];
    ResetMode* modes[2];
    int unk_F8;
    unsigned char unk_FC[4];
    int unk_100;
};

struct TimerAction {
    Game::ActionBase base;
    Game::ActionTimer timer;
};

extern "C" {
int func_0017E770(QueryState*);
int func_00173610(const Game::ActionTimer*);
int func_00180438(QueryState*);
void func_0017DB50(QueryState*, unsigned char);
}

// UNVERIFIED formation action; only the accessed native prefix is represented.
struct FormationAction {
    Game::ActionBase base;
    unsigned char unk_08[8];
    Game::Position4 point;
    unsigned char available, peer, active, direction;
    Game::ActionTimer grace, retry;
};

struct FormationBrainFlag {
    unsigned char unk_00[0x111];
    unsigned char unk_111;
};
typedef char FormationActiveOffset[(unsigned)&((FormationAction*)0)->active == 0x22 ? 1 : -1];
typedef char FormationGraceOffset[(unsigned)&((FormationAction*)0)->grace == 0x24 ? 1 : -1];

extern "C" {
int func_001735E0(const Game::ActionTimer*);
int func_00176F00(unsigned int*);
int func_001A21B0(FormationAction*);
void func_001A1FE8(FormationAction*);
void func_00173640(Game::ActionTimer*, float);
}

struct PausePointAction {
    Game::ActionBase base;
    unsigned char value;
    unsigned char unk_09[7];
    Game::Position4 point;
};
struct PointEvent {
    int kind;
    unsigned char unk_04[12];
    Game::Position4 point;
};

// UNVERIFIED six-mode family; embedded extents follow the native table addresses.
struct FamilyModeData {
    void* owner;
    unsigned char unk_04[0x5C];
};
struct FamilyMode : FamilyModeData {
    virtual int Reset();
};
struct ModeFamily {
    unsigned char unk_00, unk_01, unk_02, unk_03;
    unsigned char unk_04[4];
    int index, unk_0C;
    Game::ActionTimer timer;
    unsigned char enabled, unk_15[3];
    int unk_18;
    float unk_1C;
    int unk_20;
    unsigned char unk_24, unk_25[3];
    int unk_28, unk_2C;
    FamilyMode first;
    unsigned char unk_94[0x6C];
    FamilyMode second;
    unsigned char unk_164[0xC];
    FamilyMode third;
    unsigned char unk_1D4[0x2C];
    FamilyMode fourth;
    unsigned char unk_264[0x2C];
    FamilyMode fifth;
    unsigned char unk_2F4[0x1C];
    FamilyMode sixth;
    unsigned char unk_374[0x1C];
    FamilyMode* modes[6];
    int active;
    void* owner;
    float unk_3B0;
    Game::ActionTimer finalTimer;
};
typedef char FamilyModeSize[sizeof(FamilyMode) == 0x64 ? 1 : -1];
typedef char FamilyTableOffset[(unsigned)&((ModeFamily*)0)->modes == 0x390 ? 1 : -1];

extern "C" {
void func_001A24B0(FamilyMode*, void*);
}

// UNVERIFIED mode interface; native slot 1 receives the actor. Keep its vptr before derived data.
struct ActionModeInterface : Game::Recovered_DispatchedModeData {
    virtual int Reset();
    virtual void ActorEvent(Game::Actor*);
};
struct ActionModeView : ActionModeInterface {
    unsigned char unk_14[0xC];
    Game::Position4 point;
};
typedef char ActionModePointOffset[(unsigned)&((ActionModeView*)0)->point == 0x20 ? 1 : -1];
static inline ActiveBinding* BindingFor(Game::Brain* brain) { return (ActiveBinding*)((unsigned char*)brain + 0xD18); }
static inline float FourthWord(Game::PositionArg value) {
    volatile Game::Position4 storage;
    *(volatile Game::PositionArg*)&storage = value;
    return storage.w;
}

extern "C" {
void* func_001830D0(void*);
void func_0018AD00(ActiveBinding*);
int func_0018AD30(ActiveBinding*);
Game::PositionArg func_0018AD60(ActiveBinding*);
void func_0017E488(QueryState*, float);
Game::PositionArg func_00183380(Game::FormationGoal*);
int func_00182380(Game::Controller*, Game::PositionArg, int);
int func_001823B0(Game::Controller*, Game::PositionArg, int);
int func_00182410(Game::Controller*, Game::PositionArg, unsigned char, unsigned char);
}

static inline Value ZeroXYZ() {
    Value value;
    asm("vadd.xyz outputv, vf0, vf0" : "=j outputv"(value));
    return value;
}
static inline Game::Position4 PositionFromValue(const Value* value) { return *(const Game::Position4*)value; }
struct QuadReset {
    int pairs[4][2];
    Game::ActionTimer timer;
    unsigned char unk_24[0xC];
    Game::Position4 point;
    int unk_40;
};

// UNVERIFIED motion-state identity; the accessed offsets are native.
struct MotionState {
    unsigned char unk_00[0x30];
    Game::Position4 unk_30;
    unsigned char unk_40[0x34];
    int unk_74;
    unsigned char unk_78[4];
    unsigned char unk_7C, unk_7D, unk_7E, unk_7F, unk_80, unk_81;
};

extern "C" {
Recovered_ActorSlot* func_00188F80(Recovered_ActorRecords*);
void* func_00181F48(void*, Recovered_ManagedActor*, int, float, float);
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

extern "C" {
void func_00180090(MotionState* self) {
    Value zero = ZeroXYZ();
    self->unk_74 = 0;
    self->unk_7C = 0;
    self->unk_7F = 0;
    self->unk_81 = 0;
    self->unk_30 = PositionFromValue(&zero);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001800B8);
extern "C" {
int func_001803E8(QueryState* self) {
    ControllerView* controller = self->controller;
    OwnerView* owner = controller->owner;
    unsigned char id = controller->unk_30;
    int result = 0;
    if (id == owner->unk_3A9 && id == owner->unk_3AA) {
        int* state = owner->animation->unk_90;
        int kind = 0;
        if (state) kind = *state;
        if (kind != 11) result = kind = 1;
    }
    return result;
}
}

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

extern "C" {
void* func_00183110(ByteState* self) {
    signed char next = func_00183748(self->unk_00, self->unk_05, self->unk_04);
    if (next == self->unk_05) return 0;
    return func_00183710(self->unk_00, next);
}
}

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
extern "C" {
void func_00187E08(ModeFamily* self, void* owner) {
    FamilyMode** begin = self->modes;
    int remaining = 5;
    self->owner = owner;
    FamilyMode** clear = begin + 5;
    do {
        *clear = 0;
        remaining--;
        clear--;
    } while (remaining >= 0);
    self->modes[0] = &self->first;
    self->modes[1] = &self->second;
    self->modes[2] = &self->third;
    self->modes[3] = &self->fourth;
    self->modes[4] = &self->fifth;
    self->modes[5] = &self->sixth;
    remaining = 5;
    FamilyMode** mode = begin;
    do {
        FamilyMode* item = *mode;
        mode++;
        func_001A24B0(item, owner);
        remaining--;
    } while (remaining >= 0);
    self->active = 0;
}
}

extern "C" {
int func_00187EC8(ModeFamily* self) {
    FamilyMode** mode = self->modes;
    int remaining = 5;
    self->unk_00 = 0;
    self->unk_02 = 0;
    self->unk_18 = 0;
    self->unk_1C = 5.0f;
    self->unk_03 = 0;
    self->unk_0C = 0;
    self->unk_20 = 0;
    self->enabled = self->unk_01 = 1;
    self->index = -1;
    func_00173690(&self->timer);
    self->unk_3B0 = 5.0f;
    self->unk_24 = 0;
    self->unk_2C = 0;
    self->unk_28 = 0;
    do {
        FamilyMode* item = *mode;
        remaining--;
        mode++;
        item->Reset();
    } while (remaining >= 0);
    self->active = 0;
    func_00173690(&self->finalTimer);
    return 1;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00188B40);
extern "C" {
int func_00188B98(PoolState* self) {
    for (int i = 0; i < 3; i++) {
        self->records[i].index = -1;
        self->records[i].ordinal = i;
    }
    self->unk_120 = -1;
    self->unk_134 = 0;
    self->unk_12C = 0;
    self->unk_124 = 0;
    func_00173690(&self->timer);
    return 1;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018A380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018A540);
extern "C" {
void func_0018AA18(Recovered_ActorRecords* self) {
    int category = TagCategory((signed char*)func_00188F80(self)->actor->unk_2A4);
    if (category == 3) {
        void* selection = (unsigned char*)self->owner + 0xC80;
        Recovered_ManagedActor* actor = func_00188F80(self)->actor;
        func_00181F48(selection, actor, 8, 0.0f, 1.0f);
        return;
    }
    if (category == 10) {
        void* selection = (unsigned char*)self->owner + 0xC80;
        Recovered_ManagedActor* actor = func_00188F80(self)->actor;
        func_00181F48(selection, actor, 7, 0.0f, 1.0f);
        return;
    }
    void* selection = (unsigned char*)self->owner + 0xC80;
    Recovered_ManagedActor* actor = func_00188F80(self)->actor;
    func_00181F48(selection, actor, 6, 0.0f, 1.0f);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018AB08);
extern "C" {
void func_0018AB98(ActiveBinding* self) {
    self->active = 0;
    if (self->target) {
        func_00163FD0(self->target, self->controller);
        Animation(self)->payload = 0;
        self->target = 0;
    }
}
}

extern "C" {
void func_0018ABE8(ActiveBinding* self, BindingPayload* target) {
    if (target) {
        if (self->active) {
            func_00163F30(target, self->controller);
            Animation(self)->payload = &target->payload;
        }
    } else {
        if (self->target && self->active) {
            func_00163FD0(self->target, self->controller);
            Animation(self)->payload = 0;
            self->target = 0;
        }
    }
    self->target = target;
}
}

extern "C" {
void func_0018AC80(ActiveBinding* self, int active) {
    self->active = active;
    if (active) {
        if (self->target) {
            func_00163F30(self->target, self->controller);
            Animation(self)->payload = &self->target->payload;
        }
    } else {
        if (self->target) {
            func_00163FD0(self->target, self->controller);
            Animation(self)->payload = 0;
            self->target = 0;
        }
    }
}
}

extern "C" {
int func_0018AD88(QuadReset* self) {
    Value zero = ZeroXYZ();
    int(*pair)[2] = self->pairs;
    int remaining = 3;
    do {
        (*pair)[0] = 0;
        remaining--;
        (*pair)[1] = 0;
        pair++;
    } while (remaining >= 0);
    self->point = PositionFromValue(&zero);
    self->unk_40 = 0;
    func_00173690(&self->timer);
    return 1;
}
}

extern "C" {
int func_0018C1E0(ResetOwner* self) {
    ResetMode** mode = self->modes;
    unsigned int count = 0;
    do {
        ResetMode* item = *mode;
        count++;
        mode++;
        item->Reset();
    } while (count < 2);
    self->unk_F8 = 2;
    self->unk_100 = -1;
    return 1;
}
}

extern "C" {
int func_0018CE78(const NameQuery* self, const char* name) {
    const char* match;
    switch (self->mode) {
        case 1:
        case 2: match = self->first; goto compare;
        case 3:
            match = self->second;
        compare:
            return func_0035CA74(name, match) == 0;
        case 0:
        case 4:
        default: return 0;
    }
}
}

extern "C" {
void func_0018CEE0(Game::ModeDispatcher* self, Game::Brain* owner) {
    int remaining = 10;
    func_00183080((ByteState*)self);
    self->owner = owner;
    func_0018AB80((ActiveBinding*)self->unk_08, owner);
    for (; remaining >= 0; remaining--) self->modes[remaining] = 0;
    self->modes[0] = EmbeddedMode(self, 0x54);
    self->modes[3] = EmbeddedMode(self, 0x68);
    self->modes[2] = EmbeddedMode(self, 0x7C);
    self->modes[1] = EmbeddedMode(self, 0x94);
    self->modes[4] = EmbeddedMode(self, 0xA8);
    self->modes[5] = EmbeddedMode(self, 0xC0);
    self->modes[6] = EmbeddedMode(self, 0x104);
    self->modes[7] = EmbeddedMode(self, 0x120);
    self->modes[8] = EmbeddedMode(self, 0x13C);
    self->modes[9] = EmbeddedMode(self, 0x160);
    self->modes[10] = EmbeddedMode(self, 0x190);
    Game::Recovered_DispatchedMode** mode = self->modes;
    remaining = 10;
    do {
        func_0018E2E8(*mode, owner);
        mode++;
    } while (--remaining >= 0);
}
}

extern "C" {
int func_0018CFD8(Game::ModeDispatcher* self) {
    int remaining = 10;
    Game::Recovered_DispatchedMode** begin = self->modes;
    func_001830A0((ByteState*)self);
    Game::Recovered_DispatchedMode** mode = begin;
    func_0018AB88((ActiveBinding*)self->unk_08);
    self->flags = 16;
    self->unk_14 = 1;
    self->unk_16 = 1;
    self->paused = 0;
    self->unk_17 = 0;
    self->unk_18 = 0;
    do {
        Game::Recovered_DispatchedMode* current = *mode++;
        --remaining;
        current->Unknown0();
    } while (remaining >= 0);
    self->active = func_0018DF28((unsigned char*)self->owner + 0xC94);
    if (self->active == 1 && func_0018DDD8((unsigned char*)self->owner + 0xC94)) {
        IndexedMode(begin, self->active)->Enter((Game::Recovered_ModeDescriptor*)(D_0040F4D4 + 0x22A00));
    } else {
        IndexedMode(begin, self->active)->Enter(0);
    }
    return 1;
}
}

extern "C" {
void func_0018D108(Game::ModeDispatcher* self) { self->modes[self->active]->Unknown1(); }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0018D140);
extern "C" {
int func_0018D870(Game::ModeDispatcher* self, void* argument) {
    return ((DispatchSlots*)self->modes[self->active])->Unknown15(argument);
}
}

extern "C" {
void func_0018D8A8(Game::ModeDispatcher* self, void* argument, unsigned int flags, Game::PositionArg point) {
    ((DispatchSlots*)self->modes[self->active])->Unknown16(argument, flags, point);
}
}

extern "C" {
void func_0018D8E0(Game::ModeDispatcher* self, void* argument) {
    ((DispatchSlots*)self->modes[self->active])->Unknown17(argument);
}
}

extern "C" {
int func_0018D918(Game::ModeDispatcher* self) { return ((DispatchSlots*)self->modes[self->active])->Unknown18(); }
}

extern "C" {
int func_0018D950(Game::ModeDispatcher* self) { return func_0018EB78(self->modes[self->active]); }
}

extern "C" {
float func_0018DB58(const RangeSelection* self) {
    int kind = self->kind;
    if (kind == 40) return 40.0f;
    if (kind == 38 || kind == 41) return 7.0f;
    float value = 13.0f;
    if ((unsigned int)(kind - 36) >= 2) value = 50.0f;
    return value;
}
}

extern "C" {
float func_0018DBC0(const RangeSelection* self) {
    float value;
    if (!HasCategoryThree(self)) {
        value = 50.0f;
        if (self->kind != 39) return 20.0f;
    } else
        value = 1000.0f;
    return value;
}
}

extern "C" {
float func_0018DC48(const RangeSelection* self) {
    float value;
    if (!HasCategoryThree(self)) {
        value = 100.0f;
        if (self->kind != 39) return 50.0f;
    } else
        value = 1000.0f;
    return value;
}
}

extern "C" {
void func_001951F0(Game::Action* self) {
    if (func_00188F10(RecordsFor(self->brain))) {
        Game::Brain* brain = self->brain;
        if (func_001823B0(&brain->controller, func_00189048(RecordsFor(brain)), 0)) {
            if (func_001829E8(&self->brain->controller) || !func_001829A8(&self->brain->controller))
                func_00193990(self, 0);
        } else
            goto fallback;
    } else {
    fallback:
        func_001825B0(&self->brain->controller);
        if (func_00188F10(RecordsFor(self->brain))) {
            Game::PositionArg point = func_00189048(RecordsFor(self->brain));
            func_0017DB98(QueryFor(self->brain), point);
        }
    }
    if (func_00188F10(RecordsFor(self->brain)) && func_0018AB08(RecordsFor(self->brain))) func_00193990(self, 1);
}
}

extern "C" {
void func_00195950(TimedFlagAction* self) {
    if (!self->pending) {
        if (!func_00180438(QueryFor(self->base.brain))) {
            func_001825B0(&self->base.brain->controller);
            func_00193990((Game::Action*)self, 1);
            return;
        }
    } else if (func_00173610(&self->timer)) {
        func_0017DB50(QueryFor(self->base.brain), self->value);
        self->pending = 0;
    }
    if (func_00188F10(RecordsFor(self->base.brain))) {
        Game::PositionArg point = func_00189048(RecordsFor(self->base.brain));
        func_0017E428(QueryFor(self->base.brain), point);
    }
}
}

extern "C" {
void func_00195A00(TimedFlagAction* self, const TimedFlagEvent* event) {
    func_00193980(self, event);
    if (event->kind != 5) {
        func_00193990((Game::Action*)self, 0);
        return;
    }
    self->value = event->value;
    func_00173640(&self->timer, func_0016DE70(D_0040F4D4, 0.0f, 1.0f));
    self->pending = 1;
}
}

extern "C" {
void func_00195AA8(Game::Action* self) {
    if (!func_0017E770(QueryFor(self->brain))) {
        func_00193990(self, 1);
        return;
    }
    if (func_00188F10(RecordsFor(self->brain))) {
        Game::PositionArg point = func_00189048(RecordsFor(self->brain));
        func_0017E428(QueryFor(self->brain), point);
    }
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00195BC0);
extern "C" {
void func_001962F0(Game::Action* self) {
    if (!func_00188F10(RecordsFor(self->brain)) || !func_0018AB08(RecordsFor(self->brain)) ||
        func_00188350(Movement(self->brain))) {
        func_00193990(self, 0);
        return;
    }
    if (Movement(self->brain)->unk_01 || func_001829E8(&self->brain->controller)) {
        func_00193990(self, 1);
    } else {
        Game::PositionArg point = func_00189048(RecordsFor(self->brain));
        func_0017DB98(QueryFor(self->brain), point);
    }
}
}

extern "C" {
void func_00196428(Game::Action* self) {
    if (!func_00188F10(RecordsFor(self->brain))) {
        func_00193990(self, 0);
        return;
    }
    Game::PositionArg point = func_00189048(RecordsFor(self->brain));
    func_0017E428(QueryFor(self->brain), point);
    if (!RouteGate(self->brain) && func_00189310(RecordsFor(self->brain)) > 3.0f) {
        func_00193990(self, 0);
        return;
    }
    if (func_00188350(Movement(self->brain))) {
        func_00193990(self, 0);
        return;
    }
    if (Movement(self->brain)->unk_01) func_00193990(self, 1);
}
}

extern "C" {
void func_001964E8(Game::Action* self, const void* event) {
    func_00193980(self, event);
    func_00187FE0(Movement(self->brain), 0);
    ((RequestFlagView*)self->brain->movement)->unk_30 = 0;
    func_001825B0(&self->brain->controller);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00196578);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00196648);
extern "C" {
void func_00196758(Game::Action* self, unsigned int kind, int result) {
    if (kind == 10 || kind == 13) {
        if (result) {
            if (func_00188F10(RecordsFor(self->brain))) {
                Game::PositionArg point = func_00189048(RecordsFor(self->brain));
                func_0017E428(QueryFor(self->brain), point);
            }
            func_00193A60(self, 0, 1.5f);
            ((RequestFlagView*)self->brain->movement)->unk_30 = 1;
        } else
            func_00193990(self, 0);
    }
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001967F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00196958);
extern "C" {
void func_001969E8(FollowAction* self) {
    if (func_00188F10(RecordsFor(self->base.brain))) {
        Game::PositionArg point = func_00189048(RecordsFor(self->base.brain));
        func_0017DB98(QueryFor(self->base.brain), point);
        if (func_001891C0(RecordsFor(self->base.brain))) {
            func_00193990((Game::Action*)self, 1);
            return;
        }
    }
    if (self->target) func_0017DB98(QueryFor(self->base.brain), Game::Load(self->target->position));
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00196E58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197040);
extern "C" {
void func_001971A0(Game::Action* self) {
    func_00193988(self);
    if (*(unsigned char*)&self->payload) ((ActorFlagView*)self->brain->actor)->unk_3B8 = 0;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001971E0);
extern "C" {
void func_00197460(Game::Action* self) {
    if (!func_001830D0(&self->brain->dispatcher)) {
        func_00193990(self, 1);
        return;
    }
    Game::Controller* controller;
    if (func_001829E8(&self->brain->controller) || ((controller = &self->brain->controller), controller->publish)) {
        ActionModeView* mode = (ActionModeView*)func_001830D0(&self->brain->dispatcher);
        mode->ActorEvent(self->brain->actor);
        func_00193990(self, 1);
        return;
    }
    if (!func_001829A8(controller)) func_00193990(self, 0);
}
}

extern "C" {
void func_00197638(TimerAction* self, const void* event) {
    func_00193980(self, event);
    func_00193A28((Game::Action*)self, 31, 0);
    func_00173690(&self->timer);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_00197858);
extern "C" {
int func_001979E0(Game::Action* self, const int* event) {
    if (*event == 14) {
        func_0018AD00(BindingFor(self->brain));
        if (func_0018AD30(BindingFor(self->brain))) {
            Game::Brain* brain = self->brain;
            func_0017E428(QueryFor(brain), func_0018AD60(BindingFor(brain)));
            return 1;
        }
        Game::PositionArg point = Game::Load(((ActionModeView*)func_001830D0(&self->brain->dispatcher))->point);
        func_0017E488(QueryFor(self->brain), FourthWord(point));
        return 1;
    }
    return 0;
}
}

extern "C" {
int func_00197AE0(Game::Action* self) {
    Game::PositionArg point = func_00183380(&self->brain->formation);
    Game::Brain* brain = self->brain;
    Game::Vec delta = Game::Sub3(Game::Load(brain->actor->position), point);
    float distanceSquared = Ps2Math::VU0::ReadXWord(Game::SumSquares3(delta));
    if (distanceSquared < 10.0f) return func_00182380(&brain->controller, point, 0);
    if (!(distanceSquared < 12.0f)) return func_00182410(&brain->controller, point, 0, 0);
    return func_001823B0(&brain->controller, point, 0);
}
}

extern "C" {
void func_00197C60(Game::Action* self) {
    void* animation = ((ActorParts::Owner*)self->brain->actor)->Animation();
    if (WaitActive(self)) {
        int status = func_001A7DF0(animation, 0, 3);
        if (status == 2) {
            func_00193990(self, 1);
            return;
        }
        if (status == 3) {
            func_00193990(self, 0);
            return;
        }
    } else
        WaitActive(self) = 1;
}
}

extern "C" {
void func_00197DA0(Game::Action* self) {
    if (WaitActive(self)) {
        if (func_001829E8(&self->brain->controller) || !func_001829A8(&self->brain->controller)) {
            func_001825B0(&self->brain->controller);
            ((RequestFlagView*)self->brain->movement)->unk_30 = 1;
            WaitActive(self) = 0;
        }
    } else
        ((RequestFlagView*)self->brain->movement)->unk_30 = 1;
}
}

extern "C" {
void func_00198388(PausePointAction* self, const PointEvent* event) {
    func_00193980(self, event);
    if (event && event->kind == 7)
        self->point = event->point;
    else
        Game::Store(self->point, Game::Load(self->base.brain->actor->position));
    func_00193A60((Game::Action*)self, 0, func_0016DE70(D_0040F4D4, 2.5f, 3.0f));
    func_001825B0(&self->base.brain->controller);
    QueryState* query = QueryFor(self->base.brain);
    self->value = query->controller->owner->unk_3AA;
    query->controller->unk_30 = 1;
    func_00188148(Movement(self->base.brain), 1);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001984C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019A798);
extern "C" {
void func_0019B150(Game::Action* self, const void* event) {
    func_00193980(self, event);
    func_00193B98(self)->kind = 2;
    func_00193B98(self)->unk_7C = 1;
    func_00193B98(self)->unk_80 = 15.0f;
    ((PolicyBrainFlags*)self->brain)->unk_104 = 1;
    ((PolicyBrainFlags*)self->brain)->unk_110 = 1;
    func_00193A60(self, 1, 1.0f);
    func_00193A28(self, 37, 0);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019B270);
extern "C" {
void func_0019B320(Game::Action* self, const void* event) {
    func_00193980(self, event);
    func_00193B98(self)->kind = 3;
    func_00193B98(self)->unk_7C = 3;
    func_00193B98(self)->unk_80 = 20.0f;
    ((PolicyBrainFlags*)self->brain)->unk_104 = 1;
    func_00193A28(self, 37, 0);
}
}

extern "C" {
void func_0019B868(Game::Action* self, const void* event) {
    int requestEnabled;
    func_00193980(self, event);
    ActionPolicyFields* policy = func_00193B98(self);
    policy->unk_30 = 2.0f * policy->unk_30;
    policy = func_00193B98(self);
    policy->unk_20 = policy->unk_20 * 1.8f;
    func_00193B98(self)->unk_28 = -25.0f;
    func_00193B98(self)->unk_5C = 0.5f;
    func_00193B98(self)->unk_70 = 0;
    func_00193B98(self)->unk_6C = 0;
    func_00193B98(self)->unk_58 = 0;
    func_00193B98(self)->unk_60 = 1.0f;
    func_00193B98(self)->unk_68 = 0;
    func_00193B98(self)->unk_04 = 1.0f;
    func_00193B98(self)->kind = 2;
    func_00193B98(self)->unk_78 = 1;
    ((PolicyBrainFlags*)self->brain)->unk_104 = 0;
    requestEnabled = 1;
    ((PolicyBrainFlags*)self->brain)->unk_110 = 1;
    self->phase = 0;
    ((PolicyRequestFlags*)self->brain->movement)->unk_35 = requestEnabled;
    func_00193A28(self, 22, 0);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019BE70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019C100);
extern "C" {
void func_0019C210(TimerAction* self) {
    Game::PositionArg point = func_00189048(RecordsFor(self->base.brain));
    func_0017E428(QueryFor(self->base.brain), point);
    if (func_001829E8(&self->base.brain->controller) || !func_001829A8(&self->base.brain->controller))
        func_00193990((Game::Action*)self, 1);
    if (func_00173610(&self->timer)) func_00193990((Game::Action*)self, 1);
}
}

extern "C" {
int func_0019C968(CategoryPolicyAction* self, const void* event) {
    Game::Action* action = (Game::Action*)self;
    func_00193980(action, event);
    func_00193B98(action)->unk_84 = 0;
    func_00193B98(action)->unk_34 = 100.0f;
    func_00193B98(action)->unk_24 = -25.0f;
    func_00193B98(action)->unk_28 = 0.0f;
    func_00193B98(action)->unk_30 = 0.0f;
    func_00193B98(action)->unk_20 = 2.0f;
    func_00193B98(action)->unk_68 = 0;
    func_00193B98(action)->unk_5C = 0.0f;
    func_00193B98(action)->unk_58 = 0;
    func_00193B98(action)->unk_70 = 0;
    func_00193B98(action)->scalar_6C = 5.0f;
    func_00193B98(action)->unk_60 = 2.0f;
    func_00193B98(action)->kind = 1;
    ((PolicyBrainFlags*)action->brain)->unk_104 = 0;
    ((PolicyBrainFlags*)action->brain)->unk_110 = 1;
    func_00173690(&self->first);
    func_00173690(&self->second);
    signed char index = *(signed char*)((ActorParts::Owner*)action->brain->actor)->Action();
    int category;
    if (index == -1)
        category = 0;
    else
        category = D_00414D54[index];
    int result = 1;
    self->category = category;
    self->active = result;
    self->query = 0;
    self->unk_19 = 0;
    self->unk_1A = 0;
    return result;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019CAC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019CC80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019CD90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019CFC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019D080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019D1F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019D300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019D558);
extern "C" {
void func_0019F590(Game::Action* self) {
    if (!func_00188F10(RecordsFor(self->brain)) || func_00189310(RecordsFor(self->brain)) > 3.0f ||
        func_00188350(Movement(self->brain))) {
        func_00193990(self, 0);
        return;
    }
    if (Movement(self->brain)->unk_01) {
        func_00193990(self, 1);
        return;
    }
    Game::PositionArg point = func_00189048(RecordsFor(self->brain));
    func_0017E428(QueryFor(self->brain), point);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019FE28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_0019FF20);
extern "C" {
void func_001A06C8(TimerAction* self) {
    if (func_00173610(&self->timer)) {
        func_00193990((Game::Action*)self, 1);
        return;
    }
    if (func_00188F10(RecordsFor(self->base.brain))) {
        Game::Brain* brain = self->base.brain;
        func_0017E428(QueryFor(brain), func_00189048(RecordsFor(brain)));
    }
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A0738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A13F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A1640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A1DE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A1EE0);
extern "C" {
void func_001A1F98(Game::Action* self) {
    func_00193988(self);
    MovementControl* movement = Movement(self->brain);
    if (movement->active) func_001880D8(movement);
    func_00188148(Movement(self->brain), 0);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A1FE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A2090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A21B0);
extern "C" {
void func_001A2368(FormationAction* self) {
    if (!func_00173610(&self->retry)) return;
    unsigned char previous = self->active;
    int blocked = 0;
    if (self->available && self->peer) blocked = ((FormationBrainFlag*)self->base.brain)->unk_111 == 0;
    if (!blocked && func_0018AB08(RecordsFor(self->base.brain))) {
        Game::ActionTimer* timer = &self->grace;
        if (!func_001735E0(timer)) func_00173640(timer, 0.5f);
        if (func_001735E0(timer) && func_00173610(timer) &&
            (unsigned char)func_00176F00(&self->base.brain->generation)) {
            self->active = func_001A21B0(self);
            func_00173690(timer);
            func_00173640(&self->retry, 2.0f);
        }
    } else
        self->active = 0;
    if (previous != self->active) {
        if (self->active) {
            func_001825B0(&self->base.brain->controller);
            ((RequestFlagView*)self->base.brain->movement)->unk_30 = 1;
            self->direction = 0;
        } else
            func_001A1FE8(self);
    }
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A4FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A51C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A5738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A59D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/vu0_matrix", func_001A5B10);
