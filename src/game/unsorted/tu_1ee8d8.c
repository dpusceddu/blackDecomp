#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/audio/resource_owner.h"

extern s32 func_00280B10();

extern s32 func_00280A80(void*);
extern u8 func_00103870(void*);
extern s32 func_00103908(void*);
extern void *D_0040F0E0, *D_0040F4D0, *D_0040F510, *D_0040F0E8;
extern u8* D_0040F4D8;
extern s64** D_0040F4BC;
extern f32 D_003BDA1C, D_003BDA20, D_003BDA24, D_003BDA28;
extern f32 D_003BDA2C, D_003BDA30, D_003BDA34, D_003BDA38;
extern f32 D_003BDA3C, D_003BDA40, D_003BDA44, D_003BDA48;
// UNVERIFIED: original class identities and unrecovered callee result types.
extern void func_001ED718(void*, s32, u32);
extern void func_001C2760(void*, s32, f32);
extern void func_00107928(void*, s32, f32);
extern void* func_002842E8(void*);
extern s32 func_00284298(void*);
extern void* func_00280200(void*, u64*, s32);
extern void* func_00280BC0(void*);
extern void func_00283E78(void*, Recovered_AudioParameters*, void*);
void func_001EED98(void*, s32, f32);
void func_001EF0C0(void*, f32);
void func_001EF260(void*, u64, f32);
void func_001EF360(void*);

void func_001EEB00(void* self) {
    void* envelope;
    f32 smoothed;
    f32 previous;
    f32 level;
    f32 target;
    f32 blend;
    s32 difficulty;
    s64* currentKey;
    s64 resourceKey;
    u8 pending;

    void* table;
    void* clock;
    void* backend;

    func_00280A80((void*)self);
    func_001EF360(self);
    if (func_00103870(D_0040F0E0) == 0) {
        resourceKey = 0x6d6123044330fccfUL;
        currentKey = *D_0040F4BC;
        if (currentKey != NULL) { resourceKey = *currentKey; }
        if (resourceKey != (0x594c3cc765b41051UL)) {
            clock = (void*)(((s8*)D_0040F4D0) + 0x30);
            difficulty = M2C_FIELD(D_0040F0E0, s32*, 0x2014C);
            switch (difficulty) {
                case 0: target = M2C_FIELD(clock, f32*, 0x2F8) / 1200.0f; break;
                case 1: target = M2C_FIELD(clock, f32*, 0x2F8) / 1200.0f; break;
                case 2:
                case 3: target = M2C_FIELD(clock, f32*, 0x2F8) / 750.0f; break;
                default: target = 0.0f; break;
            }
            previous = M2C_FIELD(self, f32*, 0x258);
            smoothed = previous + ((target - previous) * D_003BDA24);
            M2C_FIELD(self, f32*, 0x258) = smoothed;
            if (smoothed < D_003BDA28) { func_001EF0C0(self, smoothed * (1.0f / D_003BDA28)); }
            level = M2C_FIELD(self, f32*, 0x258);
            envelope = M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x2C);
            if (level < D_003BDA1C) {
                if (D_003BDA20 < level) {
                    blend = (level - D_003BDA20) / (D_003BDA1C - D_003BDA20);
                } else {
                    blend = 0.0f;
                }
                func_001ED718(envelope, 3, 1U);
                backend = M2C_FIELD(envelope, void**, 0xC);
                table = M2C_FIELD(backend, void**, 0x50);
                M2C_FIELD(table, void (**)(void*, f32), 0x3C)((void*)(((s8*)backend) + M2C_FIELD(table, s16*, 0x38)),
                                                              blend);
            } else {
                func_001ED718(envelope, 3, 0U);
            }
        }
    }
    pending = M2C_FIELD(self, u8*, 0x291);

    if (pending == 1) {
        if (func_00103870(D_0040F0E0) == pending) {
            func_001EED98(self, 0, 0.0f);
            M2C_FIELD(self, u8*, 0x291) = 0U;
        }
    }
}

