#include "ps2/prelude.h"

extern s16 *D_003BD270;

void func_001D3EA0(void) {
    s16 *out = D_003BD270;
    s16 row, col;
    for (row = 0; row < 8; row++) {
        float y = (float)row * 0.125f;
        s16 y0 = (s16)(y * 4096.0f);
        s16 y1 = (s16)((y + 0.125f) * 4096.0f);
        for (col = 0; col < 4; col++) {
            float x = (float)col * 0.25f;
            s16 x0 = (s16)(x * 4096.0f);
            s16 x1 = (s16)((x + 0.25f) * 4096.0f);
            *out++ = x0;
            *out++ = y0;
            *out++ = x0;
            *out++ = y1;
            *out++ = x1;
            *out++ = y0;
            *out++ = x1;
            *out++ = y1;
        }
    }
}
