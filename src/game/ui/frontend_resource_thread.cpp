#include "include_asm.h"

#include "game/frontend_resources.hpp"

extern "C" int func_003676F0(int,int);

void FrontendCallbackQueue::Signal() {
    int result=func_003676F0(ioClient,3);
    func_003676F0(ioClient,result);
    func_003676F0(ioThread,result+2);
}

int FrontendCallbackQueue::Poll() {
    int result=func_003676F0(ioClient,3);
    func_003676F0(ioClient,result);
    return result;
}

extern "C" void func_00274920();
extern "C" void func_00271480();
extern "C" void func_00108E78(FrontendCallbackQueue*);
extern FrontendCallbackQueue* D_0040F4C4;

// Resource service thread.
extern "C" void func_00108050() {
    for (;;) {
        func_00274920();
        if (D_0040F4C4->callback) {
            D_0040F4C4->callback(D_0040F4C4->callbackData);
            D_0040F4C4->callback=0;
        }
        func_00108E78(D_0040F4C4);
        func_00271480();
    }
}
