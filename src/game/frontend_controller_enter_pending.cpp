// Unmatched: func_00107020: signed-byte loop induction and call scheduling.
#ifdef NONMATCHING
#include "game/frontend_resources.hpp"
extern "C" void func_0026C798(void*,int);
extern "C" void func_0026BA20(void*);
extern "C" void func_001246A0(void*,signed char);
extern "C" void func_0026C8D0(void*);
extern "C" void func_0026BFF0(void*);
extern "C" void func_00124708(void*);
extern "C" void func_0026BC50(float,void*);
extern "C" void func_001078F0(void*,int);
extern "C" void func_0020DCB0(void*);
extern "C" void func_0020DCF8(void*,const char*);
extern "C" void func_0020DEC8(void*,const char*);
extern char D_003F2EC0[],D_003F2EE0[];
int FrontendControllerScreen::Enter() {
    switch(state) {
    case 1: case 55:
        func_0026C798(this,0);
        for(signed char i=0;i<2;++i) {
            func_0026BA20(&samples[i]);
            func_001246A0(&channels[i],i);
        }
        state=2;
    case 2:
        func_0026C8D0(this);
        for(signed char i=0;i<2;++i) {
            func_0026BFF0(&samples[i]);
            func_00124708(&channels[i]);
            func_0026BC50(0.05f,&samples[i]);
        }
        for(signed char i=0;i<2;++i) {
            feedback[i]=1; feedback[i+1]=1; feedback[i+2]=1;
        }
        if(feedbackEnabled) func_001078F0(this,0);
        state=3;
    case 3:
        func_0020DCB0(textBox);
        func_0020DCF8(textBox,D_003F2EC0);
        func_0020DEC8(textBox,D_003F2EE0);
        state=28;
    case 28:
    default:
        return 1;
    }
}

#endif
