#include "ps2/prelude.h"

extern s32 func_00193AC8();
extern s32 func_001A0C18();

void func_001A0D80(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 8);
    switch (temp_3) {                               /* irregular */
    case 0:
        func_00193AC8();
        return;
    case 1:
        func_001A0C18();
        break;
    }
}
