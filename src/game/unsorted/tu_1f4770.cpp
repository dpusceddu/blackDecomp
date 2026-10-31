#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/classes/other/UnknownVtable_003E0A40.hpp"
#ifdef NON_MATCHING
#include "game/classes/other/UnknownVtable_003E0AC0.hpp"
#endif

struct Sprite;
extern "C" {
void func_00278F00(void*, int, Sprite*);
extern char* D_0040F518;
}
template <class T> inline T& At(void* p, int offset) { return *(T*)((char*)p + offset); }
inline void ReleaseSprite(void* self, int group, int offset) {
    func_00278F00((void*)(At<signed char>(self, 0x12) * 0xa8 + (s32)D_0040F518 + 0x40), At<short>(self, 0x10) + group,
                  At<Sprite*>(self, offset));
}
inline void ReleaseSpriteSlot(void* self, int group, Sprite** slot) {
    func_00278F00((void*)(At<signed char>(self, 0x12) * 0xa8 + (s32)D_0040F518 + 0x40), At<short>(self, 0x10) + group,
                  *slot);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F4770);

int Unnamed::UnknownVtable_003E0A40::Function_001F4CB0() {
    ReleaseSprite(this, 0, 0x1c);
    ReleaseSprite(this, 0, 0x18);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8318);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F84E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8528);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F8FB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001FAC78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001FAE18);

#ifdef NON_MATCHING
// Unmatched: primary sprite-array cursor and countdown use exchanged saved registers (six differences).
int Unnamed::UnknownVtable_003E0AC0::Function_001FBB48() {
    ReleaseSprite(this, 0, 0x50);
    ReleaseSprite(this, 0, 0x58);
    ReleaseSprite(this, 2, 0x18);
    ReleaseSprite(this, 2, 0x20);
    for (int i = 0; i < 3; ++i) ReleaseSprite(this, 1, 0x28 + i * 4);
    ReleaseSprite(this, 2, 0x40);
    ReleaseSprite(this, 1, 0x48);
    ReleaseSprite(this, 2, 0x60);
    ReleaseSprite(this, 2, 0x68);
    Sprite** tail = &At<Sprite*>(this, 0xe8);
    for (int i = 0; i < 15; ++i) ReleaseSpriteSlot(this, 2, &At<Sprite*>(this, 0x70 + i * 4));
    for (int i = 0; i < 8; ++i) ReleaseSpriteSlot(this, 2, &tail[i]);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001FBB48);
#endif