s32 func_001EED58(void* arg0) {
    func_00280B10();
    M2C_FIELD(arg0, s8*, 0x291) = 0;
    M2C_FIELD(arg0, s32*, 0x250) = 2;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ee8d8", func_001EED90);
void func_001EED98(void* self, s32 cue, f32 delay) {
    Recovered_AudioParameters parameters;
    u64 key;
    s32 timed = 0;
    parameters.flags = 0;
    // The caller supplies an internal cue in 0..21.
    switch (cue) {
        case 0:
            timed = 1;
            key = 0x79477e49df1f0000UL;
            M2C_FIELD(self, f32*, 0x28C) = M2C_FIELD(D_0040F4D0, f32*, 0x20) + delay;
            break;
        case 1: key = 0xa5403fff52ec0000UL; break;
        case 2: key = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x1F0); break;
        case 3: key = 0xa5404009755fb000UL; break;
        case 4: key = 0xa540401020c19ac0UL; break;
        case 5: key = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x200); break;
        case 6: key = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x258); break;
        case 11:
            timed = 1;
            key = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x250);
            M2C_FIELD(self, f32*, 0x28C) = M2C_FIELD(D_0040F4D0, f32*, 0x20) + delay;
            break;
        case 13:
            timed = 1;
            key = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x250);
            M2C_FIELD(self, f32*, 0x28C) = M2C_FIELD(D_0040F4D0, f32*, 0x20) + delay;
            break;
        case 15:
            timed = 1;
            key = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x268);
            M2C_FIELD(self, f32*, 0x28C) = M2C_FIELD(D_0040F4D0, f32*, 0x20) + delay;
            break;
        case 16:
            timed = 1;
            key = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x270);
            M2C_FIELD(self, f32*, 0x28C) = M2C_FIELD(D_0040F4D0, f32*, 0x20) + delay;
            break;
        case 18: key = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x280); break;
        case 19:
            timed = 1;
            key = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x288);
            M2C_FIELD(self, f32*, 0x28C) = M2C_FIELD(D_0040F4D0, f32*, 0x20) + delay;
            break;
        case 20:
            timed = 1;
            key = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x290);
            M2C_FIELD(self, f32*, 0x28C) = M2C_FIELD(D_0040F4D0, f32*, 0x20) + delay;
            break;
        case 14:
            key = 0;
            M2C_FIELD(self, f32*, 0x28C) = M2C_FIELD(D_0040F4D0, f32*, 0x20) + delay;
            break;
        case 10:
        case 12:
        case 17:
        case 21: key = 0; break;
        case 7:
        case 8:
        case 9: return;
    }
    if (timed) M2C_FIELD(self, f32*, 0x28C) -= 0.25f;
    if (key) {
        void* source = func_00280200(D_0040F510, &key, 0);
        if (source) {
            void* inner = M2C_FIELD(source, void**, 0x18);
            M2C_FIELD(inner, u32*, 0x54) &= ~2U;
            parameters.source = source;
            parameters.gain = 1.0f;
            parameters.kind = 0x10;
            parameters.flags = 0x85C;
            parameters.unk_60 = 0;
            parameters.rate = 0.0f;
            if (M2C_FIELD(D_0040F510, u8*, 0xCB9D)) {
                parameters.field88 = D_003BDA2C;
                parameters.field8C = D_003BDA30;
                parameters.field90 = D_003BDA2C;
                parameters.field94 = D_003BDA34;
                parameters.field98 = D_003BDA38;
                parameters.field9C = D_003BDA38;
                parameters.fieldAB = 1;
                parameters.flags |= 0x800000;
            }
            func_00283E78(func_00280BC0(self), &parameters, 0);
        }
    }
}
void func_001EF0C0(void* self, f32 gain) {
    f32 first, second, secondRemaining;
    s32 active;
    f32 dt = M2C_FIELD(D_0040F4D0, f32*, 0x1C);
    f32 remaining = M2C_FIELD(self, f32*, 0x26C) - dt;
    M2C_FIELD(self, f32*, 0x26C) = remaining;
    if (remaining < 0.0f) {
        func_001EF260(self, M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x2A0), 1.0f);
        if (gain < 0.5f) {
            func_001C2760(D_0040F4D8 + 0x83CA0, 8, 1.0f);
            func_00107928(D_0040F0E8, 0, 0.7f);
        }
        first = M2C_FIELD(self, f32*, 0x260);
        second = M2C_FIELD(self, f32*, 0x268);
        M2C_FIELD(self, f32*, 0x26C) = first + ((M2C_FIELD(self, f32*, 0x25C) - first) * gain);
        M2C_FIELD(self, f32*, 0x270) = second + ((M2C_FIELD(self, f32*, 0x264) - second) * gain);
    }
    secondRemaining = M2C_FIELD(self, f32*, 0x270);
    active = 1;
    if (!(secondRemaining > 0.0f)) active = 0;
    secondRemaining -= dt;
    M2C_FIELD(self, f32*, 0x270) = secondRemaining;
    if (active) {
        if (secondRemaining <= 0.0f) {
            func_001EF260(self, M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x2A8), 1.0f);
            if (gain < 0.5f) func_00107928(D_0040F0E8, 0, 0.4f);
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ee8d8", func_001EF258);
void func_001EF260(void* self, u64 key, f32 gain) {
    Recovered_AudioParameters parameters;
    void* provider;
    void* source;
    parameters.flags = 0;
    provider = func_00280BC0(self);
    source = func_00280200(D_0040F510, &key, 0);
    if (source) {
        void* inner = M2C_FIELD(source, void**, 0x18);
        M2C_FIELD(inner, u32*, 0x54) &= ~2U;
        parameters.gain = gain;
        parameters.source = source;
        parameters.kind = 0x10;
        parameters.flags = 0x81C;
        parameters.rate = 0.0f;
        if (M2C_FIELD(D_0040F510, u8*, 0xCB9D)) {
            parameters.field88 = D_003BDA3C;
            parameters.field8C = D_003BDA40;
            parameters.field90 = D_003BDA3C;
            parameters.field94 = D_003BDA44;
            parameters.field98 = D_003BDA48;
            parameters.field9C = D_003BDA48;
            parameters.fieldAB = 1;
            parameters.flags |= 0x800000;
        }
        func_00283E78(provider, &parameters, 0);
    }
}
void func_001EF360(void* self) {
    Recovered_AudioParameters parameters;
    f32 now;
    parameters.flags = 0;
    now = M2C_FIELD(D_0040F4D0, f32*, 0x20);
    if (func_00103908(D_0040F0E0) == 3) M2C_FIELD(self, f32*, 0x28C) -= M2C_FIELD(D_0040F4D0, f32*, 0x1C);
    if (now < M2C_FIELD(self, f32*, 0x28C)) {
        if (func_002842E8(M2C_FIELD(self, void**, 0x254)) == 0) {
            if (func_00103870(D_0040F0E0) == 0) {
                void* resource =
                    func_00280200(D_0040F510, (u64*)((u8*)M2C_FIELD(D_0040F4D0, void**, 0x5AEC) + 0x298), 0);
                void* inner = M2C_FIELD(resource, void**, 0x18);
                M2C_FIELD(inner, u32*, 0x54) &= ~2U;
                parameters.source = resource;
                parameters.gain = 1.0f;
                parameters.kind = 0x10;
                parameters.flags = 0x185C;
                parameters.unk_60 = 0;
                parameters.rate = 0.0f;
                parameters.unk_A9[0] = 1;
                if (M2C_FIELD(D_0040F510, u8*, 0xCB9D)) {
                    parameters.field88 = D_003BDA2C;
                    parameters.field8C = D_003BDA30;
                    parameters.field90 = D_003BDA2C;
                    parameters.field94 = D_003BDA34;
                    parameters.field98 = D_003BDA38;
                    parameters.field9C = D_003BDA38;
                    parameters.fieldAB = 1;
                    parameters.flags |= 0x800000;
                }
                func_00283E78(M2C_FIELD(self, void**, 0x254), &parameters, 0);
            }
        }
    } else {
        if (func_002842E8(M2C_FIELD(self, void**, 0x254))) {
            func_00284298(M2C_FIELD(self, void**, 0x254));
            M2C_FIELD(self, f32*, 0x28C) = -1.0f;
        }
    }
}
