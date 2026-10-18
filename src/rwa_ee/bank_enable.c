#include "rwa_ee/bank.h"

extern void func_00315EE8(RwaBank *, s32);

RwaBank *func_00313F50(RwaBank *bank, s32 argument) {
    bank->driver->enable(bank, argument, 1);
    func_00315EE8(bank, 1);
    return bank;
}
