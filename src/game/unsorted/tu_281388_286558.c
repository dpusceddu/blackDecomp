#include "include_asm.h"
#include "game/audio_command_stream.h"

// UNVERIFIED: this older status wrapper consumes the native V0 result of Submit.
extern s32 func_002867F0();
extern s32 func_00286C10(M2C_UNK, M2C_UNK);

s32 func_00286558(s32 arg0) {
    s32 temp_3;
    s32 var_2;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x2870);
    var_2 = temp_3 < 2;
    if (temp_3 >= 0) {
        if (var_2 == 0) {
            var_2 = temp_3 < 4;
            if (var_2 != 0) {
                var_2 = func_002867F0(arg0, 0);
            }
        }
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_286558", func_00286598);

u32* AudioCommandStream_Append(Recovered_AudioCommandStream* self, u32 operation, u32 payloadWords) {
    u32* cursor = self->writeCursor;
    u32* payload;

    *cursor = operation;
    payload = cursor + 1;
    self->writeCursor = payload + payloadWords;
    *self->commandCount += 1;
    return payload;
}

void func_00286C80(void) {
    func_00286C10(1, 0xFFFF);
}
