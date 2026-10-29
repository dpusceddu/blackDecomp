#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00177A98();
extern s32 func_00177AD0();

s32 func_00179640(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70) != 0;
}

void * func_00179650(void *arg0, s32 arg1) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x70), s32 *, 0x2C) + (arg1 * 0x50);
}

/* Partial native views: three pairs of words, queried at channel 1 by the actor manager.
 * Original class identities and the meaning of each pair are UNVERIFIED. */
typedef struct {
    u8 unknown00[0x10];
    s32 values10[2];
    s32 values18[2];
    s32 values20[2];
} Recovered_ActorChannelValues;
typedef struct {
    u8 unknown00[0x70];
    Recovered_ActorChannelValues* values;
} Recovered_ActorChannelOwner;
s32 func_00179698(Recovered_ActorChannelOwner* self, s32 channel) { return self->values->values10[channel]; }
s32 func_001796B0(Recovered_ActorChannelOwner* self, s32 channel) { return self->values->values18[channel]; }
s32 func_001796C8(Recovered_ActorChannelOwner* self, s32 channel) { return self->values->values20[channel]; }

void func_001796E0(void* arg0) {
    if (M2C_FIELD(arg0, u8*, 0x74) != 0) { func_00179960(M2C_FIELD(arg0, s32*, 0x70)); }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_179400_179640", func_001797B8);
s32 func_001797E0(void* self) {
    M2C_FIELD(self, s32*, 0x30) = 0;
    M2C_FIELD(self, s32*, 0x28) = 0;
    M2C_FIELD(self, s8*, 0x35) = 0;
    M2C_FIELD(self, s8*, 0x36) = 0;
    M2C_FIELD(self, s8*, 0x37) = 0;
    return 1;
}

void func_00179960(void *arg0, s32 arg1) {
    s32 var_17;
    s32 var_18;

    var_18 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x28) > 0) {
        var_17 = 0;
        do {
            if (func_00177A98(M2C_FIELD(arg0, s32 *, 0x2C) + var_17) == arg1) {
                func_00177AD0(M2C_FIELD(arg0, s32 *, 0x2C) + var_17);
            }
            var_18 += 1;
            var_17 += 0x50;
        } while (var_18 < M2C_FIELD(arg0, s32 *, 0x28));
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_179400_179640", func_001799E0);
