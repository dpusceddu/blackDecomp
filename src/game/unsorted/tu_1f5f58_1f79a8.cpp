#include "include_asm.h"
#include "ps2/prelude.h"

// Partial text ring view; the original class and field meanings are UNVERIFIED.
struct TextRingView {
    char unknown00[0x18];
    s8 index, unknown19, count;
    char unknown1b[0xd];
    u16 entries[20][200];
};

extern "C" u16* func_00275398(u16*, s32, const u16*);

extern "C" void func_001F79A8(TextRingView* self, const u16* text) {
    if (self->count < 20) {
        func_00275398(self->entries[(s32)self->index], 200, text);
        self->count++;
        self->index = (self->index + 1) % 20;
    }
}
