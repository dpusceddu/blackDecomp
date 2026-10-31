#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/playback_request.h"

extern s32 func_001DD728(void*);
extern void func_001E4E50(s32, Recovered_PlaybackParameters*, void*);
extern void func_001DD158(Recovered_PlaybackState*, Recovered_PlaybackParameters*);
extern void func_001EA518(void*, s32, s32);
extern void* D_0040F510;
extern void func_00176D10(void*);
extern void* D_0040F4D4;
extern void* D_0040F4D0;
extern s32 func_001D7CC0(Recovered_StreamBuffer*);
extern s32 func_001DD3E0(Recovered_PlaybackState*);
extern s32 func_001DCF70(void*, s32, s32, s32, s32, s32);
extern void* func_001E5D88(void*, u64);
extern void func_00176D08(void*, void*, s32, s32);
extern void func_001DD5D8(Recovered_PlaybackState*, Recovered_PlaybackParameters*);
extern s32 func_001E4B70(void*);

extern s32 func_001E51C8(void*, s32);
extern void func_001E4D28(void*);
extern void* func_001E4A78(void*, s32);
s32 func_001E4650(void* self, void* source, s32 arg2) {
    s32 state = M2C_FIELD(self, s32*, 0);
    if (state == 1) goto initialize;
    if (state < 2) return 1;
    if (state == 2) goto update;
    if (state == 3) goto finish;
    return 1;
initialize:
        M2C_FIELD(self, s32*, 0x38) = 0;
        M2C_FIELD(self, s32*, 0x34) = 0;
        M2C_FIELD(self, s32*, 0x30) = 0;
        M2C_FIELD(self, s32*, 0x2C) = 0;
        M2C_FIELD(self, s32*, 0x40) = 0;
        M2C_FIELD(self, s32*, 0x28) = 0;
        M2C_FIELD(self, s32*, 4) = 0;
        M2C_FIELD(self, void**, 0x44) = source;
        M2C_FIELD(self, s32*, 0x4C) = M2C_FIELD(source, s32*, 0x4C);
        M2C_FIELD(self, s32*, 0x48) = func_001E51C8(source, arg2);
        M2C_FIELD(self, s32*, 0) = 2;
update:
        func_001E4D28(self);
        if (!func_001E4A78(self, M2C_FIELD(self, s32*, 0x34))) return 0;
        M2C_FIELD(self, s32*, 0) = 3;
finish:
        func_001E4D28(self);
    return 1;
}
void func_001E4720(void* self) {
    Recovered_PlaybackParameters parameters;
    Recovered_PlaybackState* playback;
    f32 delay;
    u32 currentEntry;
    u32 stage;
    u32 nextEntry;
    void* slot;
    void* entries;
    void* previous;
    void* attachment;

    parameters.flags = 0;
    stage = M2C_FIELD(self, u32*, 4);
    if (stage != 5) {
        func_001E4D28(self);
        stage = M2C_FIELD(self, u32*, 4);
    }
    switch (stage) {
        case 0: break;
        case 1:
            if (func_001DD728(M2C_FIELD(M2C_FIELD(self, void**, 0x28), Recovered_PlaybackState**, 0xB8)) != 0) {
                parameters.flags = 0;
                func_001E4E50((s32)self, &parameters, M2C_FIELD(self, void**, 0x40));
                func_001DD158(M2C_FIELD(M2C_FIELD(self, void**, 0x28), Recovered_PlaybackState**, 0xB8), &parameters);
                return;
            }
            func_001EA518(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 8), 1, 0);
            func_00176D10((u8*)D_0040F4D4 + 0xD5C);
            entries = M2C_FIELD(self, void**, 0x48);
            currentEntry = M2C_FIELD(self, u32*, 0x34);
            nextEntry = currentEntry + 1;
            M2C_FIELD(self, f32*, 0x38) =
                (f32)M2C_FIELD(((currentEntry * 0x10) + M2C_FIELD(entries, s32*, 0xC)), f32*, 0xC);
            if (nextEntry >= (u8)M2C_FIELD(entries, u8*, 8)) {
                M2C_FIELD(self, u32*, 4) = 5U;
                return;
            }
            M2C_FIELD(self, u32*, 0x34) = nextEntry;
            M2C_FIELD(self, u32*, 4) = 2U;
        case 2:
            delay = M2C_FIELD(self, f32*, 0x38);
            if (delay > 0.0f) {
                M2C_FIELD(self, f32*, 0x38) = (f32)(delay - M2C_FIELD(D_0040F4D0, f32*, 0x1C));
                return;
            }
            M2C_FIELD(self, u32*, 4) = 3U;
        case 3:
            slot = func_001E4A78(self, (s32)M2C_FIELD(self, u32*, 0x34));
            if (slot != NULL) {
                previous = M2C_FIELD(self, void**, 0x2C);
                if (previous != NULL) {
                    func_001D7CC0(M2C_FIELD(previous, Recovered_StreamBuffer**, 0));
                    M2C_FIELD(M2C_FIELD(self, void**, 0x2C), s8*, 0xC) = 0;
                    M2C_FIELD(self, void**, 0x2C) = NULL;
                    func_001DD3E0(M2C_FIELD(M2C_FIELD(self, void**, 0x28), Recovered_PlaybackState**, 0xB8));
                }
                M2C_FIELD(self, void**, 0x2C) = slot;
                M2C_FIELD(slot, s8*, 0xC) = 1;
                M2C_FIELD(self, u32*, 4) = 4U;
                case 4:
                    attachment = M2C_FIELD(self, void**, 0x28);
                    if (func_001DCF70(M2C_FIELD(attachment, Recovered_PlaybackState**, 0xB8),
                                      (s32)M2C_FIELD(M2C_FIELD(self, void**, 0x2C), Recovered_StreamBuffer**, 0),
                                      (s32)((void*)(((s8*)attachment) + 0xB0)), 2,
                                      (s32)((void*)(((s8*)attachment) + 0xB4)), 1) != 0) {
                        M2C_FIELD(self, void**, 0x40) =
                            func_001E5D88(M2C_FIELD(self, void**, 0x3C),
                                          M2C_FIELD(((M2C_FIELD(self, u32*, 0x34) * 0x10) +
                                                     M2C_FIELD(M2C_FIELD(self, void**, 0x48), s32*, 0xC)),
                                                    s64*, 0));
                        func_00176D08((u8*)D_0040F4D4 + 0xD5C, M2C_FIELD(self, void**, 0x40), 0, 0);
                        func_001EA518(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 8), 1, 1);
                        parameters.flags = 0;
                        func_001E4E50((s32)self, &parameters, M2C_FIELD(self, void**, 0x40));
                        parameters.unk_A9 = 0;
                        parameters.flags |= 0x1000;
                        func_001DD5D8(M2C_FIELD(M2C_FIELD(self, void**, 0x28), Recovered_PlaybackState**, 0xB8),
                                      &parameters);
                        playback = M2C_FIELD(M2C_FIELD(self, void**, 0x28), Recovered_PlaybackState**, 0xB8);
                        playback->unk_34 = 1.0f;
                        playback->unk_3C = 0.0f;
                        M2C_FIELD(self, u32*, 4) = 1U;
                        return;
                    }
            }
            break;
        case 5:
            if (M2C_FIELD(self, s32*, 0) == 3) { func_001E4B70(self); }
            break;
    }
}

