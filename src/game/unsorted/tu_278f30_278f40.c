#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00278F30();
extern f32 func_002759E0(void *, const u16 *);

typedef struct {
    f32 position;
    u8 unk_04[4];
    f32 width;
    u8 unk_0C[4];
    const u16 *text;
    void *font;
    u8 unk_18[8];
    f32 scale;
    u16 flags;
    s8 alignment;
} Recovered_TextLayout; /* Field meanings UNVERIFIED. */

void func_00278F40(void) {
    func_00278F30();
}

f32 func_00278F60(Recovered_TextLayout *layout) {
    switch (layout->alignment) {
    case 0:
    default:
        return 0.0f;
    case 2:
        return 1.0f;
    case 1:
        return 0.5f;
    }
}

void func_00278FB0(Recovered_TextLayout *layout) {
    if ((layout->flags & 6) == 0) {
        f32 alignment = func_00278F60(layout);
        f32 width = func_002759E0(layout->font, layout->text) * layout->scale;
        layout->position += (layout->width - width) * alignment;
        if (layout->alignment != 3) {
            layout->width = width;
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_278f30_278f40", func_00279030);
