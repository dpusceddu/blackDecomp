#include "rwa_ee/bank.h"

extern RwaBank *func_00314488(RwaBank *, s32);

void *func_00313C90(RwaBank *bank, u32 size) {
    RwaBank copy = *func_00314488(bank, 0);
    void *data;

    copy.field34 = size;
    data = copy.driver->create(&copy);
    if (!data) return 0;
    bank->data = data;
    bank->data_size = copy.field34;
    return data;
}
