#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "ps2/ee_types.h"

// UNVERIFIED: packet field names and the address argument remain unidentified.
extern EeU128* D_0040E5F0;
extern void func_002B3D88(s32 channel, s32 count);

static inline EeU128 PackGifWords(u64 high, u64 low) {
    EeU128 packet;
    __asm__("pcpyld pv, hv, lv" : "=r pv"(packet) : "r hv"(high), "r lv"(low));
    return packet;
}
#endif

extern s8 D_0040DE71;
extern s8 D_0040DE74;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_00269EA0);

s32 func_0026A450(void) {
    D_0040DE71 = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026A460);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026A6F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026A7A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026A840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026A8D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026A998);

void func_0026AA60(s8 arg0) {
    D_0040DE74 = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026AA68);
#ifdef NON_MATCHING
// Unmatched: packet cursor and quadword construction scheduling differ.
void func_0026AB20(s64 address) {
    EeU128* packet;
    func_002B3D88(0, 3);
    packet = D_0040E5F0;
    *packet++ = PackGifWords(((u64)0xA000 << 29 | 0x8440) << 18, 0x10000002);
    *packet++ = PackGifWords(14, ((u64)0x8000 << 45) | 0x8001);
    *packet++ = PackGifWords(address + 8, 5);
    D_0040E5F0 = packet;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026AB20);
#endif
#ifdef NON_MATCHING
// Unmatched: packet cursor and quadword construction scheduling differ.
void func_0026ABB0(s64 address) {
    EeU128* packet;
    func_002B3D88(0, 3);
    packet = D_0040E5F0;
    *packet++ = PackGifWords(((u64)0xA000 << 29 | 0x8440) << 18, 0x10000002);
    *packet++ = PackGifWords(14, ((u64)0x8000 << 45) | 0x8001);
    *packet++ = PackGifWords(address + 8, 0);
    D_0040E5F0 = packet;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026ABB0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026AC40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026AC48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026AEF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026B230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026B480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_269ea0", func_0026B738);
