#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0034B128(void *, void *, s32, s32, s32, void *);
extern s32 func_0034AEA0(void *, void *, s32, s32, s32, void *);
extern s32 func_0034A1E8(void *, s32, s32, s32, s32, s32);
extern s32 func_0034A3C0(void *, s32, s32, s32, s32, s32);
extern s32 func_0034A770(s32, s32, s32, s32);
extern s32 func_0034A598(void *, s32, s32, s32, s32, s32);

s32 func_0034A7C8(void *arg0, s32 arg1, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s16 temp_7;
    s16 temp_8;
    s16 temp_8_2;
    s16 temp_8_3;

    if (M2C_FIELD(arg0, s16 *, 0x2E) != 0) {
        func_0034B128(M2C_FIELD(arg0, s32 *, 0xAC) + (M2C_FIELD(arg0, s16 *, 0x5A) * arg1), arg2, 0, M2C_FIELD(arg0, s32 *, 0x4C), M2C_FIELD(arg0, s32 *, 0xCC), M2C_FIELD(arg0, void **, 0xA8));
    }
    if (M2C_FIELD(arg0, s16 *, 0xA) != 0) {
        func_0034AEA0(M2C_FIELD(arg0, s32 *, 0xA0) + (M2C_FIELD(arg0, s16 *, 0x58) * arg1 * 2), arg3, 0, M2C_FIELD(arg0, s32 *, 0x50), M2C_FIELD(arg0, s32 *, 0xD0), M2C_FIELD(arg0, void **, 0xA4));
    }
    temp_8 = M2C_FIELD(arg0, s16 *, 0x76);
    if (temp_8 != 0) {
        func_0034A1E8(M2C_FIELD(arg0, s32 *, 0xC0) + (M2C_FIELD(arg0, s16 *, 0x7A) * arg1), arg4, M2C_FIELD(arg0, s32 *, 0xC8), 0, (s32) temp_8, M2C_FIELD(arg0, s32 *, 0xD4));
    }
    temp_8_2 = M2C_FIELD(arg0, s16 *, 0x74);
    if (temp_8_2 != 0) {
        func_0034A3C0(M2C_FIELD(arg0, s32 *, 0xBC) + (M2C_FIELD(arg0, s16 *, 0x78) * arg1 * 2), arg5, M2C_FIELD(arg0, s32 *, 0xC4), 0, (s32) temp_8_2, M2C_FIELD(arg0, s32 *, 0xD8));
    }
    temp_7 = M2C_FIELD(arg0, s16 *, 0x72);
    if (temp_7 != 0) {
        func_0034A770(M2C_FIELD(arg0, s32 *, 0xB4) + (temp_7 * arg1 * 0xC), arg6, 0, (s32) temp_7);
    }
    temp_8_3 = M2C_FIELD(arg0, s16 *, 0x8A);
    if (temp_8_3 != 0) {
        func_0034A598(M2C_FIELD(arg0, s32 *, 0xE0) + (M2C_FIELD(arg0, u8 *, 0x89) * arg1 * 2), arg7, M2C_FIELD(arg0, s32 *, 0xE4), 0, (s32) temp_8_3, M2C_FIELD(arg0, s32 *, 0xE8));
    }
    return 1;
}

