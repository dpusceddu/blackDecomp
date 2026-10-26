#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00352A30();

s32 func_003485E8(u32 *arg0, u32 *arg1) {
    u32 temp_3;
    u32 temp_4;

    temp_4 = *arg0;
    temp_3 = *arg1;
    if (temp_3 >= temp_4) {
        return (temp_4 >= temp_3) ? 0 : -1;
    }
    return 1;
}

/* Partial views; the middle record fields and the full key type are UNVERIFIED. */
typedef struct Recovered_AnimationLookupRecord {
    u32 key;
    u32 unk_04[3];
    int value;
} Recovered_AnimationLookupRecord;
typedef struct Recovered_AnimationLookupKey {
    u32 key;
    u32 unknown[3];
} Recovered_AnimationLookupKey;

int func_00348610(u32* key, Recovered_AnimationLookupRecord* records, int count) {
    int result = -1;
    int lower = -1;
    int upper = count;
    if (upper != 0) {
        do {
            int middle = (lower + upper) >> 1;
            if (func_003485E8(&records[middle].key, key) < 0)
                lower = middle;
            else
                upper = middle;
        } while (lower + 1 != upper);
    }
    if (upper < count) {
        if (func_003485E8(&records[upper].key, key) == 0) result = upper;
    }
    return result;
}
int func_003486E0(int key, Recovered_AnimationLookupRecord* records, int count) {
    Recovered_AnimationLookupKey query;
    int found;
    query.key = key;
    query.unknown[0] = 0;
    query.unknown[1] = 0;
    query.unknown[2] = 0;
    found = func_00348610(&query.key, records, count);
    if (found != -1) return records[found].value;
    return -1;
}

void func_00348738(s32 arg0, Recovered_AnimationLookupRecord* arg1, s32 arg2) {
    func_003486E0(func_00352A30(), arg1, arg2);
}
