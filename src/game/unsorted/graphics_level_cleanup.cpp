#include "include_asm.h"

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

int Unnamed::UnknownVtable_003E10B0::Function_0020EDB0() {

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

#ifdef NON_MATCHING
struct FrontendValue;
struct ProgressStore;
struct DifficultyRecord { int completion;char unknown04[22];unsigned char unlocked; };
struct LevelCallbacks {static int Select(const char*);static int Start(const char*);static int SetDifficulty(const char*);};
#define FIELD(type,p,n) (*(type*)((char*)(p)+(n)))
template<class T> inline T& At(void* p,int n){return *(T*)((char*)p+n);}
extern "C" {
extern char *D_0040F0E0,*D_0040F544,*D_0040F510;
extern void *D_0040F4E8,*D_0040F4C4;
extern ProgressStore D_0048EFA8;
extern int D_0040EB38,D_003BE7D4,D_0040EB40,D_003BE7D0,D_0040EAFC;
extern char* D_0040EADC;
extern unsigned char D_0040EAE0;
extern FrontendValue D_00492000,D_00491FE0,D_00491FF0,D_00492010;
extern const char D_003FAE50[],D_003FAEA0[],D_003FA878[];
int func_0035E750(const char*);
DifficultyRecord* func_00123C90(ProgressStore*,int,int);
int func_00123C20(ProgressStore*,int);
signed char func_001228E0(void*,signed char);
int func_00122900(void*,signed char);
int func_001229F8(void*);
int func_00123BD0(ProgressStore*,int,int);
int func_0035D728(char*,const char*,...);
const char* func_001087C8(void*,const char*);
int func_0020DD88(FrontendValue*);
int func_0020DE28(FrontendValue*,const char*);
void func_001EF808(void*,int);
void func_001EF7B0(void*,int);
void func_00217408();
void func_00216AF0(void(*)());
void func_00103DB0();
void func_0020E118(void*,int);
char* func_0035CBC0(char*,const char*);
}
inline bool Completed(int level,int difficulty){return func_00123C90(&D_0048EFA8,level,difficulty)->completion==2;}
// Unmatched: record layout and call/register lifetimes; 99 differences.
int LevelCallbacks::Select(const char* command){
 char key[16] __attribute__((aligned(16)));
 int level=func_0035E750(command);
 D_0040EB38=0;D_003BE7D4=level;
 if(Completed(level,0))D_0040EB38|=1;
 if(Completed(level,1))D_0040EB38|=2;
 if(Completed(level,2))D_0040EB38|=4;
 if(Completed(level,3))D_0040EB38|=8;
 func_0035D728(key,D_003FAE50,func_001228E0(D_0040F4E8,(signed char)level));
 const char* title=func_001087C8(D_0040F4C4,key);
 DifficultyRecord* record=func_00123C90(&D_0048EFA8,level,func_00123C20(&D_0048EFA8,level));
 func_0020DD88(&D_00492000);
 if(record->unlocked==1)func_0020DE28(&D_00491FE0,title);
 else func_0020DE28(&D_00491FE0,func_001087C8(D_0040F4C4,"FE_LOCKED"));
 func_0020DE28(&D_00491FF0,title);
 FIELD(signed char,D_0040F0E0,0x2020c)=func_001228E0(D_0040F4E8,(signed char)level);
 FIELD(signed char,D_0040F0E0,0x2020d)=1;FIELD(signed char,D_0040F0E0,0x2020e)=1;
 D_0040EB40=func_00123C20(&D_0048EFA8,level)+1;
 void* menu=FIELD(void*,At<void*>(D_0040F510,0xcbd8),0x38);
 func_001EF808(menu,D_003BE7D0);
 func_001EF7B0(FIELD(void*,At<void*>(D_0040F510,0xcbd8),0x38),D_003BE7D0);
 switch(D_0040EB40-1){
 case 0:return func_0020DE28(&D_00492010,func_001087C8(D_0040F4C4,"FE_DIFFEASY"));
 case 1:return func_0020DE28(&D_00492010,func_001087C8(D_0040F4C4,"FE_DIFFNORMAL"));
 case 2:return func_0020DE28(&D_00492010,func_001087C8(D_0040F4C4,"FE_DIFFHARD"));
 case 3:return func_0020DE28(&D_00492010,func_001087C8(D_0040F4C4,D_003FAEA0));
 default:return func_0020DD88(&D_00492010);
 }
}
inline bool AnyProgress(signed char level,int difficulty){return func_00123C90(&D_0048EFA8,func_00122900(D_0040F4E8,level),difficulty)->completion>=0;}
// Unmatched: lookup helpers, small data and scheduling; 47 differences.
int LevelCallbacks::Start(const char*){
 int selection=255;signed char i=0;unsigned char level=FIELD(unsigned char,D_0040F0E0,0x2020c);
 while(i<func_001229F8(D_0040F4E8)){if(func_001228E0(D_0040F4E8,i)==level){selection=(unsigned char)i;i=func_001229F8(D_0040F4E8);}++i;}
 int result=func_00123BD0(&D_0048EFA8,selection,FIELD(int,D_0040F0E0,0x2014c));
 if(result==1){
  D_0040EAFC=0;
  if(AnyProgress((signed char)FIELD(unsigned char,D_0040F0E0,0x2020c),0)||AnyProgress((signed char)FIELD(unsigned char,D_0040F0E0,0x2020c),1)||AnyProgress((signed char)FIELD(unsigned char,D_0040F0E0,0x2020c),2)||AnyProgress((signed char)FIELD(unsigned char,D_0040F0E0,0x2020c),3))D_0040EAE0=1;else D_0040EAE0=0;
  func_00217408();D_0040EADC=D_0040F0E0+0x20f78;func_00216AF0(func_00103DB0);func_0020E118(D_0040F0E0+0x20260,1);
  char* menu=D_0040F544;func_0035CBC0(menu+0x3820,D_003FA878);
  if(FIELD(signed char,menu,0x3840)==0)FIELD(int,menu,0x388c)=1;else FIELD(int,menu,0x3884)=1;
  return 1;
 }
 return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020EF28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020F268);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020F490);
