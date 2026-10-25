#ifndef BLACK_ANIMATION_SELECTOR_HPP
#define BLACK_ANIMATION_SELECTOR_HPP
#include "ps2/vu0.hpp"
namespace AnimationSelectPS2 {
// Partial PS2 views. Original class names and inheritance are still unverified.
static inline float SumWord(Game::Vec value) {
 Game::Vec one,result;
 asm("vaddw.x onev, vf0, vf0w" : "=j onev"(one));
 asm("vadday.x ACC, vv, vvy\n\tvmaddz.x resultv, onev, vvz" : "=j resultv"(result):"j vv"(value),"j onev"(one));
 return Ps2Math::VU0::ReadXWord(result);
}
struct Actor {
 template<class T> inline T& At(int offset) { return *(T*)((char*)this+offset); }
 inline char* AnimationPrefix() { return (char*)this+0x3b9; }
 inline bool HasLayer() { char* layer=At<char*>(0x26c); bool result=false; if(layer)result=*(int*)(layer+12+4*(unsigned char)layer[0x19])!=0;return result; }
};
struct Movement {
 template<class T> inline T& At(int offset) { return *(T*)((char*)this+offset); }
};
struct Selector {
 signed char familyIndex; char opaque[0x5b]; void* table;
 // Constructor array stores prove vptr+0x5c and a0x60 stride; no allocation-size claim.
 void Emit(char*,const char*,const char*,const char*,Actor*) __asm__("func_001AB1C0");
 void EmitFallback(char*,const char*,const char*,const char*,const char*,Actor*) __asm__("func_001AAF10");
 void Stand(char*,Actor*,long);
 void Move(char*,Actor*);
 void Idle(char*,Actor*);
 void MoveAlternate(char*,Actor*,long);
 void Action(char*,Actor*,int);
 void Combat(char*,Actor*,long,unsigned long,long,float);
 void Turn(char*,Actor*,long,float);
 void Aim(char*,Actor*);
 void Sector(char*,Actor*,long,float);
 void Utility(char*,Actor*,long);
};
struct PrefixedSelector : Selector {
 // Same constructor uses0x6c stride: the derived prefix is12bytes at0x60.
 char prefix[12];
 long CheckBC(Actor*) __asm__("func_001ADBC0");
 long CheckBF(Actor*) __asm__("func_001ADBF0");
 long CheckC1(Actor*) __asm__("func_001ADC10");
 void Stand(char*,Actor*); void State(char*,Actor*,int,long);
 void Transition(char*,Actor*); void Alternate(char*,Actor*,long,int);
 void Special(char*,Actor*); void Primary(char*,Actor*);
 void Secondary(char*,Actor*); void Tertiary(char*,Actor*);
 void Utility(char*,Actor*,long); void Final(char*,Actor*);
};
extern "C" {
Movement* func_00135550(Actor*);
const char* func_00137AE0(Actor*);
void func_00135578(Actor*,int);
int func_00136B30(void*);
char* func_0015D248(void*,int,int);
char* func_0015D210(void*,int);
int func_00360838(const char*,const char*);
void func_0035CBC0(char*);
char* func_0035C7A4(char*,const char*);
long func_0018DDD8(void*);
float func_0029E0D8(float);
extern char* D_0040F4D0;
extern void* D_0040F4E0;
extern const char *D_003BD140,*D_003BD190,*D_003BD14C,*D_003BD150;
extern int* D_00414D54;
extern const char D_003F70E8[],D_003F70F8[],D_003F7130[];
extern const char D_003F69F8[];
extern const char D_003F6A00[];
extern const char D_003F6A08[];
extern const char D_003F6A10[];
extern const char D_003F6A18[];
extern const char D_003F6A20[];
extern const char D_003F6A78[];
extern const char D_003F6A80[];
extern const char D_003F6A88[];
extern const char D_003F6DE8[];
extern const char D_003F6DF0[];
extern const char D_003F6DF8[];
extern const char D_003F6E20[];
extern const char D_003F6E28[];
extern const char D_003F6E30[];
extern const char D_003F70A8[];
extern const char D_003F70B0[];
extern const char D_003F70B8[];
extern const char D_003F70C0[];
extern const char D_003F70C8[];
extern const char D_003F70D0[];
extern const char D_003F70D8[];
extern const char D_003F70E0[];
extern const char D_003F70F0[];
extern const char D_003F7118[];
extern const char D_003F7120[];
extern const char D_003F7128[];
extern const char D_003F7138[];
extern const char D_003F7140[];
extern const char D_003F7168[];
extern const char D_003F7170[];
extern const char D_003F7180[];
extern const char D_0040D9C8[];

}
}
#endif
