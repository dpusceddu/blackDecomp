#include "auto/prelude.h"

f32 func_0013EE68(void *arg0) {
    f32 var_f3;

    var_f3 = M2C_FIELD(arg0, f32 *, 0) - M2C_FIELD(arg0, f32 *, 4);
    if (var_f3 < -180.0f) {
        var_f3 += 360.0f;
    } else if (var_f3 > 180.0f) {
        var_f3 -= 360.0f;
    }
    if (M2C_FIELD(arg0, f32 *, 0x74) > 0.01f) {
        var_f3 -= 5.0f;
    }
    return var_f3;
}
