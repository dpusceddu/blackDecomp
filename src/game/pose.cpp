#include "include_asm.h"

#include "game/camera/local_pose.hpp"
namespace CampaignActor {
extern "C" BlackPS2::VU0::Matrix4 *func_001A68E0(ModCamera::LocalPoseAnimation*,int);

BlackPS2::VU0::Matrix4 ActorMotion::GetLocalMatrix() {
 ModCamera::LocalPoseAnimation *animation=(ModCamera::LocalPoseAnimation*)Field_0330();
 if(animation->definition->rootIndex>=0)return *func_001A68E0(animation,0);
 BlackPS2::VU0::Matrix4 result;
 result.basis[0]=Field_00D0();result.basis[1]=Field_00E0();result.basis[2]=Field_00F0();result.basis[3]=Field_0100();
 if(Field_00C4()==1)result.basis[3]=ModCamera::LowerY(result.basis[3],0x3e800000);
 return result;
}
}
