#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/vu0_lowering.h"
/* Recovered_Action: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Action {
    void * unk_0;
    u8 unk_4[4];
    u8 unk_8;
} Recovered_Action;

/* Recovered_Vtable_003DE8A0: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003DE8A0 {
    void * unk_0;
} Recovered_Vtable_003DE8A0;


#include "ps2/recovered_types.h"
extern void * D_0040F4D0;
extern void func_00193990(Recovered_Action *, u8);

void func_0019D6B8(Recovered_Vtable_003DE8A0 *arg0) {
    s128 temp_vf1;
    s128 temp_vf1_2;
    s128 temp_vf1_3;

    temp_vf1 = M2C_FIELD(M2C_FIELD(arg0->unk_0, void **, 0x7C), s128 *, 0xA0);
    temp_vf1_2 = __ee_vu_sub_keep(temp_vf1, temp_vf1, (s128) M2C_FIELD(D_0040F4D0, s128 *, 0xD0));
    temp_vf1_3 = __ee_vu_mul_keep(temp_vf1_2, temp_vf1_2, temp_vf1_2);
    if (__ee_vu_read_x(__ee_vu_sum_keep(temp_vf1_3, temp_vf1_3, __ee_vu_one())) > 100.0f) {
        func_00193990((Recovered_Action *) arg0, 1U);
    }
}
