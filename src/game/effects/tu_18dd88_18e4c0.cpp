#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/graphics/movement_core.hpp"
#include "game/effects/vu_math.h"
using namespace Graphics;
using namespace Game;
extern "C" {
extern unsigned char *D_0040F4D4,*D_0040F4D0;
extern void *func_00179258(void *,long);
extern long func_00178F18(void *);
extern unsigned char *func_00135550(unsigned);
extern Vec *func_00178D30(void *);
extern long func_00184238(void *,int);
extern void *func_00183500(void *);
extern float func_00180A10(void *);
extern Vec func_00180A00(void *);
extern GoalRecord *func_001809F0(void *);
extern void func_0018E338(void *);
extern long func_00189BF8(void *,unsigned);
extern void func_0016ABA8(void *,unsigned,unsigned char,void *);
extern long func_00185C38(void *,unsigned);
extern long func_001829E8(void *);
extern unsigned func_001829A8(void *);
extern long func_001829A0(void *);
extern void func_00190C18(void *);
extern void *func_0013D400(void *);
extern long func_001726A0(void *,void *);
extern void func_0018EE00(void *);
extern unsigned char func_00180BC0(void *);
extern long func_0018AB08(void *);
extern long func_00188F10(void *);
extern void func_00384290(void *);
extern long func_0018E590(void *);
extern long func_00174FB0(void *);
extern long func_00185F00(void *);
extern long func_00185F18(void *);
extern Vec *func_00185F10(void *);
extern Vec *func_00185FE8(void *);
extern bool func_00182320(void *,Vec,int);
extern bool func_00182410(void *,Vec,unsigned char,unsigned char);
extern void func_00193990(void *,bool);
extern unsigned func_00173610(void *);
extern void func_0017E488(void *,float);
}
static inline float DistanceSquared(Vec a,Vec b)
{return Ps2Math::VU0::ReadXWord(SumSquares3(Sub3(a,b)));}
// Unmatched: 26 instruction differences in helper lifetime, allocation or scheduling.
long MovementCore::Event(unsigned *event)
{
    switch(*event){
    case 2:if(!func_0018AB08(brain->Part(0x150)))return 0;func_00384290(this);Choose(3);break;
    case 3:if(func_00188F10(brain->Part(0x150)))return 0;Choose(5);break;
    case 4:case 19:case 20:func_00384290(this);Choose(4);break;
    }
    return 0;
}

// Unmatched: 50 instruction differences in helper lifetime, allocation or scheduling.
long MovementCore::Allowed(long id)
{
    bool close=false;int tier=0;
    if(id!=-1){
        void *identity=func_00179258(D_0040F4D4+0xfa8,id);
        if(!func_00178F18(identity))return 1;
        if(*(int *)(func_00135550(*(unsigned *)((unsigned char *)identity+8))+0x80)==1)tier=*(int *)(func_00135550(*(unsigned *)((unsigned char *)identity+8))+0x754);
        Vec point=*func_00178D30(identity);
        if(DistanceSquared(point,brain->Position())<25.0f)close=true;
        if(brain->Field<float>(0x70c)>=0){
            point=*func_00178D30(identity);float range=brain->Field<float>(0x70c);
            bool outside=true;if(!(range*range<DistanceSquared(point,brain->Position())))outside=false;if(outside)return 0;
        }
    }
    switch(behavior){
    case 1:
        if(close)return 1;
        if(tier<=1)return 0;
        if(func_00184238(brain->Part(0x6f0),0))return 1;
        if(func_00183500(brain->Part(0x1eb0)))return func_00184238(brain->Part(0x6f0),2)!=0;
        return 0;
    case 2:
        if(close)return 1;
        if(tier<=1)return 0;
        if(func_00183500(brain->Part(0x1eb0))&&func_00183500(brain->Part(0x1eb0))!=brain->Field<void *>(0x7c))
            return func_00184238(brain->Part(0x6f0),2);
        return func_00184238(brain->Part(0x6f0),0);
    }
    return 1;
}

