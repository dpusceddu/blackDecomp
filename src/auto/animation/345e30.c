#include "auto/prelude.h"

extern s32 func_00345C78();

void func_00345E30(s32 *arg0) {
    if (!(*arg0 & 0x480000)) {
        func_00345C78();
    }
}
