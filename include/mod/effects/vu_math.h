#ifndef BLACK_EFFECTS_VU_MATH_H
#define BLACK_EFFECTS_VU_MATH_H
#include "game/effects/geometry.h"
#include "game/actor/vector_math.h"
/* Inferred EE helpers; no matching caller yet verifies these implementations. */
static inline s128 BkEffectAddPS2(s128 a,s128 b) {s128 r;__asm__("vadd.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b));return r;}
static inline s128 BkEffectScalePS2(s128 a,f32 value) {s128 r,s;__asm__("qmtc2.ni fr, sv":"=j sv"(s):"r fr"(value));__asm__("vmulx.xyz outv, av, svx":"=j outv"(r):"j av"(a),"j sv"(s));return r;}
static inline void BkEffectVUSeedPS2(f32 seed) {s128 v;__asm__("qmtc2.ni bitsv, seedv":"=j seedv"(v):"r bitsv"(seed));__asm__ volatile("vrinit R, seedvx": :"j seedv"(v));}
static inline s128 BkEffectVUNextPS2(void) {s128 v;__asm__ volatile("vrnext.x randv, R\n\tvrnext.y randv, R\n\tvrnext.z randv, R\n\tvrnext.w randv, R":"=j randv"(v));return v;}
static inline s128 BkEffectVUNextXPS2(void) {s128 v;__asm__ volatile("vrnext.x randv, R":"=j randv"(v));return v;}
static inline s128 BkEffectVUNextYZWPS2(s128 v) {__asm__ volatile("vrnext.y randv, R\n\tvrnext.z randv, R\n\tvrnext.w randv, R":"+j randv"(v));return v;}
static inline s128 BkEffectVUNextYZPS2(s128 v) {__asm__ volatile("vrnext.y randv, R\n\tvrnext.z randv, R":"+j randv"(v));return v;}
static inline s128 BkEffectVURotateLanesPS2(s128 v) {s128 r;__asm__("vmr32.xyzw outv, inv":"=j outv"(r):"j inv"(v));return r;}
static inline s128 BkEffectVUUnitRandomPS2(s128 random,s128 scale,s128 offset) {
 s128 r;
 __asm__("vmul.xyzw outv, scalev, randv\n\tvadda.xyzw ACC, outv, offsetv\n\tvmsubaw.xyzw ACC, offsetv, vf0w\n\tvmsubw.xyzw outv, outv, vf0w":"=&j outv"(r):"j randv"(random),"j scalev"(scale),"j offsetv"(offset));return r;
}
/* Four lanes hold cos(a), sin(a), cos(b), sin(b), using the game's VU I/ACC polynomial. */
static inline s128 BkEffectVUSinCosPS2(f32 a,f32 b) {
 BkEffectPointPS2 input={a,a,b,b};s128 x=*(s128 *)&input,one,p2,p4,p8,c3,c5,c7,c9,result;
 __asm__ volatile("vmaxw.xyzw onesv, vf0, vf0w\n\tctc2.ni quarterv, vi21\n\tvnop\n\tvsubi.xz anglesv, anglesv, I\n\tvabs.xyzw anglesv, anglesv\n\tctc2.ni invtauv, vi21\n\tvnop\n\tvmulai.xyzw ACC, anglesv, I\n\tctc2.ni biasv, vi21\n\tvnop\n\tvmsubai.xyzw ACC, onesv, I\n\tvmaddai.xyzw ACC, onesv, I\n\tctc2.ni invtauv, vi21\n\tvnop\n\tvmsubai.xyzw ACC, anglesv, I\n\tctc2.ni halfv, vi21\n\tvnop\n\tvmsubi.xyzw anglesv, onesv, I\n\tvabs.xyzw anglesv, anglesv\n\tctc2.ni fourthv, vi21\n\tvnop\n\tvsubi.xyzw anglesv, anglesv, I":"+j anglesv"(x),"=&j onesv"(one):"r quarterv"(0x3fc90fdb),"r invtauv"(0xbe22f983),"r biasv"(0x4b400000),"r halfv"(0x3f000000),"r fourthv"(0x3e800000));
 __asm__("vmul.xyzw squarev, anglesv, anglesv\n\tvmul.xyzw fourthv, squarev, squarev\n\tvmul.xyzw eighthv, fourthv, fourthv":"=&j squarev"(p2),"=&j fourthv"(p4),"=j eighthv"(p8):"j anglesv"(x));
 __asm__ volatile("ctc2.ni coef7v, vi21\n\tvnop\n\tvmuli.xyzw cubic7v, anglesv, I\n\tvmul.xyzw cubic7v, cubic7v, squarev\n\tctc2.ni coef3v, vi21\n\tvnop\n\tvmuli.xyzw cubic3v, anglesv, I\n\tctc2.ni coef5v, vi21\n\tvnop\n\tvmuli.xyzw cubic5v, anglesv, I\n\tctc2.ni coef9v, vi21\n\tvnop\n\tvmuli.xyzw cubic9v, anglesv, I":"=&j cubic3v"(c3),"=&j cubic5v"(c5),"=&j cubic7v"(c7),"=j cubic9v"(c9):"j anglesv"(x),"j squarev"(p2),"r coef3v"(0xc2255de0),"r coef5v"(0x42a33457),"r coef7v"(0xc2992661),"r coef9v"(0x421ed7b7));
 __asm__ volatile("vmula.xyzw ACC, cubic3v, squarev\n\tvmadda.xyzw ACC, cubic7v, fourthv\n\tctc2.ni tauv, vi21\n\tvmadda.xyzw ACC, cubic5v, fourthv\n\tvmaddai.xyzw ACC, anglesv, I\n\tvmadd.xyzw outv, cubic9v, eighthv":"=j outv"(result):"j cubic3v"(c3),"j cubic5v"(c5),"j cubic7v"(c7),"j cubic9v"(c9),"j squarev"(p2),"j fourthv"(p4),"j eighthv"(p8),"j anglesv"(x),"r tauv"(0x40c90fda));return result;
}
static inline void BkEffectAxisRotationPS2(s128 *matrix,s128 axis,f32 radians) {
 BkEffectPointPS2 n=BkEffectSpillPS2(BkNormalizePS2(axis)),trig=BkEffectSpillPS2(BkEffectVUSinCosPS2(radians,radians));f32 c=trig.x,s=trig.y,t=1.0f-c;
 BkEffectPointPS2 rows[4]={{1-(1-n.x*n.x)*t,n.x*n.y*t+n.z*s,n.x*n.z*t-n.y*s,0},{n.x*n.y*t-n.z*s,1-(1-n.y*n.y)*t,n.y*n.z*t+n.x*s,0},{n.x*n.z*t+n.y*s,n.y*n.z*t-n.x*s,1-(1-n.z*n.z)*t,0},{0,0,0,0}};
 for(int i=0;i<4;i++)matrix[i]=*(s128 *)&rows[i];
}
#endif