extern void* func_001E51E0(void*, const u64*, const u64*);
extern void* func_0028BD80(void*, s32);
extern s32 D_003BD470;
void* func_001E49D0(void* self, u32 index) {
    void* table = M2C_FIELD(self, void**, 0x48);
    void* result = NULL;
    if (index < M2C_FIELD(table, u8*, 8)) {
        u8* item = M2C_FIELD(table, u8**, 0xC) + index * 0x10;
        u64 key = 0x4DFF8E5600000000ULL;
        void* choice = func_0028BD80(func_001E51E0(M2C_FIELD(self, void**, 0x44), (u64*)item, &key), M2C_FIELD(item, s32*, 8));
        M2C_FIELD(choice, s16*, 2) = D_003BD470++;
        result = M2C_FIELD(M2C_FIELD(self, void**, 0x4C), u8**, 0x18) + M2C_FIELD(choice, u16*, 0) * 8;
    }
    return result;
}
void* func_001E4A78(void* self, s32 key) {
    u8* entry = (u8*)self + 8;
    u8* selected = entry;
    u32 i = 0;
    do {
        i++;
        if (M2C_FIELD(entry, s32*, 8) == key) {
            return M2C_FIELD(M2C_FIELD(entry, void**, 0), s32*, 0x14) == 4 ? selected : NULL;
        }
        selected += 0x10;
        entry += 0x10;
    } while (i < 2);
    return NULL;
}

void func_001E4AC8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x28) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 3;
}

extern void func_001DD6C0(void*);
void func_001E4AD8(void* self) {
    s32 state = M2C_FIELD(self, s32*, 4);
    if (state < 5) {
      if (state > 0) {
        if (func_001DD728(M2C_FIELD(M2C_FIELD(self, void**, 0x28), void**, 0xB8))) {
            func_001DD6C0(M2C_FIELD(M2C_FIELD(self, void**, 0x28), void**, 0xB8));
        }
        M2C_FIELD(self, s32*, 4) = 5;
      }
    }
}


s32 func_001E4B38(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 4);
    var_4 = 0;
    if ((temp_3 == 1) || (temp_3 == 3) || (temp_3 == 2) || (temp_3 == 4)) {
        var_4 = 1;
    }
    return var_4;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4650", func_001E4B70);
extern void func_001E6A40(void*, void*);
s32 func_001E4CA0(void* self) {
    u8* slot = (u8*)self + 8;
    u32 i = 0;
    s32 again;
    do {
        void* value = M2C_FIELD(slot, void**, 0);
        if (value) {
            func_001E6A40(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 4), value);
            M2C_FIELD(slot, void**, 0) = NULL;
        }
        i++;
        again = i < 2;
        slot += 0x10;
    } while (again);
    M2C_FIELD(self, s32*, 0) = 0;
    return again;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4650", func_001E4D28);
