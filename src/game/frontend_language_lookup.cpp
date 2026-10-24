#include "include_asm.h"

// Inferred PS2 frontend layout and behavior.
extern unsigned char D_0040D99A;
extern "C" void* func_002750B8(void*,int);
struct FrontendLanguageLookup {
    char reserved[0xd10];
    void* archives[11];
    void* Find(int key) __asm__("func_00108818");
};

void* FrontendLanguageLookup::Find(int key) {
    if(!D_0040D99A) return 0;
    void** archive=archives;
    for(int index=0;index<11;++index,++archive) {
        if(*archive) {
            void* found=func_002750B8(*archive,key);
            if(found) return found;
        }
    }
    return 0;
}
