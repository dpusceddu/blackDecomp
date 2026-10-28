#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002050B0();
extern s32 func_00278F00();
extern void * D_003BDCC8;
extern void func_00204FF0(void*, void*);
extern void func_00276728(void*, const void*, const void*, const void*, s128, s32, const void*, const void*, s32);
extern s32 D_003BE718;
extern s32 func_0020D188(s32);
extern s32 D_0040F544;
extern s32 func_00205000(void*, s32, s32, s32);
extern void* func_00278EC0(void*, s32, s32);
extern void func_00277530(void*, f32, const void*, const void*, s128, void*, const u16*, const void*, s32);
extern void* D_0040F0E0;
extern s32* D_0040F4C0;
extern s128 D_00438CE0;
extern void func_00276610(void*, const void*, const void*, const void*, s128);
extern u8 D_0043D9D8[5];
extern s64 D_00438E38[5];
extern s64 D_00438E10, D_00438E18, D_00438E20;
extern s128 D_00438DF0, D_00438E00;
extern void* func_00275448(void*, s32, s32, s32);
extern s32 func_00384CF0(void*, const void*, const void*, const void*);

/* Private access views confirmed by command consumers; original class names,
 * unaccessed fields and the statistics panel's complete extent are UNVERIFIED. */
typedef union {
    struct {
        f32 x, y;
    };
    s64 bits;
} FrontendVec2;

typedef struct {
    u8 unk_00[8];
    void* manager;
    s32 handle;
    u8 unk_10[0x10];
    s128 color, targetColor;
    FrontendVec2 position, targetPosition, scale, extent, targetExtent, uvStart, uvEnd;
    s32 index;
    f32 remaining, duration;
    void* command;
    s32 mode;
} FrontendSprite;

typedef struct {
    u8 unk_00[8];
    void* manager;
    s32 handle;
    u8 unk_10[0x10];
    s128 color, targetColor;
    FrontendVec2 position, targetPosition, scale, uvSize;
    const u16* text;
    s32 index, style;
    f32 height, targetHeight, remaining, duration;
    void* command;
} FrontendText;

typedef struct {
    // UNVERIFIED: these counters are accessed only by the statistics setup draft.
    s32 state;
    f32 elapsed, time;
    s16 count0, count1;
    s8 count2;
    u8 unk_11[3];
    FrontendText* labels;
    FrontendText* values;
    void* resources[2]; // UNVERIFIED
    FrontendSprite* sprites;
    FrontendText* title;
} FrontendStatistics;

typedef char FrontendSpriteStride[sizeof(FrontendSprite) == 0x90 ? 1 : -1];
typedef char FrontendTextStride[sizeof(FrontendText) == 0x80 ? 1 : -1];

static inline void SetFrontendVec2(f32* value, f32 x, f32 y) {
    value[0] = x;
    value[1] = y;
}

s32 func_00206F08(void) {
    func_002050B0();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00206F28);
s32 func_00207110(void* self, const void* scale, const void* position) {
    f32 extent[2];
    void* command;
    func_00205000(self, 1, 30, 30);
    SetFrontendVec2(extent, (f32)D_0040F4C0[0], (f32)D_0040F4C0[1] / 6.0f);
    command = func_00278EC0(D_003BDCC8, 0, M2C_FIELD(self, s32*, 0xC));
    M2C_FIELD(self, void**, 0x18) = command;
    func_00276610(command, position, scale, extent, D_00438CE0);
    return 1;
}

void func_002071C0(void) {

}

s32 func_002071C8(void *arg0) {
    func_00278F00(D_003BDCC8, 0, M2C_FIELD(arg0, s32 *, 0x18));
    return 1;
}

void func_002071F8(void* self, void* manager) {
    func_00204FF0(self, manager);
}

s32 func_00207218(FrontendSprite* self, s32 index, s32 arg2, s32 arg3, s32 arg4) {
    void* command;
    func_00205000(self, arg2, arg3, arg4);
    self->index = index;
    self->remaining = 0;
    command = func_00278EC0(self->manager, index, self->handle);
    self->command = command;
    func_00276728(command, &self->position, &self->scale, &self->extent, self->color, self->mode, &self->uvStart,
                  &self->uvEnd, 0);
    return 1;
}

