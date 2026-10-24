#include "ps2/ee_fpu.h"
#include "animation/arms/instance.hpp"
#include "ps2/prelude.h"
namespace ArmsAnimation {
static inline void ScaleRow(float scalar,const BlackGame::Position4& input,BlackGame::Position4& output) {
    asm("lqc2 vf9,0(%1)\n\tmfc1 $8,%2\n\tqmtc2.ni $8,vf11\n\tvmulx.xyzw vf12,vf9,vf11x\n\tsqc2 vf12,0(%0)"
        : :"r"(&output),"r"(&input),"f"(scalar):"$8","vf9","vf11","vf12","memory");
}
static inline void CopyRow(const BlackGame::Position4& input,BlackGame::Position4& output) {
    asm("lq $8,0(%1)\n\tsq $8,0(%0)": :"r"(&output),"r"(&input):"$8","memory");
}

}
namespace Fragment347A50 {


s32 func_00347A50(void *arg0) __asm__("func_00347A50") __attribute__((section(".text.func_00347A50")));
s32 func_00347A50(void *arg0) {
    s32 var_5;

    var_5 = 0;
    if (M2C_FIELD(arg0, f32 *, 0x1C) <= 1.0f) {
        var_5 = 1;
    }
    return !(M2C_FIELD(arg0, s32 *, 0) & 0x02000001) ? var_5 : 1;
}
}

namespace ArmsAnimation {
long __attribute__((section(".text.func_00347A90"))) Instance::SetGraph(int graph,int transition,int mode,float start) {
    int changed=0;
    if(graph!=-1) {
        if(!transition || !TryTransition(this,graph,mode,start)) BindGraph(this,graph,mode,start);
        flags &= ~0x200000;
        changed=1;
    }
    flags &= 0xedfffffe;
    return changed;
}
}

namespace ArmsAnimation {
long __attribute__((section(".text.func_00347B40"))) Instance::SetGraphFlags(int graph,int transition,int flag800) {
    if(this) {
        if(flag800)flags|=0x800;else flags&=~0x800;
        return SetGraph(graph,transition,0,0.0f);
    }
    return 0;
}
}

namespace Fragment347B90 {

extern s32 func_003509E0(s32 *, s32, s32, s32, f32, f32, f32) __asm__("func_003509E0");


s32 func_00347B90(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0, f32 fparg1) __asm__("func_00347B90") __attribute__((section(".text.func_00347B90")));
s32 func_00347B90(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0, f32 fparg1) {
    s32 var_4;

    var_4 = 0;
    if (arg0 != NULL) {
        if (arg1 != -1) {
            func_003509E0(arg0, arg1, arg2, arg3, fparg0, 0.0f, fparg1);
            var_4 = 1;
            *arg0 &= 0xFFDFFFFF;
        }
        *arg0 &= 0xEDFFFFFE;
    }
    return var_4;
}
}

namespace Fragment347C08 {

extern s32 func_00350570(...) __asm__("func_00350570");


s32 func_00347C08(s32 arg0, s32 arg1, s32 arg2) __asm__("func_00347C08") __attribute__((section(".text.func_00347C08")));
s32 func_00347C08(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_7;

    var_7 = 0;
    if (arg1 != -1) {
        func_00350570(arg0, arg1, arg2);
        var_7 = 1;
        M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFDFFFFF);
    }
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xEDFFFFFE);
    return var_7;
}
}

namespace ArmsAnimation {
long __attribute__((section(".text.func_00347C70"))) Instance::Activate(int graph) {
    if(this)return SwitchGraph(this,graph,0,0.0f);
    return 0;
}
}

