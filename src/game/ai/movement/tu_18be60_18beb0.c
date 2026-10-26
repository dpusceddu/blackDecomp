#include "include_asm.h"
#include "ps2/prelude.h"

/* Serialization prepends the event kind to a copy of the complete object.
 * The 24-byte and 8-byte variants retain their distinct payload sizes. */
typedef struct {
    s32 kind;
    u8 unk_04[20];
} Recovered_MovementEvent24;

typedef struct {
    s32 kind;
    s32 unk_04;
} Recovered_MovementEvent8;

typedef struct {
    s32 kind;
    Recovered_MovementEvent24 payload;
} Recovered_MovementEvent24Output;

typedef struct {
    s32 kind;
    Recovered_MovementEvent8 payload;
} Recovered_MovementEvent8Output;

typedef char MovementEvent24Size[sizeof(Recovered_MovementEvent24) == 24 ? 1 : -1];
typedef char MovementEvent8Size[sizeof(Recovered_MovementEvent8) == 8 ? 1 : -1];

extern s32 func_0018BE88();

s32 func_0018BEB0(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_0018BE88(arg0, 0x13);
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    return temp_v0;
}

s32 func_0018BEE8(const Recovered_MovementEvent24* event, Recovered_MovementEvent24Output* output) {
    output->payload = *event;
    output->kind = event->kind;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18be60_18beb0", func_0018BF28);

s32 func_0018BFA8(const Recovered_MovementEvent24* event, Recovered_MovementEvent24Output* output) {
    output->payload = *event;
    output->kind = event->kind;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18be60_18beb0", func_0018BFE8);

s32 func_0018C068(const Recovered_MovementEvent8* event, Recovered_MovementEvent8Output* output) {
    output->payload = *event;
    output->kind = event->kind;
    return 1;
}
