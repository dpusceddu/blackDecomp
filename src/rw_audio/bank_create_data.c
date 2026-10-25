#include "include_asm.h"

#include "rw_audio/sound.h"

extern RwaSound *func_00314488(RwaBank *, s32);

void *func_00313C90(RwaBank *bank, u32 size) {
    RwaSound copy = *func_00314488(bank, 0);
    void *data;

    copy.output_format.extent = size;
    data = copy.driver->create(&copy);
    if (!data) return 0;
    bank->data = data;
    bank->data_size = copy.output_format.extent;
    return data;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/bank_create_data", func_00313DC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/bank_create_data", func_00313F00);