namespace Fragment347CA0 {

extern s32 func_00345F28(...) __asm__("func_00345F28");
extern s32 func_00347C08(s32 *, s32, s32, f32) __asm__("func_00347C08");


s32 func_00347CA0(s32 *arg0, s32 arg1, s32 arg2, f32 fparg0) __asm__("func_00347CA0") __attribute__((section(".text.func_00347CA0")));
s32 func_00347CA0(s32 *arg0, s32 arg1, s32 arg2, f32 fparg0) {
    u8 sp[16] __attribute__((aligned(16)));
    s32 var_18;

    var_18 = 0;
    if ((arg0 != NULL) && (arg1 != 0)) {
        *(s32 *)(sp + 0) = -1;
        if (func_00345F28(arg1, arg0, (s32*)sp) != 0) {
            var_18 = func_00347C08(arg0, *(s32 *)(sp + 0), arg2, fparg0);
        }
    }
    return var_18;
}
}

namespace Fragment347D28 {

extern s32 func_00347CA0(s32 *, s8 *, s32, f32) __asm__("func_00347CA0");


s32 func_00347D28(s32 *arg0, s8 *arg1) __asm__("func_00347D28") __attribute__((section(".text.func_00347D28")));
s32 func_00347D28(s32 *arg0, s8 *arg1) {
    return func_00347CA0(arg0, arg1, 0, 0.0f);
}
}

namespace Fragment347D48 {

extern s32 func_00347CA0(...) __asm__("func_00347CA0");
extern s32 func_003461E0(...) __asm__("func_003461E0");
extern s32 func_0034F080(...) __asm__("func_0034F080");
extern s32 *func_003489A8(...) __asm__("func_003489A8");
extern s32 func_003511D0(...) __asm__("func_003511D0");




s32 func_00347D48(s32 arg0, s32 arg1) __asm__("func_00347D48") __attribute__((section(".text.func_00347D48")));
s32 func_00347D48(s32 arg0, s32 arg1) {
    return func_00347CA0(arg0, arg1, 1);
}
}

namespace Fragment347D68 {

extern s32 func_00347CA0(...) __asm__("func_00347CA0");
extern s32 func_003461E0(...) __asm__("func_003461E0");
extern s32 func_0034F080(...) __asm__("func_0034F080");
extern s32 *func_003489A8(...) __asm__("func_003489A8");
extern s32 func_003511D0(...) __asm__("func_003511D0");




void func_00347D68(void *arg0) __asm__("func_00347D68") __attribute__((section(".text.func_00347D68")));
void func_00347D68(void *arg0)
{
  s32 temp_17;
  s8 *new_var2;
  f32 *new_var;
  if ((((BkModAnimationInstancePS2*)arg0)->graph) != 0)
  {
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((M2C_FIELD(arg0, s32 *, 0)) | 0x800000);
    func_003461E0();
    temp_17 = func_0034F080(arg0, 0);
    new_var2 = ((s8 *) arg0) + 0;
    *((s32 *) new_var2) = (s32) ((*((s32 *) new_var2)) & 0xFF7FFFFF);
    new_var = &((BkModAnimationInstancePS2*)arg0)->root.quaternion[3];
    if (temp_17 != 0)
    {
      ((BkModAnimationInstancePS2*)arg0)->root.translation[0] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.translation[1] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.translation[2] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.quaternion[0] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.quaternion[1] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.quaternion[2] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.translation[3] = 1.0f;
      *new_var = 1.0f;
      if (func_003489A8(arg0) != NULL)
      {
        func_003511D0(arg0, temp_17);
      }
    }
  }
}
}

namespace ArmsAnimation {
void __attribute__((section(".text.func_00347E18"))) Instance::Matrices(Pose* pose) {
    AnimationSkeleton* skeleton=Skeleton(this);
    if(skeleton) {
        if(selectedMatrices==matrixBase)selectedMatrices=(char*)matrixBase+skeleton->boneCount*64;
        else selectedMatrices=matrixBase;
        BuildMatrices(this,pose);
    }
}
}

