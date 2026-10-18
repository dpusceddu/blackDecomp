#include "auto/prelude.h"

extern s32 (*D_004494D4)();

s32 func_002A9108(s32 arg0) {
    return (D_004494D4() == 0) ? 0 : arg0;
}
