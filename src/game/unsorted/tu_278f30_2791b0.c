#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00278F30(s32);
extern void func_00278F40(void *);

typedef struct {
    u32 unk_00;
    s32 type;
    void *data;
} Recovered_TextAssetEntry;

typedef struct {
    Recovered_TextAssetEntry *entries;
    s16 count;
} Recovered_TextAssetList; /* Fields UNVERIFIED. */

void func_002791B0(void *data) {

}

void func_002791B8(Recovered_TextAssetEntry *entry) {
    switch (entry->type) {
    case 0:
        entry->data = (void *)((u32)entry->data + (u32)entry);
        func_00278F30((s32)entry->data);
        break;
    case 1:
        entry->data = (void *)((u32)entry->data + (u32)entry);
        func_00278F40(entry->data);
        break;
    case 2:
        entry->data = (void *)((u32)entry->data + (u32)entry);
        func_002791B0(entry->data);
        break;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_278f30_2791b0", func_00279248);
void func_00279250(Recovered_TextAssetList *list) {
    s32 index = 0;
    list->entries = (Recovered_TextAssetEntry *)((u32)list->entries + (u32)list);
    while (index < list->count) {
        func_002791B8(&list->entries[index]);
        index++;
    }
}
