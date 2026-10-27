#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

#include "ps2/ee_types.h"

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
extern void func_002667E8(int);
extern void func_00266808(int, int);
extern void func_00266D28(EeU128, const CommandVec2*, int, const CommandVec2*, CommandExtra*);
extern CommandVec2 D_0043F8A8;
extern void func_00276698(CommandRecord*);

extern void func_002763B0(void *arg0);
extern s32 func_002761A0(...);
extern s32 func_00274040(void *);
extern s32 func_00277400(...);
extern void func_002778C8(...);

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276698);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276728);
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_002768B0);

void func_00276960(void *arg0, s64 *arg1, s64 *arg2) {
    M2C_FIELD(arg0, s64 *, 0x20) = (s64) *arg1;
    M2C_FIELD(arg0, s64 *, 0x28) = (s64) *arg2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276980);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276DA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276E58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00276E68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00277400);

void func_00277510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    func_00277400(arg0, arg1, arg2, arg3, arg4, arg5, (s32) func_002778C8, arg7);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276410", func_00277530);

}
