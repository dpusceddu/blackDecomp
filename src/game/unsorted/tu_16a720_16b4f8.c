#include "ps2/prelude.h"
extern void func_001D4630(s128, f32, f32);
extern void func_001D4858(void);
extern u8 D_0040D9B3;
extern void func_001D4A50(s32, f32);
extern void func_001D4998(void);

void func_0016B4F8(void* unused, s128 value) {
    func_001D4630(value, 0.0f, 0.0f);
    func_001D4858();
    if (D_0040D9B3 != 0) {
        func_001D4A50(3, 0.0f);
        func_001D4A50(4, 0.0f);
        func_001D4A50(5, 0.0f);
    } else {
        func_001D4A50(0, 0.0f);
        func_001D4A50(1, 0.0f);
        func_001D4A50(2, 0.0f);
    }
    func_001D4998();
}
