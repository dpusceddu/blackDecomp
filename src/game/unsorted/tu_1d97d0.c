#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/audio_transfer.h"
#include "game/playback_request.h"

extern s32 func_001DA848(Recovered_AudioTransferChannel*);
extern s32 func_001DAAD0(void*);
extern s32 AudioTransferChannel_PollBusy(Recovered_AudioTransferChannel*);
extern s32 AudioTransferGroup_IsBlockFinished(Recovered_AudioTransferGroup*, s32);
extern u8* AudioTransferGroup_GetInputBlock(Recovered_AudioTransferGroup*, s32);
extern void AudioTransferGroup_AdvanceBlock(Recovered_AudioTransferGroup*, s32);
extern s32 AudioTransferGroup_IsFinalBlock(Recovered_AudioTransferGroup*, s32);
/* These native consumers copy a 0xB0-byte parameter record. The shared view is
 * partial; its unaccessed tail and original identity remain UNVERIFIED. */
extern void func_001DA5C8(Recovered_AudioTransferChannel*, Recovered_PlaybackParameters*);
extern void func_001DAB20(Recovered_AudioTransferChannel*, Recovered_PlaybackParameters*);
extern void func_001DA8D8(Recovered_AudioTransferChannel*, void*, s32, s32);
extern void func_001DACB0(void*);
extern void func_001DAD60(void*, s32);
extern s32 func_00324F98(void);

#ifdef NON_MATCHING
extern void func_001DAD90(Recovered_AudioTransferChannel*, const u8*, u8*);
/* Caller-only view: the matched dispatcher consumes self; forwarded argument
 * consumption and original library parameter identities are UNVERIFIED. */
extern void NativeTransferSubmit(void*, s32, const void*, s32) __asm__("func_0031D528");
#endif

extern s32 func_001DACE0(void* arg0);
extern s32 func_001DAD08(void* arg0);
extern s32 func_0031D528();
extern s32 func_00284298(s32);
extern s32 func_002842E8(s32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001D97D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001D9990);
void AudioTransferGroup_Update(Recovered_AudioTransferGroup* self, Recovered_PlaybackParameters* parameters) {
    s32 i;
    for (i = 0; i < self->channelCount; i++) {
        Recovered_AudioTransferChannel* channel = self->slots[i].channel;
        func_001DA5C8(channel, parameters);
        if (func_001DAAD0(channel)) {
            u8* data;
            AudioTransferGroup_AdvanceBlock(self, i);
            data = AudioTransferGroup_GetInputBlock(self, i);
            if (data) func_001DA8D8(channel, data, self->blockBytes, AudioTransferGroup_IsFinalBlock(self, i));
        }
    }
}
s32 AudioTransferGroup_TryReset(Recovered_AudioTransferGroup* self) {
    s32 i;
    for (i = 0; i < self->channelCount; i++) {
        if (!func_001DA848(self->slots[i].channel)) return 0;
    }
    self->unk_28 = 0;
    self->state = 4;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001D9C00);

u8* AudioTransferGroup_GetInputBlock(Recovered_AudioTransferGroup* self, s32 index) {
    s32 blockBytes;
    if (AudioTransferGroup_IsBlockFinished(self, index)) return 0;
    blockBytes = self->blockBytes;
    return self->data + blockBytes * self->slots[index].blockIndex + (blockBytes * self->blockCount) * index;
}

void AudioTransferGroup_AdvanceBlock(Recovered_AudioTransferGroup* self, s32 index) {
    u8* counts = (u8*)self + 4;
    s32* block;
    counts += index * sizeof(Recovered_AudioTransferSlot);
    block = (s32*)counts;
    if (*block < self->blockCount) (*block)++;
}

s32 AudioTransferGroup_IsBlockFinished(Recovered_AudioTransferGroup* self, s32 index) {
    return self->slots[index].blockIndex == self->blockCount;
}

s32 AudioTransferGroup_IsFinalBlock(Recovered_AudioTransferGroup* self, s32 index) {
    if (self->final && self->slots[index].blockIndex == self->blockCount - 1) return 1;
    return 0;
}
s32 AudioTransferGroup_AllBlocksFinished(Recovered_AudioTransferGroup* self) {
    s32 i;
    for (i = 0; i < self->channelCount; i++) {
        if (!AudioTransferGroup_IsBlockFinished(self, i)) return 0;
    }
    return 1;
}
void AudioTransferGroup_ApplyParameters(Recovered_AudioTransferGroup* self, Recovered_PlaybackParameters* parameters) {
    s32 i;
    for (i = 0; i < self->channelCount; i++) func_001DAB20(self->slots[i].channel, parameters);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001D9E38);
void AudioTransferGroup_ResetChannels(Recovered_AudioTransferGroup* self) {
    s32 i;
    for (i = 0; i < self->channelCount; i++) func_001DACB0(self->slots[i].channel);
}

void func_001D9EA8(void **arg0) {
    func_001DACE0(*arg0);
}

void AudioTransferGroup_SetTargetFlag(Recovered_AudioTransferGroup* self, s32 value) {
    s32 i;
    for (i = 0; i < self->channelCount; i++) func_001DAD60(self->slots[i].channel, value);
}

void func_001D9F40(void **arg0) {
    func_001DAD08(*arg0);
}

