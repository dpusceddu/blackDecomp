#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/audio_runtime.h"

#include "ps2/recovered_types.h"
extern s32 D_0040EBB8;
extern u8 D_0040EBBC;
extern s32 D_0040EBB4;
extern u8 D_0040EBBD;
extern s32 func_002831A0(Recovered_AudioRuntime* self, void* bank);
extern Recovered_AudioDriverState* func_00326538(Recovered_AudioSetupCommand* command, s32 kind, s32 arg2, s32 arg3);
extern void func_00326858(s32 value);

s32 func_002859A0(void) {
    D_0040EBB8 = 0;
    D_0040EBBC = 0;
    return D_0040EBB4;
}

#ifdef NON_MATCHING
// Unmatched: G1 uses a gp-relative byte store instead of the native absolute address.
void func_002859B8(void) {
    D_0040EBBD = 0;
    D_0040EBB4 = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2859a0", func_002859B8);
#endif
#ifdef NON_MATCHING
// Unmatched: G1 uses a gp-relative byte load instead of the native absolute address.
s32 func_002859D0(void) {
    if (D_0040EBBC == 0) return 0;
    return D_0040EBB8;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2859a0", func_002859D0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2859a0", func_002859F0);
void AudioRuntime_Configure(Recovered_AudioRuntime* self, s32 firstValue, s32 secondValue, s32 thirdValue, void* bank) {
    Recovered_AudioSetupCommand command;
    func_002831A0(self, bank);
    self->unk_CBB8 = secondValue;
    self->unk_CB9D = 0;
    command.unk_10 = firstValue;
    command.unk_14 = thirdValue;
    command.unk_0C = secondValue;
    command.enabled = 1;
    command.operation = 0x30;
    command.unk_04 = 0;
    self->driver = func_00326538(&command, 2, 0, 0);
    func_00326858(0);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2859a0", func_00285A98);