namespace ArmsAnimation {
Pose* Instance::Evaluate() {
    Pose* pose=0;
    if(graph) {
        ScratchReset();
        Pose rootPose;
        evaluationFlags=0;
        pose=EvaluateGraph(this,&rootPose);
        for(Instance* overlay=(Instance*)next;overlay&&pose;overlay=(Instance*)overlay->next) {
            if((int)overlay->graphHash!=-1) {
                overlay->evaluationFlags=0;
                if(overlay->At<int>(0x9a8)==1&&overlay->At<int>(0x99c)==1)overlay->current=0;
                Pose* other=EvaluateGraph(overlay,0);
                if(other) {
                    float weight=BlendWeight(overlay,0.3f);
                    if((int)overlay->graphHash!=-1) {
                        AnimationGraphNode* node=(AnimationGraphNode*)overlay->graph;
                        AnimationGraphNode* child=node->children[0];
                        if(!node->childCount)goto mix;
                        if((child->opcode&0x3f)==14)pose=Compose(overlay,pose,other,0);
                        else {
                        mix:
                            if(overlay->At<int>(0x99c))pose=BlendOverlay(overlay,pose,other,weight);
                            else pose=SelectPresent(overlay,pose,other,0);
                        }
                    }
                }
            }
        }
        if(pose) {
            asm("lq $8,0(%1)\n\tsq $8,0(%0)": :"r"(pose->quaternion),"r"(rootPose.quaternion):"$8","memory");
            EeS64 xy=*(EeS64*)rootPose.translation;
            int z=((int*)rootPose.translation)[2];
            *(EeS64*)pose->translation=xy;
            ((int*)pose->translation)[2]=z;
        }
    }
    return pose;
}
}

namespace Fragment348018 {

extern s32 func_00349278(...) __asm__("func_00349278");


void func_00348018(void *arg0) __asm__("func_00348018") __attribute__((section(".text.func_00348018")));
void func_00348018(void *arg0)
{
  int new_var;
  s32 temp_3;
  if ((((BkModAnimationInstancePS2*)arg0)->evaluationFlags) == 0)
  {
    temp_3 = ((BkModAnimationInstancePS2*)arg0)->flags;
    new_var = 1;
    if ((temp_3 & new_var) && (temp_3 & 0x10000000))
    {
      ((BkModAnimationInstancePS2*)arg0)->flags = (s32) (temp_3 & 0xEFFFFFFF);
      func_00349278(arg0);
    }
  }
}
}

namespace ArmsAnimation {
long __attribute__((section(".text.func_00348070"))) Instance::Advance(float* residual,float delta) {
    int atEnd=0;
    int reverseMask=0x40000;
    Instance* cursor=this;
    do {
        if(delta<0)cursor->flags|=reverseMask;
        else {
            cursor->flags&=~0x40000;
            if(cursor->graph&&cursor->current==0)EvaluateGraph(cursor,0);
        }
        if(this!=cursor)ResetTransition(cursor);
        if(cursor->flags&0x200000) {
            float advance=Rate(cursor)*delta;
            float position=cursor->current;
            float limit=cursor->span-1.0f;
            if(limit<=position+advance) {
                AdvanceCoordinate(cursor,limit-position);
                atEnd=1;
                *residual=(cursor->span-1.0f)-cursor->current;
            }else AdvanceCoordinate(cursor,Rate(cursor)*delta);
        }else AdvanceCoordinate(cursor,Rate(cursor)*delta);
        if(0<cursor->current) {
            float advance=Rate(cursor)*delta;
            float span=cursor->span;
            float position=cursor->current;
            if(span-1.0f<=position+advance&&span==1.0f)cursor->flags|=0x200000;
        }
        if(cursor->At<int>(0x99c))cursor->At<float>(0x9a0)+=delta;
        cursor->At<float>(0x24)=cursor->At<float>(0x20);
        cursor->At<float>(0x20)+=delta;
        cursor=(Instance*)cursor->next;
    }while(cursor);
    return atEnd;
}
}