// Unmatched: 74 instruction differences in helper lifetime, allocation or scheduling.
Vec MovementCore::Direction()
{
    float heading=func_00180A10(brain->Part(0xb30));
    Vec trig=BkEffectVUSinCosPS2(heading*0.017453292f,heading*0.017453292f),zero=(Vec)0;
    asm("vaddy.z resv, vf0, resvy\n\tvaddx.y resv, vf0, zerovx":"+j resv"(trig):"j zerov"(zero));
    return trig;
}

// Unmatched: 28 instruction differences in helper lifetime, allocation or scheduling.
Vec MovementCore::Nearest(Vec point)
{
    float best=3.402823466e38f;
    int count=brain->Field<int>(0x90);
    Vec result=func_00180A00(brain->Part(0xb30));
    if(count>0){Vec **next=(Vec **)brain->Part(0x94);do{
        Vec candidate=**next;float distance=DistanceSquared(candidate,point);
        --count;if(distance<best){best=distance;result=candidate;}++next;
    }while(count);}
    return result;
}

// Unmatched: 13 instruction differences in helper lifetime, allocation or scheduling.
Vec MovementCore::Target()
{
    Vec result;
    if(func_001809F0(brain->Part(0xb30))){
        const Point3& p=func_001809F0(brain->Part(0xb30))->point;
        result=WidenVec(p);
    }else result=func_00180A00(brain->Part(0xb30));
    return result;
}

// Unmatched: 13 instruction differences in helper lifetime, allocation or scheduling.
Vec MovementCore::AlternateTarget()
{
    Vec result;
    if(func_001809F0(brain->Part(0xb30))){
        const Point3& p=func_001809F0(brain->Part(0xb30))->point;
        result=WidenVec(p);
    }else result=func_00180A00(brain->Part(0xb30));
    return result;
}

// Unmatched: 2 instruction differences in helper lifetime, allocation or scheduling.
float ActionWeight::Score(unsigned char *event)
{
    if(*(int *)(event+0x24)==4&&func_00174FB0(value))return 1.0f;
    return 0.0f;
}

// Unmatched: policy Update retains 13 instruction differences in completion-branch layout.
void MovementPolicy::Update()
{
    Vec target=func_00180A00(brain->Part(0xb30));
    if(!brain->Field<unsigned char>(0xc7e)){
        if(func_00185F00(brain->Part(0x90)))target=*func_00185F10(brain->Part(0x90));
        else if(func_00185F18(brain->Part(0x90)))target=*func_00185FE8(brain->Part(0x90));
    }
    ((unsigned char *)brain->Field<void *>(0x694))[0x30]=0;
    bool result;
    if(brain->Field<int>(0x754)<1)result=func_00182320(brain->Part(0x810),target,0);
    else result=func_00182410(brain->Part(0x810),target,0,0);
    if(result&&func_001829A8(brain->Part(0x810))){
        if(func_001829E8(brain->Part(0x810))){
            void *turn=brain->Part(0x650);
            float heading=func_00180A10(brain->Part(0xb30));func_0017E488(turn,heading);func_00193990(this,true);
        }else if(!(unsigned char)func_00173610(brain->Part(0xc78)))func_00193990(this,false);
    }else func_00193990(this,false);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_0018E4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_0018E7C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_0018EA20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_0018EBE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_0018EF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_0018F100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_0018F2A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_001948A0);
#endif

// UNVERIFIED: original type and untouched fields.
struct Recovered_EffectEvent {
    void* owner;
    unsigned char* brain;
    unsigned char unknown08[12];
    unsigned char active;
};
extern "C" void func_0018E338(void*);
extern "C" unsigned char func_00180BC0(void*);
extern "C" void EffectQueueAdd(void*, int, int, int) __asm__("func_0016ABA8");
extern "C" void func_00190CB8(Recovered_EffectEvent* self) {
    func_0018E338(self);
    unsigned char* data = *(unsigned char**)((unsigned char*)self->owner + 0x30);
    if (!self->active) {
        self->active = func_00180BC0(self->brain + 0xB30);
        if (self->active && data[0x2C]) {
            EffectQueueAdd(self->brain + 0x1F90, *(int*)(data + 0x20), data[0x2C], *(int*)(self->brain + 0x7C));
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_00190D30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_00193608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_001936C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_18dd88_18e4c0", func_001938C0);
