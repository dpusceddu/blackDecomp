#include "auto/prelude.h"

extern void * func_00135550(void *);
extern void func_001A7450(void **arg0);

void func_001A7498(void **arg0) {
    void *temp_3;

    temp_3 = func_00135550(*arg0);
    if ((*arg0 == NULL) || (temp_3 == NULL)) {
        func_001A7450(arg0);
    }
}
