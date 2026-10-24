#include "include_asm.h"

#include "ps2/vu0_micro.hpp"
#include "animation/instance.h"

// Descriptive names; the original pose class identity is unverified.

extern "C" BkModAnimationPoseHeaderPS2 *func_00344178(
    BkModAnimationPoseHeaderPS2 *output, const BkModAnimationPoseHeaderPS2 *a,
    const BkModAnimationPoseHeaderPS2 *b, float weight)
{
    BlackPS2::AnimationMicro::Slerp(output->quaternion, a->quaternion, b->quaternion, weight);
    BlackPS2::AnimationMicro::InterpolateXYZ(output->translation, a->translation,
                                          b->translation, weight);
    return output;
}

#include "animation/instance_state.h"
// Scoped PS2 bind-record views; original class identities remain unverified.
struct Quaternion {float x,y,z,w;Quaternion(float a,float b,float c,float d):x(a),y(b),z(c),w(d) {}} __attribute__((aligned(16)));
struct Record {float ignored[4],quaternion[4],position[3];int parent;};
struct RecordList {int count;Record* records;};
struct RecordsCollection {unsigned char unknown[0x38];RecordList* lists;};
extern "C" int func_00348C08(AnimationInstanceView* instance,int index,AnimationMatrix* output) {
 if(index<0)return 0;
 RecordList* list=((RecordsCollection*)instance->collection)->lists+instance->skeletonIndex;
 if(index>=list->count)return 0;
 Record* record=list->records+index;
 Quaternion quaternion(record->quaternion[0],record->quaternion[1],record->quaternion[2],record->quaternion[3]);
 AnimationMatrix matrix;
 BlackPS2::AnimationMicro::QuaternionRotation(&matrix,&quaternion);
 asm volatile("sqc2 vf0,0(%0)" : : "r"(matrix.v+12) : "memory");
 matrix.v[12]=record->position[0];matrix.v[13]=record->position[1];matrix.v[14]=record->position[2];
 char* offset=(char*)(record->parent<<6);
 char* base=(char*)instance->selectedMatrices;
 AnimationMatrix* parent=(AnimationMatrix*)((int)offset+(int)base);
 BlackPS2::AnimationMicro::Multiply4x4(output,&matrix,parent);
 return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003441D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00344240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003443E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003452B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345500);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345508);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345510);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345C78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345CE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345E30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345E60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345E90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345ED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345F98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345FB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00345FD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003460E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003461D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003461E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003461F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00346230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00346510);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00346668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00346940);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00346CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00346F38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00346F48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00346F58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347238);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347280);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003474F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347600);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003477D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003477F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003478F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347948);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347A28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347A50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347A90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347B90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347C08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347C70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347CA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347D48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347D68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347E18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347E80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348070);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348288);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348378);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003483A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003483E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003484C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003484D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003484F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003485B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003485C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003485E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003486E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003487D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003487E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003487E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003487F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003489A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003489A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003489E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348A10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348A28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348A38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348A90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348B18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348B50);
