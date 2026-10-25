#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Notifiable: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Notifiable {
    u8 unk_0[16];
    s32 unk_10;
    void * unk_14;
} Recovered_Notifiable;

/* Recovered_SlotUser: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_SlotUser {
    u8 unk_0[20];
    s32 unk_14;
    u8 unk_18[16];
    u32 unk_28;
} Recovered_SlotUser;

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_16fa50", func_0016FAB0);
