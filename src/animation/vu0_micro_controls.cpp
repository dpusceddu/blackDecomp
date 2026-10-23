#include "ps2/vu0_micro.hpp"
#include "mod/animation/instance.h"

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
