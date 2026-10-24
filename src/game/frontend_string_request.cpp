#include "include_asm.h"

// Inferred PS2 frontend layout and behavior.
extern unsigned char D_0040D99A,D_0040D99B;
extern char* D_0040F4C4;
extern const char* D_003BC580;
extern int D_0040EAE4;
extern const char* D_003F40B0[];
extern "C" int func_0035D728(char*,const char*,...);
extern "C" void func_00108958();
extern "C" void func_001093C0(void*,void*,int,int,void(*)(),void*,int,int);
struct FrontendStringRequestFlags { char reserved[0x138]; unsigned char first,second; };

static inline bool HasPendingStringRequests(FrontendStringRequestFlags* status) { return status->first || status->second; }
extern "C" void func_00108890() {
    char path[64];
    if(!D_0040D99A && !D_0040D99B) {
        FrontendStringRequestFlags* status=(FrontendStringRequestFlags*)((unsigned)D_0040F4C4+0xa00);
        if(!HasPendingStringRequests(status)) {
            D_0040D99B=1;
            func_0035D728(path,D_003BC580,D_003F40B0[D_0040EAE4]);
            func_001093C0(D_0040F4C4,path,8,1,func_00108958,0,0,0x2000000);
        }
    }
}
