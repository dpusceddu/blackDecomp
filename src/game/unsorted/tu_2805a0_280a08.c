#include "ps2/prelude.h"

typedef struct {
    u8 unk_00[0x34];
    u8 unk_34;
} Recovered_AudioResource;

typedef struct {
    Recovered_AudioResource* resource;
    u32 age;
    u8 active;
    u8 unk_09[3];
} Recovered_AudioPoolEntry;

typedef struct {
    Recovered_AudioPoolEntry entries[48];
    s32 count;
} Recovered_AudioPool; /* Resource and flag meanings UNVERIFIED. */

void func_00280A08(Recovered_AudioPool* pool) {
    Recovered_AudioPoolEntry* entry = pool->entries;
    Recovered_AudioPoolEntry* end = entry + 48;
    do {
        entry->resource = NULL;
        entry->active = 0;
        entry++;
    } while ((s32)entry < (s32)end);
    pool->count = 0;
}
