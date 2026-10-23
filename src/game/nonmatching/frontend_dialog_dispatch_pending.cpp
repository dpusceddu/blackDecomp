// Unmatched: global clock address construction and switch register allocation.
#if 0
#include "game/frontend/save_dialog.hpp"
extern "C" unsigned char func_0010B610(FrontendSaveDialog*);
extern "C" void func_0010C398(FrontendSaveDialog*);
extern "C" void func_0010E0F0(FrontendSaveDialog*);
extern "C" void func_0010CF18(FrontendSaveDialog*);
extern "C" void func_0010E720(FrontendSaveDialog*);
extern "C" void func_0010C8E8(FrontendSaveDialog*);
extern "C" void func_0010D9F0(FrontendSaveDialog*);
extern "C" void func_0010E498(FrontendSaveDialog*);
extern "C" void func_0010E5F0(FrontendSaveDialog*);
extern "C" void func_0010E740(FrontendSaveDialog*);
extern "C" void func_0010EBD0(FrontendSaveDialog*);
struct FrontendClock {char reserved[0x20];float now;};
extern "C" int D_0040F0E0;
void FrontendSaveDialog::UpdateOperation() {
    if (mode && phase != 1 && !func_0010B610(this)) {
        float now=((FrontendClock*)(D_0040F0E0+0x20120))->now;
        float delta=now-previousTime;
        previousTime=now;
        timeout-=delta;
        if(timeout<0.0f) timeout=0.0f;
        switch(mode) {
        case 1:func_0010C398(this);break;
        case 2:func_0010E0F0(this);break;
        case 3:func_0010CF18(this);break;
        case 9:func_0010E720(this);break;
        case 4:func_0010C8E8(this);break;
        case 5:func_0010D9F0(this);break;
        case 6:func_0010E498(this);break;
        case 7:func_0010E5F0(this);break;
        case 8:func_0010E740(this);break;
        }
        func_0010EBD0(this);
    }
}
#endif
