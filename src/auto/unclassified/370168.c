#include "auto/prelude.h"

extern M2C_UNK D_0040BF00;
extern M2C_UNK D_0040BF18;

void func_00370168(void *arg0, void *arg1, void *arg2) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, void **, 8) = arg2;
        M2C_FIELD(arg0, void **, 0) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = &D_0040BF00;
    }
}

void func_00370188(void *arg0, void *arg1) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, void **, 0) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = &D_0040BF18;
    }
}
