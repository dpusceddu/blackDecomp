// Unmatched: func_00107228: controller-state branch layout and register allocation.
#ifdef NONMATCHING
#include "game/frontend_resources.hpp"
extern char* D_0040F0E0;
extern char* D_0040F544;
extern "C" void func_0026C8E0();
extern "C" int func_0026BC80(void*);
extern "C" int func_0026C9C0(void*,signed char);
extern "C" void func_0026CA98(void*,void*,signed char);
extern "C" void func_0026CB38(void*,void*,int);
extern "C" int func_00103860();
extern "C" void func_00103800(void*,int);
extern "C" void func_00124728(void*);
extern "C" void func_00124730(void*);
extern "C" void func_00125970(void*);
struct FrontendDisconnectRequest { signed char index; char reserved[7]; unsigned char active; };
struct FrontendStateLink { int state; void* parent; };
void FrontendControllerScreen::Update() {
    func_0026C8E0();
    for(signed char index=0;index<2;++index) {
        FrontendControllerSample* sample=&samples[index];
        int previous=func_0026BC80(sample);
        int current=func_0026C9C0(this,index);
        if(previous==-1 && current==4) func_0026CA98(this,sample,index);
        if(current!=4 && previous!=-1) {
            FrontendDisconnectRequest* request=*(FrontendDisconnectRequest**)(D_0040F0E0+0x21060);
            if(!request) func_0026CB38(this,sample,previous);
            else if(request->active && request->index==index && !func_00103860()) {
                FrontendStateLink* currentState=*(FrontendStateLink**)(D_0040F0E0+0x21070);
                if(currentState==(void*)(D_0040F0E0+0x20f78) || currentState==(void*)(D_0040F0E0+0x20fa0) || currentState==(void*)(D_0040F0E0+0x20fd8)) {
                    int allow=1;
                    if(currentState->parent==D_0040F0E0+0x21028) {
                        if(*(int*)(D_0040F0E0+0x21084) || *(int*)(D_0040F544+0x3924)) allow=0;
                    } else allow=0;
                    func_00103800(D_0040F0E0,allow);
                }
                if(!*(int*)(D_0040F0E0+0x21084)) func_0026CB38(this,sample,previous);
            }
        }
    }
    for(signed char index=0;index<2;++index) {
        func_00124728(&channels[index]);
        func_00124730(&channels[index]);
    }
    func_00125970(this);
}

#endif
