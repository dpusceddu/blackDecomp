#include "ps2/prelude.h"

/* Observed two-word generator: the intermediate state store precedes the accumulator read.
 * The original pool, slot-table and generator class identities remain UNVERIFIED. */
class ControllerRandom {
public:
    u32 state;
    u32 accumulator;
    inline u32 Next() {
        state = (state << 16) + ((s32)state >> 16);
        state += accumulator;
        accumulator += state;
        return state;
    }
    inline f32 Fraction() { return (f32)Next() * 2.3283064365386963e-10f; }
};

typedef struct {
    u8 unknown00[0xC];
    void* slots[3];
    u8 unknown18;
    u8 selected;
} ControllerSelectionSlots;

extern "C" {
extern s32 func_00156F00(void*);
extern s32 func_001580C0(void*);
extern void* func_00135550(void*);
extern s32 func_00185C58(void*);
}

static inline bool HasWeapon(void* actor) {
    ControllerSelectionSlots* slots = M2C_FIELD(actor, ControllerSelectionSlots**, 0x25C);
    if (!slots->slots[slots->selected]) return false;
    if (!M2C_FIELD(actor, void**, 0x2A4)) return false;
    return true;
}

extern "C" s32 func_0011D200(void* pool, void* actor) {
    if (M2C_FIELD(pool, void**, 4)) return 0;
    if (!HasWeapon(actor)) return 0;
    if (func_00156F00(M2C_FIELD(actor, void**, 0x2A4))) return 0;
    if (func_001580C0(M2C_FIELD(actor, void**, 0x2A4))) return 0;
    if (M2C_FIELD(func_00135550(actor), s32*, 0x80) == 1 && func_00185C58((u8*)func_00135550(actor) + 0x6F0)) return 0;
    ControllerRandom* random = (ControllerRandom*)((u8*)pool + 0x10);
    return random->Fraction() <= 0.1f;
}