s32 func_001D9F60(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x24) * M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0xE0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001D9F78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001DA1C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001DA5C8);
#ifdef NON_MATCHING
// Unmatched: reset call setup and independent field-store scheduling differ.
s32 func_001DA848(Recovered_AudioTransferChannel* self) {
    if (self->state != 11) {
        if (self->pending) {
            AudioTransferChannel_PollBusy(self);
            if (!func_001DAAD0(self)) return 0;
        }
        if (self->handle) {
            func_00284298(self->handle);
            self->handle = 0;
        }
        self->input = 0;
        self->state = 11;
        self->inputBytes = 0;
        self->outputBytes = 0;
        self->final = 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001DA848);
#endif
#ifdef NON_MATCHING
// Unmatched: native unguarded divides and independent store scheduling differ.
void func_001DA8D8(Recovered_AudioTransferChannel* self, void* data, s32 bytes, s32 final) {
    if (self->format == 3) {
        bytes = (bytes / 36) * 36;
    } else if (self->format == 5) {
        bytes = (bytes / 19) * 19;
        self->outputBytes = (bytes / 19) * 64;
        goto ready;
    }
    self->outputBytes = bytes;
ready:
    self->final = final;
    self->input = data;
    self->inputBytes = bytes;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001DA8D8);
#endif
#ifdef NON_MATCHING
// Unmatched: native unguarded divide lowering differs.
u8* func_001DA940(Recovered_AudioTransferChannel* self) {
    s32 blocks = self->inputBytes / 19;
    u8* input = self->input;
    u8* output = self->decoded;
    if (blocks > 0) {
        s32 remaining = blocks;
        do {
            func_001DAD90(self, input, output);
            input += 19;
            remaining--;
            output += 64;
        } while (remaining != 0);
    }
    return self->decoded;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001DA940);
#endif
#ifdef NON_MATCHING
// Unmatched: submission setup and final-flag register assignment differ.
void func_001DA9C0(Recovered_AudioTransferChannel* self) {
    u8* data;
    if (self->format == 5)
        data = func_001DA940(self);
    else
        data = self->input;
    NativeTransferSubmit((u8*)self + 0x18, self->bufferIndex * self->bufferStride, data, self->outputBytes);
    if (self->final) {
        self->finalSubmitted = 1;
        self->lastBuffer = self->bufferIndex;
    }
    self->bufferIndex = (self->bufferIndex + 1) % 2;
    self->pending = 1;
    self->submitted++;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001DA9C0);
#endif

void func_001DAA68(void *arg0) {
    func_0031D528(arg0 + 0x18, M2C_FIELD(arg0, s32 *, 0xD0) * M2C_FIELD(arg0, s32 *, 0xDC), M2C_FIELD(arg0, s32 *, 0xC0), M2C_FIELD(arg0, s32 *, 0xD8));
    M2C_FIELD(arg0, s8 *, 0xF8) = 1;
    M2C_FIELD(arg0, s32 *, 0xD0) = (s32) ((M2C_FIELD(arg0, s32 *, 0xD0) + 1) % 2);
}

s32 func_001DAAD0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC4) == 0;
}

/* The library status is global; its transfer ownership is UNVERIFIED. */
s32 AudioTransferChannel_PollBusy(Recovered_AudioTransferChannel* self) {
    if (func_00324F98()) return 1;
    if (self->pending) {
        self->pending = 0;
        self->input = 0;
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001DAB20);

void func_001DACB0(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xFA) = 0;
    M2C_FIELD(arg0, s8 *, 0xFB) = 0;
    M2C_FIELD(arg0, s8 *, 0xFC) = 0;
    func_00284298(M2C_FIELD(arg0, s32 *, 0xB0));
}

s32 func_001DACE0(void *arg0) {
    s32 temp_4;
    s32 var_2;

    temp_4 = M2C_FIELD(arg0, s32 *, 0xB0);
    var_2 = 0;
    if (temp_4 != 0) {
        var_2 = func_002842E8(temp_4);
    }
    return var_2;
}

s32 func_001DAD08(void *arg0)
{
  int new_var;
  s32 temp_5;
  s32 var_3;
  var_3 = 0;
  if (((u32) ((M2C_FIELD(arg0, s32 *, 0xB4)) - 6)) < 4U)
  {
    temp_5 = M2C_FIELD(arg0, s32 *, 0xF0);
    if (temp_5 >= 2)
    {
      var_3 = ((((s32) (temp_5 + (((u32) temp_5) >> 0x1F))) >> 1) * (new_var = 2)) * (M2C_FIELD(arg0, s32 *, 0xE0));
    }
    if ((M2C_FIELD(arg0, s32 *, 0xB0)) != 0)
    {
      var_3 += M2C_FIELD(arg0, s32 *, 0xE8);
    }
  }
  return var_3;
}

void func_001DAD60(void *arg0, s32 arg1) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0xA8);
    if (arg1 != 0) {
        M2C_FIELD(temp_4, s32 *, 0x54) = (s32) (M2C_FIELD(temp_4, s32 *, 0x54) | 2);
        return;
    }
    M2C_FIELD(temp_4, s32 *, 0x54) = (s32) (M2C_FIELD(temp_4, s32 *, 0x54) & 0xFFFFFFFD);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d97d0", func_001DAD90);
