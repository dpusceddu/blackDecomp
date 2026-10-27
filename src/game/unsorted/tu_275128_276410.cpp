#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

#include "ps2/ee_types.h"
#ifdef NON_MATCHING
#include "game/effects/vu_math.h"
#endif

// Private command views; original class identities and unused fields are UNVERIFIED.

struct CommandVec2 {
    union {
        struct {
            float x, y;
        };
        EeU64 bits;
    };
    CommandVec2() {}
    CommandVec2(float a, float b) : x(a), y(b) {}
    CommandVec2(const CommandVec2& other) { bits = other.bits; }
    CommandVec2& operator=(const CommandVec2& other) {
        bits = other.bits;
        return *this;
    }
    CommandVec2 operator*(const CommandVec2& other) const {
        CommandVec2 result(x * other.x, y * other.y);
        return result;
    }
    CommandVec2 operator-(const CommandVec2& other) const {
        CommandVec2 result(x - other.x, y - other.y);
        return result;
    }
    CommandVec2 operator/(const CommandVec2& other) const {
        CommandVec2 result(x / other.x, y / other.y);
        return result;
    }
    CommandVec2 operator+(const CommandVec2& other) const {
        CommandVec2 result(x + other.x, y + other.y);
        return result;
    }
};
struct CommandExtra {
    CommandVec2 start;
    CommandVec2 end;
    int unk_10;
    int unk_14;
};
struct CommandTextExtra {
    void* font;
    const unsigned short* text;
    float inverseAspect;
};

struct CommandRecord {
    CommandVec2 position;
    CommandVec2 extent;
    EeU128 payload;
    unsigned char unk_20[0x1c];
    void (*callback)(void);
};
struct CommandNode {
    CommandNode* next;
    int unk_4;
    unsigned char record[0x50];
};
struct CommandState {
    EeU128 local[2];
    EeU128 current[2];
    unsigned char unk_40[4];
    CommandNode* first;
    int unk_48;
    void* owner;
};
struct CommandManager {
    unsigned char unk_0[0x14];
    CommandState* state;
};

static inline CommandExtra& Extra(CommandRecord* self) { return *(CommandExtra*)((char*)self + 0x20); }
static inline void InitializeExtra(CommandExtra* const& fields, int mode, int value, const CommandVec2& start,
                                   const CommandVec2& end) {
    fields->unk_10 = mode;
    fields->unk_14 = value;
    fields->start = start;
    fields->end = end;
}

#ifdef NON_MATCHING
// UNVERIFIED: rotation layouts and affine lowering have no matching callback yet.
struct CommandRotation {
    CommandVec2 pivot;
    int texture;
    float degrees;
};
struct CommandRotationExtra {
    CommandVec2 start;
    CommandVec2 end;
    CommandRotation* rotation;
    int variant;
};

static inline CommandVec2 ScaleCommandVector(const CommandVec2& v, float scale) {
    CommandVec2 result(v.x * scale, v.y * scale);
    return result;
}

struct CommandAffine {
    CommandVec2 xAxis;
    CommandVec2 yAxis;
    CommandVec2 translation;

    void Transform(CommandVec2* points) const {
        for (int remaining = 3; remaining >= 0; --remaining, ++points) {
            CommandVec2 result = translation;
            result.x += xAxis.x * points->x;
            result.y += xAxis.y * points->x;
            result.x += yAxis.x * points->y;
            result.y += yAxis.y * points->y;
            *points = result;
        }
    }
};

#endif

#define COMMAND_OFFSET(type, field) ((EeU32) & ((type*)0)->field)

