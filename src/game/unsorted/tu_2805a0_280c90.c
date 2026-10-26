#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00388E40(void *);
extern void func_00284298(void *);
extern void func_0026F3C0(void *);
extern void func_00382348(void *, s32);
extern u32 D_0040EB30[];

typedef struct {
    void *object;
    s32 unk_04;
    u8 unk_08;
    u8 unk_09[3];
} Recovered_AudioEntry;

typedef struct {
    Recovered_AudioEntry entries[48];
    s32 count;
} Recovered_AudioEntryList; /* Entry and object roles UNVERIFIED. */

typedef struct {
    u16 year, month, day, hour, minute, second;
} Recovered_ClockFields;

s32 func_00280C90(s32 arg0, s32 arg1) {
    s32 var_2;
    s32 var_6;
    s32 var_7;

    var_2 = M2C_FIELD(arg0, s32 *, 0x240);
    var_7 = 0;
    if (var_2 > 0) {
        var_6 = arg0;
        do {
            var_7 += 1;
            M2C_FIELD(M2C_FIELD(var_6, u32 *, 0), s8 *, 0x35) = (s8) arg1;
            var_2 = var_7 < M2C_FIELD(arg0, s32 *, 0x240);
            var_6 += 0xC;
        } while (var_2 != 0);
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280c90", func_00280CC8);
#ifdef NON_MATCHING
// Unmatched: prologue and loop scheduling differ.
void func_00280CD0(Recovered_AudioEntryList *list, s32 arg1) {
    s32 index = 0;
    Recovered_AudioEntry *entry = list->entries;
    while (index < list->count) {
        void *object = entry->object;
        s64 *key = (s64 *)func_00388E40(object);
        if (key != 0 && *key == arg1) {
            func_00284298(object);
            entry->unk_08 = 0;
            entry->unk_04 = 0;
        }
        index++;
        entry++;
    }
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280c90", func_00280CD0);

u32 func_00280D70(void) {
    Recovered_ClockFields time;
    u32 value;
    func_0026F3C0(&time);
    value = time.second + time.minute * 60 + time.hour * 3600 + time.day * 216000;
    func_00382348(D_0040EB30, 0x02B9D6F8);
    D_0040EB30[1] = value;
    D_0040EB30[0] = ~value;
    return ~value;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280c90", func_00280E00);