namespace ArmsAnimation {
Pose* Instance::Update(float delta) {
    float residual=0;
    Pose* pose=0;
    flags&=~0x4000000;
    if(delta==0) {
        if(graph) {
            flags|=0x800000;
            pose=Evaluate();flags&=~0x800000;
            if(pose) {
                asm("sqc2 vf0,0(%0)": :"r"(root.translation):"memory");
                asm("sqc2 vf0,0(%0)": :"r"(root.quaternion):"memory");
                Matrices(pose);
            }
        }
        flags&=~8;
        return pose;
    } else {
        Advance(&residual,delta);pose=Evaluate();
        if(pose) {CopyIfPresent((Pose*)&root,pose);Matrices(pose);}
    }
    return pose;
}
}

namespace Fragment348378 {

extern s32 func_003486E0(s32 arg0, s32 arg1, s32) __asm__("func_003486E0");
extern s32 func_00348738(s32 arg1, s32 arg2, s32) __asm__("func_00348738");
extern s32 D_003D2520 __asm__("D_003D2520");












void func_00348378(s32 *arg0, s32 arg1) __asm__("func_00348378") __attribute__((section(".text.func_00348378")));
void func_00348378(s32 *arg0, s32 arg1)
{
  s32 *new_var;
  s32 temp_2;
  ;
  if (arg1 == 1)
  {
    *arg0 = (*arg0) & (~0x200);
    return;
  }
  new_var = arg0;
  *new_var = (*arg0) | 0x200;
}
}

namespace Fragment3483A0 {

extern s32 func_003486E0(s32 arg0, s32 arg1, s32) __asm__("func_003486E0");
extern s32 func_00348738(s32 arg1, s32 arg2, s32) __asm__("func_00348738");
extern s32 D_003D2520 __asm__("D_003D2520");












void func_003483A0(void *arg0, s32 arg1) __asm__("func_003483A0") __attribute__((section(".text.func_003483A0")));
void func_003483A0(void *arg0, s32 arg1) {
    void *temp_2;

    temp_2 = (void*)((M2C_FIELD(arg0, s16 *, 8) * 0x10) + M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x1C));
    func_003486E0(arg1, M2C_FIELD(temp_2, s32 *, 0xC), M2C_FIELD(temp_2, s32 *, 0));
}
}

namespace Fragment3483E0 {

extern s32 func_003486E0(s32 arg0, s32 arg1, s32) __asm__("func_003486E0");
extern s32 func_00348738(s32 arg1, s32 arg2, s32) __asm__("func_00348738");
extern s32 D_003D2520 __asm__("D_003D2520");












s32 func_003483E0(void *arg0, s32 arg1) __asm__("func_003483E0") __attribute__((section(".text.func_003483E0")));
s32 func_003483E0(void *arg0, s32 arg1) {
    void *temp_2;
    void *temp_3;

    if (arg0 != NULL) {
        temp_3 = M2C_FIELD(arg0, void **, 4);
        if (temp_3 != NULL) {
            temp_2 = (void*)((M2C_FIELD(arg0, s16 *, 8) * 0x10) + M2C_FIELD(temp_3, s32 *, 0x1C));
            return func_003486E0(arg1, M2C_FIELD(temp_2, s32 *, 0xC), M2C_FIELD(temp_2, s32 *, 0));
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return -1;
    }
    return -1;
}
}

namespace Fragment348430 {

extern s32 func_003486E0(s32 arg0, s32 arg1, s32) __asm__("func_003486E0");
extern s32 func_00348738(s32 arg1, s32 arg2, s32) __asm__("func_00348738");
extern s32 D_003D2520 __asm__("D_003D2520");












void func_00348430(void *arg0, s32 arg1) __asm__("func_00348430") __attribute__((section(".text.func_00348430")));
void func_00348430(void *arg0, s32 arg1) {
    void *temp_2;

    temp_2 = (void*)((M2C_FIELD(arg0, s16 *, 8) * 0x10) + M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x1C));
    func_00348738(arg1, M2C_FIELD(temp_2, s32 *, 0xC), M2C_FIELD(temp_2, s32 *, 0));
}
}

