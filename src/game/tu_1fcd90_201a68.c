#include "auto/prelude.h"

f32 func_00201A68(f32 fparg0) {
    if (fparg0 < 0.5f) {
        return 2.0f * fparg0;
    }
    if (fparg0 >= 4.0f) {
        return 1.0f - (2.0f * (fparg0 - 4.0f));
    }
    return 1.0f;
}
