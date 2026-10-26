#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

extern void func_00170C90(PS2LiveCollision* collision);
extern void func_001718D0(PS2LiveCollision* collision, PS2GameObjectRecord* object, s32 index);

extern void * D_0040F4D0;
extern s32 func_0012A7C0(void *);
extern s32 func_0012AE58(void *);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_001756C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175750);
#ifdef NON_MATCHING
// Unmatched: loop branch and delay-slot scheduling differ.
s32 func_00175930(PS2CollisionQueue* queue) {
    PS2LiveCollision** current = queue->live;
    PS2LiveCollision* collision = *current;
    s32 remaining = 15;
    do {
        remaining--;
        current++;
        func_00170C90(collision);
        if (remaining < 0)
            break;
        collision = *current;
    } while (1);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175930);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175980);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175A00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175AB8);
#ifdef NON_MATCHING
// Unmatched: loop exit and success branch layout differ.
s32 func_00175B60(PS2CollisionQueue* queue, PS2GameObjectRecord* object) {
    PS2LiveCollision** current = queue->live;
    s32 index = 0;
loop:
    {
        PS2LiveCollision* collision = *current;
        index++;
        if (collision->object == object) {
            func_001718D0(collision, object, index);
            return 1;
        }
    }
    current++;
    if (index < 16)
        goto loop;
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175B60);
#endif
s32 func_00175BB0(PS2CollisionQueue* queue, PS2GameObjectRecord* object) {
    PS2LiveCollision** current = queue->live;
    s32 index = 0;
    do {
        PS2LiveCollision* collision = *current;
        if (collision->state == 4 && collision->object == object)
            return index;
        index++;
        current++;
    } while (index < 16);
    return -1;
}

s32 func_00175BF0(void *arg0, void *arg1) {
    s32 var_3;
    void *var_4;

    var_4 = arg0 + 0x44;
    var_3 = 0;
loop_1:
    if (M2C_FIELD(var_4, u8 *, -4) != 0) {
        goto block_3;
    }
    var_3 += 1;
    goto block_8;
block_3:
    if (M2C_FIELD(var_4, s32 *, 0) == arg1) {
        goto block_6;
    }
    var_3 += 1;
    goto block_8;
block_6:
    return var_3;
block_8:
    var_4 += 0xC;
    if (var_3 < 0x30) {
        goto loop_1;
    }
    return -1;
}

s32 func_00175C30(void *arg0) {
    s32 var_3;
    u8 *var_4;

    var_4 = arg0 + 0x40;
    var_3 = 0;
loop_1:
    if (*var_4 != 0) {
        var_3 += 1;
        var_4 += 0xC;
        if (var_3 >= 0x30) {
            return -1;
        }
        goto loop_1;
    }
    return var_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175C60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175DB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175E80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175EF8);

void func_00175F10(void *arg0, s32 arg1, s8 arg2) {
    M2C_FIELD(arg0, s8 *, 1) = arg2;
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
}

void func_00175F38(void) {

}

s32 func_00175F40(void) {
    return 1;
}

s32 func_00175F48(void) {
    return 1;
}

s32 func_00175F50(void) {
    return func_0012A7C0(D_0040F4D0) != 0;
}

s32 func_00175F78(void) {
    return func_0012AE58(D_0040F4D0) != 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175FA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00176258);