namespace Fragment348470 {

extern s32 func_003486E0(s32 arg0, s32 arg1, s32) __asm__("func_003486E0");
extern s32 func_00348738(s32 arg1, s32 arg2, s32) __asm__("func_00348738");
extern s32 D_003D2520 __asm__("D_003D2520");












s32 func_00348470(void *arg0, s32 arg1) __asm__("func_00348470") __attribute__((section(".text.func_00348470")));
s32 func_00348470(void *arg0, s32 arg1) {
    void *temp_2;
    void *temp_3;

    if (arg0 != NULL) {
        temp_3 = M2C_FIELD(arg0, void **, 4);
        if (temp_3 != NULL) {
            temp_2 = (void*)((M2C_FIELD(arg0, s16 *, 8) * 0x10) + M2C_FIELD(temp_3, s32 *, 0x1C));
            return func_00348738(arg1, M2C_FIELD(temp_2, s32 *, 0xC), M2C_FIELD(temp_2, s32 *, 0));
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return -1;
    }
    return -1;
}
}

extern "C" {
int D_003D2520 __attribute__((section(".data.animation_graph_mode"), aligned(4))) = 1;
}

namespace Fragment3484C0 {

extern s32 func_003486E0(s32 arg0, s32 arg1, s32) __asm__("func_003486E0");
extern s32 func_00348738(s32 arg1, s32 arg2, s32) __asm__("func_00348738");
extern s32 D_003D2520 __asm__("D_003D2520");












void func_003484C0(s32 arg0) __asm__("func_003484C0") __attribute__((section(".text.func_003484C0")));
void func_003484C0(s32 arg0) {
    D_003D2520 = arg0;
}
}

namespace ArmsAnimation {
void __attribute__((section(".text.func_003484D0"))) Instance::Scale(float value) {float one=1.0f;rootScale=value;inverseRootScale=BkEeDividePipelineGuarded(one,value);}
}

namespace ArmsAnimation {
void __attribute__((section(".text.func_003484F0"))) Instance::ScaleMatrix(const BlackGame::Position4* input,BlackGame::Position4* output) {
    ScaleRow(inverseRootScale,input[0],output[0]);
    ScaleRow(inverseRootScale,input[1],output[1]);
    ScaleRow(inverseRootScale,input[2],output[2]);
    CopyRow(input[3],output[3]);
}
}

namespace Fragment348560 {

extern s32 * func_00345F28(s8 *, s32 *, s32 *) __asm__("func_00345F28");
extern s32 * func_00348470(s32 *, s8 *) __asm__("func_00348470");


void func_00348560(s32 *arg0, s8 *arg1, s8 *arg2) __asm__("func_00348560") __attribute__((section(".text.func_00348560")));
void func_00348560(s32 *arg0, s8 *arg1, s8 *arg2) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 *var_2;

    *(s32 *)(sp + 0) = -1;
    var_2 = func_00345F28(arg1, arg0, (s32*)sp);
    if (var_2 != NULL) {
        func_00348470(arg0, arg2);
    }

}
}

namespace Fragment3485B8 {



s32 func_003485B8(void) __asm__("func_003485B8") __attribute__((section(".text.func_003485B8")));
s32 func_003485B8(void) {
    return (s32) "UNKNOWN";
}
}

namespace Fragment3485C8 {

extern s32 func_00343278(...) __asm__("func_00343278");


void func_003485C8(void *arg0) __asm__("func_003485C8") __attribute__((section(".text.func_003485C8")));
void func_003485C8(void *arg0) {
    func_00343278(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 0x10));
}
}
