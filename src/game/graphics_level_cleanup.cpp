#include "game/classes/other/UnknownVtable_003E10B0.hpp"
struct FrontendValue;
extern "C" {
void func_0020DF90(void*,const char*);
extern const char D_003FACD0[];
extern const char D_003FACE0[];
extern const char D_003FAD00[];
extern const char D_003FAD10[];
extern const char D_003FAD28[];
void func_0020DD48(FrontendValue*);
extern FrontendValue D_00491FD0;
extern FrontendValue D_00491FE0;
extern FrontendValue D_00491FF0;
extern FrontendValue D_00492000;
extern FrontendValue D_00492010;
int func_0020DF30(FrontendValue*);
extern const char* D_003BE7B0[];
void func_0020E0C8(void*,const char*);
extern int D_003BE7D4;
extern unsigned char D_0040DDFB;
extern unsigned char D_0040DDFA;
extern const char D_003FADA8[];
extern const char D_003FADC0[];
extern const char D_003FADD8[];
}
int BlackPS2Classes::UnknownVtable_003E10B0::Function_0020EDB0() {

    func_0020DF90(this, D_003FACD0);
    func_0020DF90(this, D_003FACE0);
    func_0020DF90(this, D_003FAD00);
    func_0020DF90(this, D_003FAD10);
    func_0020DF90(this, D_003FAD28);
    func_0020DD48(&D_00491FD0);
    func_0020DD48(&D_00491FE0);
    func_0020DD48(&D_00491FF0);
    func_0020DD48(&D_00492000);
    func_0020DD48(&D_00492010);
    func_0020DF30(&D_00491FE0);
    func_0020DF30(&D_00491FF0);
    func_0020DF30(&D_00492000);
    func_0020DF30(&D_00492010);
    for (int i = 0; i < 8; ++i) func_0020E0C8(this, D_003BE7B0[i]);
    D_003BE7D4 = -1;
    D_0040DDFB = 0;
    D_0040DDFA = 0;
    func_0020E0C8(this, D_003FADA8);
    func_0020E0C8(this, D_003FADC0);
    func_0020E0C8(this, D_003FADD8);
    return 1;
}
