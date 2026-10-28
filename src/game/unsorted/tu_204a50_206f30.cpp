#include "include_asm.h"
#include "ps2/prelude.h"
extern "C" void func_00275260(const char*, u16*, s32);
extern "C" void func_00277510(void*, const void*, f32, const void*, s128, void*, const u16*);
extern void* D_0040F0E0;
extern u16 D_0043CB88[256];
extern u16 D_0043CD88[256];
// Private access views; original class names and unaccessed fields remain UNVERIFIED.
struct FrontendVec2 {
    union {
        struct {
            f32 x, y;
        };
        s64 bits;
    };
    FrontendVec2(const FrontendVec2& value) { bits = value.bits; }
    FrontendVec2& operator=(const FrontendVec2& value) {
        bits = value.bits;
        return *this;
    }
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

struct FrontendStatisticsPanel;
extern "C" s32 func_00204F30(void*);
extern "C" void func_00103800(void*, s8);
extern "C" void func_001227A8(s32*);
extern "C" s32 func_00207B80(FrontendStatisticsPanel*);
extern "C" void func_00208140(FrontendStatisticsPanel*, f32);
extern "C" s32 func_00124A70(void*);
extern "C" s32 func_00124CA8(void*);
extern "C" void func_001034B0(void*, void*);
extern s32* D_0040F4E8;
extern s32* D_0040F4C0;

extern void* D_0040F510;
extern u8 D_0043D988[5], D_0043D9D8[5];
extern s8 D_0043D9D0[5];
extern "C" void func_001EED98(void*, s32, f32);
extern "C" void* func_00275448(void*, s32, s32, s32);
extern "C" s32 func_00208C60(void*, f32);
extern u16 D_003BDD10[5][256];

// The native table has a no-op first slot and Initialize at byte 0x10.
// UNVERIFIED: first slot's original signature and base-class field meanings.
struct FrontendSolidBase {
    u8 unk00[0x14];
    virtual void Unknown0();
    virtual s32 Initialize(const FrontendVec2&, const FrontendVec2&);
};
struct FrontendSolid : FrontendSolidBase {
    void* command;
};
typedef char FrontendSolidStride[sizeof(FrontendSolid) == 0x1C ? 1 : -1];
struct FrontendClock {
    u8 unk00[0x1C];
    f32 delta;
};
static inline f32 FrontendDelta(const FrontendClock* clock) { return clock->delta; }

extern "C" s32 func_00205AA0(void* self) {
    func_00204F30(self);
    func_00103800(D_0040F0E0, 1);
    func_001227A8(D_0040F4E8);
    func_00207B80(M2C_FIELD(self, FrontendStatisticsPanel**, 0x64));
    M2C_FIELD(self, FrontendSolid**, 0x60)->Initialize(FrontendVec2(0, 0), FrontendVec2(0, 0));
    M2C_FIELD(self, FrontendSolid**, 0x60)[1].Initialize(FrontendVec2(0, 1), FrontendVec2(0, (f32)D_0040F4C0[1]));
    return 1;
}
extern "C" void func_00205B68(void* self) {
    func_00208140(M2C_FIELD(self, FrontendStatisticsPanel**, 0x64),
                  FrontendDelta((FrontendClock*)((s8*)D_0040F0E0 + 0x20120)));
    if (func_00124A70(M2C_FIELD(D_0040F0E0, void**, 0x21060)) ||
        func_00124CA8(M2C_FIELD(D_0040F0E0, void**, 0x21060))) {
        void* context = D_0040F0E0;
        func_001034B0(context, (s8*)context + 0x20220);
    }
}

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
#ifdef NON_MATCHING
    void SetPosition(const FrontendVec2& p, const FrontendVec2& s) {
        position = targetPosition = p;
        scale = s;
    }
    void SetHeight(f32 value) { height = targetHeight = value; }
    void SetColor(const s128& value) { color = targetColor = value; }
#endif
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
#ifdef NON_MATCHING
    void SetPosition(const FrontendVec2& p, const FrontendVec2& s) {
        position = targetPosition = p;
        scale = s;
    }
    void SetExtent(const FrontendVec2& value) { extent = targetExtent = value; }
    void SetColor(const s128& value) { color = targetColor = value; }
    void SetUV(const FrontendVec2& start, const FrontendVec2& end) {
        uv[0] = start;
        uv[1] = end;
    }
    void Initialize(s32 index, s32 first, s32 count, s32 last) {
        s16 delta = M2C_FIELD(table, s16*, 0x10);
        M2C_FIELD(table, s32(**)(void*, s32, s32, s32, s32), 0x14)((s8*)this + delta, index, first, count, last);
    }
#endif
    FrontendSpriteObject() : FrontendFrameHeader(D_003E0C10) {}
};
struct FrontendStatisticsPanel {
    f32 countdown;
    f32 elapsed, time;
    s16 count0, count1;
    s8 count2;
    u8 unk11[3];
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
#ifdef NON_MATCHING
extern void* D_0040F4C4;
extern const char* D_003BE714;
extern const char* D_003BE710;
extern u16 D_0043D990[32];
extern const u16 D_003BDCD0[];
extern "C" const char* func_00103358(void*, s32);
extern "C" u16* func_002753F0(u16*, const u16*);
extern "C" s32 func_00207610(void*, s32, s32, s32, s32);
extern "C" void* func_00108328(void*, const char*);
// Unmatched: setter argument lifetimes, loop scheduling and register allocation differ.
extern "C" s32 func_00207B80(FrontendStatisticsPanel* self) {
    s8 i = 0;
    self->countdown = 0;
    self->elapsed = 0;
    self->time = 0;
    self->count0 = 0;
    self->count1 = 0;
    self->count2 = 0;
    func_00275260(func_00103358(D_0040F0E0, M2C_FIELD(D_0040F0E0, u8*, 0x2020C)), D_0043D990, 32);
    func_002753F0(D_0043D990, D_003BDCD0);
    self->title->text = D_0043D990;
    self->title->uvSize = D_00438D48;
    self->title->style = 1;
    self->title->SetPosition(FrontendVec2((f32)D_0040F4C0[0] * 0.5f, 50), D_00438D10);
    self->title->SetHeight(30);
    self->title->SetColor(D_00438D00);
    func_00207610(self->title, 1, 2, 30, 30);
    for (; i < 5; i++) {
        self->labels[i].text = D_0043CF88[i];
        self->labels[i].uvSize = D_00438D48;
        self->labels[i].style = 1;
        self->labels[i].SetPosition(D_00438D50[i], D_00438D40);
        self->labels[i].SetHeight(23);
        self->labels[i].SetColor(D_00438D20);
        func_00207610(&self->labels[i], 1, 2, 30, 30);
        self->labels[i].targetPosition = D_00438D78[i];
        self->labels[i].targetHeight = 23;
        self->labels[i].targetColor = D_00438D30;
        D_0043D988[i] = 0;
        D_0043D9D8[i] = 0;
    }
    for (i = 0; i < 5; i++) {
        D_003BDD10[i][0] = '0';
        self->values[i].text = D_003BDD10[i];
        self->values[i].uvSize = D_00438D48;
        self->values[i].style = 1;
        self->values[i].SetPosition(D_00438CF0, D_00438CF8);
        self->values[i].SetHeight(23);
        self->values[i].SetColor(D_00438DA0);
        if (i == 1) {
            self->values[1].targetColor = D_00438DB0;
            self->values[1].color = self->values[1].targetColor;
        }
        func_00207610(&self->values[i], 1, 2, 30, 30);
        D_0043D9D0[i] = 0;
    }
    self->resource[0] = func_00108328(D_0040F4C4, D_003BE714);
    self->resource[1] = func_00108328(D_0040F4C4, D_003BE710);
    for (i = 0; i < 10; i++) {
        self->sprites[i].mode = (s32)self->resource[(s8)(i / 5)];
        self->sprites[i].SetPosition(D_00438CF0, D_00438CF8);
        self->sprites[i].SetExtent(D_00438E20);
        self->sprites[i].SetColor(D_00438DF0);
        self->sprites[i].SetUV(D_00438E28[0], D_00438E28[1]);
        self->sprites[i].Initialize(1, 2, 30, 30);
    }
    self->labels[0].duration = 0.6f;
    self->labels[0].remaining = 0.6f;
    func_001EED98(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x30), 0, 0.0f);
    func_001EED98(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x30), 7, 0.0f);
    D_0043D988[0] = 1;
    func_00275448(D_003BDD10[0], self->count2, 0, 0);
    func_00208C60(D_003BDD10[1], self->elapsed);
    func_00275448(D_003BDD10[2], self->count0, 0, 0);
    func_00275448(D_003BDD10[3], self->count1, 0, 0);
    func_00208C60(D_003BDD10[4], self->time);
    return 1;
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f30", func_00207B80);
#endif

