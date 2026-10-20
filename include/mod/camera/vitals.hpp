#ifndef BLACK_MOD_CAMERA_VITALS_HPP
#define BLACK_MOD_CAMERA_VITALS_HPP
#include "mod/camera/vitals.h"
#include "ps2/vu0.hpp"
namespace ModCamera {
/* Instruction-only13C778 callback view: vptr84 and adjusted slot28/2C.
   Original class identity and semantic virtual signatures remain unverified. */
struct DamageSinkPrefix { unsigned char unknown00[0x84]; };
class DamageSink:public DamageSinkPrefix {
public:
 virtual void V0();virtual void V1();virtual void V2();virtual void V3();
 virtual void Event(float,int,BlackGame::Vec,int);
};
struct DamagePoint2 {float x,z;};
class PlayerVitals:public BkModPlayerVitalsPS2 {
public:
 void Damage(BlackGame::Vec,float) __asm__("func_0013C778");
 int AddMedkit() __asm__("func_0013CD20");
 void Restore(int) __asm__("func_0013C9D8");
};
}
#endif
