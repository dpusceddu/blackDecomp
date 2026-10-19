#include "classes/other/UnknownVtable_003E0EB8.hpp"
struct FrontendValue;
struct UnlockDefinition { const char* name; unsigned char opaque[12]; };
typedef char UnlockDefinition_stride[(sizeof(UnlockDefinition)==16)?1:-1];
extern "C" {
extern UnlockDefinition D_003FC8C8;
void func_0020E0C8(void*, const char*);
void func_0020DD48(FrontendValue*);
void func_0020DF30(FrontendValue*);
void func_0020DF90(void*, const char*);
extern FrontendValue D_00492370;
extern FrontendValue D_00492380;
extern FrontendValue D_00492390;
extern FrontendValue D_004923A0;
extern FrontendValue D_004923B0;
extern FrontendValue D_004923C0;
extern FrontendValue D_004923E0;
extern FrontendValue D_004923F0;
extern FrontendValue D_004923D0;
extern FrontendValue D_00492400;
extern FrontendValue D_00492410;
extern const char D_003FB7C8[];
extern const char D_003FB7E0[];
extern const char D_003FB800[];
extern const char D_003FB818[];
extern const char D_003FB838[];
}
int BlackPS2Classes::UnknownVtable_003E0EB8::Function_00213758(){
UnlockDefinition* entry=&D_003FC8C8;
for(int i=0;i<16;++i)func_0020E0C8(this,(&D_003FC8C8)[i].name);
    func_0020DD48(&D_00492370);
    func_0020DD48(&D_00492380);
    func_0020DD48(&D_00492390);
    func_0020DD48(&D_004923A0);
    func_0020DD48(&D_004923B0);
    func_0020DD48(&D_004923C0);
    func_0020DD48(&D_004923E0);
    func_0020DD48(&D_004923F0);
    func_0020DD48(&D_004923D0);
    func_0020DD48(&D_00492400);
    func_0020DF30(&D_00492370);
    func_0020DF30(&D_00492380);
    func_0020DF30(&D_00492390);
    func_0020DF30(&D_004923A0);
    func_0020DF30(&D_004923B0);
    func_0020DF30(&D_004923C0);
    func_0020DF30(&D_004923E0);
    func_0020DF30(&D_004923F0);
    func_0020DF30(&D_004923D0);
    func_0020DF30(&D_00492400);
    func_0020DF30(&D_00492410);
    func_0020DF90(this,D_003FB7C8);
    func_0020DF90(this,D_003FB7E0);
    func_0020DF90(this,D_003FB800);
    func_0020DF90(this,D_003FB818);
    func_0020DF90(this,D_003FB838);
 return 1;
}