extern void** D_0040F4DC;
extern "C" void* func_00122780(void*, s32);
extern "C" void func_002072A0(void*);
extern "C" void func_002072E0(void*, f32);
extern "C" void func_002076A8(void*);
extern "C" void func_002076F8(void*, f32);
extern "C" void func_00208AF8(void*, s32);
static inline void StatisticsSound(s32 id) {
    void* sound = (s8*)D_0040F510 + 0x8000;
    func_001EED98(M2C_FIELD(M2C_FIELD(sound, void**, 0x4BD8), void**, 0x30), id, 0.0f);
}
static inline s32 StatisticsLabelFinished(const FrontendTextObject* label) {
    u8 finished = 1;
    if (!(label->remaining <= 0.0f)) finished = 0;
    return finished;
}
static inline void StatisticsSpritePosition(FrontendSpriteObject* sprite, const FrontendVec2& position) {
    sprite->position = sprite->targetPosition = position;
    sprite->scale = D_00438E10;
}
static inline void StatisticsSpriteColor(FrontendSpriteObject* sprite, s128 color) {
    sprite->color = sprite->targetColor = color;
}
static inline void StatisticsValuePosition(FrontendTextObject* text, const FrontendVec2& position) {
    text->position = text->targetPosition = position;
    text->scale = D_00438D40;
}
static inline void StatisticsValueColor(FrontendTextObject* text, s128 color) {
    text->color = text->targetColor = color;
}
extern "C" void func_00208140(FrontendStatisticsPanel* self, f32 delta) {
    s8 i = 0;
    void* comparison = func_00122780(D_0040F4E8, 0);
    for (; i < 5; i++) {
        if (i && !D_0043D988[i] && D_0043D988[i - 1] && (u8)StatisticsLabelFinished(&self->labels[i - 1])) {
            if (D_0043D9D0[i - 1] == 0) {
                D_0043D9D0[i - 1] = 1;
                StatisticsSound(10);
                StatisticsSpritePosition(&self->sprites[i - 1], D_00438E38[i - 1]);
                StatisticsSpriteColor(&self->sprites[i - 1], D_00438E00);
                func_002072A0(&self->sprites[i - 1]);
                if (i == 2) {
                    {
                        FrontendSpriteObject* array = self->sprites;
                        void* sprite = (s8*)array + 0x360;
                        M2C_FIELD(sprite, s64*, 0x48) = D_00438E38[1].bits;
                        M2C_FIELD(sprite, s64*, 0x40) = M2C_FIELD(array, s64*, 0x3A8);
                        M2C_FIELD(sprite, s64*, 0x50) = D_00438E10.bits;
                    }
                    {
                        FrontendSpriteObject* array = self->sprites;
                        void* sprite = (s8*)array + 0x360;
                        M2C_FIELD(sprite, s128*, 0x30) = D_00438E00;
                        M2C_FIELD(sprite, s128*, 0x20) = M2C_FIELD(array, s128*, 0x390);
                    }
                    func_002072A0(&self->sprites[6]);
                }
            } else if (D_0043D9D0[i - 1] == 2) {
                {
                    void* label = (void*)(i * 0x80 + (u32)self->labels);
                    M2C_FIELD(label, f32*, 0x74) = 0.6f;
                    M2C_FIELD(label, f32*, 0x78) = 0.6f;
                }
                StatisticsSound(7);
                D_0043D988[i] = 1;
            }
        }
        func_002076F8(&self->labels[i], delta);
    }
    if (D_0043D9D0[3] == 2 && (u8)StatisticsLabelFinished(&self->labels[4]) && D_0043D9D0[4] == 0) {
        D_0043D9D0[4] = 1;
        StatisticsSound(10);
        StatisticsSpritePosition(&self->sprites[i - 1], D_00438E38[i - 1]);
        StatisticsSpriteColor(&self->sprites[i - 1], D_00438E00);
        func_002072A0(&self->sprites[i - 1]);
    }
    for (i = 0; i < 5; i++) {
        if (D_0043D9D0[i] == 1) {
            self->countdown -= delta;
            if (self->countdown <= 0.0f) {
                self->countdown = 0.01f;
                switch (i) {
                    case 0:
                        StatisticsValuePosition(&self->values[i], D_00438DC0[i]);
                        ++self->count2;
                        if (self->count2 >= M2C_FIELD(comparison, s8*, 0x15)) {
                            StatisticsValueColor(&self->values[i], D_00438DB0);
                            func_00208AF8(self, i);
                        }
                        func_00275448(D_003BDD10[i], self->count2, 0, 0);
                        StatisticsSound(9);
                        D_0043D9D0[i] = 2;
                        break;
                    case 1: {
                        StatisticsValuePosition(&self->values[i], D_00438DC0[i]);
                        if (M2C_FIELD(comparison, f32*, 4) <= self->elapsed) {
                            StatisticsValueColor(&self->values[i], D_00438DA0);
                            if (!D_0043D9D8[i]) {
                                M2C_FIELD(i * 0x90 + M2C_FIELD(self, u32*, 0x24), s64*, 0x330) = D_00438E18.bits;
                                M2C_FIELD(i * 0x90 + M2C_FIELD(self, u32*, 0x24), s128*, 0x300) = D_00438DF0;
                                {
                                    void* sprite = (void*)(i * 0x90 + M2C_FIELD(self, u32*, 0x24) + 0x2D0);
                                    M2C_FIELD(sprite, f32*, 0x7C) = 0.2f;
                                    M2C_FIELD(sprite, f32*, 0x80) = 0.2f;
                                }
                                StatisticsSound(10);
                                D_0043D9D8[i] = 1;
                            }
                        }
                        f32 total = M2C_FIELD(*D_0040F4DC, f32*, 4);
                        f32 step = total / 20.0f;
                        if (self->elapsed < total - step) {
                            self->elapsed += step;
                            if ((s32)self->elapsed & 3) StatisticsSound(8);
                            func_00208C60(D_003BDD10[i], self->elapsed);
                        } else if (self->elapsed + 1.0f < total) {
                            self->elapsed = total;
                            func_00208C60(D_003BDD10[i], total);
                        } else {
                            StatisticsSound(9);
                            D_0043D9D0[i] = 2;
                        }
                        break;
                    }
                    case 2:
                        StatisticsValuePosition(&self->values[i], D_00438DC0[i]);
                        if (self->count0 >=
                            (s16)(M2C_FIELD(comparison, u16*, 0x1C) + M2C_FIELD(comparison, u16*, 0x1E))) {
                            StatisticsValueColor(&self->values[i], D_00438DB0);
                            func_00208AF8(self, i);
                        }
                        if (self->count0 <
                            (s16)(M2C_FIELD(*D_0040F4DC, u16*, 0x1C) + M2C_FIELD(*D_0040F4DC, u16*, 0x1E))) {
                            ++self->count0;
                            func_00275448(D_003BDD10[i], self->count0, 0, 0);
                            if (self->count0 % 10 == 0) StatisticsSound(8);
                        } else {
                            StatisticsSound(9);
                            D_0043D9D0[i] = 2;
                        }
                        break;
                    case 3:
                        StatisticsValuePosition(&self->values[i], D_00438DC0[i]);
                        if (self->count1 >= (s16)M2C_FIELD(comparison, u16*, 0x1E)) {
                            StatisticsValueColor(&self->values[i], D_00438DB0);
                            func_00208AF8(self, i);
                        }
                        if (self->count1 < M2C_FIELD(*D_0040F4DC, s16*, 0x1E)) {
                            ++self->count1;
                            func_00275448(D_003BDD10[i], self->count1, 0, 0);
                            if (self->count1 % 10 != 0) StatisticsSound(8);
                        } else {
                            StatisticsSound(9);
                            D_0043D9D0[i] = 2;
                        }
                        break;
                    case 4:
                        StatisticsValuePosition(&self->values[i], D_00438DC0[i]);
                        if (M2C_FIELD(comparison, f32*, 0xC) <= self->time) {
                            StatisticsValueColor(&self->values[i], D_00438DB0);
                            func_00208AF8(self, i);
                        }
                        if (self->time < M2C_FIELD(*D_0040F4DC, f32*, 0xC)) {
                            self->time += 1.0f;
                            func_00208C60(D_003BDD10[i], self->time);
                            if ((s32)self->time & 3) StatisticsSound(8);
                        } else {
                            StatisticsSound(9);
                            D_0043D9D0[i] = 2;
                        }
                        break;
                }
            }
        }
        func_002076A8(&self->values[i]);
        func_002076F8(&self->values[i], delta);
    }
    for (i = 0; i < 10; i++) func_002072E0(&self->sprites[i], delta);
}
