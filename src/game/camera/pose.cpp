#include "include_asm.h"

#include "game/camera/local_pose.hpp"
namespace ActorParts {
extern "C" Ps2Math::VU0::Matrix4 *func_001A68E0(Camera::LocalPoseAnimation*,int);

Ps2Math::VU0::Matrix4 ActorMotion::GetLocalMatrix() {
 Camera::LocalPoseAnimation *animation=(Camera::LocalPoseAnimation*)Field_0330();
 if(animation->definition->rootIndex>=0)return *func_001A68E0(animation,0);
 Ps2Math::VU0::Matrix4 result;
 result.basis[0]=Field_00D0();result.basis[1]=Field_00E0();result.basis[2]=Field_00F0();result.basis[3]=Field_0100();
 if(Field_00C4()==1)result.basis[3]=Camera::LowerY(result.basis[3],0x3e800000);
 return result;
}
}
