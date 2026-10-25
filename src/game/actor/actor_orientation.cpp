#include "include_asm.h"

#include "game/actor/orientation.hpp"

namespace ActorParts {

#ifdef NON_MATCHING
// Unmatched: 0x13db40 native class/helper allocation and control-flow context.
// Unmatched: 0x13dc00 native class/helper allocation and control-flow context.
// Unmatched: 0x13df58 native matrix copy/product, axis-angle and rigid inverse inline contracts.
// Unmatched: 0x13eb00 native class/helper allocation and control-flow context.
// Unmatched: 0x13ec38 mutable vector normalization and persistent dot temporaries.
// Unmatched: 0x13ed98 native class/helper allocation and control-flow context.
// Unmatched: 0x13ef28 native vector value/cross/dot allocation.
// Unmatched: 0x13f0d8 native class/helper allocation and control-flow context.
// Unmatched: 0x13f328 native class/helper allocation and control-flow context.
// Unmatched: 0x13f3e0 mixed registration argument order and native field scheduling.
// Unmatched: 0x13f618 native pad/weapon call context, input predicate and stack temporary lifetimes.
// Unmatched: 0x140068 narrow scalar-to-VU and normalization/member allocation.
// Unmatched: 0x140468 native class/helper allocation and control-flow context.
// Unmatched: 0x1404a8 native FPU curve/helper and smoothing temporary scheduling.
// Unmatched: 0x1407c8 matrix copy/inverse and VU component scheduling.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013DB40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013DC00);
#endif

int OrientationState::Begin(void *actor)
{
    if (started) return 1;
    active = 0;
    elapsed = 0;
    state = 0;
    previousState = 0;
    locked = 0;
    changed = 1;
    Attach(actor);
    started = 1;
    return 1;
}
// Unmatched: 0013DB40 initialization retains aggregate-load and scalar scheduling differences.
// Unmatched: 0013DC00 target assignment retains seven scalar/byte lifetime differences.
// Unmatched: 0013DF58 turn interpolation needs original matrix copy/axis-angle helper contracts.
// Unmatched: 0013EB00 look-at needs the original matrix/vector temporary stores.
// Unmatched: 0013EC38 actor attachment retains vector normalization and persistent-dot temporary differences.
}
