#include "include_asm.h"
#include "ps2/prelude.h"
#include "kynapse/name_registries.h"

extern Recovered_NamedClassRegistry* func_003935D8(void);
extern Recovered_NamedValueRegistry* func_00393650(void);
extern Recovered_NamedValueRegistry* func_003936C8(void);
extern Recovered_NamedValueRegistry* func_00393740(void);
extern Recovered_NamedValueRegistry* func_003937B8(void);
extern s32 strcmp(const char*, const char*);

#ifdef NON_MATCHING
// Unmatched: loop-entry scheduling differs.
Recovered_NamedClassRecord* func_00393978(const char* name) {
    Recovered_NamedClassRegistry* registry;
    Recovered_NamedClassRecord** cursor;
    Recovered_NamedClassRecord** resultSlot;
    s32 i;
    if (!name) { return NULL; }
    registry = func_003935D8();
    cursor = registry->slots;
    resultSlot = registry->slots;
    for (i = 0; i < registry->count; ++i, ++cursor, ++resultSlot) {
        if (strcmp((*cursor)->name, name) == 0) { return *resultSlot; }
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/inline/linkonce_393978", func_00393978);
#endif

#ifdef NON_MATCHING
static inline void* FindNamedValue(Recovered_NamedValueRegistry* registry, const char* name) {
    s32 available = registry->count;
    s32 i = 0;
    if (available > 0) {
        Recovered_NamedValueRecord** cursor = registry->slots;
        char first = *name;
        s64 count = available;
        do {
            s32 offset = 0;
            Recovered_NamedValueRecord* record = *cursor;
            const char* recordName = record->name;
            if (recordName[offset] == first) {
                const char* current = name;
                do {
                    if (*current == 0) { return registry->slots[i]->value; }
                    ++offset;
                    ++current;
                } while (recordName[offset] == *current);
            }
            ++i;
            ++cursor;
        } while (i < count);
    }
    return NULL;
}

#endif

#ifdef NON_MATCHING
// Unmatched: slot-cursor capture and returned-record register selection differ.
void* func_00393A18(const char* name) { return FindNamedValue(func_00393650(), name); }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/inline/linkonce_393978", func_00393A18);
#endif
#ifdef NON_MATCHING
// Unmatched: slot-cursor capture and returned-record register selection differ.
void* func_00393AC0(const char* name) { return FindNamedValue(func_003936C8(), name); }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/inline/linkonce_393978", func_00393AC0);
#endif
#ifdef NON_MATCHING
// Unmatched: slot-cursor capture and returned-record register selection differ.
void* func_00393B68(const char* name) { return FindNamedValue(func_00393740(), name); }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/inline/linkonce_393978", func_00393B68);
#endif
#ifdef NON_MATCHING
// Unmatched: slot-cursor capture and returned-record register selection differ.
void* func_00393C10(const char* name) { return FindNamedValue(func_003937B8(), name); }
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/inline/linkonce_393978", func_00393C10);
#endif
