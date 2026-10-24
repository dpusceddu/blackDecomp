#include "include_asm.h"

// Inferred PS2 frontend layout and behavior.
extern "C" int func_00129DE8(void*);
extern "C" int func_001E8900(int);
extern "C" void func_0020B0C0(void*);
extern void* D_0040F4D0;
extern char* D_0040F510;
extern void* D_0040F544;
extern unsigned char* D_0040F504;
struct FrontendLoadExit {
    int state;
    int Step() __asm__("func_001065D0");
};

int FrontendLoadExit::Step() {
    switch(state) {
    case 2: case 3: case 4: case 28:
        state=29;
    case 29:
        if (!func_00129DE8(D_0040F4D0)) break;
        *D_0040F504=1;
        state=30;
    case 30:
        if (!func_001E8900(*(int*)(D_0040F510+0xcbd8))) break;
        state=32;
    case 32:
        func_0020B0C0(D_0040F544);
        state=55;
    case 1: case 55:
    default:
        return 1;
    }
    return 0;
}
