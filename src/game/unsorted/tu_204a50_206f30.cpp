#include "ps2/prelude.h"
extern "C" void func_00275260(const char*, u16*, s32);
extern "C" void func_00277510(void*, const void*, f32, const void*, s128, void*, const u16*);
extern void* D_0040F0E0;
extern u16 D_0043CB88[256];
extern u16 D_0043CD88[256];
// Private access views; original class names and unaccessed fields remain UNVERIFIED.
struct FrontendVec2 {
    float x, y;
    FrontendVec2(float x0, float y0) : x(x0), y(y0) {}
};
struct FrontendColor {
    union {
        struct {
            volatile f32 r, g, b, a;
        };
        volatile s128 bits;
    };
    FrontendColor(f32 r0, f32 g0, f32 b0, f32 a0) : r(r0), g(g0), b(b0), a(a0) {}
};
struct FrontendTitlePanel {
    u8 unk_00[0x24];
    void* firstCommand;
    FrontendVec2 firstPosition;
    void* secondCommand;
    u8 unk_34[4];
    FrontendVec2 secondPosition;
};

// Volatile lanes and capture preserve the native four stores followed by LQ.
extern "C" {
void func_00206F30(FrontendTitlePanel* self, const char* text, s32 selected) {
    s128 color = FrontendColor(1.0f, 1.0f, 1.0f, 0.8f).bits;
    f32 height = 30.0f;

    if (!selected) {
        color = FrontendColor(1.0f, 1.0f, 1.0f, 0.4f).bits;
        height = 25.0f;
    }
    func_00275260(text, D_0043CB88, 256);

    func_00277510(self->firstCommand, &self->firstPosition, height, &FrontendVec2(0.5f, 0.5f), color,
                  M2C_FIELD(D_0040F0E0, void**, 0x2107C), D_0043CB88);
}
void func_00207020(FrontendTitlePanel* self, const char* text, s32 selected) {
    s128 color = FrontendColor(1.0f, 1.0f, 1.0f, 0.8f).bits;
    f32 height = 30.0f;

    if (!selected) {
        color = FrontendColor(1.0f, 1.0f, 1.0f, 0.4f).bits;
        height = 25.0f;
    }
    func_00275260(text, D_0043CD88, 256);

    func_00277510(self->secondCommand, &self->secondPosition, height, &FrontendVec2(0.5f, 0.5f), color,
                  M2C_FIELD(D_0040F0E0, void**, 0x2107C), D_0043CD88);
}
}
