#include "mod/arms/instance.hpp"
namespace ArmsAnimation {
long Instance::SetGraph(int graph,int transition,int mode,float start) {
    int changed=0;
    if(graph!=-1) {
        if(!transition || !TryTransition(this,graph,mode,start)) BindGraph(this,graph,mode,start);
        flags &= ~0x200000;
        changed=1;
    }
    flags &= 0xedfffffe;
    return changed;
}
long Instance::SetGraphFlags(int graph,int transition,int flag800) {
    if(this) {
        if(flag800)flags|=0x800;else flags&=~0x800;
        return SetGraph(graph,transition,0,0.0f);
    }
    return 0;
}
long Instance::Activate(int graph) {
    if(this)return SwitchGraph(this,graph,0,0.0f);
    return 0;
}
void Instance::Matrices(Pose* pose) {
    AnimationSkeleton* skeleton=Skeleton(this);
    if(skeleton) {
        if(selectedMatrices==matrixBase)selectedMatrices=(char*)matrixBase+skeleton->boneCount*64;
        else selectedMatrices=matrixBase;
        BuildMatrices(this,pose);
    }
}
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
// Unmatched: Reverse-mask hoisting and floating-point schedule retain31 differing instructions.
#if 0
long Instance::Advance(float* residual,float delta) {
    int atEnd=0;
    Instance* cursor=this;
    do {
        int state=cursor->flags;
        if(delta<0)cursor->flags=state|0x40000;
        else {
            cursor->flags=state&~0x40000;
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
#endif
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
// Unmatched: Original retains two divide hazard slots absent from this compiler expression.
#if 0
void Instance::Scale(float value) {rootScale=value;inverseRootScale=1.0f/value;}
#endif
// Unmatched: VU row primitive reaches112bytes but scalar-load scheduling retains8 differing instructions.
#if 0
static inline void ScaleRow(const BlackGame::Position4& input,BlackGame::Position4& output,float scalar) {
    asm("lqc2 vf9,0(%1)\n\tmfc1 $8,%2\n\tqmtc2.ni $8,vf11\n\tvmulx.xyzw vf12,vf9,vf11x\n\tsqc2 vf12,0(%0)"
        : :"r"(&output),"r"(&input),"f"(scalar):"$8","memory");
}
static inline void CopyRow(BlackGame::Position4& output,const BlackGame::Position4& input) {
    asm("lq $8,0(%1)\n\tsq $8,0(%0)": :"r"(&output),"r"(&input):"$8","memory");
}
void Instance::ScaleMatrix(const BlackGame::Position4* input,BlackGame::Position4* output) {
    ScaleRow(input[0],output[0],inverseRootScale);
    ScaleRow(input[1],output[1],inverseRootScale);
    ScaleRow(input[2],output[2],inverseRootScale);
    CopyRow(output[3],input[3]);
}
#endif
}