void func_002072A0(void *arg0) {
    func_00276728(M2C_FIELD(arg0, void **, 0x84), arg0 + 0x40, arg0 + 0x50, arg0 + 0x58, M2C_FIELD(arg0, s128 *, 0x20), M2C_FIELD(arg0, s32 *, 0x88), arg0 + 0x68, arg0 + 0x70, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_002072E0);

void func_002075F0(void* self, void* manager) {
    func_00204FF0(self, manager);
}

s32 func_00207610(void* self, s32 index, s32 arg2, s32 arg3, s32 arg4) {
    void* command;
    func_00205000(self, arg2, arg3, arg4);
    M2C_FIELD(self, s32*, 0x74) = 0;
    command = func_00278EC0(M2C_FIELD(self, void**, 8), index, M2C_FIELD(self, s32*, 0xC));
    M2C_FIELD(self, s32*, 0x64) = index;
    M2C_FIELD(self, void**, 0x7C) = command;
    func_00277530(command, M2C_FIELD(self, f32*, 0x6C), (s8*)self + 0x40, (s8*)self + 0x50,
                  M2C_FIELD(self, s128*, 0x20), M2C_FIELD(D_0040F0E0, void**, 0x2107C),
                  M2C_FIELD(self, const u16**, 0x60), (s8*)self + 0x58, M2C_FIELD(self, s32*, 0x68));
    return 1;
}
void func_002076A8(FrontendText* self) {
    func_00277530(self->command, self->height, &self->position, &self->scale, self->color,
                  M2C_FIELD(D_0040F0E0, void**, 0x2107C), self->text, &self->uvSize, self->style);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_002076F8);

s32 func_00207938(void *arg0)
{
  s8 *new_var;
  new_var = (s8 *) arg0;
  func_002050B0();
  func_00278F00(*((void **) (new_var + 8)), *((s32 *) (new_var + 0x64)), *((s32 *) (new_var + 0x7C)));
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00207970);
#ifdef NON_MATCHING
extern void* D_0040F0E0;
extern s32* D_0040F4C0;
extern void* D_0040F4C4;
extern void* D_0040F510;
extern const char* D_003BE714;
extern const char* D_003BE710;
extern u16 D_0043D990[32], D_0043CF88[5][256], D_003BDD10[5][256];
extern const u16 D_003BDCD0[];
extern s8 D_0043D988[5], D_0043D9D0[5];
extern FrontendVec2 D_00438D48, D_00438D10, D_00438D40, D_00438CF0, D_00438CF8;
extern FrontendVec2 D_00438D50[5], D_00438D78[5], D_00438E28[2];
extern s128 D_00438D00, D_00438D20, D_00438D30, D_00438DA0, D_00438DB0, D_00438DF0;
extern const char* func_00103358(void*, s32);
extern void func_00275260(const char*, u16*, s32);
extern u16* func_002753F0(u16*, const u16*);
extern s32 func_00207610(void*, s32, s32, s32, s32);
extern void* func_00108328(void*, const char*);
extern void func_001EED98(void*, s32, f32);
extern void* func_00275448(void*, s32, s32, s32);
extern s32 func_00208C60(void*, f32);
static inline void TextPosition(FrontendText* self, s64 position, const s64* scale) {
    self->targetPosition.bits = position;
    self->position.bits = position;
    self->scale.bits = *scale;
}
static inline void TextHeight(FrontendText* self, f32 height) {
    self->targetHeight = height;
    self->height = height;
}
static inline void TextColor(FrontendText* self, s128 color) {
    self->targetColor = color;
    self->color = color;
}
static inline void SpritePosition(FrontendSprite* self, s64 position, const s64* scale) {
    self->targetPosition.bits = position;
    self->position.bits = position;
    self->scale.bits = *scale;
}
static inline void SpriteExtent(FrontendSprite* self, s64 extent) {
    self->targetExtent.bits = extent;
    self->extent.bits = extent;
}
static inline void SpriteColor(FrontendSprite* self, s128 color) {
    self->targetColor = color;
    self->color = color;
}
static inline s64 HeaderPosition(f32 x, f32 y) {
    FrontendVec2 value;
    value.x = x;
    value.y = y;
    return value.bits;
}
// Unmatched: setter inlining, loop lifetimes and register allocation differ.
s32 func_00207B80(FrontendStatistics* self) {
    s8 i = 0;
    self->state = 0;
    self->elapsed = 0.0f;
    self->time = 0.0f;
    self->count0 = 0;
    self->count1 = 0;
    self->count2 = 0;
    func_00275260(func_00103358(D_0040F0E0, M2C_FIELD(D_0040F0E0, u8*, 0x2020C)), D_0043D990, 32);
    func_002753F0(D_0043D990, D_003BDCD0);
    self->title->text = D_0043D990;
    self->title->uvSize = D_00438D48;
    self->title->style = 1;
    TextPosition(self->title, HeaderPosition((f32)D_0040F4C0[0] * 0.5f, 50.0f), D_00438D10.bits);
    TextHeight(self->title, 30.0f);
    TextColor(self->title, D_00438D00);
    func_00207610(self->title, 1, 2, 30, 30);
    for (; i < 5; i++) {
        self->labels[i].text = D_0043CF88[i];
        self->labels[i].uvSize = D_00438D48;
        self->labels[i].style = 1;
        TextPosition(&self->labels[i], D_00438D50[i].bits, &D_00438D40.bits);
        TextHeight(&self->labels[i], 23.0f);
        TextColor(&self->labels[i], D_00438D20);
        func_00207610(&self->labels[i], 1, 2, 30, 30);
        self->labels[i].targetPosition = D_00438D78[i];
        self->labels[i].targetHeight = 23.0f;
        self->labels[i].targetColor = D_00438D30;
        D_0043D988[i] = 0;
        D_0043D9D8[i] = 0;
    }
    for (i = 0; i < 5; i++) {
        D_003BDD10[i][0] = '0';
        self->values[i].text = D_003BDD10[i];
        self->values[i].uvSize = D_00438D48;
        self->values[i].style = 1;
        TextPosition(&self->values[i], D_00438CF0.bits, &D_00438CF8.bits);
        TextHeight(&self->values[i], 23.0f);
        TextColor(&self->values[i], D_00438DA0);
        if (i == 1) {
            self->values[1].targetColor = D_00438DB0;
            self->values[1].color = self->values[1].targetColor;
        }
        func_00207610(&self->values[i], 1, 2, 30, 30);
        D_0043D9D0[i] = 0;
    }
    self->resources[0] = func_00108328(D_0040F4C4, D_003BE714);
    self->resources[1] = func_00108328(D_0040F4C4, D_003BE710);
    for (i = 0; i < 10; i++) {
        FrontendSprite* sprite;
        void* table;
        s16 adjust;
        self->sprites[i].mode = (s32)self->resources[(s8)(i / 5)];
        SpritePosition(&self->sprites[i], D_00438CF0.bits, &D_00438CF8.bits);
        SpriteExtent(&self->sprites[i], D_00438E20);
        SpriteColor(&self->sprites[i], D_00438DF0);
        self->sprites[i].uvStart = D_00438E28[0];
        self->sprites[i].uvEnd = D_00438E28[1];
        sprite = &self->sprites[i];
        table = M2C_FIELD(sprite, void**, 0x14);
        adjust = M2C_FIELD(table, s16*, 0x10);
        M2C_FIELD(table, s32(**)(void*, s32, s32, s32, s32), 0x14)((s8*)sprite + adjust, 1, 2, 30, 30);
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00207B80);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00208140);
static inline const s64* FrontendSlotPosition(s32 index) { return &D_00438E38[index]; }
void func_00208AF8(void* self, s32 index) {
    u8* initialized = (s8)index + D_0043D9D8;
    if (*initialized == 0) {
        s32 offset = (s8)index * 0x90;
        s64 position = *FrontendSlotPosition((s8)index);
        {
            void* item = (void*)(offset + M2C_FIELD(self, u32*, 0x24) + 0x2D0);
            M2C_FIELD(item, s64*, 0x48) = position;
            M2C_FIELD(item, s64*, 0x40) = position;
            M2C_FIELD(item, s64*, 0x50) = D_00438E10;
        }
        {
            void* item = (void*)(offset + M2C_FIELD(self, u32*, 0x24) + 0x2D0);
            {
                s64 extent = D_00438E18;
                M2C_FIELD(item, s64*, 0x60) = extent;
                M2C_FIELD(item, s64*, 0x58) = extent;
            }
        }
        {
            void* item = (void*)(offset + M2C_FIELD(self, u32*, 0x24) + 0x2D0);
            {
                s128 color = D_00438DF0;
                M2C_FIELD(item, s128*, 0x30) = color;
                M2C_FIELD(item, s128*, 0x20) = color;
            }
        }
        M2C_FIELD(offset + M2C_FIELD(self, u32*, 0x24), s64*, 0x330) = D_00438E20;
        M2C_FIELD(offset + M2C_FIELD(self, u32*, 0x24), s128*, 0x300) = D_00438E00;
        {
            void* item = (void*)(offset + M2C_FIELD(self, u32*, 0x24) + 0x2D0);
            M2C_FIELD(item, f32*, 0x7C) = 0.2f;
            M2C_FIELD(item, f32*, 0x80) = 0.2f;
        }
        *initialized = 1;
    }
}
s32 func_00208BF0(FrontendStatistics* self) {
    s8 i;
    for (i = 0; i < 5; i++) { func_00207938(&self->labels[i]); }
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00208C58);
// Native adjacent constants; the SDK marker's original owner and identifier are UNVERIFIED.
const u16 D_003FA270[] = {'%', '1', ':', '%', '2', 0};
const char D_003FA280[] = "DirtyXSDK";

s32 func_00208C60(void* destination, f32 time) {
    u16 minutes[8];
    u16 seconds[8];
    s32 wholeMinutes = (s32)(time / 60.0f);
    s32 remaining = (s32)(time - (f32)wholeMinutes * 60.0f);
    func_00275448(minutes, wholeMinutes, 1, 0);
    func_00275448(seconds, remaining, 2, 0);
    return func_00384CF0(destination, D_003FA270, minutes, seconds);
}


void func_002092D8(s32 arg0) {
    D_003BE718 = arg0;
}

void func_002092E8(void) {
    func_0020D188(D_0040F544 + 0xE90);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_206f08", func_00209310);
