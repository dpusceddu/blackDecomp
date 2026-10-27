#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/audio/sound_object_fields.h"

extern unsigned char D_0040DA30;
// SN omits extern object sizes at -O0; preserve the native byte-sized GP declaration.
__asm__(".extern D_0040DA30, 1");

void* memset(void*, int, unsigned);
void* func_0035C544(void*, const void*, unsigned);
void func_001F09C0(void*, void*, int, void*);
void func_00285CC8(void*, void*, void*);
extern unsigned char D_0048FF50[];

/* Callback access view of the object's 0x1d0 storage; original type identity is UNVERIFIED. */
typedef struct RecoveredSoundMixState {
    int count, gain0, gain1, gain2;
    unsigned char* tone;
    int size;
    unsigned char* base;
    int cursor[2];
    unsigned char extra;
} RecoveredSoundMixState;

typedef char RecoveredSoundMixStateSize[sizeof(RecoveredSoundMixState) == 0x28 ? 1 : -1];

// Unmatched: the 648-byte body matches, but source omits eight trailing native bytes.
void func_001F0C98(int arg0, int arg1, int arg2, int arg3, int arg4, unsigned char* buffer, int arg6, void* context) {
    RecoveredSoundMixState* state = (RecoveredSoundMixState*)context;
    int gain;
    int i;
    int start, end;
    unsigned char* left = buffer;
    unsigned char* right = buffer + 0x200;
    unsigned char* base = state->base;
    if (!D_0040DA30) return;
    memset(buffer, 0, 0x400);
    i = state->count - 1;
    while (i >= 0) {
        start = state->cursor[i] + (int)base;
        end = (int)base + state->size;
        if (end - start > 0x200) end = start + 0x200;
        if (i)
            gain = state->gain1;
        else
            gain = state->gain0;
        if (start < end) func_001F09C0(left, (void*)start, gain, (void*)end);
        func_00285CC8(left, right, D_0048FF50);
        func_0035C544(left, right, 0x200);
        state->cursor[i] += 0x200;
        if (state->cursor[i] >= state->size) state->count--;
        i--;
    }
    if (state->extra) {
        func_001F09C0(left, state->tone, state->gain2, state->tone + 0x200);
        func_001F09C0(right, state->tone, state->gain2, state->tone + 0x200);
    }
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/sound_mix_callback", func_001F0C98);
#endif
