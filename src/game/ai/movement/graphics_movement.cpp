#include "include_asm.h"

#include "game/graphics/movement_core.hpp"
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
void MovementCore::Update()
{
    func_0018E338(this);
    if(!actorMode){void *owner=func_0013D400(brain);if(func_001726A0(owner,brain))func_0018EE00(this);}
    else {unsigned char *policy=*(unsigned char **)(parameters+0x30);if(!signaled&&policy[0x40]){
        signaled=func_00180BC0(brain->Part(0xb30));
        if(signaled)func_0016ABA8(brain->Part(0x1f90),*(unsigned *)(policy+0x20),policy[0x40],brain->Field<void *>(0x7c));
    }}
}

int MovementCore::Choose(int phase)
{
    unsigned char *policy=*(unsigned char **)(parameters+0x30);
    switch(phase){
    case 0:func_0016ABA8(brain->Part(0x1f90),*(unsigned *)(policy+0x28),policy[0x3c],brain->Field<void *>(0x7c));break;
    case 1:func_0016ABA8(brain->Part(0x1f90),*(unsigned *)(policy+0x2c),policy[0x3d],brain->Field<void *>(0x7c));break;
    case 3:func_0016ABA8(brain->Part(0x1f90),*(unsigned *)(policy+0x30),policy[0x3e],brain->Field<void *>(0x7c));break;
    case 4:func_0016ABA8(brain->Part(0x1f90),*(unsigned *)(policy+0x34),policy[0x3f],brain->Field<void *>(0x7c));break;
    default:return 0;}return 1;
}

int MovementCore::AlternateChoose(int phase)
{
    unsigned char *policy=*(unsigned char **)(parameters+0x94);
    switch(phase){
    case 0:func_0016ABA8(brain->Part(0x1f90),*(unsigned *)(policy+0x8),policy[0x1c],brain->Field<void *>(0x7c));break;
    case 1:func_0016ABA8(brain->Part(0x1f90),*(unsigned *)(policy+0xc),policy[0x1d],brain->Field<void *>(0x7c));break;
    case 3:func_0016ABA8(brain->Part(0x1f90),*(unsigned *)(policy+0x10),policy[0x1e],brain->Field<void *>(0x7c));break;
    case 4:func_0016ABA8(brain->Part(0x1f90),*(unsigned *)(policy+0x14),policy[0x1f],brain->Field<void *>(0x7c));break;
    default:return 0;}return 1;
}

bool MovementCore::IsNear(Vec point)
{return DistanceSquared(point,func_00180A00(brain->Part(0xb30)))<49.0f;}

long MovementCore::Priority()
{
    if(!func_001829A8(brain->Part(0x810))&&func_001829A0(brain->Part(0x810)))goto finish;
    if(brain->Field<int>(0x754)<2)return 30;
finish:
    return func_0018E590(this);
}

void MovementCore::UpdateProximity()
{
    func_0018E338(this);
    unsigned char *policy=*(unsigned char **)(parameters+0x28);
    if(!signaled&&func_00189BF8(brain->Part(0x150),*(unsigned *)(D_0040F4D0+0x3b0))){
        signaled=1;if(policy[0x28])func_0016ABA8(brain->Part(0x1f90),*(unsigned *)(policy+0x20),policy[0x28],brain->Field<void *>(0x7c));
    }
    if(!brain->Field<unsigned char>(0xc7c)){
        if(!func_00189BF8(brain->Part(0x150),*(unsigned *)(D_0040F4D0+0x3b0)))return;
        if(func_00185C38(brain->Part(0x6f0),*(unsigned *)(D_0040F4D0+0x3b0)))return;
    }
    Vec target=func_00180A00(brain->Part(0xb30));
    float distance=DistanceSquared(target,brain->Position());
    if(func_001829E8(brain->Part(0x810))||!func_001829A8(brain->Part(0x810))||distance<radius*0.5f*0.5f)func_00190C18(this);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018ED50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EE00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F0B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F2A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F2E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018F358);
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
