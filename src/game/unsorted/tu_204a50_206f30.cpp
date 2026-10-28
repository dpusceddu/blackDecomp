#include "ps2/prelude.h"
extern "C" void func_00275260(const char*, u16*, s32);
extern "C" void func_00277510(void*, const void*, f32, const void*, s128, void*, const u16*);
extern void* D_0040F0E0;
extern u16 D_0043CB88[256];
extern u16 D_0043CD88[256];
// Private access views; original class names and unaccessed fields remain UNVERIFIED.
struct FrontendVec2 {
    float x, y;
    FrontendVec2() {}
    FrontendVec2(float x0, float y0) : x(x0), y(y0) {}
};
struct FrontendVec3 {
    union {
        struct {
            volatile f32 x, y, z;
        };
        volatile s128 bits;
    };
    FrontendVec3(f32 a, f32 b, f32 c) : x(a), y(b), z(c) {}
};

// Volatile lanes and capture preserve constructor stores followed by LQ.
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

// Explicit array storage uses the native allocation wrapper, followed by construction.
extern "C" void* func_00107D20(unsigned int);
inline void* operator new[](unsigned int, void* memory) { return memory; }
extern u8 D_003E0C90[], D_003E0C10[];
extern void* D_003BDCC8;
extern const char* D_003BDCF8[5];
extern u16 D_0043CF88[5][256];
extern "C" void func_002075F0(void*, void*);
extern "C" void func_002071F8(void*, void*);
static inline void*& FrontendCommandManager() { return D_003BDCC8; }
struct FrontendFrameHeader {
    u8 unk00[0x14];
    void* table;
    u8 unk18[8];
    FrontendFrameHeader(void* value) : table(value) {}
};
struct FrontendTextObject : FrontendFrameHeader {
    s128 color, targetColor;
    FrontendVec2 position, targetPosition, scale, uvSize;
    const u16* text;
    s32 index, style;
    f32 height, targetHeight, remaining, duration;
    void* command;
    FrontendTextObject() : FrontendFrameHeader(D_003E0C90) {}
};
struct FrontendSpriteObject : FrontendFrameHeader {
    s128 color, targetColor;
    FrontendVec2 position, targetPosition, scale, extent, targetExtent;
    FrontendVec2 uv[2];
    s32 index;
    f32 remaining, duration;
    void* command;
    s32 mode;
    FrontendSpriteObject() : FrontendFrameHeader(D_003E0C10) {}
};
struct FrontendStatisticsPanel {
    u8 unk00[0x14];
    FrontendTextObject* labels;
    FrontendTextObject* values;
    void* resource[2];
    FrontendSpriteObject* sprites;
    FrontendTextObject* title;
};
typedef char TextStride[sizeof(FrontendTextObject) == 0x80 ? 1 : -1];
typedef char SpriteStride[sizeof(FrontendSpriteObject) == 0x90 ? 1 : -1];
extern "C" void func_00207978(FrontendStatisticsPanel* self) {
    s8 i;
    self->title = new FrontendTextObject;
    self->labels = new (func_00107D20(sizeof(FrontendTextObject) * 5)) FrontendTextObject[5];
    self->values = new (func_00107D20(sizeof(FrontendTextObject) * 5)) FrontendTextObject[5];
    self->sprites = new (func_00107D20(sizeof(FrontendSpriteObject) * 10)) FrontendSpriteObject[10];
    func_002075F0(self->title, FrontendCommandManager());
    for (i = 0; i < 5; i++) {
        func_002075F0(&self->labels[i], FrontendCommandManager());
        func_002075F0(&self->values[i], FrontendCommandManager());
        if (i < 5) func_00275260(D_003BDCF8[i], D_0043CF88[i], 256);
    }
    for (i = 0; i < 10; i++) { func_002071F8(&self->sprites[i], FrontendCommandManager()); }
}

// These definitions recover the native static initializer and its I wrapper.
// Array entries and scalar values follow the original constructor sequence.
s128 D_00438C10 = FrontendVec3(1.5707964f, -0.15915494f, 1.2582912e7f).bits;
s128 D_00438C20 = FrontendVec3(-0.15915494f, 0.5f, 0.25f).bits;
s128 D_00438C30 = FrontendVec3(-76.57496f, -41.341675f, 81.60223f).bits;
s128 D_00438C40 = FrontendVec3(39.71066f, 6.283185f, 0.0f).bits;
FrontendVec2 D_00438C50(1.0f, 1.3333334f);
s128 D_00438C60 = FrontendColor(491.15646f, 721.33453f, 551.7273f, 301.12344f).bits;
s128 D_00438C70 = FrontendColor(8388608.0f, 8388608.0f, 8388608.0f, 8388608.0f).bits;
FrontendVec2 D_00438C80(0.5f, 0.5f);
s128 D_00438C90 = FrontendColor(1, 1, 1, 0).bits;
s128 D_00438CA0 = FrontendColor(1, 1, 1, 1).bits;
FrontendVec2 D_00438CB0(1, 1);
s128 D_00438CC0 = FrontendColor(1, 1, 1, 0.8f).bits;
s128 D_00438CD0 = FrontendColor(1, 1, 1, 0.2f).bits;
s128 D_00438CE0 = FrontendColor(0, 0, 0, 1).bits;
FrontendVec2 D_00438CF0(-1, -1);
FrontendVec2 D_00438CF8(1, 1);
s128 D_00438D00 = FrontendColor(1, 1, 1, 1).bits;
FrontendVec2 D_00438D10(0.5f, 0.5f);
s128 D_00438D20 = FrontendColor(1, 1, 1, 0.5f).bits;
s128 D_00438D30 = FrontendColor(1, 1, 1, 1).bits;
FrontendVec2 D_00438D40(1, 0.5f);
FrontendVec2 D_00438D48(1, 1);
FrontendVec2 D_00438D50[5] = {FrontendVec2(-1, 140), FrontendVec2(-1, 180), FrontendVec2(-1, 220),
                              FrontendVec2(-1, 260), FrontendVec2(-1, 300)};
FrontendVec2 D_00438D78[5] = {FrontendVec2(350, 140), FrontendVec2(350, 180), FrontendVec2(350, 220),
                              FrontendVec2(350, 260), FrontendVec2(350, 300)};
s128 D_00438DA0 = FrontendColor(0.7f, 0, 0, 1).bits;
s128 D_00438DB0 = FrontendColor(1, 1, 1, 1).bits;
FrontendVec2 D_00438DC0[5] = {FrontendVec2(450, 140), FrontendVec2(450, 180), FrontendVec2(450, 220),
                              FrontendVec2(450, 260), FrontendVec2(450, 300)};
s128 D_00438DF0 = FrontendColor(1, 1, 1, 0).bits;
s128 D_00438E00 = FrontendColor(1, 1, 1, 1).bits;
FrontendVec2 D_00438E10(0.5f, 0.5f);
FrontendVec2 D_00438E18(300, 300);
FrontendVec2 D_00438E20(30, 30);
FrontendVec2 D_00438E28[2] = {FrontendVec2(0, 0), FrontendVec2(1, 1)};
FrontendVec2 D_00438E38[5] = {FrontendVec2(500, 140), FrontendVec2(500, 180), FrontendVec2(500, 220),
                              FrontendVec2(500, 260), FrontendVec2(500, 300)};
