#include "game/audio/resource_owner.h"

extern u8 D_0040D9F9;
__asm__(".extern D_0040D9F9, 1");
extern u8* D_003C09E8[];
extern f32 D_003BD2A8[];
extern const char* D_003BD2CC[];
extern const char D_003F7598[];
extern char D_0042A3D0[];
extern void func_001D62F8(void*, void*, u32);
extern void func_001D6388(void*, void*, u32);
extern void func_0027BB50(void*, void*);
extern void func_002726D0(u64, void*);
extern void func_0027B950(void*, void*, const char*, const char*, const char*, s32, f32, f32, s32);
void func_001D6E78(Recovered_PlaybackSlots* self, void* next, u64 key, s32 active) {
    self->active = active;
    if (self->current) {
        func_001D62F8(self->current, 0, 0);
        func_001D6388(self->current, 0, 0);
    }
    if (D_0040D9F9 == 1) { func_0027BB50(D_003C09E8[0] + 4, D_003BD2A8); }
    func_002726D0(key, D_0042A3D0);
    func_0027B950(D_003C09E8[0] + 4, D_003BD2A8, D_0042A3D0, D_003F7598, D_003BD2CC[0], 0, 0.0f, 0.0f, 0);
    D_0040D9F9 = 1;
    self->key = key;
    self->current = next;
    func_001D62F8(next, (u8*)self + 0x284, M2C_FIELD(self, u32*, 0x29C));
    func_001D6388(self->current, M2C_FIELD(self, void**, 0x1C18), M2C_FIELD(self, u32*, 0x1C1C));
}
