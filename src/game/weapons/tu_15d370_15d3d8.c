#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/weapons/shot.h"

extern void func_0015D620(BkMovingShotPS2*);
typedef struct Recovered_ShotClock {
    u8 unk_00[0x20];
    f32 time;
} Recovered_ShotClock;
extern Recovered_ShotClock* D_0040F4D0;

void func_0015D3D8(void *arg0) {
    BkShotDeactivatePS2(arg0);
}

#ifdef NON_MATCHING
// Unmatched: field-store scheduling and clock-load register allocation differ.
s32 func_0015D3E0(BkMovingShotPS2* shot, void* weapon, s128 origin, s128 direction, s8 flags,
                   f32 remaining, f32 speed) {
    f32 now;
    shot->weapon = weapon;
    shot->flags80 = flags;
    shot->active = 1;
    shot->flags89 = 0;
    now = D_0040F4D0->time;
    shot->origin = origin;
    shot->launchTime = now;
    shot->direction = direction;
    shot->remaining = remaining;
    shot->speed = speed;
    shot->endpoint = origin;
    shot->distance = 0.0f;
    func_0015D620(shot);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_15d370_15d3d8", func_0015D3E0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_15d370_15d3d8", func_0015D440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_15d370_15d3d8", func_0015D620);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_15d370_15d3d8", func_0015D750);

void func_0015D850(void *arg0, s128 arg1) {
    ((BkMovingShotPS2*)arg0)->endpoint = arg1;
    func_0015D620((BkMovingShotPS2*)arg0);
}

