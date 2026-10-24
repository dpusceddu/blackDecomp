#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/partial/Recovered_Notifiable.h"
#include "game/partial/Recovered_SlotUser.h"
#include "ps2/recovered_types.h"
extern void * func_0016EAD0(void *);
extern void * func_0016FB18(s32, s32);
extern s32 func_00171CA8(void *, void *);
extern u8 func_002E1248(Recovered_Notifiable *, Recovered_SlotUser *);
extern s8 * D_003C9ED4;

s32 func_0016FA50(s32 arg0, void *arg1) {
    Recovered_SlotUser *temp_2;

    temp_2 = func_0016EAD0(func_0016FB18(arg0, M2C_FIELD(arg1, s32 *, 0xC4)));
    M2C_FIELD(arg1, Recovered_SlotUser **, 0x34C) = temp_2;
    func_00171CA8(temp_2, arg1);
    func_002E1248((Recovered_Notifiable *) D_003C9ED4, temp_2);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016FAB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016FB18);
