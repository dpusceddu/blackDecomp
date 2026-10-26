#include "include_asm.h"
#include "ps2/prelude.h"

// UNVERIFIED: fields retain offsets until their roles are established.
typedef struct {
    u32 unk_00;
    s32 unk_04;
    u32 unk_08;
    s32 unk_0C;
    u8 unk_10[0xFE0];
    char name[0x3C];
    u8 unk_102C;
    u8 unk_102D;
    u8 unk_102E;
    u8 unk_102F[0x11];
} Recovered_SoundLoadSlot;

typedef struct {
    Recovered_SoundLoadSlot slots[11];
    u32 unk_B2C0;
    u32 count;
    s32 unk_B2C8;
} Recovered_SoundLoadPool;

typedef struct {
    s32 unk_00;
    s32 unk_04;
} Recovered_SoundLoadSizes;

extern s32 _stricmp(const char* left, const char* right);
extern void* func_0027FCF8(Recovered_SoundLoadSlot* slot, void* arg, s32 size);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_0027FCF8);

s32 func_0027FE68(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_0027FE70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_0027FF00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_0027FF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_0027FF78);

s32 func_00280100(s32 arg0, void *arg1)
{
  s32 temp_2;
  void *temp_3;
  temp_2 = M2C_FIELD(arg1, s32 *, 0x1024);
  if (temp_2 == 0)
  {
    temp_3 = *((void **) (((s8 *) arg1) + 0x1030));
    (*((M2C_UNK (**)(void *)) (((s8 *) temp_3) + 0x24)))(arg1 + (M2C_FIELD(temp_3, s16 *, 0x20)));
    M2C_FIELD(arg1, s8 *, 0x102E) = (M2C_FIELD(arg1, s8 *, 0x102D) = 0);
  }
  else
  {
    M2C_FIELD(arg1, s32 *, 0x1024) = (s32) (temp_2 - 1);
  }
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_00280158);
#ifdef NON_MATCHING
// Unmatched: slot and name cursor register lifetimes differ.
Recovered_SoundLoadSlot* func_00280160(Recovered_SoundLoadPool* pool, const char* name) {
    u32 index = 0;
    if (pool->count != 0) {
        Recovered_SoundLoadSlot* slot = pool->slots;
        do {
            if (slot->unk_102D && _stricmp(slot->name, name) == 0)
                return slot;
            index++;
            slot++;
        } while (index < pool->count);
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_00280160);
#endif
#ifdef NON_MATCHING
// Unmatched: slot and count-base initialization order differs.
void* func_00280200(Recovered_SoundLoadPool* pool, void* arg, s32 size) {
    u32 index = 0;
    if (pool->count != 0) {
        Recovered_SoundLoadSlot* slot = pool->slots;
        do {
            if (slot->unk_102D && slot->unk_102C) {
                void* result = func_0027FCF8(slot, arg, size);
                if (result != NULL)
                    return result;
            }
            index++;
            slot++;
        } while (index < pool->count);
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_00280200);
#endif
Recovered_SoundLoadSlot* func_002802A8(Recovered_SoundLoadPool* pool, const Recovered_SoundLoadSizes* sizes) {
    Recovered_SoundLoadSlot* slot = pool->slots;
    u32 index = 0;
    if (pool->count != 0) {
        do {
            if (!slot->unk_102D && (!sizes || (slot->unk_04 == sizes->unk_00 && slot->unk_0C == sizes->unk_04))) {
                slot->unk_102D = 1;
                return slot;
            }
            index++;
            slot++;
        } while (index < pool->count);
    }
    return NULL;
}

void func_00280320(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x102D) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_00280328);