s32 func_0034A950(void *arg0, s32 arg1, void *arg2, s32 arg3, void *arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, s32 arg_sp8, s32 arg_sp10, s32 arg_sp18, s32 arg_sp20, s32 arg_sp28) {
    s16 temp_4;

    if (arg3 < M2C_FIELD(arg0, s16 *, 0x2E)) {
        func_0034B128(M2C_FIELD(arg0, s32 *, 0xAC) + (M2C_FIELD(arg0, s16 *, 0x5A) * arg1), arg2, arg3, arg3 + 1, M2C_FIELD(arg0, s32 *, 0xCC), M2C_FIELD(arg0, void **, 0xA8));
    }
    if (arg5 < M2C_FIELD(arg0, s16 *, 0xA)) {
        func_0034AEA0(M2C_FIELD(arg0, s32 *, 0xA0) + (M2C_FIELD(arg0, s16 *, 0x58) * arg1 * 2), arg4, arg5, arg5 + 1, M2C_FIELD(arg0, s32 *, 0xD0), M2C_FIELD(arg0, void **, 0xA4));
    }
    if (arg7 < M2C_FIELD(arg0, s16 *, 0x76)) {
        func_0034A1E8(M2C_FIELD(arg0, s32 *, 0xC0) + (M2C_FIELD(arg0, s16 *, 0x7A) * arg1), arg6, M2C_FIELD(arg0, s32 *, 0xC8), arg7, arg7 + 1, M2C_FIELD(arg0, s32 *, 0xD4));
    }
    if (arg_sp8 < M2C_FIELD(arg0, s16 *, 0x74)) {
        func_0034A3C0(M2C_FIELD(arg0, s32 *, 0xBC) + (M2C_FIELD(arg0, s16 *, 0x78) * arg1 * 2), arg_sp0, M2C_FIELD(arg0, s32 *, 0xC4), arg_sp8, arg_sp8 + 1, M2C_FIELD(arg0, s32 *, 0xD8));
    }
    temp_4 = M2C_FIELD(arg0, s16 *, 0x72);
    if (arg_sp18 < temp_4) {
        func_0034A770(M2C_FIELD(arg0, s32 *, 0xB4) + (temp_4 * arg1 * 0xC), arg_sp10, arg_sp18, arg_sp18 + 1);
    }
    if (arg_sp28 < M2C_FIELD(arg0, s16 *, 0x8A)) {
        func_0034A598(M2C_FIELD(arg0, s32 *, 0xE0) + (M2C_FIELD(arg0, u8 *, 0x89) * arg1 * 2), arg_sp20, M2C_FIELD(arg0, s32 *, 0xE4), arg_sp28, arg_sp28 + 1, M2C_FIELD(arg0, s32 *, 0xE8));
    }
    return 1;
}

s32 func_0034AB18(void *arg0, s32 arg1, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6) {
    s16 temp_4;

    if (M2C_FIELD(arg0, s16 *, 0x2E) != 0) {
        func_0034B128(M2C_FIELD(arg0, s32 *, 0xAC) + (M2C_FIELD(arg0, s16 *, 0x5A) * arg1), arg2, 0, 1, M2C_FIELD(arg0, s32 *, 0xCC), M2C_FIELD(arg0, void **, 0xA8));
    }
    if (M2C_FIELD(arg0, s16 *, 0xA) != 0) {
        func_0034AEA0(M2C_FIELD(arg0, s32 *, 0xA0) + (M2C_FIELD(arg0, s16 *, 0x58) * arg1 * 2), arg3, 0, 1, M2C_FIELD(arg0, s32 *, 0xD0), M2C_FIELD(arg0, void **, 0xA4));
    }
    if (M2C_FIELD(arg0, s16 *, 0x76) != 0) {
        func_0034A1E8(M2C_FIELD(arg0, s32 *, 0xC0) + (M2C_FIELD(arg0, s16 *, 0x7A) * arg1), arg4, M2C_FIELD(arg0, s32 *, 0xC8), 0, 1, M2C_FIELD(arg0, s32 *, 0xD4));
    }
    if (M2C_FIELD(arg0, s16 *, 0x74) != 0) {
        func_0034A3C0(M2C_FIELD(arg0, s32 *, 0xBC) + (M2C_FIELD(arg0, s16 *, 0x78) * arg1 * 2), arg5, M2C_FIELD(arg0, s32 *, 0xC4), 0, 1, M2C_FIELD(arg0, s32 *, 0xD8));
    }
    temp_4 = M2C_FIELD(arg0, s16 *, 0x72);
    if (temp_4 != 0) {
        func_0034A770(M2C_FIELD(arg0, s32 *, 0xB4) + (temp_4 * arg1 * 0xC), arg6, 0, 1);
    }
    return 1;
}
