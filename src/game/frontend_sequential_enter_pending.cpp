// Unmatched: func_00106868: switch exit layout and virtual-call scheduling.
#ifdef NONMATCHING
#include "game/frontend_resources.hpp"
extern char* D_0040F0E0;
extern char* D_0040F544;
extern char* D_0040F4D0;
extern unsigned char* D_0040F504;
extern void** D_0040F4DC;
extern char* D_003BC51C;
extern "C" int func_00128480(void*);
extern "C" int func_0020AD10(void*);
extern "C" void func_00121C38(void*);
extern "C" void func_00122478(void*);
extern "C" void func_00382BD8(void*);
extern "C" void func_00153438(void*);
extern "C" void func_001052A0(void*,void*);
extern "C" void* func_001033A0(void*,unsigned char,unsigned char);
extern "C" void func_0020B678(void*,const char*,int);
int FrontendSequentialLoadingState::Enter() {
    if(state==28) virtualTable[4].function((char*)this+virtualTable[4].adjustment);
    *(int*)(D_0040F0E0+0x20208)=1;
    switch(state) {
    case 1: case 55:
        state=2;
    case 2: case 28:
        *(unsigned char*)(D_0040F544+0x390f)=1;
        state=3;
    case 3:
        if (func_00128480(D_0040F4D0)) {
        state=4;
    case 4:
        if (func_0020AD10(D_0040F544)) {
        state=5;
    case 5:
        *D_0040F504=0;
        { void** models=D_0040F4DC;
          func_00121C38(*models);
          func_00122478(models);
          func_00382BD8(models); }
        func_001052A0(this,D_0040F0E0+0x21028);
        flags=0;
        func_00153438(counter);
        specification=func_001033A0(D_0040F0E0,*(unsigned char*)(D_0040F0E0+0x2020c),*(unsigned char*)(D_0040F0E0+0x2020e));
        timeout=3.0f;
        waiting=0;
        forced=0;
        elapsed=0;
        state=28;
        return 1;
        }
        }
        return 0;
    default:
        return 1;
    }
    return 0;
}

#endif
