#include "include_asm.h"

struct Vec3Value {
    float x, y, z;
};

extern "C" {
extern Vec3Value D_004514F8;
extern Vec3Value D_00451508;
Vec3Value D_00451518 __attribute__((aligned(8)));
extern Vec3Value D_00451528;

void func_002EA2F8(int phase, int priority) {
    if (priority == 65535 && phase != 0) {
        D_004514F8.x = 0.0f;
        D_004514F8.y = 0.0f;
        D_004514F8.z = 0.0f;
        D_00451508.x = 0.0f;
        D_00451508.y = 0.0f;
        D_00451508.z = 1.0f;
        D_00451518.x = 1.0f;
        D_00451518.y = 0.0f;
        D_00451518.z = 0.0f;
        D_00451528.x = 0.0f;
        D_00451528.y = 1.0f;
        D_00451528.z = 0.0f;
    }
}

void func_002EA368() {
    func_002EA2F8(1, 65535);
}
}
