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
extern void func_00171CA8(void *, void *);
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

/* Pool contents are managed by the lookup and release helpers. */
typedef struct Recovered_ActorPool Recovered_ActorPool;
extern void func_0016EB28(Recovered_ActorPool*, void*);
extern u8 func_002E1280(void*, s32);

s32 func_0016FAB0(s32 self, void* actor) {
    void* component = M2C_FIELD(actor, void**, 0x34C);
    func_0016EB28((Recovered_ActorPool*)func_0016FB18(self, M2C_FIELD(actor, s32*, 0xC4)), component);
    func_00171CA8(component, NULL);
    M2C_FIELD(actor, void**, 0x34C) = NULL;
    func_002E1280(D_003C9ED4, (s32)component);
    return 1;
}
