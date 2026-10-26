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

void AudioCommandStream_SetCachedControls(Recovered_AudioCommandStream* self, u32 firstControl, u32 secondControl,
                                          f32 firstValue, f32 secondValue, f32 thirdValue) {
    s32 first = (s32)(firstValue * 32767.0f);
    s32 second = (s32)(secondValue * 32767.0f);
    s32 third = (s32)(thirdValue * 32767.0f);
    u32 mode = self->unk_2418 == 1;
    u32* payload;

    if (self->unk_288C == firstControl && self->unk_288D == secondControl && self->cachedValues[0] == first &&
        self->cachedValues[1] == second && self->cachedValues[2] == third && self->unk_288F == mode) {
        return;
    }
    self->unk_288C = firstControl;
    self->unk_288D = secondControl;
    self->cachedValues[0] = first;
    self->cachedValues[1] = second;
    self->cachedValues[2] = third;
    self->unk_288F = mode;
    payload = AudioCommandStream_Append(self, 0x60, 6);
    payload[0] = self->unk_288C;
    payload[1] = self->unk_288D;
    payload[2] = self->cachedValues[0];
    payload[3] = self->cachedValues[1];
    payload[4] = self->cachedValues[2];
    payload[5] = self->unk_288F;
}

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
