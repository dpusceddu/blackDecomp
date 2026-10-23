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

extern "C" {
void func_0020DF68(void*,const char*,int (*)());
void func_0020E068(void*,const char*,int*);
void func_0020DCB0(FrontendValue*);
void func_0020DCF8(FrontendValue*,const char*);
void func_00213938();
extern int D_00492330;
int func_00213CA8();
int func_00213DC0();
int func_00213FA8();
int func_00214130();
int func_00214300();
}
int BlackPS2Classes::UnknownVtable_003E0EB8::Function_002134F8(){
func_0020DF68(this,D_003FB7C8,func_00213CA8);
func_0020DF68(this,D_003FB7E0,func_00213DC0);
func_0020DF68(this,D_003FB800,func_00213FA8);
func_0020DF68(this,D_003FB818,func_00214130);
func_0020DF68(this,D_003FB838,func_00214300);
for(int i=0;i<16;++i)func_0020E068(this,(&D_003FC8C8)[i].name,(&D_00492330)+i);
func_00213938();
func_0020DCB0(&D_00492370);
func_0020DCB0(&D_00492380);
func_0020DCB0(&D_00492390);
func_0020DCB0(&D_004923A0);
func_0020DCB0(&D_004923B0);
func_0020DCB0(&D_004923C0);
func_0020DCB0(&D_004923E0);
func_0020DCB0(&D_004923F0);
func_0020DCB0(&D_004923D0);
func_0020DCB0(&D_00492400);
func_0020DCB0(&D_00492410);
func_0020DCF8(&D_00492370,"FE_CURRENTCHALLENGELEVEL");
func_0020DCF8(&D_00492380,"FE_HEADCOUNTANDRATING");
func_0020DCF8(&D_00492390,"FE_GUNRUNANDRATING");
func_0020DCF8(&D_004923A0,"FE_KILLINGTIMEANDRATING");
func_0020DCF8(&D_004923B0,"FE_CHALLENGENAME");
func_0020DCF8(&D_004923C0,"FE_CURRENTCHALLENGERECORD");
func_0020DCF8(&D_004923E0,"FE_REQUIREMENT1");
func_0020DCF8(&D_004923F0,"FE_REQUIREMENT2");
func_0020DCF8(&D_004923D0,"FE_REQUIREMENT3");
func_0020DCF8(&D_00492400,"FE_REQUIREMENT4");
return 1;
}
