#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/vu0.hpp"

extern "C" {

#include "game/ai/movement_events.h"

extern s32 func_0018BE88(s32, s32);

s32 func_0018BEB0(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_0018BE88(arg0, 0x13);
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    return temp_v0;
}

s32 func_0018BEE8(const Recovered_MovementEvent24* event, Recovered_MovementEvent24Output* output) {
    output->payload = *event;
    output->kind = event->kind;
    return 1;
}

#ifdef NON_MATCHING
// UNVERIFIED: member accesses follow assembly; the constructor is not source-exact.
typedef struct {
    s32 kind;
    Game::Point3 point;
    f32 unk_10;
    u8 unk_14;
    u8 unk_15[3];
} Recovered_MovementPointEvent;

// Unmatched: saved-register restore is scheduled after the scalar loads.
void func_0018BF28(Recovered_MovementPointEvent* event, Game::Vec point, s32 mode, f32 value) {
    func_0018BE88((s32)event, 0x14);
    event->point.x = Game::X(point);
    event->point.y = Game::Y(point);
    event->point.z = Game::Z(point);
    event->unk_10 = value;
    event->unk_14 = mode;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18be60_18beb0", func_0018BF28);
#endif

s32 func_0018BFA8(const Recovered_MovementEvent24* event, Recovered_MovementEvent24Output* output) {
    output->payload = *event;
    output->kind = event->kind;
    return 1;
}

#ifdef NON_MATCHING
// UNVERIFIED: member accesses follow assembly; the constructor is not source-exact.
typedef struct {
    s32 kind;
    u8 unk_04;
    u8 unk_05[3];
    Game::Point3 point;
    s32 unk_14;
} Recovered_MovementTaggedPointEvent;

// Unmatched: scalar-store ordering and FPR/saved-register allocation differ.
void func_0018BFE8(Recovered_MovementTaggedPointEvent* event, s32 mode, Game::Vec point, s32 value) {
    func_0018BE88((s32)event, 0x15);
    event->unk_14 = value;
    event->unk_04 = mode;
    event->point.x = Game::X(point);
    event->point.y = Game::Y(point);
    event->point.z = Game::Z(point);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18be60_18beb0", func_0018BFE8);
#endif

s32 func_0018C068(const Recovered_MovementEvent8* event, Recovered_MovementEvent8Output* output) {
    output->payload = *event;
    output->kind = event->kind;
    return 1;
}

} // extern "C"