typedef char CheckVec2Size[sizeof(CommandVec2) == 8 ? 1 : -1];
typedef char CheckRecordSize[sizeof(CommandRecord) == 0x40 ? 1 : -1];
typedef char CheckRecordPayload[COMMAND_OFFSET(CommandRecord, payload) == 0x10 ? 1 : -1];
typedef char CheckRecordCallback[COMMAND_OFFSET(CommandRecord, callback) == 0x3c ? 1 : -1];
typedef char CheckExtraSize[sizeof(CommandExtra) == 0x18 ? 1 : -1];
typedef char CheckNodeRecord[COMMAND_OFFSET(CommandNode, record) == 8 ? 1 : -1];
typedef char CheckStateSize[sizeof(CommandState) == 0x50 ? 1 : -1];
typedef char CheckStateFirst[COMMAND_OFFSET(CommandState, first) == 0x44 ? 1 : -1];
typedef char CheckManagerState[COMMAND_OFFSET(CommandManager, state) == 0x14 ? 1 : -1];

extern "C" {

extern void func_00276290(void*, void*);
extern int func_00274018(int, int, int);
extern void func_002740D8(void*, void*);
extern void func_00273F30(CommandManager*, int, int, int, CommandState*, void*, int);
extern void func_00266F50(EeU128, const CommandVec2*, int, const CommandVec2*);
extern int func_002667E8(int);
extern int func_00266808(int, int);
extern void func_00266D28(EeU128, const CommandVec2*, int, const CommandVec2*, CommandExtra*);
extern CommandVec2 D_0043F8A8;
#ifdef NON_MATCHING
extern void func_002679E8(EeU128, const CommandVec2*, int, const CommandVec2*, const CommandVec2*);
extern CommandVec2 D_0043F8B0;
#endif
extern float func_002758E0(void*, const unsigned short*);
extern void func_00276698(CommandRecord*);
extern void func_002767E8(CommandRecord*, CommandExtra*);
extern void func_00276980(CommandRecord*, CommandExtra*);
extern void func_00276E68(CommandRecord*, CommandExtra*);

extern void func_002763B0(void *arg0);
extern s32 func_002761A0(...);
extern s32 func_00274040(void *);
extern void func_00277400(CommandRecord*, const CommandVec2*, const CommandVec2*, EeU128, void*,
                          const unsigned short*, void (*)(void), float);
extern void func_002778C8(...);
extern void (*const D_00400408[])(void);


void func_00276410(void *arg0) {
    func_002763B0(M2C_FIELD(arg0, void **, 0x14));
    func_002761A0(M2C_FIELD(arg0, void **, 0x14));
    func_002761A0((char*)M2C_FIELD(arg0, void **, 0x14) + 0x20);
    func_00274040(arg0);
}

void func_00276458(CommandManager* self) {
    CommandState* state = self->state;
    EeU128 first = state->local[0];
    EeU128 second = state->local[1];
    state->current[0] = first;
    state->current[1] = second;
    CommandNode* node = self->state->first;
    while (node) {
        func_00276290(node->record, self->state->current);
        node = node->next;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_002764C8);

void* func_002764D0(CommandManager* self, int count, CommandState* storage) {
    void* end = (char*)storage + 0x50;
    int size = func_00274018(count, 0x50, 0x10);
    self->state = storage;
    func_002761A0(storage);
    func_002761A0(self->state->current);
    func_002740D8(self->state->unk_40, self);
    self->state->unk_48 = 0;
    self->state->owner = self;
    func_00273F30(self, count, 0x50, 0x10, self->state, end, size);
    return (void*)(size + (EeU32)end);
}

void func_00276590(CommandRecord* self, const CommandVec2* position, const CommandVec2* extent, EeU128 payload,
                   void (*callback)(void), int size, int extra) {
    self->position = *position;
    self->extent = *extent;
    self->payload = payload;
    self->callback = callback;
}

void func_002765B0(CommandRecord* self, const CommandVec2* position, const CommandVec2* scale) {
    self->position = *position - (self->extent * *scale);
}

void func_00276610(CommandRecord* self, const CommandVec2* position, const CommandVec2* scale,
                   const CommandVec2* extent, EeU128 payload) {
    func_00276590(self, &(*position - (*extent * *scale)), extent, payload, (void (*)(void))func_00276698, 0x40, 0);
}

void func_00276698(CommandRecord* self) {
    CommandVec2 corners[2];
    corners[0] = self->position;
    corners[1] = self->position + self->extent;
    func_00266F50(self->payload, &CommandVec2(0.0f, 0.0f), 1, corners);
}
void func_00276728(CommandRecord* self, const CommandVec2* position, const CommandVec2* scale,
                   const CommandVec2* extent, EeU128 payload, int mode, const CommandVec2* start,
                   const CommandVec2* end, int value) {
    CommandExtra* extra = &Extra(self);
    InitializeExtra(extra, mode, value, *start, *end);
    func_00276590(self, &(*position - (*extent * *scale)), extent, payload, (void (*)(void))func_002767E8, 0x40, 0x18);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_002767E0);
void func_002767E8(CommandRecord* self, CommandExtra* extra) {
    CommandVec2 corners[2];
    corners[0] = self->position;
    corners[1] = self->position + self->extent;
    if (extra->unk_14 == 0) {
        func_002667E8(extra->unk_10);
    } else {
        func_00266808(extra->unk_10, extra->unk_14);
    }
    func_00266D28(self->payload, &D_0043F8A8, 1, corners, extra);
}

void func_002768B0(CommandRecord* self, const CommandVec2* position, const CommandVec2* extent,
                   const CommandVec2* scale, EeU128 payload, int mode, const CommandVec2* start, const CommandVec2* end,
                   int value) {
    CommandExtra* extra = &Extra(self);
    InitializeExtra(extra, mode, value, *start, *end);
    func_00276590(self, &(*position - (*extent * *scale)), extent, payload, (void (*)(void))func_00276980, 0x40, 0x18);
}

void func_00276960(void *arg0, s64 *arg1, s64 *arg2) {
    M2C_FIELD(arg0, s64 *, 0x20) = (s64) *arg1;
    M2C_FIELD(arg0, s64 *, 0x28) = (s64) *arg2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276978);
#ifdef NON_MATCHING
// Unmatched: native scalar VU trig input/readback, affine copies and loop scheduling differ.
void func_00276980(CommandRecord* self, CommandExtra* raw) {
    CommandRotationExtra* extra = (CommandRotationExtra*)raw;
    CommandVec2 points[4];
    CommandVec2 uv[4];
    float radians = extra->rotation->degrees * 0.01745329238474369f;
    BkEffectPointPS2 trig = BkEffectSpillPS2(BkEffectVUSinCosPS2(radians, radians));
    CommandVec2 pivot = extra->rotation->pivot;
    points[0] = CommandVec2(0.0f, 0.0f);
    points[1] = CommandVec2(1.0f, 0.0f);
    points[2] = CommandVec2(0.0f, 1.0f);
    points[3] = CommandVec2(1.0f, 1.0f);
    CommandAffine transform;
    transform.xAxis = CommandVec2(trig.y * self->extent.x, -trig.x * self->extent.y);
    transform.yAxis = CommandVec2(trig.x * self->extent.x, trig.y * self->extent.y);
    transform.translation = ((pivot * self->extent) - ScaleCommandVector(transform.xAxis, pivot.x)) -
                            ScaleCommandVector(transform.yAxis, pivot.y) + self->position;
    transform.Transform(points);
    uv[0] = extra->start;
    uv[1] = CommandVec2(extra->end.x, extra->start.y);
    uv[2] = CommandVec2(extra->start.x, extra->end.y);
    uv[3] = extra->end;
    if (extra->variant == 0) {
        func_002667E8(extra->rotation->texture);
    } else {
        func_00266808(extra->rotation->texture, extra->variant);
    }
    func_002679E8(self->payload, &D_0043F8B0, 4, points, uv);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276980);
#endif
void func_00276DA8(CommandRecord* self, const CommandVec2* position, const CommandVec2* extent,
                   const CommandVec2* scale, EeU128 payload, int mode, const CommandVec2* start, const CommandVec2* end,
                   int value) {
    CommandExtra* extra = &Extra(self);
    InitializeExtra(extra, mode, value, *start, *end);
    func_00276590(self, &(*position - (*extent * *scale)), extent, payload, (void (*)(void))func_00276E68, 0x40, 0x18);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276E58);
#ifdef NON_MATCHING
// Unmatched: native scalar VU trig input/readback, affine copies and loop scheduling differ.
void func_00276E68(CommandRecord* self, CommandExtra* raw) {
    CommandRotationExtra* extra = (CommandRotationExtra*)raw;
    CommandVec2 points[4];
    CommandVec2 uv[4];
    points[0] = self->position;
    points[3] = self->position + self->extent;
    points[1] = CommandVec2(points[3].x, points[0].y);
    points[2] = CommandVec2(points[0].x, points[3].y);
    uv[0] = extra->start;
    uv[1] = CommandVec2(extra->end.x, extra->start.y);
    uv[2] = CommandVec2(extra->start.x, extra->end.y);
    uv[3] = extra->end;
    if (extra->rotation->degrees != 0.0f) {
        CommandAffine transform;
        transform.xAxis = CommandVec2(1.0f, 0.0f);
        transform.yAxis = CommandVec2(0.0f, 1.0f);
        transform.translation = CommandVec2(-extra->rotation->pivot.x, -extra->rotation->pivot.y);
        transform.Transform(points);
        float radians = extra->rotation->degrees * 0.01745329238474369f;
        BkEffectPointPS2 trig = BkEffectSpillPS2(BkEffectVUSinCosPS2(radians, radians));
        transform.xAxis = CommandVec2(trig.y, -trig.x);
        transform.yAxis = CommandVec2(trig.x, trig.y);
        transform.translation = CommandVec2(0.0f, 0.0f);
        transform.Transform(points);
        transform.xAxis = CommandVec2(1.0f, 0.0f);
        transform.yAxis = CommandVec2(0.0f, 1.0f);
        transform.translation = extra->rotation->pivot;
        transform.Transform(points);
    }
    if (extra->variant == 0) {
        func_002667E8(extra->rotation->texture);
    } else {
        func_00266808(extra->rotation->texture, extra->variant);
    }
    func_002679E8(self->payload, &D_0043F8B0, 4, points, uv);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276E68);
#endif
void func_00277400(CommandRecord* self, const CommandVec2* position, const CommandVec2* scale, EeU128 payload,
                   void* font, const unsigned short* text, void (*callback)(void), float height) {
    CommandTextExtra* extra = (CommandTextExtra*)((char*)self + 0x20);
    float aspect = func_002758E0(font, text);
    CommandVec2 extent(aspect * height, height);
    extra->font = font;
    extra->text = text;
    extra->inverseAspect = 1.0f / aspect;
    func_00276590(self, &(*position - (extent * *scale)), &extent, payload, callback, 0x40, 0xc);
}

void func_00277510(CommandRecord* self, const CommandVec2* position, const CommandVec2* scale, EeU128 payload,
                   void* font, const unsigned short* text, void (*unused)(void), float height) {
    func_00277400(self, position, scale, payload, font, text, (void (*)(void))func_002778C8, height);
}

#ifdef NON_MATCHING
// Unmatched: instructions match, but the owned callback table and adjacent string layout are unresolved.
void func_00277530(CommandRecord* self, const CommandVec2* position, const CommandVec2* scale, EeU128 payload,
                   void* font, const unsigned short* text, const CommandVec2* uvSize, int style, float height) {
    func_00277400(self, position, scale, payload, font, text, D_00400408[style], height);
    *(CommandVec2*)((char*)self + 0x30) = *uvSize / self->extent;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00277530);
#endif

}
