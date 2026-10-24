#include "include_asm.h"

#include "game/classes/other/UnknownVtable_003E10B0.hpp"
struct FrontendValue;
// Callback signatures and wrapper return semantics remain provisional ABI views.
extern "C" {
int func_0020DF68(void*,const char*,int (*)(const char*));
extern const char D_003FACD0[];
int func_0020EF28(const char*);
extern const char D_003FACE0[];
int func_0020F268(const char*);
extern const char D_003FAD00[];
int func_0020F490(const char*);
extern const char D_003FAD10[];
int func_0020F5A0(const char*);
extern const char D_003FAD28[];
int func_0020F5E8(const char*);
extern int D_0040EB40;
extern int D_0040EB38;
extern int D_0040EAFC;
int func_0020DCB0(FrontendValue*);
extern FrontendValue D_00491FD0;
extern FrontendValue D_00491FE0;
extern FrontendValue D_00491FF0;
extern FrontendValue D_00492000;
extern FrontendValue D_00492010;
void func_0020DCF8(FrontendValue*,const char*);
extern const char D_003FAD90[];
extern const char* D_003BE7B0[];
extern int D_00491FB0[];
void func_0020E068(void*,const char*,int*);
extern const char D_003FADA8[];
extern const char D_003FADC0[];
extern int D_0040EB3C;
extern const char D_003FADD8[];
void func_0020E8C8();
extern const char D_003FADE8[];
int func_0020DE28(FrontendValue*,const char*);
const char* func_001087C8(void*,const char*);
extern void* D_0040F4C4;
extern const char D_003FAE00[];
extern const char D_003FAE20[];
extern const char D_003FAE38[];
extern int D_003BE7D4;
}

int BlackPS2Classes::UnknownVtable_003E10B0::Function_0020EAC8() {

    func_0020DF68(this, D_003FACD0, func_0020EF28);
    func_0020DF68(this, D_003FACE0, func_0020F268);
    func_0020DF68(this, D_003FAD00, func_0020F490);
    func_0020DF68(this, D_003FAD10, func_0020F5A0);
    func_0020DF68(this, D_003FAD28, func_0020F5E8);
    D_0040EB40 = 3;
    D_0040EB38 = 0;
    D_0040EAFC = 0;
    func_0020DCB0(&D_00491FD0);
    func_0020DCB0(&D_00491FE0);
    func_0020DCB0(&D_00491FF0);
    func_0020DCB0(&D_00492000);
    func_0020DCB0(&D_00492010);
    func_0020DCF8(&D_00491FD0, "FE_DIFFICULTYDESC");
    func_0020DCF8(&D_00491FE0, "FE_LEVEL_AND_RATING");
    func_0020DCF8(&D_00491FF0, "FE_LEVELNAME");
    func_0020DCF8(&D_00492000, "FE_OVERALLRATING2");
    func_0020DCF8(&D_00492010, D_003FAD90);
    for (int i = 0; i < 8; ++i) func_0020E068(this, D_003BE7B0[i], D_00491FB0 + i);
    func_0020E068(this, D_003FADA8, &D_0040EB40);
    func_0020E068(this, D_003FADC0, &D_0040EB3C);
    func_0020E068(this, D_003FADD8, &D_0040EB38);
    func_0020E8C8();
    switch (D_0040EB3C) {
    case 0:func_0020DE28(&D_00491FD0,func_001087C8(D_0040F4C4,D_003FADE8));break;
    case 1:func_0020DE28(&D_00491FD0,func_001087C8(D_0040F4C4,D_003FAE00));break;
    case 2:func_0020DE28(&D_00491FD0,func_001087C8(D_0040F4C4,D_003FAE20));break;
    case 3:func_0020DE28(&D_00491FD0,func_001087C8(D_0040F4C4,D_003FAE38));break;
    }
    D_003BE7D4 = -1;
    return 1;
}
