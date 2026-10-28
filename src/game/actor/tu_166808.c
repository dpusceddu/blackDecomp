#include "ps2/prelude.h"
#include "game/effects/render_state.h"
extern u8 D_0040D9B2;
extern BkActorRenderPS2* D_0040F4C0 __attribute__((section(".bss")));
extern void func_001AE5A0(BkActorRenderPS2*);
extern void func_001AE5C8(BkActorRenderPS2*);
typedef void (*RenderCall)(void*);
#define RENDER(P, C, G)                                                                                              \
    if (M2C_FIELD(self, s32*, P)) {                                                                                  \
        for (i = 0; i < M2C_FIELD(self, u16*, C); i++) {                                                             \
            void* entry = M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, P), void**, 0);                                    \
            if (!G || M2C_FIELD(entry, u8*, 0x11C)) {                                                                \
                void* vtable = M2C_FIELD(entry, void**, 0x10);                                                       \
                M2C_FIELD(vtable, RenderCall*, 0xAC)((char*)entry + M2C_FIELD(vtable, s16*, 0xA8));                  \
            }                                                                                                        \
        }                                                                                                            \
    }
void func_00166808(void* self) {
    s32 i;
    if (D_0040D9B2) {
        func_001AE5A0(D_0040F4C0);
        RENDER(0x48, 0, 1);
        RENDER(0x4C, 2, 1);
        RENDER(0x88, 0x24, 1);
        RENDER(0x8C, 0x26, 1);
        RENDER(0x90, 0x28, 1);
        RENDER(0x94, 0x2A, 1);
        RENDER(0x98, 0x2C, 1);
        RENDER(0x9C, 0x2E, 1);
        RENDER(0xD0, 0x44, 0);
        RENDER(0xD4, 0x46, 0);
        func_001AE5C8(D_0040F4C0);
    }
}
#undef RENDER
