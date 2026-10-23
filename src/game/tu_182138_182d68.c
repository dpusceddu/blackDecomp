#include "auto/prelude.h"

extern s32 func_00192EB0(void *);
extern s32 func_00193608(void *);

void func_00182D68(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x40);
    switch (temp_3) {                               /* irregular */
    case 1:
        func_00192EB0(arg0 + 0x60);
        return;
    case 2:
        func_00193608(arg0 + 0x1F0);
        break;
    }
}
