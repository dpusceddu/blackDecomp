#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#include "game/ai_manager.h"

extern s32 func_00126098();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_133fa8", func_00133FA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_133fa8", func_001347B8);

void func_00134970(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_00126098(arg0, arg1, arg2, arg3, arg4, arg5, arg0 + 0x1E0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_133fa8", func_00134990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_133fa8", func_00134BB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_133fa8", func_00134C98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_133fa8", func_00134FD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_133fa8", func_00135138);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_133fa8", func_001353F8);
/* Native link callbacks and the accessed object prefix; original class identities are UNVERIFIED. */
typedef struct {
    u8 unknown00[0x10];
    s16 attachAdjustment;
    u16 unknown12;
    void (*attach)(void*);
    s16 detachAdjustment;
    u16 unknown1A;
    void (*detach)(void*);
} ControllerLinkTable;
typedef struct {
    u8 unknown00[0x84];
    ControllerLinkTable* table;
} ControllerLink;

void func_001354E0(void* actor, ControllerLink* next) {
    ControllerLink* current = M2C_FIELD(actor, ControllerLink**, 0x32C);
    if (current == next) return;
    if (current) {
        ControllerLinkTable* table = current->table;
        table->detach((u8*)current + table->detachAdjustment);
    }
    M2C_FIELD(actor, ControllerLink**, 0x32C) = next;
    if (next) {
        ControllerLinkTable* table = next->table;
        table->attach((u8*)next + table->attachAdjustment);
    }
}

Recovered_ManagedSlot* Actor_GetManagedSlot(Recovered_ManagedActor* actor) {
    return actor->managedSlot;
}
