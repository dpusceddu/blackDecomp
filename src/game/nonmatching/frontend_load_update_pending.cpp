// Unmatched: func_00106200: clock subobject addressing and flags/virtual-call scheduling.
#ifdef NONMATCHING
#include "game/frontend_resources.hpp"
extern char* D_0040F0E0;
extern char* D_0040F4D0;
extern char* D_0040F510;
extern void* D_0040F524;
extern long** D_0040F4BC;
extern "C" int func_00103870(void*);
extern "C" int func_001063F8(void*);
extern "C" void func_00105228(void*,int);
extern "C" void func_001052A0(void*,void*);
extern "C" void func_00205180(void*);
extern "C" void func_001E8980(int);
void FrontendLoadingState::Update() {
    if (!waiting) {
        long mode=0x6d6123044330fccfL;
        long* current=*D_0040F4BC;
        if(current) mode=*current;
        if(mode==0x594c3b3ed729e1c6L && !func_00103870(D_0040F0E0)) {
            elapsed+=*(float*)(D_0040F4D0+0x1c);
            func_001063F8(this);
        }
    } else {
        struct Clock { char reserved[0x1c]; float delta; };
        Clock* clock=(Clock*)((unsigned int)D_0040F0E0+0x20120);
        timeout-=clock->delta;
        if(timeout<0) {
            if(forced) func_00105228(D_0040F0E0+0x20220,5);
            else func_00105228(D_0040F0E0+0x20220,4);
        }
    }
    if(flags&2) func_001052A0(this,D_0040F0E0+0x2104c);
    else if(flags&1) func_001052A0(this,D_0040F0E0+0x2103c);
    else if(flags&4) {
        if(!request) func_001052A0(this,D_0040F0E0+0x21028);
        else {
            func_001052A0(this,D_0040F0E0+0x21058);
            flags=0;
            goto updateOwner;
        }
    }
    flags=0;
updateOwner:
    func_00205180(D_0040F524);
    func_001E8980(*(int*)(D_0040F510+0xcbd8));
    owner->virtualTable[2].function((char*)owner+owner->virtualTable[2].adjustment);
}

#endif
