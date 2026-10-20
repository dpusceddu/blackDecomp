#ifndef BLACK_CAMPAIGN_WEAPONS_CONTROLLER_HPP
#define BLACK_CAMPAIGN_WEAPONS_CONTROLLER_HPP
#include "mod/weapons/state.h"
#include "ps2/vu0.hpp"
namespace ModWeapons {
using namespace BlackGame;
// Receiver views preserve the shared verified prefix. Opaque fields and helper
// signatures below are instruction-backed leads until their own source matches.
template<class T>inline T&Field(void *p,unsigned int offset){return *(T*)((char*)p+offset);}
template<class T>inline const T&Field(const void *p,unsigned int offset){return *(const T*)((const char*)p+offset);}
struct Hit;
struct Action {int kind;EeU8 unknown04[8];int variant;EeU8 flag10;};
struct Frame {EeU8 unknown00[0x1c];float delta,now;};
struct Weapon: BkModWeaponControllerPS2 {
 void Update(int,int,int,int,int,int,int,Action*);
 void Advance(int,int,int,int,int,int,int,Action*) __asm__("func_00156FD0");
 int Shutdown();
 void CancelAim() __asm__("func_00157E10");
 void UpdateAim(float) __asm__("func_00157EA0");
 void SetPose(int);
 int Trace(Vec,Vec,unsigned int,BkModWeaponOwnerPS2*,Hit*) __asm__("func_00156A88");
 void UpdateTarget() __asm__("func_001564D0");
 void ThrowPlayer();void ThrowActor();void Melee();void AreaMelee(float,int);
 static void AnimationEvent(EeU64,BkModWeaponOwnerPS2**);
};
struct PosePair {EeU8 unknown00[8];void*primary,*secondary;};
struct PoseManager {EeU8 unknown00[0x7c];PosePair *pair;};
struct AnimationService {EeU8 unknown00[0xc];void*graph;void*unknown10;void*state;};
struct Presentation {EeU8 unknown00[0xcbd8];AnimationService*animation;};
extern Frame *frame __asm__("D_0040F4D0");
extern void *weaponManager __asm__("D_0040F4E0");
extern void *inputManager __asm__("D_0040F544");
extern PoseManager *poseManager __asm__("D_0040F540");
extern Presentation *presentation __asm__("D_0040F510");
extern int audioManager __asm__("D_0040F51C");
extern EeU8 aimActive __asm__("D_003BCEB4");
extern "C" {
 void func_0015D198(void*,BkModWeaponInstancePS2*);
 void *func_0020BC00(void*,int);
 void func_00209FF8(void*,EeU64);
 EeU64 func_0027C278(const char*);
 int func_0015A948(BkModWeaponInstancePS2*);
 void func_001D6E78(void*,void*,EeU64,int);
 void *func_00135550(BkModWeaponOwnerPS2*);
 void func_0020B988(void*,int);
 void func_001F2838(int,int,int);
 void func_00110478(float,void*);
 int func_00155118(void*,int);
 void func_00159120(float,BkModWeaponInstancePS2*);
 int func_00135138(BkModWeaponOwnerPS2*,Vec,Vec,int,Hit*,int);
 int func_0012AE58(Frame*,Vec,Vec,unsigned int,void*,int,Hit*);
}
extern void *camera __asm__("D_0040F4BC");
}
#endif
