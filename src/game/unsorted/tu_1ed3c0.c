#include "include_asm.h"
#include "game/timed_value_pool.h"

s32 func_001ED3C0(Recovered_TimedValuePool* self, Recovered_TimedValueAction** actions, u32 count, u32 value) {
    TimedValuePool_SetActions(self, actions, (u16)count, value);
    return 1;
}
