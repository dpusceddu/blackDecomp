// Unmatched: timer address construction, unsigned conversion and state scheduling.
#if 0
#include "ps2/prelude.h"
#include "game/frontend/movie_stream.hpp"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern "C" u8 func_00272308(void *);
extern "C" void func_001094C0(void *,const char*,s32,s32);
extern "C" s32 func_00109CF8(void *);
extern "C" s32 func_00109BB0(void *);
extern "C" s32 func_00109588(void *);
extern "C" s32 D_003BD1F0;
extern "C" s32 func_002722C8(void *, f32);
extern "C" char* D_0040F0E0;
extern "C" s32 func_00271F10(void *);

void FrontendMovieState::Update() {
    f32 var_f0;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_3;
    s32 temp_3_2;
    s32 temp_7;
    u32 var_2;

    temp_2 = state;
    var_2 = temp_2 - 0x1D;
    if (temp_2 == 0x1C) {
        if (stopRequested == 0) {
            if (func_00272308(decoder) != 0) {
                temp_7 = flags;
                if (temp_7 & 1) {
                    func_001094C0(this, name, fade, temp_7);
                } else {
                    goto block_6;
                }
            }
        } else {
block_6:
            stopRequested = 0U;
            state = 0x1D;
        }
        var_2 = state - 0x1D;
    }
    if (var_2 < 0x1AU) {
        func_00109CF8(this);
    }
    temp_3 = state;
    if (((temp_3 == 0x37) || (temp_3 == 1)) && (requested != 0)) {
        temp_3_2 = pendingFade;
        state = 2;
        requested = 0U;
        fade = temp_3_2;
        pendingFade = 0;
        if (temp_3_2 != 0) {
            flags = (s32) (flags | 2);
        }
    }
    if ((u32) (state - 2) < 0x1AU) {
        func_00109BB0(this);
    }
    if (state == 0x1C) {
        if (!(flags & 0x100)) {
            if (active == 0) {
                func_00109588(this);
                startedAt = (s32) D_003BD1F0;
                goto block_21;
            }
            goto block_22;
        }
block_21:
        if (active != 0) {
block_22:
            if (fade != 0) {
                var_f0 = (f32)((u32)D_003BD1F0-startedAt);
                func_002722C8(decoder, var_f0 * (M2C_FIELD((D_0040F0E0 + 0x20120), f32 *, 0x1C) * 0.5f));
            }
            func_00271F10(decoder);
        }
    }
}
#endif
