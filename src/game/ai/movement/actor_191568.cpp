#include "include_asm.h"

#define BLACK_PS2 1
#include "game/ai_movement_modes_decls.hpp"
#include "ps2/vu0.hpp"

namespace Game {
extern "C" void SegmentProject7(PositionArg start, PositionArg direction, PositionArg point,
                                Position4* result, float* fraction) __asm__("func_0027F470");

void MovementModeBase::SetDestination(PositionArg point)
{
    Store(target, point);
    distance = Ps2Math::VU0::Length3Word(Sub3(point, Load(brain->actor->position)));
    retargeted = 0;
    stallTimer.Clear();
    resumeTimer.Clear();
    UpdateDestinationDistances();
}

PositionResult ProjectOntoSegment(const MovementModeBase* mode, PositionArg start, PositionArg end)
{
    Position4 result;
    float fraction;
    SegmentProject7(start, Sub3(end, start), Load(mode->brain->actor->position), &result, &fraction);
    return Load(result);
}
}
// Unmatched: 0x1917a0 VU normalization, heading helpers and FPU temporary lifetimes.
// Unmatched: 0x191a28 VU lane update and scalar spill ordering.
// Unmatched: 0x191aa0 VU in-place lane updates and argument allocation.
// Unmatched: 0x191c80 original reset helper argument scheduling.
// Unmatched: 0x1921d8 controller publication lvalue and store scheduling.
// Unmatched: 0x192380 callback selection and pointer allocation.
// Unmatched: 0x192470 original request helper and phase lifetimes.
// Unmatched: 0x192698 original follower state and vector temporary context.
// Unmatched: 0x192a78 request ownership and follower field allocation.
// Unmatched: 0x192d48 point equality comparison operand scheduling.
// Unmatched: 0x192eb0 callback ABI and raised-segment helper context.
// Unmatched: 0x1930f8 node iterator lifetime and vector endpoint spills.
// Unmatched: 0x1934a8 controller publication lvalue and store scheduling.
// Unmatched: 0x193568 direction vector component extraction and allocation.

