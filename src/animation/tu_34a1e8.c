#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00352958(void*, float, float, float);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34a1e8", func_0034A1E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34a1e8", func_0034A3C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34a1e8", func_0034A598);
#ifdef NON_MATCHING
/* Return-value meaning and complete vector type are UNVERIFIED. */
typedef struct {
    float x, y, z;
} Recovered_AnimationVector3;
// Unmatched: input/output pointer and register allocation differ.
int func_0034A770(int source, int destination, int first, int end) {
    int adjusted = -12;
    int offset, count;
    Recovered_AnimationVector3 *input, *output;
    if (first < end) {
        offset = first * 12;
        count = end - first;
        adjusted = first * -12 + source;
        input = (Recovered_AnimationVector3*)(offset + adjusted);
        output = (Recovered_AnimationVector3*)(offset + destination);
        do {
            --count;
            output->x = input->x;
            output->y = input->y;
            output->z = input->z;
            ++input;
            ++output;
        } while (count != 0);
    }
    return adjusted;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34a1e8", func_0034A770);
#endif

#include "ps2/recovered_types.h"
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

/* Convert packed turns to negative radians for the rotation helper. */
void func_0034AC70(const unsigned short* values, char* output, int count) {
    if (count > 0) {
        int remaining = count;
        do {
            float y = -((float)values[1] * 6.2831855f) * 0.0000152587890625f;
            float z = -((float)values[2] * 6.2831855f) * 0.0000152587890625f;
            float x = -((float)values[0] * 6.2831855f) * 0.0000152587890625f;
            func_00352958(output, y, z, x);
            values += 3;
            output += 16;
            --remaining;
        } while (remaining != 0);
    }
}
void func_0034AD48(const unsigned short* data, void* output, int index) {
    const unsigned short* values = data + index * 3;
    float y = -((float)values[1] * 6.2831855f) * 0.0000152587890625f;
    float z = -((float)values[2] * 6.2831855f) * 0.0000152587890625f;
    float x = -((float)values[0] * 6.2831855f) * 0.0000152587890625f;
    func_00352958(output, y, z, x);
}
void func_0034ADD8(const unsigned short* values, void* output) {
    float y = -((float)values[1] * 6.2831855f) * 0.0000152587890625f;
    float z = -((float)values[2] * 6.2831855f) * 0.0000152587890625f;
    float x = -((float)values[0] * 6.2831855f) * 0.0000152587890625f;
    func_00352958(output, y, z, x);
}
