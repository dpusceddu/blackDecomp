#include "include_asm.h"

#include "game/frontend_resources.hpp"

extern "C" int func_001092F8();
extern "C" void func_00272730(int);
extern "C" void func_00108540(FrontendResourceCache*,int,int,int);
extern FrontendResourceCache* D_0040F4C4;
extern unsigned char D_0040D99A;

// Language-string archive completion callback.

extern "C" void func_00108958() {
    int archive=func_001092F8();
    func_00272730(archive);
    func_00108540(D_0040F4C4,3,archive,0);
    D_0040D99A=1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001089A8);
