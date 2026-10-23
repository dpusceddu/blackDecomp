// Unmatched: 00155C28: inline normalization and matrix references improve code, but call scheduling and byte-loop allocation differ.
#if 0
#include "campaign/weapons/projectiles.hpp"
namespace ModWeapons {
extern void*presentationRoot __asm__("D_0040F4D8");
extern "C" void func_001B6CF8(void*,Projectile*,int);
extern "C" void func_0012A280(Frame*,Projectile*);
extern "C" void func_0012C428(Frame*,Vec,Vec,EeU64,int,int,int,int,int,float,float);
static inline Vec One(){Vec one;asm("vaddw.x onev, vf0, vf0w":"=j onev"(one));return one;}
static inline void Normalize(Vec&value,Vec one){Vec v=value;
 Vec square=Mul3(v,v),sum;
 asm("vadday.x ACC, squarev, squarevy
	vmaddz.x sumv, onev, squarevz":"=j sumv"(sum):"j squarev"(square),"j onev"(one));
 asm("vnop
	vnop
	vnop
	vrsqrt Q, vf0w, sumvx
	vwaitq
	vmulq.xyz resultv, resultv, Q":"+j resultv"(v):"j sumv"(sum));value=v;
}
void ProjectilePool::RetireOther(Projectile*actor,int emit,int alternate){
 unsigned char*activeFlags=otherActive;
 Vec one=One();
 EeU64 effect=alternate?0x6856391B39AD6000UL:0x6855DD9AD0643000UL;
 Matrix&world=actor->world;
 Projectile*body=other;int*handle=otherHandles;EeS8 index=0;
 do{
  if(body==actor){
   activeFlags[index]=0;
   func_001B6CF8((char*)presentationRoot+0x66290,body,1);
   func_0012A280(frame,body);
   if(emit){
    Normalize(body->angularVelocity,one);
    func_0012C428(frame,Load(world.p),body->angularVelocity,effect,2,0,*handle,1,body->special,7.0f,442.0f);
   }
  }
  ++handle;++index;++body;
 }while(index<16);
}
}
#endif
