#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/graphics/movement_core.hpp"
#include "game/effects/vu_math.h"
using namespace CampaignGraphics;
using namespace BlackGame;
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
{return BlackPS2::VU0::ReadXWord(SumSquares3(Sub3(a,b)));}
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E7C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EA20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EBE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F2A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001948A0);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E578);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E588);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E5B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E5E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E680);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EB78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018ECA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018ED50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EE00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F008);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F0B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F180);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F2E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F358);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F378);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F3E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F3E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F408);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F4E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F6A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F6D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F700);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F730);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F750);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F7C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FB40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FB88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FC18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FCB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FD80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FE28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FE30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FE50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FE58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FF38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018FFC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001901E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001902D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190428);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001904D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190580);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190730);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190768);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001907E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001908A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001909F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190A00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190A68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190BC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190C18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190CB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190D30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190E98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190EA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191010);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191070);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001911A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191270);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191290);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191360);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191450);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191578);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001915D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001916E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191788);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001917A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191A28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191AA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191B78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191BB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191C18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191C20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191C48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191C80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191D40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001920D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001921D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001922E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192570);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001925D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192698);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192A00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192A78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192D48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192E50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192EB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192FB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193040);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001930F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001933F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001934A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001936C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193700);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193720);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193818);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193880);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001938C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193970);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193980);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001939E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193A08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193A28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193A58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193A60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193B98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193BB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193BE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193CC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193D18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193D38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193D40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193FE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001940C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001940E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001941A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001941F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00194240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00194420);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00194490);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001944D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001945F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00194610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00194878);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00194888);
